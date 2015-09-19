#include <Hanoi.hpp>

#pragma region Ctor
Hanoi::Hanoi() : m_gamestate(PIN), m_pinNum(m_minPins), m_discNum(m_minDiscs), m_startPin(m_pinNum), m_endPin(m_pinNum), m_moves(0), m_pinSelected(0), m_discHeld(m_pinNum)
{
	updateParameters();
}

#pragma endregion

#pragma region Accessors
unsigned int Hanoi::getGameState() const { return m_gamestate; }

char* Hanoi::getGameStateAsString() const
{
	switch (m_gamestate)
	{
	case PIN:
		return "PIN";
	case DISC:
		return "DISC";
	case PLAYING:
		return "PLAYING";
	case SOLVED:
		return "SOLVED";
	default:
		return "ERROR";
	}
}

//Minimum number of moves is (2^n) - 1 where n is number of discs
unsigned int Hanoi::getMinimumMoves() const { return pow(2, m_discNum) - 1; }

unsigned int Hanoi::getMoves() const { return m_moves; }

unsigned int Hanoi::getPinNum() const { return m_pinNum; }

unsigned int Hanoi::getPinHeight() const { return m_pins[0].capacity();  }

unsigned int Hanoi::getStartPin() const { return m_startPin; }

unsigned int Hanoi::getEndPin() const { return m_endPin; }

vector<Pin> Hanoi::getPins() const { return vector<Pin>(m_pins); }

unsigned int Hanoi::getPinSelected() const { return m_pinSelected; }

unsigned int Hanoi::getDiscHeld() const { return m_discHeld; }

int Hanoi::getLastInput() const { return m_lastInput; }
#pragma endregion

#pragma region Game & Setup Functions
//resets the gamestate and prepares for a new game
bool Hanoi::reset()
{
	m_gamestate = PIN;
	m_moves = 0;
	m_pinSelected = m_pinNum;
	m_discHeld = m_pinNum;
	m_pins.clear();
	updateParameters();
	return true;
}

