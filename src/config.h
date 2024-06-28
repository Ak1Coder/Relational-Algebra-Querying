#include <string>

/**
 * Class Config loads constants from a file
 */
class Config
{
public:
  /**
   * Config constructor loads constants from a file and stores them in a member variables
   * @param[in] fileName name of the config file to load from
   * @throw runtime_error when there is a problem with reading the file
   */
  Config(const std::string &fileName);
  /**
   * Getter for the number representing the amount of spaces between columns of tables when printing them out
   * @return the constant loaded from a file
   */
  int getSpacesBetweenColumns() const;
  /**
   * Getter for the name subqueries are gonna be called when translating relational algebra to SQL
   * @return the constant loaded from a file
   */
  std::string getSubqueryPostfix() const;
  /**
   * Getter for what should be written next to the input
   * @return the constant loaded from a file
   */
  std::string getInputDelimeter() const;

private:
  /**
   * @brief amount of spaces between columns of tables when printing them out
   */
  int m_SpacesBetweenColumns;
  /**
   * @brief name for subqueries in SQL when Relational algebra is translated
   */
  std::string m_SubqueryPostfix;
  /**
   * @brief whatever is at a line next to your input
   */
  std::string m_InputDelimeter;
};