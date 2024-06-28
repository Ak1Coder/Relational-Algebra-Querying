#include "projection.h"

/**
 * Class Union represents set union operation between two relations
 */

class Union : public Operator
{
public:
  /**
   * Union constructror calling the base class constructor with the relation parameters being 2 and expression parameters being 0
   */
  Union();
  /**
   * Method realizes union between two relations
   * @param[in] relations vector of 2 relations where the we get union of those two
   * @param[in] expression not mandatory condition for set operator which should be left as the default value of ""
   * @throw runtime_error if the expression is not empty
   * @return the union of the first relation and the second relation
   */
  virtual Relation getResult(const std::vector<Relation> &relations, const std::string &expression) const override;
};