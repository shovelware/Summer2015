#include "Hanoi.hpp"

#pragma region Ctor
Hanoi::Hanoi() : gamestate(PIN), m_pinNum(m_minPins), m_discNum(m_minDiscs), m_startPin(m_pinNum), m_endPin(m_pinNum), m_moves(0)
{
}

#pragma endregion

#pragma region Accessors
//returns the number of pins
unsigned int Hanoi::getPinNum() const { return m_pinNum; }

//returns pin height
unsigned int Hanoi::getPinHeight() const { return m_pins[0].capacity();  }

//returns game solved state
bool Hanoi::getSolved() const {	return (gamestate == SOLVED); }

//returns a copy of pins
vector<Pin> Hanoi::getPins() const { return vector<Pin>(m_pins); }
#pragma endregion

#pragma region Game Functions
//resets the game and can populate pins for a new game
void Hanoi::updateParameters()
{
	//Pin changes can only be done before discs
	if (gamestate == PIN)
	{
		if (m_pins.size() != m_pinNum)
		{
			//Reset pins
			m_pins.clear();
			m_pins.reserve(m_pinNum);

			for (int p = 0; p < m_pinNum; ++p)
			{
				m_pins.push_back(Pin(m_discNum));
			}
		}
	}
	
	//Disc population only takes place once pins are locked
	else if (gamestate == DISC)
	{
		//clear all pins
		for (int p = 0; p < m_pinNum; ++p)
		{
			m_pins[p].clear();
		}

		//If no start is specified
		if (m_startPin >= m_pinNum)
		{
			//Place discs on middle pin (right-biased)
			m_startPin = m_pinNum / 2;
		}

		//Make sure pins are correct height for game
		if (m_pins[m_startPin].size() != m_discNum)
		{
			for (int p = 0; p < m_pinNum; ++p)
			{
				m_pins[p].resize(m_discNum);
			}
		}

		for (unsigned int d = m_discNum; d > 0; --d)
		{
			m_pins[m_startPin].push(Disc(d));
		}
	}
}

//Minimum number of moves is (2^n) - 1 where n is number of disks
unsigned int Hanoi::minimumMoves()
{
	return pow(2, m_discNum) - 1;
}

//attempts a move between two pin indices, returns success
bool Hanoi::move(unsigned int const& from, unsigned int const& dest)
{
	bool moved = false;

	//only if we're playing
	if (gamestate == PLAYING)
	{
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
					if (moved = m_pins[dest].push(m_pins[from].pop()))
					{
						checkGameState();
						m_moves++;
					}
				}
			}
		}
	}
	
	return moved;
}

//Locks pins, then discs. Advances gamestate one step towards gameplay
void Hanoi::lockParameter()
{
	if (gamestate == PIN)
	{
		updateParameters();
		gamestate = DISC;
	}

	else if (gamestate == DISC)
	{
		updateParameters();
		gamestate = PLAYING;
	}
}

bool Hanoi::getPlaying()
{
	return (gamestate == PLAYING);
}

//PRIVATE

void Hanoi::setNumPins(unsigned int const& numPins)
{
	//pin phase only
	if (gamestate == PIN)
	{
		//valid number
		if (numPins > m_minPins)
		{
			//need to update start pin
			if (m_startPin >= m_pinNum)
			{
				m_startPin = numPins;
			}

			m_pinNum = numPins;

		}
		
		else m_pinNum = m_minPins;

		updateParameters();
	}
}

void Hanoi::setNumDiscs(unsigned int const& numDiscs)
{
	//disc phase only
	if (gamestate == DISC)
	{
		m_discNum = numDiscs > m_minDiscs ? numDiscs : m_minDiscs;
		updateParameters();
	}
}

void Hanoi::setStartPin(unsigned int const& startPin)
{
	//start pin must be before discs are added
	if (gamestate == PIN)
	{
		m_startPin = startPin > 0 ? startPin : m_pinNum;
	}
}

void Hanoi::setEndPin(unsigned int const& endPin)
{
	//either setup phase
	if (gamestate < PLAYING)
	{
		m_endPin = endPin > 0 ? endPin : m_pinNum;
	}
}
//checks if a solution has been found
void Hanoi::checkGameState()
{
	//Can only win if we've moved all discs
	if (m_pins[m_startPin].empty())
	{
		//if an end pin is specified
		if (m_endPin < m_pinNum)
		{
			if (m_pins[m_endPin - 1].full())
			{
				gamestate = SOLVED;
			}
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
				gamestate = SOLVED;
			}
		}//end any pin end
	}
}
#pragma endregion