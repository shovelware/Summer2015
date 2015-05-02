#ifndef HANOI_H
#define HANOI_H

#include <Pin.hpp>

#include <vector>

using std::vector;

//Wrapper/controller class for Tower Of Hanoi game
//*Arbitrary numbers of disks and pins
//*Minimum move calculator
//Cyclical rules (Bi-directional)
//AI solving
//endPin || startPin >= pinNum [THIS MEANS NONE SPECIFIED]

class Hanoi{
private:
	const unsigned int m_minPins = 3, m_minDiscs = 2;
	unsigned int m_pinNum, m_discNum, m_startPin, m_endPin, m_moves;
	vector<Pin> m_pins;
	unsigned int m_pinSelected;
	unsigned int m_discHeld;

	//Game Functions
	void checkGameState();

	//State control
	enum m_gamestate_t { PIN, DISC, PLAYING, SOLVED };
	m_gamestate_t m_gamestate;

	//Game Setup functions
	void lockParameter();
	bool setNumPins(unsigned int numPins);
	bool setNumDiscs(unsigned int numDiscs);
	void setStartPin(unsigned int startPin);
	void setEndPin(unsigned int endPin);
public:
	Hanoi();

	//direction for movement
	enum direction_t { LEFT, UP, RIGHT, DOWN };

	//Accessors
	bool getPlaying() const;
	bool getSolved() const;
	unsigned int getPinNum() const;
	unsigned int getPinHeight() const;
	vector<Pin> getPins() const;
	char* getGameStateAsString() const;
	unsigned int getGameState() const;
	unsigned int getPinSelected() const;
	unsigned int getDiscHeld() const;

	//Game Functions
	bool reset();
	void updateParameters();
	unsigned int minimumMoves();
	bool moveDisc(unsigned int from, unsigned int dest);
	bool move(direction_t dir);

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	bool handleDisc(unsigned int pin);

	bool actionButton();


};

#endif