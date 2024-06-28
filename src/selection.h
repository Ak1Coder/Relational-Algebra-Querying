#include "rename.h"

/**
 * Class Selection represents an operation of picking only the rows or tuples satisfying some condition
 */
class Selection : public Operator
{
public:
  /**
   * Selection constructror calling the base class constructor with the relation parameters being 1 and expression parameters being 1
   */
  Selection();
  /**
   * Method realizes selection of only the rows satisfying the condition
   * @param[in] relations vector of 1 relation to have its rows selected from it
   * @param[in] expression a condition with only equalities or strict inequalities (lexicographic order) connected by ANDs if more than one and a whitespace used as a delimiter unless '' are used for attributes or strings containing whitespaces
   * @throw runtime_error if the condition is invalid
   * @return a relation with only the tuples satisfying the conditions
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;

private:
  /**
   * Method splits the condition into a vector and also treats anything inside '' as one word otherwise it uses whitespace as a delimiter
   * @param[in] expressionToEvaluate
   * @throw runtime_error if ' doesnt have a its ending ' in the condition
   * @return parsed condition in a vector
   */
  std::vector<std::string> evaluateCondition(const std::string &expressionToEvaluate) const;
};