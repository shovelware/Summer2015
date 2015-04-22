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
	unsigned int m_pinNum, m_pinHeight;
	vector<Pin> m_pins;
	GameClock m_clock;

public:
	Hanoi();
	Hanoi(unsigned int const &numPins, unsigned int const &pinHeight);

	void draw();
	bool move(int from, int dest);

	void getNumPins();

	void reset();
	void updateGameState();
	unsigned int randomPin();

};

#endif