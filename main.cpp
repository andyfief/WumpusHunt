#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

/*********************************************************************
** Program Filename: wumpushunt
** Author:	Andrew Fief
** Date:	11/28/2023
** Description:	A terminal game called hunt the wumpus. The goal is to raid the scary Wumpus' cave, steal their gold, and escape with
				your life. Or, try to shoot the wumpus with an arrow. Different obstacles litter the Wumpus' cave, so be careful!
** Input:	Movement directions, action choice, arrow direction.
** Output:	"Screen", or game interface, percepts for events, messages upon activating events, win/loss messages, prompts for inputs
*********************************************************************/


/*********************************************************************
** Function: main
** Description: run the program. Set random seed, ask for width and legnth of cave, ask for debug mode, run game with inputs
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/


int main()
{
	//set the random seed
	srand(time(NULL));
	
	int wid, len;
	bool debug;
	
	Game g;

	//get inputs: size of the cave(wid and len), and debug mode
	
	cout << "Enter width of cave: " << endl;
	cin >> wid;
	cout << "Enter length of cave: " << endl;
	cin >> len;
	cout << "Enter debug mode? 0: no, 1: yes" << endl;
	cin >> debug;

	//Play game
	g.play_game(wid, len, debug);


	return 0;
}