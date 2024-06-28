#include <unordered_map>
#include <algorithm>
#include "join.h"

/**
 * CommandController class takes care of parsing all relational algebra commands and checking their validity
 */
class CommandController
{
public:
  /**
   * CommandController default constructor
   */
  CommandController();
  /**
   * Method evaluateCommand checks whether the relational algebra command has correct syntax and splits it into a vector of single words
   * @param[in] command command is the command to be split and checked
   * @throw runtime_error when the syntax is not valid
   * @return vector of strings of single words in the command
   */
  std::vector<std::string> evaluateCommand(const std::string &command) const;

private:
  /**
   * @brief unordered_map with relational algebra keywords as a key to pair of parameters they need where first is number of relations and second is number of expression meaning conditions or rename, export, import expressions
   */
  const std::unordered_map<std::string, std::pair<size_t, size_t>> m_Operators =
      {
          {"PROJECTION", {1, 1}},
          {"SELECTION", {1, 1}},
          {"RENAME", {1, 1}},
          {"JOIN", {2, 1}},
          {"UNION", {2, 0}},
          {"CROSS", {2, 0}},
          {"INTERSECT", {2, 0}},
          {"NJOIN", {2, 0}},
          {"DIFF", {2, 0}},
          {"PRINT", {1, 0}},
          {"TRANSLATE", {1, 0}},
          {"EXPORT", {1, 1}},
          {"IMPORT", {0, 2}}};
  /**
   * Method that splits a string into a vector by whitespaces which can be ignored if "" are used
   * @param[in] command the string to be split
   * @return vector of the individual words of the command
   */
  std::vector<std::string> turnIntoVector(const std::string &command) const;
  /**
   * Method checks the validity of the relational algebra command based on number of parameters
   * @param[in] command the relational algebra command to be checked for validity
   * @return true if the command is valid and false otherwise
   */
  bool isValid(const std::string &command) const;
};