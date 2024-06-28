#include "join.h"

Join::Join() : Operator(2, 1) {}

Relation Join::getResult(const std::vector<Relation> &relations, const std::string &expression) const
{
  std::vector<std::string> evaluatedExpression = evaluateExpression(expression);

  if (evaluatedExpression.size() % 3 != 0)
    throw std::runtime_error("ERROR: Expression not expected.");

  std::vector<std::pair<size_t, size_t>> matchedAttributes;

  for (size_t i = 0; i < evaluatedExpression.size(); ++i)
    if (i % 3 == 0)
    {
      if (relations.at(0).getAttributesOrder(evaluatedExpression.at(i)) == -1)
        throw std::runtime_error("ERROR: Expression not expected.");
      matchedAttributes.push_back({relations.at(0).getAttributesOrder(evaluatedExpression.at(i)), -1});
    }
    else if (i % 3 == 2)
    {
      if (relations.at(1).getAttributesOrder(evaluatedExpression.at(i)) == -1)
        throw std::runtime_error("ERROR: Expression not expected.");
      matchedAttributes.back().second = relations.at(1).getAttributesOrder(evaluatedExpression.at(i));
    }

  Relation result;
  const std::set<Tuple> &firstRelation = relations.at(0).getRefToRelation();
  const std::set<Tuple> &secondRelation = relations.at(1).getRefToRelation();

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    result.addAttribute(relations.at(0).getAttribute(i));

  std::string attributeToInsert = "";

  for (size_t i = 0; i < relations.at(1).getAttributesCount(); ++i)
  {
    attributeToInsert = relations.at(1).getAttribute(i);
    while (true)
    {
      if (relations.at(0).getAttributesOrder(attributeToInsert) == -1 && result.getAttributesOrder(attributeToInsert) == -1)
      {
        result.addAttribute(attributeToInsert);
        break;
      }
      attributeToInsert += m_Postfix;
    }
  }

  bool conditionFulfilled = true;

  for (auto itFirst = firstRelation.begin(); itFirst != firstRelation.end(); ++itFirst)
  {
    for (auto itSecond = secondRelation.begin(); itSecond != secondRelation.end(); ++itSecond)
    {
      conditionFulfilled = true;

      for (size_t i = 0; i < matchedAttributes.size(); ++i)
        if ((*itFirst)[matchedAttributes[i].first] != (*itSecond)[matchedAttributes[i].second])
          conditionFulfilled = false;

      if (conditionFulfilled)
        result.addTuple(*itFirst + *itSecond);
    }
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}
