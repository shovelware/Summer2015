#include <Pin.hpp>

#pragma region Ctor
Pin::Pin(unsigned int const& height) : m_height(height) {}
#pragma endregion

#pragma region Accessors
//returns stack empty state
bool Pin::empty() const
{
	return (m_stack.size() == 0);
}

//returns stack full state
bool Pin::full() const
{
	return (m_stack.size() >= m_height);
}

//returns the size of the stack
int Pin::size() const
{
	return m_stack.size();
}

//returns the max size of the stack
int Pin::capacity() const
{
	return m_height;
}

//Returns a copy of the top disc, or max if pin is empty
Disc Pin::top() const
{
	if (m_stack.size() <= 0)
		return Disc(UINT_MAX);

	else return Disc(m_stack.top());
}

//returns a copy of the stack
stack<Disc> Pin::getStack() const
{
	return stack<Disc>(m_stack);
}
#pragma endregion

#pragma region Container Operations
//attempts to push to stack, returns success
bool Pin::push(Disc d)
{
	//if we're full or bad disc, no go
	if (m_stack.size() >= m_height || d == 0)
	{
		return false;
	}

	//otherwise go
	else
	{
		m_stack.push(d);
		return true;
	}
}

//returns top disc popped from stack
Disc Pin::pop()
{
	if (m_stack.size() > 0)
	{
		Disc retDisc = m_stack.top();
		m_stack.pop();
		return retDisc;
	}

	else
	{
		return 0;
	}
}

//Changes the height value of pin 
void Pin::resize(unsigned int const& height)
{
	m_height = height > 0 ? height : m_height;
}

void Pin::clear()
{
	m_stack = stack<Disc>();
}

#pragma endregion