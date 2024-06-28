#include "intersection.h"

/**
 * Class SetDifference represents set difference operation between two relations
 */
class SetDifference : public Operator
{
public:
  /**
   * SetDifference constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 0
   */
  SetDifference();
  /**
   * Method realize set differenece between two relations
   * @param[in] relations vector of 2 relations where the we get the first one minus the second one
   * @param[in] expression not mandatory condition for set operator which should be left as the default value of ""
   * @throw runtime_error if the expression is not empty
   * @return the first relation minus the second relation
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};
