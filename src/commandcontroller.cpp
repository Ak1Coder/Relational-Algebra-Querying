#include "commandcontroller.h"

CommandController::CommandController() = default;

std::vector<std::string> CommandController::evaluateCommand(const std::string &command) const
{
  std::vector<std::string> result = turnIntoVector(command);

  if (!isValid(command))
  {
    throw std::runtime_error("ERROR: Invalid command.");
  }

  return result;
}

std::vector<std::string> CommandController::turnIntoVector(const std::string &command) const
{
  std::vector<std::string> result;
  std::string tmp = "";
  bool isInsideMarks = false;
  bool lastCharWasSpace = false;

  for (auto it = command.begin(); it != command.end(); ++it)
  {
    if (isspace(*it))
    {
      if (tmp.size() && !isInsideMarks)
      {
        result.push_back(tmp);
        tmp = "";
      }
      else if (!lastCharWasSpace && isInsideMarks)
      {
        tmp += " ";
      }
      lastCharWasSpace = true;
      continue;
    }
    else if (*it == '=')
    {
      if (isInsideMarks)
      {
        tmp += "=";
      }
      else
      {
        if (tmp.size())
        {
          result.push_back(tmp);
          tmp = "";
        }
        result.push_back("=");
      }
    }
    else if (*it == '\"')
    {
      if (isInsideMarks)
      {
        tmp += '\"';
        result.push_back(tmp);
        tmp = "";
      }
      else
      {
        if (tmp.size())
          result.push_back(tmp);
        tmp = "\"";
      }
      isInsideMarks = !isInsideMarks;
    }
    else
    {
      tmp += *it;
    }
    lastCharWasSpace = false;
  }

  if (tmp.size())
    result.push_back(tmp);

  return result;
}

bool CommandController::isValid(const std::string &command) const
{
  std::vector<std::string> slicedExpression = turnIntoVector(command);

  for (size_t i = 0; i < slicedExpression.size(); ++i)
  {
    if (slicedExpression[i] == "=" && (i != 1 || slicedExpression.size() <= 2))
    {
      return false;
    }
    else if (slicedExpression[i].front() == '\"' && slicedExpression[i].back() != '\"')
    {
      return false;
    }
    else if (slicedExpression[i].front() != '\"' && slicedExpression[i].back() == '\"')
    {
      return false;
    }
  }

  std::string tmp = "";
  size_t relationArguments = 0;
  size_t expressionArguments = 0;

  for (int i = slicedExpression.size() - 1; i >= 0; --i)
  {
    tmp = slicedExpression[i];

    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c)
                   { return std::toupper(c); });

    if (m_Operators.count(tmp))
    {
      if (m_Operators.at(tmp).second > expressionArguments)
      {
        return false;
      }
      else
      {
        expressionArguments -= m_Operators.at(tmp).second;
      }

      if (m_Operators.at(tmp).first > relationArguments)
      {
        return false;
      }
      else
      {
        relationArguments -= m_Operators.at(tmp).first;
        if (i != 0)
          relationArguments++;
      }
    }
    else if (tmp.size() >= 2 && tmp.front() == '\"' && tmp.back() == '\"')
    {
      expressionArguments++;
    }
    else if (tmp == "=")
    {
      relationArguments--;

      tmp = slicedExpression.at(0);

      std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c)
                     { return std::toupper(c); });

      if (m_Operators.count(tmp))
        return false;
      break;
    }
    else
    {
      relationArguments++;
    }
  }

  if (expressionArguments != 0 || relationArguments != 0)
    return false;

  return true;
}
