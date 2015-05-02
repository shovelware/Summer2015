#ifndef PIN_H
#define PIN_H

#include <Disc.hpp>
#include <stack>
using std::stack;

class Pin{
private:
	Pin();
	stack<Disc> m_stack;
	unsigned int m_height;

public:
	Pin(unsigned int const& height);

	//Accessors
	bool empty() const;
	bool full() const;
	int size() const;
	int capacity() const;
	Disc top() const;
	stack<Disc> getStack() const;

	//Container operations
	bool push(Disc d);
	Disc pop();
	void resize(unsigned int const& height);
	void clear();
};

#endif