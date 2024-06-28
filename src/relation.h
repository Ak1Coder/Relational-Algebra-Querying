#include <vector>
#include <set>
#include <string>
#include <iomanip>
#include <memory>
#include "tuple.h"

/**
 * Relation class represents a relation or a table where all of the data is stored in the memory of a program
 */
class Relation
{
public:
  /**
   * Relation default constructor
   */
  Relation();
  /**
   * Relation copy constructor
   * @param[in] relation a relation that is being copied
   */
  Relation(const Relation &relation);
  /**
   * Overload of the operator =
   * @param[in] relation a relation to get assigned or copied
   * @return reference to relation so the method can be chained
   */
  Relation &operator=(const Relation &relation);
  /**
   * Overload of the operator += takes all the tuples from relation and adds it to this one if they are compatible
   * @param[in] relation relation whose tuples will be added if compatible
   * @return reference to relation so the method can be chained
   */
  Relation &operator+=(const Relation &relation);
  /**
   * Overload of the operator -= takes all the tuples from relation and erases them from this relation if they are present
   * @param[in] relation relation whose tuples will be erased from this instance of relation
   * @return reference to relation so the method can be chained
   */
  Relation &operator-=(const Relation &relation);
  /**
   * Method adds a new attribute to the end of all the other attributes
   * @param[in] newAttribute the attribute to be added at the end of all the other attributes
   * @return reference to the relation so that the method can be chained
   */
  Relation &addAttribute(const std::string &newAttribute);
  /**
   * Methods add a tuple (row) to the relation
   * @param[in] newTuple the tuple to be added if compatible
   * @throw runtime_error if adding fails
   * @return reference to the relation so that the method can be chained
   */
  Relation &addTuple(const Tuple &newTuple);
  std::shared_ptr<Relation> clone() const;
  /**
   * Getter for an attribute on a certain index
   * @param[in] idx is the index of the attribute to get
   * @return the attribute at index equal to idx
   */
  std::string getAttribute(size_t idx) const;
  /**
   * Setter for an attribute on a certain index
   * @param[in] idx is the index to be set
   * @param[in] newAttribute is the attribute to set it to
   */
  void setAttribute(size_t idx, const std::string &newAttribute);
  /**
   * Getter for number of attributes
   * @return number of attributes
   */
  size_t getAttributesCount() const;
  /**
   * Method gets the the order of an attribute or -1 if not present
   * @param[in] attribute to get his order in the attribute vector
   * @return the index of the attribute or -1 if not found
   */
  int getAttributesOrder(const std::string &attribute) const;
  /**
   * Getter for a reference to the set of all the tuples relation contains
   * @return reference to the set of all the tuples relations contains
   */
  const std::set<Tuple> &getRefToRelation() const;
  /**
   * Simple getter for the number of tuples relation contains
   * @return number of tuples (rows)
   */
  size_t getTuplesCount() const;
  /**
   * Prints out the relation as a table
   */
  void print(unsigned int spacesBetweenColumns = 3) const;
  /**
   * Method that exports the relation to a csv file
   * @param[in] fileName is a name of file the relation will be exported as
   * @throws runtime_error if the fileName is not of a csv file
   */
  void exportToFile(const std::string &fileName) const;

private:
  /**
   * @brief the attributes of the relations
   */
  std::vector<std::string> m_Attributes;
  /**
   * @brief tuples of relations (or rows of a table)
   */
  std::set<Tuple> m_Relation;
};