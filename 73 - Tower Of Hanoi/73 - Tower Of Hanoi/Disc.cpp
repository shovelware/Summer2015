#include <Disc.hpp>

#pragma region Ctor
Disc::Disc(unsigned int const& size) : m_size(size) {}
#pragma endregion

#pragma region Accessors
int Disc::size() const { return m_size; }
#pragma endregion

#pragma region Operators
bool Disc::operator<(const Disc& other) const {	return m_size < other.m_size; }
bool Disc::operator>(const Disc& other) const {	return m_size > other.m_size; }
bool Disc::operator==(const Disc& other) const { return m_size == other.m_size; }
bool Disc::operator<=(const Disc& other) const { return m_size <= other.m_size; }
bool Disc::operator>=(const Disc& other) const { return m_size >= other.m_size; }
bool Disc::operator!=(const Disc& other) const { return m_size != other.m_size; }
#pragma endregion

