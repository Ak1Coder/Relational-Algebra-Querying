#include "setdifference.h"

/**
 * Class NJoin represents a natural join operation between two relations
 */
class NJoin : public Operator
{
public:
  /**
   * NJoin constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 0
   */
  NJoin();
  /**
   * Method realizes natural join between two relations
   * @param[in] relations vector of 2 relations to be made natural join of
   * @param[in] expression not mandatory condition for set operator which should be left as the default value of ""
   * @throw runtime_error when there is a wrong number of relations in the vector or the expression is not left empty
   * @return a result of the natural join of the two relations in relations vector
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};
