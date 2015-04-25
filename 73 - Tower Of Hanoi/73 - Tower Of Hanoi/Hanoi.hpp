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
//endPin || startPin >= pinNum [THIS MEANS NONE SPECIFIED]

class Hanoi{
private:
	const unsigned int m_minPins = 3, m_minDiscs = 2;
	unsigned int m_pinNum, m_discNum, m_startPin, m_endPin, m_moves;
	vector<Pin> m_pins;

	//Game Functions
	void checkGameState();

	//State control
	enum gamestate_t { PIN, DISC, PLAYING, SOLVED };
	gamestate_t gamestate;

public:
	Hanoi();

	//Accessors
	unsigned int getPinNum() const;
	unsigned int getPinHeight() const;
	bool getSolved() const;
	vector<Pin> getPins() const;

	//Game Functions
	void updateParameters();
	unsigned int minimumMoves();
	bool move(unsigned int const& from, unsigned int const& dest);
	void lockParameter();
	bool getPlaying();


	void setNumPins(unsigned int const& numPins);
	void setNumDiscs(unsigned int const& numDiscs);
	void setStartPin(unsigned int const& startPin);
	void setEndPin(unsigned int const& endPin);
};

#endif