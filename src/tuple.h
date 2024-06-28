#include <vector>
#include <string>

class Tuple
{
public:
  /**
   * Tuple default constructor
   */
  Tuple();
  /**
   * Tuple constructor from a vector of strings
   * @param[in] v the vector to be copied into the tuple
   */
  Tuple(const std::vector<std::string> v);
  /**
   * Tuple copy constructor
   * @param[in] tuple to be copied
   */
  Tuple(const Tuple &tuple);
  /**
   * Method adds another string to the end of tuple
   * @param[in] element string to be added at the end of the tuple
   * @return reference to the tuple so the method can be chained
   */
  Tuple &add(const std::string &element);
  /**
   * Overloaded operator [] for reading at a certain index of a tuple
   * @param[in] idx is the index
   * @return the element at index idx
   */
  std::string operator[](const size_t idx) const;
  /**
   * Getter for the size of how many string are in the tuple
   * @return the size of the tuple
   */
  size_t size() const;
  /**
   * Method erases all data from the tuple
   */
  void clear();
  /**
   * Overloaded operator < which works as lexicographic order
   * @param[in] tuple to be compared
   * @return true if the comparing is true and false otherwise
   */
  bool operator<(const Tuple &tuple) const;
  /**
   * Overloaded operator == which compares if two tuples are equal
   * @param[in] tuple to be compared
   * @return true if both tuples are equal otherwise false
   */
  bool operator==(const Tuple &tuple) const;
  /**
   * Overloaded operator > which works as lexicographic order
   * @param[in] tuple to be compared
   * @return true if the comparing is true and false otherwise
   */
  bool operator>(const Tuple &tuple) const;
  /**
   * Overloaded operator != which compares if two tuples are not equal
   * @param[in] tuple to be compared
   * @return true if tuples are not equal otherwise false
   */
  bool operator!=(const Tuple &tuple) const;
  /**
   * Overloaded + operator adds two tuples together tuple1 and then tuple2
   * @param[in] tuple1 first tuple
   * @param[in] tuple2 second tuple
   * @return both tuples added together as one tuple
   */
  friend Tuple operator+(const Tuple &tuple1, const Tuple &tuple2);

private:
  /**
   * @brief strings stored in the tuple
   */
  std::vector<std::string> m_Data;
};