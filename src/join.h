#include "njoin.h"

class Join : public Operator
{
public:
  /**
   * Join constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 1
   */
  Join();
  /**
   * Method realizes set regular Join On between two relations
   * @param[in] relations vector of 2 relations to be joined based on the condition
   * @param[in] expression condition of joining in the form of any number of equalities between attributes implicitly with AND between them
   * @throw runtime_error if the condition is not possible or just invalid like non existent attributes
   * @return a result of the Join On operation of the two relations in relations vector
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;

private:
  /**
   * @brief a postfix added to the end of attribute when a duplicity between attrbutes occurs
   */
  const std::string m_Postfix = "_0";
};