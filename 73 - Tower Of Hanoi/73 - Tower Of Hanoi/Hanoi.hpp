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
	//Game variables
	const unsigned int 
		m_minPins = 3, m_minDiscs = 2,
		m_maxPins = 16, m_maxDiscs = 16;
	unsigned int 
		m_pinNum, m_discNum, 
		m_startPin, m_endPin,
		m_pinSelected, m_discHeld, 
		m_moves;
	vector<Pin> m_pins;

	//Game Functions
	void checkGameState();

	//State control
	enum m_gamestate_t { PIN, DISC, PLAYING, SOLVED };
	m_gamestate_t m_gamestate;

	//Input control
	enum m_input_t { ACTION, INDEX };
	m_input_t m_lastInput;

	//Game Setup functions
	void lockParameter();
	bool setNumPins(unsigned int numPins);
	bool setNumDiscs(unsigned int numDiscs);
	void setStartPin(unsigned int startPin);
	void setEndPin(unsigned int endPin);
public:
	Hanoi();

	//Accessors
	unsigned int getGameState() const;
	char* getGameStateAsString() const;
	unsigned int getMinimumMoves() const;
	unsigned int getMoves() const;
	unsigned int getPinNum() const;
	unsigned int getPinHeight() const;
	unsigned int getStartPin() const;
	unsigned int getEndPin() const;
	vector<Pin> getPins() const;
	unsigned int getPinSelected() const;
	unsigned int getDiscHeld() const;
	int getLastInput() const;

	//Game Functions
	bool reset();
	void updateParameters();

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	bool pickupDisc(unsigned int pin);
	bool putdownDisc(unsigned int pin);
	bool returnDisc();
	bool handleDisc();
	bool handleDisc(unsigned int pin);
	bool moveDisc(unsigned int from, unsigned int dest);

	bool actionButton();
};

#endif