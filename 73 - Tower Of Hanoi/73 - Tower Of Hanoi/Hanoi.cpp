#include "Hanoi.hpp"

#pragma region Ctor
//Stores passed arguments, or minimum for a functional game
Hanoi::Hanoi(unsigned int const& discNum, unsigned int const& pinNum, unsigned int const& startPin, unsigned int const& endPin) : m_startPin(startPin), m_endPin(endPin)
{
	m_pinNum = pinNum > 2 ? pinNum : 3;
	m_discNum = discNum > 1 ? discNum : 2;
	
	reset();
}
#pragma endregion

#pragma region Accessors
//returns the number of pins
unsigned int Hanoi::getNumPins() const
{
	return m_pinNum;
}

//returns game solved state
bool Hanoi::getSolved() const
{
	return m_solved;
}
#pragma endregion

#pragma region Game Functions
//resets the game state for a new game
void Hanoi::reset()
{
	//Reset pins
	m_pins.clear();
	m_pins.reserve(m_pinNum);

	for (int p = 0; p < m_pinNum; ++p)
	{
		m_pins.push_back(Pin(m_discNum));
	}

	//If no start is specified
	if (m_startPin >= m_pinNum)
	{
		//Place discs on middle pin (right-biased)
		m_startPin = m_pinNum / 2;
	}

	for (int d = m_discNum; d > 0; --d)
	{
		m_pins[m_startPin].push(Disc(d));
	}

	//reset win state
	m_solved = false;
}

//attempts to move between two pin indices, returns success
bool Hanoi::move(unsigned int const& from, unsigned int const& dest)
{
	bool moved = false;

	//if from and dest are different and valid indexes
	if (from != dest && from < m_pinNum && dest < m_pinNum)
	{
		//if from isn't empty and dest isn't full
		if (m_pins[from].empty() == false && m_pins[dest].full() == false)
		{
			//if the move is valid
			if (m_pins[from].top() < m_pins[dest].top());
			{
				//perform the move and update if we need to
				if (moved = m_pins[dest].push(m_pins[from].pop()));
					updateGameState();
			}
		}
	}
	
	return moved;
}

//checks if a solution has been found
void Hanoi::updateGameState()
{
	//Can only win if we've moved all discs
	if (m_pins[m_startPin].empty())
	{
		//if an end pin is specified
		if (m_endPin <= m_pinNum)
		{
			if (m_pins[m_endPin - 1].full())
				m_solved = true;
		}

		//else any pin can be end
		else
		{
			unsigned int emptyCount = 1;
			unsigned int fullCount = 0;

			//for each pin
			for (int p = 0; p < m_pinNum; ++p)
			{
				//not start
				if (p != m_startPin)
				{
					if (m_pins[p].empty())
					{
						emptyCount++;
						continue;
					}

					else if (m_pins[p].full())
					{
						fullCount++;
						continue;
					}

					//If it's not full and not empty you can't have won!
					else break;
				}
			}//end pin loop

			if (emptyCount == m_pinNum - 1 && fullCount == 1)
			{
				m_solved = true;
			}
		}//end any pin end
	}
}
#pragma endregion