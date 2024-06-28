#include "union.h"

/**
 * Class CrossJoin represents the operator for cartesian product in relational algebra
 */
class CrossJoin : public Operator
{
public:
  /**
   * CrossJoin constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 0
   */
  CrossJoin();
  /**
   * Method realizes cartesian product between two relations
   * @param[in] relations vector of 2 relations to be made cartesian product of
   * @param[in] expression not mandatory condition for an operator which should be left as the default value of ""
   * @throw runtime_error when there is a wrong number of relations in the vector or the expression is not empty
   * @return a result of the cartesian product of the two relations in relations vector
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;

private:
  /**
   * @brief a postfix added to the end of attribute when a duplicity between attrbutes occurs
   */
  const std::string m_Postfix = "_0";
};