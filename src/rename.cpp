#include "rename.h"

Rename::Rename() : Operator(1, 1) {}

Relation Rename::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  if (relations.size() < getRelationCount())
    throw std::runtime_error("ERROR: Wrong number of arguments.");

  Relation result(relations.at(0));
  std::vector<std::string> names = evaluateExpression(expression);
  int index = -1;

  for (size_t i = 0; i < names.size(); i += 2)
  {
    index = result.getAttributesOrder(names.at(i));

    if (index == -1)
      continue;

    if (i + 1 < names.size())
      result.setAttribute(index, names.at(i + 1));
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}
