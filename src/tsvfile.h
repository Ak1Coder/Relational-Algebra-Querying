#include "file.h"

/**
 * Class TSVFile represents a variable containing .tsv file that is not stored in memory of a program
 */
class TSVFile : public File
{
public:
  /**
   * Constructor checks if file is valid and saves the path to the file
   * @throw runtime_error if the file is not a tsv file or the method isValid() evalutes it as invalid
   */
  TSVFile(const std::string &fileName);
  /**
   * Method clones a file
   * @return shared pointer to the base class File pointing to the copy of TSVFile
   */
  virtual std::shared_ptr<File> clone() const override;
  /**
   * Method reads the file and loads it into memory and returns it in the form of Relation object
   * @throw runtime_error if the file cannot be longer found or opened
   * @return the relation containing same content as the CSVFile
   */
  virtual Relation turnIntoRelation() const override;
  /**
   * Checks the validity of the file whether it can be opened and has correct number of elements on each row
   * @return true if valid and false otherwise
   */
  virtual bool isValid() const;
};