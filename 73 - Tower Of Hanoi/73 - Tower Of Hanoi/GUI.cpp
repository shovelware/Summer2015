#include <GUI.hpp>

#pragma region Ctor
GUI::GUI() : m_scale(8), m_curClickL(false), m_prvClickL(false), m_drawBase(true), m_drawPins(true), m_drawDisc(true), m_width(0), m_height(0), m_updateBounds(true), m_mouseControl(false)
{
	colpls();
}
#pragma endregion

#pragma region Accessors
void GUI::setScale(unsigned int scale) 
{ 
	if (m_scale = scale > 0 ? scale : m_scale)
	{
		m_updateBounds = true;
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

void GUI::calcOutline()
{
	m_outline = (m_scale / 8 + (m_scale > 8 ? m_scale % 2 : 1)); 
}

//returns a calculated rectangle for the base
UIntRect GUI::calcBase(unsigned int winHeight, unsigned int pinNum, unsigned int pinHeight)
{
	return UIntRect(
		m_scale,
		winHeight - (2 * m_scale),
		(((2 * pinNum) + 1) * m_scale) + (((pinNum * 2) * pinHeight) * m_scale),
		m_scale
		);
}

//returns a calculated rectangle for the pin at passed index
UIntRect GUI::calcPin(unsigned int winHeight, unsigned int pinNum, unsigned int pinHeight, unsigned int pinIndex)
{
	return UIntRect(
		(2 * m_scale) + (pinHeight * m_scale) + (pinIndex * ((2 * m_scale) + (2 * pinHeight * m_scale))),
		winHeight - (2 * m_scale) - pinHeight * m_scale /**/ - m_scale,
		m_scale,
		pinHeight * m_scale /**/ + m_scale
		);
}

//updates parameters of drawing rectangle, also handles special rules
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
			m_drawRect.setOutlineThickness(-m_outline);
		}

		else if (rectType == SELECT)
		{
			m_drawRect.setFillColor(c);
			m_drawRect.setOutlineColor(m_cselect);
			m_drawRect.setOutlineThickness(-m_outline);
		}

		else if (rectType == GHOST)
		{
			m_drawRect.setFillColor(Color(c.r, c.g, c.b, c.a / 2));
		}
	}//end special draws

	return m_drawRect;
}

//PUBLIC

void GUI::drawGame(sf::RenderWindow& const w, Hanoi const& g)
{
	//update mouse Position and click prior to draw
	//m_mousePos = sf::Mouse::getPosition(w);
	//m_prvClickL = m_curClickL;
	//m_curClickL = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	//grab vars from game
	unsigned int pinHeight = g.getPinHeight(), pinNum = g.getPinNum(), winW = w.getSize().x, winH = w.getSize().y, pinSelected = g.getPinSelected(), discHeld = g.getDiscHeld();
	bool discInHand = (g.getDiscHeld() < pinNum);

	//Temp rects for storing dimensions
	UIntRect rectBase(calcBase(winH, pinNum, pinHeight)), rectPin;
	unsigned int offset = winW / 2 - rectBase.w / 2;

	//Update game bounds if we've changed scale
	if (m_updateBounds)
	{
		//base width + border
		m_width = (((2 * pinNum) + 1) * m_scale) + (((pinNum * 2) * pinHeight) * m_scale) + (2 * m_scale);
		//pin height + base height(1) + border(2) + selected disc(2)
		m_height = (pinHeight * m_scale) + m_scale * 5;
		calcOutline();
		m_updateBounds = false;
	}

	//Base (Plus filthy maths for it's xywh)
	if (m_drawBase)
	{
		w.draw(updateRect(
			offset,
			rectBase.y,
			rectBase.w,
			rectBase.h,
			m_cbase
			));

		//1u x border
		//1u y border
		//1u gap between pins, for pins. discNum units * 2 for each pin's discs
		//1u height
		//base colour
		//rect type
		//draw condition
	}//end base draw toggle

	//rectBase = m_drawRect.getGlobalBounds();
	//Pins
	vector<Pin> pins = g.getPins();

	for (int p = 0; p < pinNum; ++p)
	{
		rectPin = calcPin(winH, pinNum, pinHeight, p);

		if (m_drawPins)
		{
			//draw each pin, with selected pin highlighted
			w.draw(updateRect(
				offset + rectPin.x,
				rectPin.y,
				rectPin.w,
				rectPin.h,
				m_cpin,
				(p == pinSelected ? SELECT : DEFAULT )
				));

			//(1u x border + 1u base border) + (width of discs on left) + (index * (width of discs on right, gap, width of discs on left))
			//base y - pin height
			//1u width
			//pinHeight height
			//pin colour
			//rect type
			//draw condition

		}//end pin draw toggle

		//Discs on Pin
		if (!pins[p].empty())
		{
			if (m_drawDisc)
			{
				stack<Disc> discs = pins[p].getStack();
				unsigned int discIndex = discs.size();

				rectType_t type = DEFAULT;

				//Decide draw type for top
				if (pinSelected == p)
				{
					type = HIGHLIGHT;
				}
				
				else if (discHeld == p)
				{
					type = GHOST;
				}
					
				//pin disc draw loop
				while (!discs.empty())
				{
					Disc drawDisc = discs.top();
					discs.pop();
					discIndex--;



					//Draw each disc, with selected pin's top disc highlighted
					w.draw(updateRect(
						offset + (rectPin.x - (drawDisc.size() * m_scale)),
						(rectPin.y + (pinHeight - 1) * m_scale) - (discIndex * m_scale),
						2 * (m_scale * drawDisc.size()) + m_scale,
						m_scale,
						m_cdisc,
						type
						));

					//pin position - half disc
					//pin top + height - 1u * index from bottom
					//2 * sides + 1u gap for pin
					//1u height
					//disc colour
					//rect type
					//draw condition

					//Top disc is first drawn, now we switch to hover for second if we're on this pin
					if (discHeld == p && pinSelected == p)
					{
						type = HIGHLIGHT;
					}

					//Otherwise we stick with normal
					else type = DEFAULT;

				}//end pin disc draw loop
			}//end pin disc draw toggle
		}//end pin empty check
	}//end pin draw loop

	//Held Disc draw
	if (m_drawDisc && discInHand)
	{
		UIntRect pinRect = calcPin(winH, pinNum, pinHeight, pinSelected);
		Disc drawDisc = g.getPins()[discHeld].getStack().top();

		w.draw(updateRect(
			offset + pinRect.x - (drawDisc.size() * m_scale),
			(pinRect.y - m_scale * 2),
			2 * (m_scale * drawDisc.size()) + m_scale,
			m_scale,
			m_cdisc,
			SELECT
			));

		//pin position - half disc
		//pin top + height - 1u * index from bottom
		//2 * sides + 1u gap for pin
		//1u height
		//disc colour
		//rect type
		//draw condition

	}//end held disc draw toggle

	//Debug drawing
	if (m_debug)
	{
		//Debug text
		cout
			<< "Game refreshed"
			<< " | State: "
			<< g.getGameStateAsString()
			<< " | Selected: "
			<< pinSelected
			<< " | Disc: "
			<< discHeld
			<< endl;
	}
}

void GUI::drawGUI(sf::RenderWindow& const w, Hanoi const& g)
{

}
#pragma endregion