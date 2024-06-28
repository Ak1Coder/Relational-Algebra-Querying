#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <vector>
#include "relation.h"

/**
 * Class File is an abstract base class for all files that will not be stored in the memory of the program
 */
class File
{
public:
  /**
   * File constructor takes the path and checks whether file is valid by isValid() method
   * @param[in] fileName path to the
   * @throw runtime_error exception if the file is evaluated as invalid
   */
  File(const std::string &fileName);
  /**
   * Pure abstract method that will be used for derived File classes to make copies of themselves
   * @return shared pointer to the base class File
   */
  virtual std::shared_ptr<File> clone() const = 0;
  /**
   * Pure abstract method that will be used for derived File classes to transform into in memory stored object Relation
   * @return Relation object whose content is equal to what is inside the file object
   */
  virtual Relation turnIntoRelation() const = 0;
  /**
   * Getter for a in program name for the File
   * @return the in program name of a file
   */
  std::string getName() const;
  /**
   * Getter for a name or the whole path to the file
   * @return the name or the whole path to the file
   */
  std::string getFileName() const;
  /**
   * Setter for the in program name for the file
   * @param[in] newName the new name
   */
  void setName(const std::string &newName);
  /**
   * Setter for the real name or path to the file
   * @param[in] newName the new name
   */
  void setFileName(const std::string &newName);
  /**
   * Method checks whether the file can be opened or not
   * @return true if it can be opened and returns false otherwise
   */
  virtual bool isValid() const;
  /**
   * Default virtual destructor
   */
  virtual ~File();

protected:
  /**
   * @brief an alias or name of the program only used in program when file is being stored as a variable
   */
  std::string m_Alias;
  /**
   * @brief a name or path to the actual file on the computer
   */
  std::string m_FileName;
};
