#include "selection.h"

Selection::Selection() : Operator(1, 1) {}

Relation Selection::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  std::vector<std::string> condition = evaluateCondition(expression);

  if (condition.size() % 3 != 0 || !condition.size())
    throw std::runtime_error("ERROR: Condition has wrong number of arguments.");
  for (size_t i = 0; i < condition.size(); ++i)
  {
    if (i % 3 == 1 && condition.at(i) != "=" && condition.at(i) != ">" && condition.at(i) != "<")
      throw std::runtime_error("ERROR: Condition is missing \'=\'.");
    else if (i % 3 == 0 && relations.at(0).getAttributesOrder(condition.at(i)) == -1)
      throw std::runtime_error("ERROR: Unknown attribute \'" + condition.at(i) + "\'.");
  }

  Relation result;
  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    result.addAttribute(relations.at(0).getAttribute(i));

  const std::set<Tuple> &relation = relations.at(0).getRefToRelation();
  int index = -1;
  bool isConditionFulfilled = true;

  for (auto it = relation.begin(); it != relation.end(); ++it)
  {
    isConditionFulfilled = true;
    for (size_t i = 0; i < condition.size(); i += 3)
    {
      std::string sign = condition.at(i + 1);
      index = result.getAttributesOrder(condition.at(i));

      if (index == -1)
      {
        isConditionFulfilled = false;
        continue;
      }

      if (i + 2 < condition.size())
      {
        if (sign == "=" && (*it)[index] != condition.at(i + 2))
          isConditionFulfilled = false;

        if (sign == ">" && (*it)[index] <= condition.at(i + 2))
          isConditionFulfilled = false;

        if (sign == "<" && (*it)[index] >= condition.at(i + 2))
          isConditionFulfilled = false;
      }
      else
      {
        isConditionFulfilled = false;
      }
    }
    if (isConditionFulfilled)
      result.addTuple(*it);
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}

std::vector<std::string> Selection::evaluateCondition(const std::string &expressionToEvaluate) const
{
  bool insideWord = false;
  std::vector<std::string> result;
  std::string expression = expressionToEvaluate;
  std::string tmp = "";

  for (auto it = expression.begin(); it != expression.end(); ++it)
  {
    if ((*it == '=' || *it == '<' || *it == '>') && !insideWord)
    {
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
      std::string signToInsert = "=";

      if (*it == '=')
        signToInsert = "=";
      else if (*it == '>')
        signToInsert = ">";
      else if (*it == '<')
        signToInsert = "<";

      result.push_back(signToInsert);
    }
    else if (isspace(*it) && !insideWord)
    {
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
    }
    else if (*it == '\'')
    {
      insideWord = !insideWord;
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

  if (insideWord)
    throw std::runtime_error("ERROR: Selection condition is not valid.");

  return result;
}