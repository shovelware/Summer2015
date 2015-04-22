#include <iostream>;
#include <sstream>;

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

//Collatz conjecture:
//Take any natural number n. If n is even, divide it by 2 to get n / 2. If n is odd, multiply it by 3 and add 1 to obtain 3n + 1. 
//Repeat the process (which has been called "Half Or Triple Plus One", or HOTPO) indefinitely. 
//The conjecture is that no matter what number you start with, you will always eventually reach 1. The property has also been called oneness.
//Takes a number, returns one collatz step later
unsigned int collatz(unsigned int input)
{
	unsigned int output = input;

	if (output % 2 == 0)
	{
		output /= 2;
	}

	else
	{
		output *= 3;
		output++;
	}

	return output;
}

//Process input string to check for numbers, returns 0 if no numbers
unsigned int parseInt(string input)
{
	unsigned int inputNum = 0; 
	stringstream(input) >> inputNum;
	return inputNum;
}

//cout a passed string safely
void output(string output)
{
	cout << output.c_str() << endl;
}

//cout a number
void output(unsigned int output)
{
	cout << output;
}

//Checks if input character is a carriage return or space
bool isButton(char input)
{
	if (input == '^G' || input == '\n' || input == ' ')
		return true;

	else return false;
}

unsigned int main()
{
	unsigned int m_curCollatz = 0;
	string m_input = "";
	bool m_exit = false;
	bool m_run = true;

	string str_request = "Please input a number.",

		str_complete = "Complete, result is 1.",

		str_stop = "Stop Collatz of this number? Enter/Space to cancel, all else to confirm.",
		str_stopped = "Collatz stopped.",

		str_exit = "Do you wish to exit? Input non-number to confirm.",
		str_exiting = "Exit...";

	while (m_run)
	{
		//Check for complete
		if (m_curCollatz == 1)
		{
			output(str_complete);
			m_curCollatz = 0;
		}
		
		//Ask for number
		else if (m_curCollatz == 0)
		{
			if (!m_exit)
				output(str_request);

			//Input number
			getline(cin, m_input);
			m_curCollatz = parseInt(m_input);

			//If it's still zero = junk input = infer as exit
			if (m_curCollatz == 0)
			{
				if (!m_exit)
				{
					output(str_exit);
					m_exit = true;
				}

				else
				{
					output(str_exiting);
					m_run = false;
				}
			}
		}

		//Otherwise we're in the process
		else
		{
			m_exit = false;

			//Enter or space to collatz
			if (isButton(cin.get()))
			{
				m_curCollatz = collatz(m_curCollatz);

				if (m_curCollatz != 1)
					output(m_curCollatz);
			}

			//Input to init stop
			else
			{
				output(str_stop);

				//Input again to stop or enter/space to continue collatz
				if (!isButton(cin.get()))
					m_curCollatz = 0;
			}
		}
	}
	
	return 0;
}