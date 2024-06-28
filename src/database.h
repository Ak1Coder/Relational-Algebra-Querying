#include <memory>
#include <utility>
#include <set>
#include "config.h"
#include "translator.h"

class Database
{
public:
  /**
   * Database constructor loads the configuration
   * @param[in] configuration the configuration to be loaded and stored
   */
  Database(const Config &configuration);
  /**
   * Methods adds a file to the database or prints out an error if the file is already added or file with same name exists
   * @return reference to Database so it can be chained
   */
  Database &add(const File &fileToAdd);
  /**
   * Method takes in a relational algebra query or another command and realizes it over the Database and its variables
   * @param[in] command a command or realtional algebra query to be called over the Database
   * @throw runtime_error if the command is invalid or the command cannot be called with the current state of Database
   */
  void command(const std::string &command);

private:
  /**
   * @brief configuration with all the constants loaded from a config file
   */
  Config m_Configuration;
  /**
   * @brief unordered_map of all the files variables not stored in memory with keys being their names
   */
  std::unordered_map<std::string, std::shared_ptr<File>> m_Files;
  /**
   * @brief unordered_map of all the relations stored in memory with keys being their names
   */
  std::unordered_map<std::string, std::shared_ptr<Relation>> m_Variables;
  /**
   * @brief unordered_map of relational algebra keywords which are a key to shared pointer to corresponding relational algebra operator
   */
  const std::unordered_map<std::string, std::shared_ptr<Operator>> m_Operators =
      {
          {"PROJECTION", std::shared_ptr<Operator>(new Projection())},
          {"SELECTION", std::shared_ptr<Operator>(new Selection())},
          {"RENAME", std::shared_ptr<Operator>(new Rename())},
          {"UNION", std::shared_ptr<Operator>(new Union())},
          {"CROSS", std::shared_ptr<Operator>(new CrossJoin())},
          {"INTERSECT", std::shared_ptr<Operator>(new Intersection())},
          {"NJOIN", std::shared_ptr<Operator>(new NJoin())},
          {"DIFF", std::shared_ptr<Operator>(new SetDifference())},
          {"JOIN", std::shared_ptr<Operator>(new Join())}};
  /**
   * @brief Dictionary of commands which are not relational algebra keywords
   */
  const std::set<std::string> m_Commands =
      {"PRINT", "TRANSLATE", "EXPORT", "IMPORT"};
};