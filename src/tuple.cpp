#include "tuple.h"

Tuple::Tuple() = default;

Tuple::Tuple(const std::vector<std::string> v)
{
  for (auto &x : v)
    m_Data.push_back(x);
}

Tuple::Tuple(const Tuple &tuple)
{
  for (size_t i = 0; i < tuple.size(); ++i)
    this->m_Data.push_back(tuple[i]);
}

Tuple &Tuple::add(const std::string &element)
{
  m_Data.push_back(element);
  return *this;
}
std::string Tuple::operator[](const size_t idx) const
{
  return m_Data.at(idx);
}

size_t Tuple::size() const
{
  return m_Data.size();
}

void Tuple::clear()
{
  m_Data.erase(m_Data.begin(), m_Data.end());
}

bool Tuple::operator<(const Tuple &tuple) const
{
  for (size_t i = 0; i < size(); ++i)
    if (m_Data[i] != tuple.m_Data[i])
      return m_Data[i] < tuple.m_Data[i];
  return false;
}

bool Tuple::operator==(const Tuple &tuple) const
{
  if (m_Data.size() != tuple.m_Data.size())
    return false;

  for (size_t i = 0; i < size(); ++i)
    if (m_Data[i] != tuple.m_Data[i])
      return false;
  return true;
}

bool Tuple::operator>(const Tuple &tuple) const
{
  return !(*this < tuple) && !(*this == tuple);
}

bool Tuple::operator!=(const Tuple &tuple) const
{
  return !(*this == tuple);
}

Tuple operator+(const Tuple &tuple1, const Tuple &tuple2)
{
  Tuple result = tuple1;

  for (size_t i = 0; i < tuple2.size(); ++i)
  {
    result.add(tuple2[i]);
  }
  return result;
}