#include "selection.h"

/**
 * Class representing the Projection operation which means picking columns from relation
 */
class Projection : public Operator
{
public:
  /**
   * Projection constructror calling the base class constructor with the relation parameters being 1 and expression parameters being 1
   */
  Projection();
  /**
   * Method realizes projection on one relation based on the expression
   * @param[in] relations vector of 1 relation to be projected based on the expression
   * @param[in] expression expression containing the columns to be projected which can be repeated
   * @throw runtime_error when there is a wrong number of relations in the vector
   * @return a result of the projection of the relation in relations vector
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};