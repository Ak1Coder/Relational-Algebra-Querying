#include "crossjoin.h"

CrossJoin::CrossJoin() : Operator(2, 0) {}

Relation CrossJoin::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  if (expression.size())
    throw std::runtime_error("ERROR: Expression not expected.");

  if (relations.size() < getRelationCount())
    throw std::runtime_error("ERROR: Wrong number of arguments.");

  Relation result;

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    result.addAttribute(relations.at(0).getAttribute(i));

  std::string attributeToInsert;

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

  const std::set<Tuple> &firstRelation = relations.at(0).getRefToRelation();
  const std::set<Tuple> &secondRelation = relations.at(1).getRefToRelation();

  for (auto itFirst = firstRelation.begin(); itFirst != firstRelation.end(); ++itFirst)
  {
    for (auto itSecond = secondRelation.begin(); itSecond != secondRelation.end(); ++itSecond)
    {
      result.addTuple(*itFirst + *itSecond);
    }
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}