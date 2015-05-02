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

#include <Hanoi.hpp>
#include <GUI.hpp>
#include <InputAction.hpp>


#include <map>
using std::map;
enum buttonsName_t { LEFT, RIGHT, UP, DOWN, ACTION, SCALEUP, SCALEDOWN, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0 };
typedef map<buttonsName_t, InputAction> InputMap;

////////////////////////////////////////////////////////////
///Global Variables
//////////////////////////////////////////////////////////// 
const int g_screenW = 800;
const int g_screenH = 600;

const sf::Mouse g_mouse;
const sf::Keyboard g_keyboard;

Hanoi game;
GUI gui;
InputMap buttons;

////////////////////////////////////////////////////////////
///Functions
//////////////////////////////////////////////////////////// 

void registerInputs()
{
	//Left Arrow / A : Move Left
	buttons[LEFT] = InputAction(Keyboard::Left, Keyboard::A);

	//Right Arrow / D : Move Right
	buttons[RIGHT] = InputAction(Keyboard::Right, Keyboard::D);

	//Up Arrow / W : Move Up
	buttons[UP] = InputAction(Keyboard::Up, Keyboard::W);

	//Down Arrow / S : Move Left
	buttons[DOWN] = InputAction(Keyboard::Down, Keyboard::S);

	//Space : Lock Parameter / Pickup
	buttons[ACTION] = InputAction(Keyboard::Space);

	//Num Plus : Scale Up
	buttons[SCALEUP] = InputAction(Keyboard::Add);

	//Num Minus : Scale Down
	buttons[SCALEDOWN] = InputAction(Keyboard::Subtract);

	//Digits, Numpad : Pins
	buttons[NUM0] = InputAction(Keyboard::Num0, Keyboard::Numpad0);
	buttons[NUM1] = InputAction(Keyboard::Num1, Keyboard::Numpad1);
	buttons[NUM2] = InputAction(Keyboard::Num2, Keyboard::Numpad2);
	buttons[NUM3] = InputAction(Keyboard::Num3, Keyboard::Numpad3);
	buttons[NUM4] = InputAction(Keyboard::Num4, Keyboard::Numpad4);
	buttons[NUM5] = InputAction(Keyboard::Num5, Keyboard::Numpad5);
	buttons[NUM6] = InputAction(Keyboard::Num6, Keyboard::Numpad6);
	buttons[NUM7] = InputAction(Keyboard::Num7, Keyboard::Numpad7);
	buttons[NUM8] = InputAction(Keyboard::Num8, Keyboard::Numpad8);
	buttons[NUM9] = InputAction(Keyboard::Num9, Keyboard::Numpad9);
}

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
int main()
{

	gui.setScale(16);
	gui.m_debug = true;

	bool updateGUI = true;
	//game.actionButton();
	//game.moveUp();
	//game.moveUp();
	//game.moveUp();
	//game.actionButton();

	int minMoves = game.minimumMoves();
	bool solvedState = game.getSolved();

	registerInputs();

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
			if ((Event.type == sf::Event::KeyPressed) && ((Event.key.code == g_keyboard.Escape) || (Event.key.code == g_keyboard.BackSpace)/*Alt+F4 support here*/))
				window.close();
#pragma region Input
		//Update all keys
		for (InputMap::iterator mStart = buttons.begin(), mIter = mStart, mEnd = buttons.end(); mIter != mEnd; ++mIter)
		{
 			mIter->second.update();
		}

		//Check all keys, take actions
		if (*buttons[LEFT])			{ updateGUI = game.moveLeft(); }
		if (*buttons[RIGHT])		{ updateGUI = game.moveRight(); }
		if (*buttons[UP])			{ updateGUI = game.moveUp(); }
		if (*buttons[DOWN])			{ updateGUI = game.moveDown(); }
		if (*buttons[ACTION])		{ updateGUI = game.actionButton(); }
		
		if (*buttons[SCALEUP])		{ updateGUI = gui.setScale(gui.getScale() + 1); }
		if (*buttons[SCALEDOWN])	{ updateGUI = gui.setScale(gui.getScale() - 1); }
		
		if (*buttons[NUM0])			{ updateGUI = game.returnDisc(); }
		if (*buttons[NUM1])			{ updateGUI = game.handleDisc(0); }
		if (*buttons[NUM2])			{ updateGUI = game.handleDisc(1); }
		if (*buttons[NUM3])			{ updateGUI = game.handleDisc(2); }
		if (*buttons[NUM4])			{ updateGUI = game.handleDisc(3); }
		if (*buttons[NUM5])			{ updateGUI = game.handleDisc(4); }
		if (*buttons[NUM6])			{ updateGUI = game.handleDisc(5); }
		if (*buttons[NUM7])			{ updateGUI = game.handleDisc(6); }
		if (*buttons[NUM8])			{ updateGUI = game.handleDisc(7); }
		if (*buttons[NUM9])			{ updateGUI = game.handleDisc(8); }
#pragma endregion
		}
		


		// Draw loop
		if (updateGUI)
		{
			window.clear();
			gui.drawGame(window, game);
			window.display();
			updateGUI = false;
		}
	}

	return EXIT_SUCCESS;
}