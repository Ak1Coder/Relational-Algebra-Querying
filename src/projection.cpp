#include "projection.h"

Projection::Projection() : Operator(1, 1) {}

Relation Projection::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  if (relations.size() < getRelationCount())
    throw std::runtime_error("ERROR: Wrong number of arguments.");

  Relation result;
  std::vector<std::string> columns = evaluateExpression(expression);
  std::vector<size_t> orderOfColumns;

  for (size_t i = 0; i < columns.size(); ++i)
    if (relations.at(0).getAttributesOrder(columns.at(i)) != -1)
      orderOfColumns.push_back(relations.at(0).getAttributesOrder(columns.at(i)));
    else
      throw std::runtime_error("ERROR: Unknown attribute \'" + columns.at(i) + "\'.");

  for (size_t i = 0; i < columns.size(); ++i)
    result.addAttribute(columns.at(i));

  const std::set<Tuple> &relation = relations.at(0).getRefToRelation();

  for (auto it = relation.begin(); it != relation.end(); ++it)
  {
    Tuple tmp;
    for (size_t i = 0; i < orderOfColumns.size(); ++i)
    {
      tmp.add((*it)[orderOfColumns[i]]);
    }
    result.addTuple(tmp);
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}