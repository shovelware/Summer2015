#include "Hanoi.hpp"

#pragma region Ctor
Hanoi::Hanoi()
{
	reset();
}

//Stores passed arguments, or minimum for a functional game
Hanoi::Hanoi(unsigned int const &pinNum, unsigned int const &pinHeight)
{
	m_pinNum = pinNum > 2 ? pinNum : 3;
	m_pinHeight = pinHeight > 1 ? pinHeight : 2;
	
	reset();
}
#pragma endregion

#pragma region Accessors
#pragma endregion

#pragma region Game Functions
void Hanoi::reset()
{
	//Reset pins
	m_pins.clear();
	m_pins.reserve(m_pinNum);

	for (int i = 0; i <= m_pinNum; ++i)
	{
		m_pins.push_back(Pin(m_pinHeight));
	}

	//Reset discs on middle pin (left-biased)
	for (int i = m_pinHeight; i > 0; --i)
	{
		m_pins[m_pinNum / 2 - 1].push(Disc(i));
	}
}

void Hanoi::updateGameState()
{
	
}

bool Hanoi::move(int from, int dest)
{
	bool moved = false;

	//check from and dest are different and valid indexes
	if (from != dest && from < m_pinNum && dest < m_pinNum)
	{
		//check from isn't empty and dest isn't full
		if (m_pins[from].empty() == false && m_pins[dest].full() == false)
		{
			//perform the move
			moved = m_pins[from].push(m_pins[dest].pop());
		}
	}
	
	return moved;
}
#pragma region