#include "setdifference.h"

SetDifference::SetDifference() : Operator(2, 0) {}

Relation SetDifference::getResult(const std::vector<Relation> &relations, const std::string &expression) const
{
  if (expression.size())
    throw std::runtime_error("ERROR: Expression not expected.");

  Relation result(relations.at(0));
  result -= relations.at(1);

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}