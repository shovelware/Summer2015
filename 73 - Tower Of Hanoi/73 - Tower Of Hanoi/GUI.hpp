#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>

#include <Hanoi.hpp>

using sf::Vector2i;
using sf::Color;
using sf::RectangleShape;

//debug output
#include <iostream>
using std::cout;
using std::endl;

//rect bounds class?
struct UIntRect{
	unsigned int m_x, m_y, m_w, m_h;
public:
	unsigned int const& x = m_x, const& y = m_y, const& w = m_w, const& h = m_h;
	UIntRect() : m_x(0), m_y(0), m_w(0), m_h(0) {}
	UIntRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : m_x(x), m_y(y), m_w(w), m_h(h) {}
	UIntRect(UIntRect const& that) : m_x(that.x), m_y(that.y), m_w(that.w), m_h(that.h) {}
	UIntRect& operator=(UIntRect const& that)
	{
		if (this != &that)
		{
			m_x = that.x;
			m_y = that.y;
			m_w = that.w;
			m_h = that.h;
		}
		return *this;
	}

	bool operator !=(UIntRect const& that) { return (m_x != that.x && m_y != that.y && m_w != that.w && m_h != that.h); }
	bool operator ==(UIntRect const& that) { return (m_x == that.x && m_y == that.y && m_w == that.w &&m_h == that.h); }
};

class GUI{
private:
	//Scaling values
	unsigned int m_scale, m_width, m_height;
	int m_outline;
	bool m_updateBounds;

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
	//Color lighten(Color const& c);
	//Color darken(Color const& c);
	void colpls();
	bool mouseOverRect(RectangleShape rect) const;
	void calcOutline();
	UIntRect calcBase(unsigned int winHeight, unsigned int pinNum, unsigned int pinHeight);
	UIntRect calcPin(unsigned int winHeight, unsigned int pinNum, unsigned int pinHeight, unsigned int pinIndex);
	RectangleShape& updateRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color &const c, rectType_t rectType, rectDrawOn_t drawOn);
	RectangleShape& updateRect(UIntRect rect, Color &const c, rectType_t rectType, rectDrawOn_t drawOn);
	RectangleShape& processRect(Color &const c, rectType_t rectType, rectDrawOn_t drawOn);



public:
	GUI();

	//Settings (should be privatised later)
	bool m_mouseControl;
	bool m_debug;

	//Accessors
	void setScale(unsigned int scale);
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setBase(bool base);
	void setPins(bool pins);
	void setDisc(bool disc);

	//Drawing functions
	void drawGame(sf::RenderWindow& const w, Hanoi const& g);
	void drawGUI(sf::RenderWindow& const w, Hanoi const& game);
};
#endif