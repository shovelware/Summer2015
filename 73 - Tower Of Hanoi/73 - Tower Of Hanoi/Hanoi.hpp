#ifndef HANOI_H
#define HANOI_H

#include "GameClock.hpp"
#include "Pin.hpp"

#include <vector>

using std::vector;

//Wrapper/controller class for Tower Of Hanoi game
//Arbitrary numbers of disks and pins
//Minimum move calculator
//Cyclical rules (Bi-directional)
//AI solving

//Minimum moves is 2^n-1 where n is number of disks

class Hanoi{
private:
	unsigned int m_pinNum, m_discNum, m_startPin, m_endPin;
	bool m_solved;
	vector<Pin> m_pins;
public:
	Hanoi(unsigned int const& discNum, unsigned int const& pinNum, unsigned int const& startPin, unsigned int const& endPin);

	//Accessors
	unsigned int getNumPins() const;
	bool getSolved() const;

	//Game Functions
	void reset();
	bool move(unsigned int const& from, unsigned int const& dest);
	void updateGameState();
};

#endif