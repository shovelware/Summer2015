#ifndef INPUTACTION_H
#define INPUTACTION_H

#include <SFML\Window\Keyboard.hpp>

using sf::Keyboard;

#include <map>
using std::map;

//typedef key since we can't use it, keymap for readability
typedef Keyboard::Key Key;
typedef map<Key, bool> Keymap;

//Input action class that raises flags when any keys are pressed
//usage: Add keys to vector, update, check for action (action is reset on update)

class InputAction{
private:
	Keymap m_keys;
	bool m_response;
public:
	InputAction();
	InputAction(Key key);
	InputAction(Key key, Key alt);
	InputAction(Key *keys);

	bool addKey(Key key);
	bool removeKey(Key key);
	
	bool getResponse() const;
	const bool operator*() const;

	void update();
};

#endif