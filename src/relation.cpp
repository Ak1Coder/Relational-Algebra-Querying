#include <iostream>
#include <fstream>
#include "relation.h"

Relation::Relation() = default;

Relation::Relation(const Relation &relation)
{
  m_Attributes.reserve(relation.m_Attributes.size());

  for (size_t i = 0; i < relation.m_Attributes.size(); ++i)
    m_Attributes.push_back(relation.m_Attributes[i]);

  std::vector<std::string> tmp;

  for (auto it = relation.m_Relation.begin(); it != relation.m_Relation.end(); ++it)
  {
    tmp.erase(tmp.begin(), tmp.end());
    for (size_t j = 0; j < m_Attributes.size(); ++j)
    {
      tmp.push_back((*it)[j]);
    }
    if (m_Attributes.size())
      m_Relation.insert(tmp);
  }
}

Relation &Relation::operator=(const Relation &relation)
{
  if (this == &relation)
    return *this;

  m_Attributes.erase(m_Attributes.begin(), m_Attributes.end());
  m_Relation.erase(m_Relation.begin(), m_Relation.end());

  m_Attributes.reserve(relation.m_Attributes.size());

  for (size_t i = 0; i < relation.m_Attributes.size(); ++i)
    m_Attributes.push_back(relation.m_Attributes[i]);

  std::vector<std::string> tmp;

  for (auto it = relation.m_Relation.begin(); it != relation.m_Relation.end(); ++it)
  {
    tmp.erase(tmp.begin(), tmp.end());
    for (size_t j = 0; j < m_Attributes.size(); ++j)
    {
      tmp.push_back((*it)[j]);
    }
    if (m_Attributes.size())
      m_Relation.insert(tmp);
  }
  return *this;
}

Relation &Relation::operator+=(const Relation &relation)
{
  if (getAttributesCount() != relation.getAttributesCount())
    return *this;

  for (size_t i = 0; i < getAttributesCount(); ++i)
    if (getAttribute(i) != relation.getAttribute(i))
      return *this;

  for (auto it = relation.m_Relation.begin(); it != relation.m_Relation.end(); ++it)
    addTuple(*it);
  return *this;
}

Relation &Relation::operator-=(const Relation &relation)
{
  if (getAttributesCount() != relation.getAttributesCount())
    return *this;

  for (size_t i = 0; i < getAttributesCount(); ++i)
    if (getAttribute(i) != relation.getAttribute(i))
      return *this;

  for (auto it = relation.m_Relation.begin(); it != relation.m_Relation.end(); ++it)
    m_Relation.erase(*it);

  return *this;
}

void Relation::print(unsigned int spacesBetweenColumns) const
{
  std::vector<std::size_t> columnWidths;
  size_t lineLen = 0;
  for (size_t i = 0; i < getAttributesCount(); ++i)
    columnWidths.push_back(m_Attributes[i].size());

  for (auto it = m_Relation.begin(); it != m_Relation.end(); ++it)
    for (size_t i = 0; i < getAttributesCount(); ++i)
      if (columnWidths[i] < (*it)[i].size())
        columnWidths[i] = (*it)[i].size();

  for (size_t i = 0; i < columnWidths.size(); ++i)
  {
    columnWidths[i] += spacesBetweenColumns;
    lineLen += columnWidths[i] + 1;
  }
  lineLen--;

  std::cout << std::setfill(' ');

  for (size_t i = 0; i < m_Attributes.size(); ++i)
  {
    std::cout << std::left << std::setw(columnWidths.at(i)) << m_Attributes.at(i) << " ";
  }
  if (m_Attributes.size())
    std::cout << std::endl
              << std::setw(lineLen) << std::setfill('-') << "" << std::endl;

  std::cout << std::setfill(' ');

  for (auto it = m_Relation.begin(); it != m_Relation.end(); ++it)
  {
    for (size_t i = 0; i < it->size(); ++i)
    {
      std::cout << std::left << std::setw(columnWidths.at(i)) << ((*it)[i]) << " ";
    }
    std::cout << std::endl;
  }

  if (m_Attributes.size())
    std::cout << std::setw(lineLen) << std::setfill('-') << "" << std::endl;
  else
    std::cout << "EMPTY RESULT" << std::endl;
  std::cout << std::setfill(' ');
}

void Relation::exportToFile(const std::string &fileName) const
{
  std::string fileToWrite = fileName;
  if (fileToWrite.substr(fileToWrite.size() - 4) != ".csv")
    throw std::runtime_error("ERROR: Only .csv export is supported.");

  std::ofstream fout(fileToWrite);
  std::string tmp = "";
  for (size_t i = 0; i < m_Attributes.size() - 1; ++i)
    tmp += m_Attributes[i] + ",";
  if (m_Attributes.size())
    tmp += m_Attributes[m_Attributes.size() - 1] + '\n';

  fout << tmp;

  if (!fout.good())
  {
    std::cout << "ERROR: Error occured during writing in the file." << std::endl;
    return;
  }

  for (auto it = m_Relation.begin(); it != m_Relation.end(); ++it)
  {
    tmp = "";
    for (size_t i = 0; i < m_Attributes.size() - 1; ++i)
      tmp += (*it)[i] + ',';
    if (m_Attributes.size())
      tmp += (*it)[m_Attributes.size() - 1] + '\n';

    fout << tmp;

    if (!fout.good())
    {
      std::cout << "ERROR: Error occured during writing in the file." << std::endl;
      return;
    }
  }
}

Relation &Relation::addAttribute(const std::string &newAttribute)
{
  m_Attributes.push_back(newAttribute);
  return *this;
}

Relation &Relation::addTuple(const Tuple &newTuple)
{
  if (m_Attributes.size() != newTuple.size())
    throw std::runtime_error("ERROR: Inserting into relation failed.");

  m_Relation.insert(newTuple);
  return *this;
}
std::shared_ptr<Relation> Relation::clone() const
{
  std::shared_ptr<Relation> result = std::make_shared<Relation>(Relation(*this));
  return result;
}

std::string Relation::getAttribute(size_t idx) const
{
  return m_Attributes.at(idx);
}

size_t Relation::getAttributesCount() const
{
  return m_Attributes.size();
}

int Relation::getAttributesOrder(const std::string &attribute) const
{
  for (size_t i = 0; i < getAttributesCount(); ++i)
    if (attribute == m_Attributes[i])
      return i;
  return -1;
}

void Relation::setAttribute(size_t idx, const std::string &newAttribute)
{
  if (idx < m_Attributes.size())
    m_Attributes.at(idx) = newAttribute;
}

const std::set<Tuple> &Relation::getRefToRelation() const
{
  return m_Relation;
}

size_t Relation::getTuplesCount() const
{
  return m_Relation.size();
}