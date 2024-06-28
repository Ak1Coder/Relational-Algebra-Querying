#include "union.h"

Union::Union() : Operator(2, 0) {}

Relation Union::getResult(const std::vector<Relation> &relations, const std::string &expression = "") const
{
  if (expression.size())
    throw std::runtime_error("ERROR: Expression not expected.");

  if (relations.at(0).getAttributesCount() != relations.at(1).getAttributesCount())
  {
    Relation empty;
    return empty;
  }

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    if (relations.at(0).getAttribute(i) != relations.at(1).getAttribute(i))
    {
      Relation empty;
      return empty;
    }

  Relation result(relations.at(0));
  result += relations.at(1);

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}