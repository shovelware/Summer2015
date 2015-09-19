#include <Disc.hpp>

#pragma region Ctor
Disc::Disc(unsigned int const& size) : m_size(size) {}
#pragma endregion

#pragma region Accessors
unsigned int Disc::size() const { return m_size; }
#pragma endregion

#pragma region Operators
bool Disc::operator< (const Disc& that) const { return this->m_size < that.m_size; }
bool Disc::operator> (const Disc& that) const { return this->m_size > that.m_size; }
bool Disc::operator==(const Disc& that) const { return this->m_size == that.m_size; }
bool Disc::operator<=(const Disc& that) const { return this->m_size <= that.m_size; }
bool Disc::operator>=(const Disc& that) const { return this->m_size >= that.m_size; }
bool Disc::operator!=(const Disc& that) const { return this->m_size != that.m_size; }
#pragma endregion