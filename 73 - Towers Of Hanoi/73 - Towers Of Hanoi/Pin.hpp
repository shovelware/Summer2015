#ifndef PIN_H
#define PIN_H

#include "Disc.hpp"
#include <stack>
#include <iterator>

using std::iterator;
using std::stack;

class Pin{
private:
	stack<Disc> m_stack;
	unsigned int m_height;
public:
	Pin();
	Pin(unsigned int height);

	bool empty() const;
	bool full() const;
	int size() const;
	int capacity() const;

	const Disc* getTop() const;//
	stack<Disc> getStack() const;//


	bool push(Disc d);
	Disc pop();
	bool clear();
};

#endif