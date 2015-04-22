#include "Pin.hpp"

#pragma region Ctor
Pin::Pin() : m_height(6){}
Pin::Pin(unsigned int height) : m_height(height) {}
#pragma endregion

#pragma region Accessors (Basic)
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
#pragma endregion

#pragma region Accessors (Basic)

//Returns a pointer to the top disc, or null if none available
const Disc* Pin::getTop() const
{
	if (m_stack.size() > 0)
	{
		//Const ptr for returning
		const Disc* retPtr = &(m_stack.top());
		return retPtr;
	}

	else return nullptr;
}

//returns a copy of the stack for drawing purposes
stack<Disc> Pin::getStack() const
{
	return stack<Disc>(m_stack);
}

#pragma endregion

#pragma region Container Operations

//attempts to push to stack
bool Pin::push(Disc d)
{
	if (m_stack.size() >= m_height)
	{
		return false;
	}

	else
	{
		m_stack.push(d);
		return true;
	}
}

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

#pragma endregion