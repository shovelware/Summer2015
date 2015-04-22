#include "Disc.hpp"

Disc::Disc() : m_size(1){}
Disc::Disc(int size) : m_size(size) {}

int Disc::size(){ return m_size; }