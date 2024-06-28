#include "intersection.h"

Intersection::Intersection() : Operator(2, 0) {}

Relation Intersection::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  if (expression.size())
    throw std::runtime_error("ERROR: Expression not expected.");

  if (relations.size() < getRelationCount())
    throw std::runtime_error("ERROR: Wrong number of arguments.");

  Relation result;

  if (relations.at(0).getAttributesCount() != relations.at(1).getAttributesCount())
  {
    return result;
  }

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    if (relations.at(0).getAttribute(i) != relations.at(1).getAttribute(i))
      return result;

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    result.addAttribute(relations.at(0).getAttribute(i));

  const std::set<Tuple> &firstRelation = relations.at(0).getRefToRelation();
  const std::set<Tuple> &secondRelation = relations.at(1).getRefToRelation();

  for (auto itFirst = firstRelation.begin(); itFirst != firstRelation.end(); ++itFirst)
    if (secondRelation.count(*itFirst))
      result.addTuple(*itFirst);

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}