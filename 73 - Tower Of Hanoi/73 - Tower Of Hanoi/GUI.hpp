#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>

#include "Hanoi.hpp"

using sf::Vector2i;
using sf::Color;
using sf::RectangleShape;

#include <iostream>
using std::cout;
using std::endl;

struct xywh{
public:
	unsigned int const x, y, w, h;
	xywh(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : x(x), y(y), w(w), h(h) {}
};

class GUI{
private:
	//Scaling values
	unsigned int m_scale, m_width, m_height;
	bool updateBounds;

	//Colour information
	Color m_cbase, m_cpin, m_cdisc,
		m_chover, m_cselect, m_cstart, m_cend;

	//Different layouts to be approached later
	enum layout_t {LINEAR, POLYGON};
	layout_t m_currentLayout = LINEAR;

	//Rectangle drawing types and conditions
	enum rectType_t {DEFAULT, HIGHLIGHT, SELECT, GHOST};
	enum rectDrawOn_t {ALWAYS, HOVER, CLICK};

	//Mouse variables
	Vector2i m_mousePos;
	bool m_curClickL, m_prvClickL;

	//Drawing toggles
	bool m_drawBase, m_drawPins, m_drawDisc;

	//Single rectangle for drawing
	RectangleShape m_drawRect;

	//Drawing functions
	//void calcBase(Hanoi const& g);
	//void calcPin(Pin const& p);
	//void calcDisc(Disc const& d);
	//Color lighten(Color const& c);
	//Color darken(Color const& c);
	bool mouseOverRect(RectangleShape rect) const;
	int outline() const;


public:
	GUI();

	//Setup colours
	void colpls();

	//Accessors
	void setScale(unsigned int scale);
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setBase(bool base);
	void setPins(bool pins);
	void setDisc(bool disc);

	//Drawing functions
	RectangleShape& updateRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color &const c, rectType_t rectType, rectDrawOn_t drawOn);
	void drawGame(sf::RenderWindow& const w, Hanoi const& game);
	void drawGUI(sf::RenderWindow& const w, Hanoi const& game);
};
#endif