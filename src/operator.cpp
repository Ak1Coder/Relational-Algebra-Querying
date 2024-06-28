#include "operator.h"

Operator::Operator(size_t i, size_t j) : m_RelationCount(i), m_ExpressionCount(j) {}

Operator::~Operator() = default;

size_t Operator::getRelationCount() const
{
  return m_RelationCount;
}

size_t Operator::getExpressionCount() const
{
  return m_ExpressionCount;
}

std::vector<std::string> Operator::evaluateExpression(const std::string &expressionToEvaluate) const
{
  bool insideWord = false;
  std::vector<std::string> result;
  std::string expression = expressionToEvaluate;
  std::string tmp = "";

  for (auto it = expression.begin(); it != expression.end(); ++it)
  {
    if (*it == '=' && !insideWord)
    {
      if (tmp.size())
        result.push_back(tmp);
      tmp = "";
      result.push_back("=");
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

  return result;
}