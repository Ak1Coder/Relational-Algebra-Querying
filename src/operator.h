#include <memory>
#include "csvfile.h"

/**
 * @class Operator is a base class for all the operators used in relational algebra
 */
class Operator
{
public:
  /**
   * Operator constructor takes in two numbers the first one representing the number of relations this operator needs and the second one number of expression like conditions
   */
  Operator(size_t i, size_t j);
  /**
   * Pure abstract class that is used to realize the actual operation over the relations with a particular not always mandatory expression
   * @param[in] relations vector of the relations that are needed for the operator
   * @param[in] expression not always mandatory condition or expression determining how to operation runs
   * @return a result of the operation
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression = "") const = 0;
  /**
   * Virtual default destructor
   */
  virtual ~Operator();
  /**
   * Getter for the number of relations a specific operator needs
   * @return number of relations needed
   */
  size_t getRelationCount() const;
  /**
   * Getter for the number of expressions a specific operator needs
   * @return number of expressions needed
   */
  size_t getExpressionCount() const;

protected:
  /**
   * @brief number of relations needed to actualize this operation
   */
  size_t m_RelationCount;
  /**
   * @brief number of expressions needed to actualize this operation
   */
  size_t m_ExpressionCount;
  /**
   * Method that splits an expression into vector by whitespaces
   * @param[in] expressionToEvaluate the expression to be split
   * @returns vector with single words of the expression as elements
   */
  std::vector<std::string> evaluateExpression(const std::string &expressionToEvaluate) const;
};