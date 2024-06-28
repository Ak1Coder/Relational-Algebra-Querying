#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "config.h"

Config::Config(const std::string &fileName)
{
  std::string SPACES_BETWEEN_COLUMNS = "SPACES_BETWEEN_COLUMNS";
  std::string SUBQUERY_POSTFIX = "SUBQUERY_POSTFIX";
  std::string INPUT_DELIMETER = "INPUT_DELIMITER";
  std::set<std::string> wasNotRead = {SPACES_BETWEEN_COLUMNS, SUBQUERY_POSTFIX, INPUT_DELIMETER};

  size_t constantCount = wasNotRead.size();

  std::ifstream fin(fileName);

  if (!fin.is_open() || !fin)
  {
    throw std::runtime_error("ERROR: Config file could not be opened.");
  }

  std::string constantName;
  std::string readWord;
  for (size_t i = 0; i < constantCount; ++i)
  {
    if (!(fin >> constantName) || wasNotRead.count(constantName) == 0)
      throw std::runtime_error("ERROR: Config file unexpected error.");

    wasNotRead.erase(constantName);

    if (!(fin >> readWord) || readWord != "=")
      throw std::runtime_error("ERROR: Config file unexpected error.");

    if (constantName == SPACES_BETWEEN_COLUMNS)
    {
      if (!(fin >> m_SpacesBetweenColumns) || fin.get() != '\n' || m_SpacesBetweenColumns < 1)
        throw std::runtime_error("ERROR: Unexpected error loading " + SPACES_BETWEEN_COLUMNS + " (at least 1).");
    }
    else if (constantName == SUBQUERY_POSTFIX)
    {
      if (!(fin >> m_SubqueryPostfix) || fin.get() != '\n' || m_SubqueryPostfix.size() > 10 || m_SubqueryPostfix.size() == 0)
        throw std::runtime_error("ERROR: Unexpected error loading " + SUBQUERY_POSTFIX + " (1-10 characters).");
    }
    else if (constantName == INPUT_DELIMETER)
    {
      if (!(fin >> m_InputDelimeter) || fin.get() != '\n' || m_InputDelimeter.size() > 10 || m_InputDelimeter.size() == 0)
        throw std::runtime_error("ERROR: Unexpected error loading " + INPUT_DELIMETER + " (1-10 characters).");
    }
  }

  fin >> readWord;
  if (!fin.eof())
    throw std::runtime_error("ERROR: Unexpected error at the end of the config file.");
}

int Config::getSpacesBetweenColumns() const
{
  return m_SpacesBetweenColumns;
}

std::string Config::getSubqueryPostfix() const
{
  return m_SubqueryPostfix;
}

std::string Config::getInputDelimeter() const
{
  return m_InputDelimeter;
}