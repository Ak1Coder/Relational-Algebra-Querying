#include "njoin.h"

NJoin::NJoin() : Operator(2, 0) {}

Relation NJoin::getResult(const std::vector<Relation> &relations, const std::string &expression) const
{
  if (expression.size())
    throw std::runtime_error("ERROR: Expression not expected.");

  if (relations.size() < getRelationCount())
    throw std::runtime_error("ERROR: Wrong number of arguments.");

  const std::set<Tuple> &firstRelation = relations.at(0).getRefToRelation();
  const std::set<Tuple> &secondRelation = relations.at(1).getRefToRelation();

  std::vector<std::pair<size_t, size_t>> matchedAttributes;

  Relation result;

  for (size_t i = 0; i < relations.at(0).getAttributesCount(); ++i)
    result.addAttribute(relations.at(0).getAttribute(i));

  bool wasMatched = false;

  for (size_t i = 0; i < relations.at(1).getAttributesCount(); ++i)
  {
    wasMatched = false;

    for (size_t j = 0; j < relations.at(0).getAttributesCount(); ++j)
      if (result.getAttribute(j) == relations.at(1).getAttribute(i))
      {
        matchedAttributes.push_back({j, i});
        wasMatched = true;
        break;
      }

    if (!wasMatched)
      result.addAttribute(relations.at(1).getAttribute(i));
  }

  for (auto itFirst = firstRelation.begin(); itFirst != firstRelation.end(); ++itFirst)
  {
    for (auto itSecond = secondRelation.begin(); itSecond != secondRelation.end(); ++itSecond)
    {
      wasMatched = true;

      for (size_t i = 0; i < matchedAttributes.size(); ++i)
        if ((*itFirst)[matchedAttributes[i].first] != (*itSecond)[matchedAttributes[i].second])
          wasMatched = false;

      if (wasMatched)
      {
        Tuple tmp;

        for (size_t i = 0; i < itSecond->size(); ++i)
        {
          wasMatched = false;
          for (size_t j = 0; j < matchedAttributes.size(); ++j)
            if (i == matchedAttributes[j].second)
              wasMatched = true;

          if (!wasMatched)
            tmp.add((*itSecond)[i]);
        }

        if (tmp.size())
          result.addTuple(*itFirst + tmp);
        else
          result.addTuple(*itFirst);
      }
    }
  }

  if (result.getTuplesCount() == 0)
    return Relation();

  return result;
}