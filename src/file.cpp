#include "file.h"

File::File(const std::string &fileName)
    : m_Alias(fileName), m_FileName(fileName)
{
  if (!isValid())
    throw std::runtime_error("ERROR: File \"" + m_FileName + "\" is not valid");
}

std::string File::getName() const
{
  return m_Alias;
}
std::string File::getFileName() const
{
  return m_FileName;
}
void File::setName(const std::string &newName)
{
  m_Alias = newName;
}
void File::setFileName(const std::string &newName)
{
  m_FileName = newName;
}
bool File::isValid() const
{
  std::fstream file(m_FileName);

  if (!file.is_open() || !file)
    return false;

  return true;
}
File::~File() = default;