//refreshes the game variables and can populate pins for a new game
void Hanoi::updateParameters()
{
	//Pin changes can only be done before discs
	if (m_gamestate == PIN)
	{
		if (m_pins.size() != m_pinNum)
		{
			//Reset pins
			m_pins.clear();
			m_pins.reserve(m_pinNum);

			for (unsigned int p = 0; p < m_pinNum; ++p)
			{
				m_pins.push_back(Pin(m_discNum));
			}

			//update selected pin and held disc (will be pregame)
			m_pinSelected = m_pinNum;
			m_discHeld = m_pinNum;
		}
	}
	
	//Disc population only takes place once pins are locked
	else if (m_gamestate == DISC)
	{
		//clear all pins
		for (unsigned int p = 0; p < m_pinNum; ++p)
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
			for (unsigned int p = 0; p < m_pinNum; ++p)
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

//Movement method, returns GUI update necessity
bool Hanoi::moveLeft()
{

	if (m_gamestate == PIN)
	{
		return setNumPins(m_pinNum - 1);
	}
	
	else if (m_gamestate == PLAYING)
	{
		//Check last input
		if (m_lastInput != ACTION)
		{
			m_lastInput = ACTION;
			return true;
		}

		return (m_pinSelected != 0 ? m_pinSelected-- : m_pinSelected);
	}

	return false;
}

//Movement method, returns GUI update necessity
bool Hanoi::moveRight()
{

	if (m_gamestate == PIN)
	{
		return setNumPins(m_pinNum + 1);
	}

	else if (m_gamestate == PLAYING)
	{
		//Check last input
		if (m_lastInput != ACTION)
		{
			m_lastInput = ACTION;
			return true;
		}

		return (m_pinSelected + 1 < m_pinNum ? ++m_pinSelected : m_pinSelected);
	}

	return false;
}

//Movement method, returns GUI update necessity
bool Hanoi::moveUp()
{
	if (m_gamestate == DISC)
	{
		return setNumDiscs(m_discNum + 1);
	}

	else if (m_gamestate == PLAYING)
	{
		//Check last input
		if (m_lastInput != ACTION)
		{
			m_lastInput = ACTION;
			return true;
		}

		return pickupDisc(m_pinSelected);
	}

	return false;
}

//Movement method, returns GUI update necessity
bool Hanoi::moveDown()
{
	if (m_gamestate == DISC)
	{
		return setNumDiscs(m_discNum - 1);
	}

	else if (m_gamestate == PLAYING)
	{
		//Check last input
		if (m_lastInput != ACTION)
		{
			m_lastInput = ACTION;
			return true;
		}

		return putdownDisc(m_pinSelected);
	}

	return false;
}

//Picks up a disc from pin, returns GUI update necessity / success
bool Hanoi::pickupDisc(unsigned int pin)
{
	if (m_gamestate == PLAYING)
	{
		//valid index and our hand is empty
		if (pin < m_pinNum && m_discHeld >= m_pinNum)
		{
			//if there's a disc there
			if (!m_pins[pin].empty())
			{
				//pick it up
				m_discHeld = pin;
				return true;
			}
		}
	}

	return false;
}

//Puts down held disc, returns GUI update necessity
bool Hanoi::putdownDisc(unsigned int pin)
{
	if (m_gamestate == PLAYING)
	{
		//if we're holding a disc
		if (m_discHeld != m_pinNum)
		{
			//If we got it from here
			if (m_discHeld == pin)
			{
				m_discHeld = m_pinNum;
				return true;
			}

			//else try moving it
			else if (moveDisc(m_discHeld, pin))
			{
				m_discHeld = m_pinNum;
				return true;
			}
		}
	}

	return false;

}

//Puts the disc back where you got it
bool Hanoi::returnDisc()
{
	if (m_gamestate == PLAYING)
	{
		m_discHeld = m_pinNum;
		return true;
	}

	return false;
}

//Used for one-button interaction with game, returns GUI update necessity
bool Hanoi::actionButton()
{
	if (m_gamestate == PIN || m_gamestate == DISC)
	{
		lockParameter();
		return true;
	}

	else if (m_gamestate == PLAYING)
	{
		if (m_lastInput != ACTION)
		{
			m_lastInput = ACTION;
			return true;
		}

		return handleDisc();
	}

	else if (m_gamestate == SOLVED)
	{
		return reset();
	}

	return false;
}

//Pick up or put down disc at selection, returns GUI update necessity
bool Hanoi::handleDisc()
{
	if (m_gamestate == PLAYING)
	{
		//If we have one
		if (m_discHeld != m_pinNum)
			return putdownDisc(m_pinSelected);

		else return pickupDisc(m_pinSelected);
	}

	return false;
}

//Pick up or put down disc at pin, returns GUI update necessity
bool Hanoi::handleDisc(unsigned int pin)
{
	m_lastInput = INDEX;

	if (m_gamestate == PLAYING)
	{
		//If we have one
		if (m_discHeld != m_pinNum)
		{
			//Select the last pin we try move to for affordance
			m_pinSelected = pin;
			return putdownDisc(pin);
		}

		else return pickupDisc(pin);
	}

	return false;
}

//attempts a move between two pin indices, returns success
bool Hanoi::moveDisc(unsigned int from, unsigned int dest)
{
	bool moved = false;

	//only if we're playing
	if (m_gamestate == PLAYING)
	{
		//if from and dest are different and valid indexes
		if (from != dest && from < m_pinNum && dest < m_pinNum)
		{
			//take reference to pins
			Pin& frm = m_pins[from];
			Pin& dst = m_pins[dest];

			//if from isn't empty and dest isn't full
			if (frm.empty() == false && dst.full() == false)
			{
				Disc frmd = frm.top();
				Disc dstd = dst.top();

				//if the move is valid
				if (frmd < dstd)
				{
					//perform the move and update if we need to
					if (moved = dst.push(frm.pop()))
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

//PRIVATE

//Locks pins, then discs. Advances m_gamestate one step towards gameplay
void Hanoi::lockParameter()
{
	if (m_gamestate == PIN)
	{
		updateParameters();
		m_gamestate = DISC;
		updateParameters();
	}

	else if (m_gamestate == DISC)
	{
		updateParameters();
		m_gamestate = PLAYING;
		m_pinSelected = m_startPin;
	}
}

bool Hanoi::setNumPins(unsigned int numPins)
{
	//pin phase only
	if (m_gamestate == PIN)
	{
		//valid number
		if (numPins >= m_minPins && numPins <= m_maxPins)
		{
			//need to update start pin
			if (m_startPin >= m_pinNum)
			{
				m_startPin = numPins;
			}

			m_pinNum = numPins;
			updateParameters();
			return true;
		}
		
	}

	return false;
}

bool Hanoi::setNumDiscs(unsigned int numDiscs)
{
	//disc phase only
	if (m_gamestate == DISC)
	{	
		//valid number
		if (numDiscs >= m_minDiscs && numDiscs <= m_maxDiscs)
		{
			m_discNum = numDiscs;
			updateParameters();
			return true;
		}
	}
	return false;
}

void Hanoi::setStartPin(unsigned int startPin)
{
	//start pin must be before discs are added
	if (m_gamestate == PIN)
	{
		m_startPin = startPin > 0 ? startPin : m_pinNum;
	}
}

void Hanoi::setEndPin(unsigned int endPin)
{
	//either setup phase
	if (m_gamestate < PLAYING)
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
				m_gamestate = SOLVED;
			}
		}

		//else any pin can be end
		else
		{
			unsigned int emptyCount = 1;
			unsigned int fullCount = 0;

			//for each pin
			for (unsigned int p = 0; p < m_pinNum; ++p)
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
				m_gamestate = SOLVED;
			}
		}//end any pin end
	}
}
#pragma endregion