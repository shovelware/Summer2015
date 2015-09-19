#include <InputAction.hpp>

#pragma region Ctor
InputAction::InputAction() : m_response(false) {}

InputAction::InputAction(Key key) : m_response(false)
{
	addKey(key);
}

InputAction::InputAction(Key key, Key alt) : m_response(false)
{
	addKey(key);
	addKey(alt);
}

InputAction::InputAction(Key *keys) : m_response(false)
{
	int size = sizeof(keys) / sizeof(Key);

	for (int k = 0; k < size; ++k)
	{
		addKey(keys[k]);
	}
}
#pragma endregion

#pragma region Key Control
bool InputAction::addKey(Key key)
{
	return(m_keys.emplace(key, false)).second;
}

bool InputAction::removeKey(Key key)
{
	return (m_keys.erase(key) > 0);
}
#pragma endregion

#pragma region Accessors
bool InputAction::getResponse() const { return m_response; }

//overload dereference operator to get easy access to response
const bool InputAction::operator*() const { return m_response; }

#pragma endregion

#pragma region Update
void InputAction::update()
{
	m_response = false;

	for (Keymap::iterator kStart = m_keys.begin(), kIter = kStart, kEnd = m_keys.end(); kIter != kEnd; ++kIter)
	{
		if (sf::Keyboard::isKeyPressed(kIter->first))
		{
			//if it's just been pressed, take action and break
			if (!kIter->second)
			{
				m_response = true;
			}

			kIter->second = true;

			if (m_response) break;
		}

		else kIter->second = false;
	}
}
#pragma endregion