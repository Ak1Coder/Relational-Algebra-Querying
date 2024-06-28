#include "operator.h"

/**
 * Class Rename represents the operation of renaming an attribute in relational algebra
 */
class Rename : public Operator
{
public:
  /**
   * Rename constructror calling the base class constructor with the relation parameters being 1 and expression parameters being 1
   */
  Rename();
  /**
   * Method realizes renaming one or more attributes of one relation based on the expression
   * @param[in] relations vector of 1 relation to have attributes renamed based on the expression
   * @param[in] expression expression containing even number of attributes where always the odd attribute is existing and the one after is the new name
   * @throw runtime_error when there is a wrong number of relations in the vector
   * @return a relation after having the said attributes renamed
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};