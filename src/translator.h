#include <unordered_set>
#include "commandcontroller.h"

/**
 * Class Translator translates relational algebra to SQL queries
 */
class Translator
{
public:
  /**
   * Translator constructor
   * @param[in] alias is used when a subquery needs to be aliased
   * @param[in] count is a number you start counting subqueries from
   */
  Translator(const std::string &alias = "R", size_t count = 0);
  /**
   * Method takes in a split relational algebra query and translates it into SQL
   * @param[in] query vector with single words of a relational algebra query
   * @return a string containing the fully translated query
   */
  std::string translateToSQL(std::vector<std::string> query);

private:
  /**
   * @brief used when a subquery needs to be aliased
   */
  std::string m_Alias;
  /**
   * @brief an index after alias
   */
  size_t m_Count;
  /**
   * @brief contains what attributes does current relations have if its known
   */
  std::set<std::string> m_Attributes;
  /**
   * @brief dictionary of all keywords in uppercase
   */
  const std::unordered_set<std::string> m_Keywords = {
      "PROJECTION",
      "SELECTION",
      "RENAME",
      "UNION",
      "INTERSECT",
      "CROSS",
      "NJOIN",
      "DIFF",
      "JOIN"};
  /**
   * Private method to make all letter in a string uppercase
   * @param[in] toUpper the string to be made uppercase
   * @return the input string with all uppercase letters
   */
  std::string makeUpper(std::string toUpper) const;
  /**
   * Splits a string into a vector
   * @param[in] stringToSplit the string to be split into a vector
   * @return the input string with all uppercase letters
   */
  std::vector<std::string> split(std::string stringToSplit) const;
  /**
   * Private method checks if a string contains any white spaces
   * @param[in] stringToCheck string to be checked
   * @return true if string does contain at least one white space and false otherwise
   */
  bool hasSpaces(const std::string &stringToCheck) const;
  /**
   * Private method creates a simple SELECT query from relation
   * @param[in] relation the relation to be selected from
   * @return the query as a string
   */
  std::string select(const std::string &relation) const;
  /**
   * Private method creates a select with only specific columns
   * @param[in] columns the columns to be selected
   * @param[in] relation the relation to be selected from
   * @return the query as a string
   */
  std::string projection(const std::vector<std::string> &columns, const std::string &relation);
  /**
   * Private method creates a select with a specific where condition
   * @param[in] condition a vector with the condition split into single words
   * @param[in] relation the relation to be selected from
   * @return the query as a string
   */
  std::string selection(const std::vector<std::string> &condition, const std::string &relation);
  /**
   * Private method creates a select while renaming certain columns
   * @param[in] columns a vector with the columns to be renamed
   * @param[in] relation the relation to be selected from
   * @return the query as a string
   */
  std::string rename(const std::vector<std::string> &columns, const std::string &relation);
  /**
   * Private method creates a select from a union of two relations
   * @param[in] firstRelation the first argument of union
   * @param[in] secondRelation the second argument of union
   * @return the query as a string
   */
  std::string unionSQL(const std::string &firstRelation, const std::string &secondRelation);
  /**
   * Private method creates a select from an intersection of two relations
   * @param[in] firstRelation the first argument of intersect
   * @param[in] secondRelation the second argument of intersect
   * @return the query as a string
   */
  std::string intersect(const std::string &firstRelation, const std::string &secondRelation);
  /**
   * Private method creates a select from a cross join of two relations
   * @param[in] firstRelation the first argument of cross join
   * @param[in] secondRelation the second argument of c
   * @return the query as a string
   */
  std::string cross(const std::string &firstRelation, const std::string &secondRelation);
  /**
   * Private method creates a select from an natural join of two relations
   * @param[in] firstRelation the first argument of natural join
   * @param[in] secondRelation the second argument of natural join
   * @return the query as a string
   */
  std::string njoin(const std::string &firstRelation, const std::string &secondRelation);
  /**
   * Private method creates a select from an set difference of two relations
   * @param[in] firstRelation the first argument of set difference
   * @param[in] secondRelation the second argument of set difference
   * @return the query as a string
   */
  std::string diff(const std::string &firstRelation, const std::string &secondRelation);
  /**
   * Private method creates a select from join on of two relations
   * @param[in] condition a vector containing the condition as single words
   * @param[in] firstRelation the first argument of join on
   * @param[in] secondRelation the second argument of join on
   * @return the query as a string
   */
  std::string join(const std::vector<std::string> &condition, const std::string &firstRelation, const std::string &secondRelation);
};