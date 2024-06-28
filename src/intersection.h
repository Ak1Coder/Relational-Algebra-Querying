#include "crossjoin.h"

/**
 * Class representing the relational algebra operator for intersection of two relations
 */
class Intersection : public Operator
{
public:
  /**
   * Interesection constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 0
   */
  Intersection();
  /**
   * Method realizes set intersection between two relations
   * @param[in] relations vector of 2 relations to be made intersection of
   * @param[in] expression not mandatory condition for an operator which should be left as the default value of ""
   * @throw runtime_error when there is a wrong number of relations in the vector or the expression is not left empty
   * @return a result of the intersection of the two relations in relations vector
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};