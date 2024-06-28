#include "database.h"

/**
 * Class Application represents the whole app and takes care of reading the input
 */
class Application
{
public:
  /**
   * Application constructor takes in a configuration and copies it as a member variable
   * @param[in] configuration is an object with the constants read from a file
   */
  Application(const Config &configuration);
  /**
   * Method run() contains the main loop of the app and catches exceptions that occur
   */
  void run() const;

private:
  /**
   * @brief a configuration with the loaded constants
   */
  Config m_Configuration;
  /**
   * Method upper() makes all letters of a string uppercase
   * @param[in] expression expression is the string to have all letters transformed to uppercase
   * @returns new string with all uppercase letters
   */
  std::string upper(const std::string &expression) const;
};