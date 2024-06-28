#include "translator.h"
#include <stack>

Translator::Translator(const std::string &alias, size_t count)
    : m_Alias(alias), m_Count(count)
{
}

std::string Translator::translateToSQL(std::vector<std::string> query)
{
  m_Count = 0;
  std::string result;
  std::stack<std::string> expressionArgs;
  std::stack<std::string> relationArgs;
  std::string workingWord, workingWordUpper;

  for (int i = query.size() - 1; i >= 0; i--)
  {
    workingWord = query.at(i);
    workingWordUpper = makeUpper(workingWord);
    if (m_Keywords.count(workingWordUpper))
    {
      if (workingWordUpper == "PROJECTION")
      {
        std::string tmp = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(projection(split(expressionArgs.top()), tmp));
        expressionArgs.pop();
      }
      else if (workingWordUpper == "SELECTION")
      {
        std::string tmp = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(selection(split(expressionArgs.top()), tmp));
        expressionArgs.pop();
      }
      else if (workingWordUpper == "RENAME")
      {
        std::string tmp = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(rename(split(expressionArgs.top()), tmp));
        expressionArgs.pop();
      }
      else if (workingWordUpper == "UNION")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(unionSQL(tmp1, tmp2));
      }
      else if (workingWordUpper == "INTERSECT")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(intersect(tmp1, tmp2));
      }
      else if (workingWordUpper == "CROSS")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(cross(tmp1, tmp2));
      }
      else if (workingWordUpper == "NJOIN")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(njoin(tmp1, tmp2));
      }
      else if (workingWordUpper == "DIFF")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(diff(tmp1, tmp2));
      }
      else if (workingWordUpper == "JOIN")
      {
        std::string tmp1 = relationArgs.top();
        relationArgs.pop();
        std::string tmp2 = relationArgs.top();
        relationArgs.pop();
        relationArgs.push(join(split(expressionArgs.top()), tmp1, tmp2));
        expressionArgs.pop();
      }
    }
    else
    {
      if (workingWord.size() >= 2 && workingWord.front() == '\"' && workingWord.back() == '\"')
      {
        expressionArgs.push(workingWord.substr(1, workingWord.length() - 2));
      }
      else
      {
        relationArgs.push(workingWord);
      }
    }
  }
  result = relationArgs.top();

  if (result.size() < 4)
    result = select(relationArgs.top());
  result = result.substr(2, result.length() - 3);
  return result;
}

std::string Translator::makeUpper(std::string toUpper) const
{
  std::transform(toUpper.begin(), toUpper.end(), toUpper.begin(), [](unsigned char c)
                 { return std::toupper(c); });
  return toUpper;
}

std::vector<std::string> Translator::split(std::string stringToSplit) const
{
  bool inside = false;
  std::vector<std::string> result;
  std::string tmp = "";
  for (auto it = stringToSplit.begin(); it != stringToSplit.end(); ++it)
  {
    if (isspace(*it) && !inside)
    {
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
    }
    else if (*it == '=')
    {
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
      result.push_back("=");
    }
    else if (*it == '\'')
    {
      inside = !inside;
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
    }
    else
    {
      tmp += *it;
    }
  }
  if (tmp.size())
    result.push_back(tmp);

  if (inside)
    throw std::runtime_error("ERROR: The condition is invalid.");

  return result;
}

bool Translator::hasSpaces(const std::string &stringToCheck) const
{
  for (auto it = stringToCheck.begin(); it != stringToCheck.end(); it++)
    if (std::isspace(*it))
      return true;
  return false;
}

std::string Translator::select(const std::string &relation) const
{
  return "( SELECT DISTINCT * FROM " + relation + " )";
}

std::string Translator::projection(const std::vector<std::string> &columns, const std::string &relation)
{
  std::string result = "( SELECT DISTINCT ";
  for (size_t i = 0; i < columns.size(); ++i)
  {
    result += columns.at(i);
    m_Attributes.insert(columns.at(i));
    if (i + 1 < columns.size())
      result += ", ";
    else
      result += " ";
  }
  result += "FROM " + (hasSpaces(relation) ? (relation + " " + m_Alias + std::to_string(m_Count++)) : relation) + " )";
  return result;
}

