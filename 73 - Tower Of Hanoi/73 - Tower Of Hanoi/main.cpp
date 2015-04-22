//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <SFML/Graphics.hpp>

#include "Hanoi.hpp"

////////////////////////////////////////////////////////////
///Global Variables
//////////////////////////////////////////////////////////// 
const int g_screenW = 400;
const int g_screenH = 400;
const sf::Mouse g_mouse;
const sf::Keyboard g_keyboard;

bool GUI = false;
////////////////////////////////////////////////////////////
///Functions
//////////////////////////////////////////////////////////// 

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
int main()
{

	Hanoi game(2, 3, 0, 3);

	int foo = game.minimumMoves();

	game.move(0, 2);
	game.move(0, 1);
	game.move(2, 1);

	bool bar = game.getSolved();

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(g_screenW, g_screenH, 32), "Tower Of Hanoi");

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && ((Event.key.code == g_keyboard.Escape) ||(Event.key.code == g_keyboard.BackSpace)/*Alt+F4 support here*/))
				window.close();

		}

		//Input

		// Draw loop
		window.clear();

		window.display();

	}

	return EXIT_SUCCESS;
}