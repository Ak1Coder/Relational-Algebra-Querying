#include <sstream>
#include "csvfile.h"

CSVFile::CSVFile(const std::string &fileName)
    : File(fileName)
{
  if (m_FileName.substr(m_FileName.size() - 4) != ".csv")
  {
    throw std::runtime_error("ERROR: Unrecognized file format of \"" + m_FileName + "\".");
  }
  else if (!isValid())
  {
    throw std::runtime_error("ERROR: File is not valid.");
  }
}

std::shared_ptr<File> CSVFile::clone() const
{
  std::string alias = this->getName();
  CSVFile result(m_FileName);
  result.setName(alias);

  return std::make_shared<CSVFile>(result);
}

Relation CSVFile::turnIntoRelation() const
{
  Relation result;

  if (!isValid())
    throw std::runtime_error("ERROR: File is not valid.");

  std::ifstream file(m_FileName);
  std::string line, word;
  Tuple tupleToInsert;
  size_t attributesCount = 0;

  std::getline(file, line);

  std::stringstream str(line);
  while (std::getline(str, word, ','))
    result.addAttribute(word);

  while (std::getline(file, line))
  {
    tupleToInsert.clear();
    attributesCount = 0;
    std::stringstream str(line);

    while (std::getline(str, word, ','))
    {
      tupleToInsert.add(word);
      attributesCount++;
    }
    if (attributesCount != result.getAttributesCount())
      throw std::runtime_error("ERROR: File is not valid.");
    result.addTuple(tupleToInsert);
  }

  return result;
}

bool CSVFile::isValid() const
{
  std::fstream file(m_FileName);
  size_t attributeCount = 0, tmpCount = 0;
  std::string line, word;

  if (!file.is_open() || !file)
    return false;

  std::getline(file, line);

  std::stringstream str(line);
  while (std::getline(str, word, ','))
    attributeCount++;

  if (!str.eof())
    return false;

  while (std::getline(file, line))
  {
    tmpCount = 0;
    std::stringstream str(line);

    while (std::getline(str, word, ','))
    {
      tmpCount++;
    }
    if (tmpCount != attributeCount)
      return false;
    if (!str.eof())
      return false;
  }
  return true;
}