std::string Translator::selection(const std::vector<std::string> &condition, const std::string &relation)
{
  if (condition.size() % 3 != 0)
    throw std::runtime_error("ERROR: Condition is invalid.");

  for (size_t i = 0; i < condition.size(); ++i)
    if (i != 0 && i % 3 == 1 && condition.at(i) != "=")
      throw std::runtime_error("ERROR: Condition is invalid.");
    else if (i != 0 && i % 3 != 1 && condition.at(i) == "=")
      throw std::runtime_error("ERROR: Condition is invalid.");

  std::string result = "( SELECT DISTINCT * FROM " + (hasSpaces(relation) ? (relation + " " + m_Alias + std::to_string(m_Count++)) : relation) + " WHERE ";
  for (size_t i = 0; i < condition.size(); ++i)
  {
    if (i != 0 && i % 3 == 0)
      result += "AND ";

    if (i != 0 && condition.at(i - 1) == "=")
      result += "\'" + condition.at(i) + "\' ";
    else
      result += condition.at(i) + " ";
  }
  result += ")";
  return result;
}

std::string Translator::rename(const std::vector<std::string> &columns, const std::string &relation)
{
  std::string result = "( SELECT DISTINCT ";
  std::set<std::string> alreadySelected;

  for (size_t i = 0; i < columns.size(); i++)
  {
    if (i % 2 == 0)
      result += columns.at(i);
    if (i % 2 == 1)
    {
      result += " AS " + columns.at(i);

      m_Attributes.erase(columns.at(i - 1));
      m_Attributes.insert(columns.at(i));
      alreadySelected.insert(columns.at(i));

      if (i + 1 < columns.size())
        result += ", ";
    }
  }
  std::vector<std::string> leftToSelect;
  std::set_difference(m_Attributes.begin(), m_Attributes.end(),
                      alreadySelected.begin(), alreadySelected.end(),
                      std::back_inserter(leftToSelect),
                      [](const std::string &a, const std::string &b)
                      { return a != b; });

  if (leftToSelect.size())
    result += ", ";

  for (size_t i = 0; i < leftToSelect.size(); ++i)
  {
    result += leftToSelect.at(i);
    if (i + 1 < leftToSelect.size())
      result += ", ";
  }

  result += " FROM " + (hasSpaces(relation) ? (relation + " " + m_Alias + std::to_string(m_Count++)) : relation) + " )";
  return result;
}

std::string Translator::unionSQL(const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM ";
  result += hasSpaces(firstRelation) ? firstRelation + " " + m_Alias + std::to_string(m_Count++) : firstRelation;
  result += " UNION ";
  result += hasSpaces(secondRelation) ? secondRelation : select(secondRelation);
  result += " )";
  return result;
}

std::string Translator::intersect(const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM ";
  result += hasSpaces(firstRelation) ? firstRelation + " " + m_Alias + std::to_string(m_Count++) : firstRelation;
  result += " INTERSECT ";
  result += hasSpaces(secondRelation) ? secondRelation : select(secondRelation);
  result += " )";
  return result;
}

std::string Translator::cross(const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM ";
  result += hasSpaces(firstRelation) ? firstRelation + " " + m_Alias + std::to_string(m_Count++) : firstRelation;
  result += " CROSS JOIN ";
  result += hasSpaces(secondRelation) ? secondRelation : select(secondRelation);
  result += " )";
  return result;
}

std::string Translator::njoin(const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM ";
  result += hasSpaces(firstRelation) ? firstRelation + " " + m_Alias + std::to_string(m_Count++) : firstRelation;
  result += " NATURAL JOIN ";
  result += hasSpaces(secondRelation) ? secondRelation : select(secondRelation);
  result += " )";
  return result;
}

std::string Translator::diff(const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM ";
  result += hasSpaces(firstRelation) ? firstRelation + " " + m_Alias + std::to_string(m_Count++) : firstRelation;
  result += " EXCEPT ";
  result += hasSpaces(secondRelation) ? secondRelation : select(secondRelation);
  result += " )";
  return result;
}

std::string Translator::join(const std::vector<std::string> &condition, const std::string &firstRelation, const std::string &secondRelation)
{
  std::string result = "( SELECT DISTINCT * FROM " + firstRelation + " JOIN " + secondRelation + " ON (";
  for (size_t i = 0; i < condition.size(); i++)
  {
    if (i != 0 && i % 3 == 0)
      result += "AND ";
    result += condition.at(i);
  }
  result += ") )";
  return result;
}