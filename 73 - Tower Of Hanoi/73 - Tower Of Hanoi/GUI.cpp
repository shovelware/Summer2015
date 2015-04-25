#include "GUI.hpp"

#pragma region Ctor
GUI::GUI() : m_scale(8), m_curClickL(false), m_prvClickL(false), m_drawBase(true), m_drawPins(true), m_drawDisc(true), m_width(0), m_height(0), updateBounds(true) 
{
}
#pragma endregion

#pragma region Accessors
void GUI::setScale(unsigned int scale) 
{ 
	if (m_scale = scale > 0 ? scale : m_scale)
	{
		updateBounds = true;
	}
}
unsigned int GUI::getWidth() const { return m_width; }
unsigned int GUI::getHeight() const { return m_height; }
void GUI::setBase(bool base) { m_drawBase = base; }
void GUI::setPins(bool pins) { m_drawPins = pins; }
void GUI::setDisc(bool disc) { m_drawDisc = disc; }

#pragma region Drawing functions
void GUI::colpls()
{
	m_cbase = Color(0, 32, 200);
	m_cpin = Color(128, 128, 128);
	m_cdisc = Color(0, 64, 0);

	m_chover = Color(250, 150, 50);
	m_cselect = Color(200, 200, 0);
	m_cstart = Color(0, 255, 255);
	m_cend = Color(255, 255, 255);
}

bool GUI::mouseOverRect(RectangleShape rect) const
{
	int mx = m_mousePos.x, my = m_mousePos.y;
	int rx = rect.getPosition().x, ry = rect.getPosition().y, rw = rect.getSize().x, rh = rect.getSize().y;

	//cout << "[" << rx << " < " << mx << " && " << mx << " <= " << rx + rw << " && " << ry << " < " << my << " && " << my << " <= " << ry + rh << "]" << endl;

	return ((rx < mx && mx <= rx + rw) && (ry < my && my <= ry + rh));
}

//updates parameters of drawing rectangle, also handles colour changes on hover
RectangleShape& GUI::updateRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color &const c, rectType_t rectType = GUI::rectType_t::DEFAULT, rectDrawOn_t drawOn = GUI::rectDrawOn_t::ALWAYS)
{
	//Update xywh
	m_drawRect.setPosition(sf::Vector2f(x, y));
	m_drawRect.setSize(sf::Vector2f(w, h));

	bool process = false;

	//Default rects just get drawn
		m_drawRect.setFillColor(c);
		m_drawRect.setOutlineThickness(0);

	if (rectType == DEFAULT);

	//ELSE (Not default), check our conditions
	else if (drawOn == ALWAYS)
	{
		process = true;
	}

	//More involved draw conditions
	else
	{
		//Hover detection
		if (drawOn == HOVER)
		{
			if (mouseOverRect(m_drawRect))
			{
				process = true;
			}
		}//End hover

		//Click detection
		if (drawOn == CLICK)
		{
			if (mouseOverRect(m_drawRect))
			{
				//Click detection for most
				process = m_curClickL;

				//Selectable rect gets special treatment: If we're only hovering, convert to highlight to indicate selectable
				if (rectType == SELECT && !m_curClickL)
				{
					rectType = HIGHLIGHT;
					process = true;
				}
			}
		}
	}//end draw conditions

	//Apply special draws
	if (process)
	{
		if (rectType == HIGHLIGHT)
		{
			m_drawRect.setFillColor(c);

			m_drawRect.setOutlineColor(m_chover);

			int outline = (m_scale / 8 + (m_scale != 2 ? m_scale % 2 : 1));
			
			m_drawRect.setOutlineThickness(-outline);
		}

		else if (rectType == SELECT)
		{
			m_drawRect.setFillColor(c);

			m_drawRect.setOutlineColor(m_cselect);

			int outline = (m_scale / 8 + (m_scale != 2 ? m_scale % 2 : 1));
			m_drawRect.setOutlineThickness(-outline);
		}

		else if (rectType == GHOST)
		{
			Color ghostCol(c);
			ghostCol.a = 128;
			m_drawRect.setFillColor(ghostCol);
		}
	}//end special draws

	return m_drawRect;
}

void GUI::drawGame(sf::RenderWindow& const w, Hanoi const& g)
{
	//update mouse Position and click prior to draw
	m_mousePos = sf::Mouse::getPosition(w);
	m_prvClickL = m_curClickL;
	m_curClickL = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	//grab vars from game
	unsigned int pinHeight = g.getPinHeight(), pinNum = g.getPinNum(), winW = w.getSize().x, winH = w.getSize().y;
	unsigned int& discNum = pinHeight;

	//Base (Plus filthy maths for it's xywh)

	if (m_drawBase)
	{
		w.draw(updateRect(
			m_scale,
			winH - (2 * m_scale),
			(((2 * pinNum) + 1) * m_scale) + (((pinNum * 2) * pinHeight) * m_scale),
			m_scale,
			m_cbase,
			GHOST,
			CLICK
			));

		//1u x border
		//1u y border
		//1u gap between pins, for pins. discNum units * 2 for each pin's discs
		//1u height
		//base colour
		//rect type
		//draw condition
	}//end base draw toggle

	//Pins
	vector<Pin> pins = g.getPins();

	for (int p = 0; p < pinNum; ++p)
	{
		if (m_drawPins)
		{
			w.draw(updateRect(
				(2 * m_scale) + (discNum * m_scale) + (p * ((2 * m_scale) + (2 * discNum * m_scale))),
				winH - (2 * m_scale) - pinHeight * m_scale,
				m_scale,
				pinHeight * m_scale,
				m_cpin,
				GHOST
				));

			//(1u x border + 1u base border) + (width of discs on left) + (index * (width of discs on right, gap, width of discs on left))
			//base y - pin height
			//1u width
			//pinHeight height
			//pin colour
			//rect type
			//draw condition

		}//end pin draw toggle

		//Discs
		if (!pins[p].empty())
		{
			//drawRect will be a pin at this point
			sf::Vector2f pinPos = m_drawRect.getPosition();

			if (m_drawDisc)
			{
				stack<Disc> discs = pins[p].getStack();
				unsigned int discIndex = discs.size();

				while (!discs.empty())
				{
					Disc drawDisc = discs.top();
					discs.pop();
					discIndex--;

					w.draw(updateRect(
						pinPos.x - (drawDisc.size() * m_scale),
						(pinPos.y + (pinHeight - 1) * m_scale) - (discIndex * m_scale),
						2 * (m_scale * drawDisc.size()) + m_scale,
						m_scale,
						m_cdisc,
						SELECT,
						CLICK
						));

					//pin position - half disc
					//pin top + height - 1u * index from bottom
					//2 * sides + 1u gap for pin
					//1u height
					//disc colour
					//rect type
					//draw condition

				}//end the pin's disc draw loop
			}//end disc draw toggle
		}//end disc draw check
	}//end pin draw loop

	if (updateBounds)
	{
		//base width + border
		m_width = (((2 * pinNum) + 1) * m_scale) + (((pinNum * 2) * pinHeight) * m_scale) + (2 * m_scale);
		//pin height + base height + border
		m_height = (pinHeight * m_scale) + m_scale * 3;
		updateBounds = false;
	}
}

void GUI::drawGUI(sf::RenderWindow& const w, Hanoi const& g)
{

}
#pragma endregion