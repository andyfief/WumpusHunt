#include "game.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"
#include "passage.h"
#include "adventurer.h"
#include <vector>
#include <iostream>

using namespace std;

/*********************************************************************
** Function: Game()
** Description: Game constructor
** Parameters:
** Pre-Conditions:
** Post-Conditions: Will initialize Game object with wumpus_win to false
*********************************************************************/

Game::Game() : wumpus_win(false){}

/*********************************************************************
** Function: ~Game()
** Description: Game destructor
** Parameters:
** Pre-Conditions:	Game object exists and goes out of scope
** Post-Conditions:
*********************************************************************/


Game::~Game(){
}

/*********************************************************************
** Function: getAdv()
** Description: returns player object in game class
** Parameters:
** Pre-Conditions: player object is initialized in class
** Post-Conditions:
*********************************************************************/


Adv& Game::getAdv(){
	return p;
}

/*********************************************************************
** Function: set_up()
** Description:	Sets up the entire game. Stores players starting coordiates.
				Randomly places events. initializes variables.
** Parameters: length and width inputted from user
** Pre-Conditions:	length and width are valid
** Post-Conditions:
*********************************************************************/


void Game::set_up(int l, int w){
	this->length = l;
	this->width = w;
	this->numbats = 0;
	this->numgold = 0;
	this->numstals = 0;
	this->numwumpus = 0;
	this->numpassage = 0;
	this->num_arrows = 3; 	//start with 3 arrows
	int roomx;
	int roomy;
	p.set_turnstoclose(5);
	// Create the game board: 2D vector of Room objects

	this->grid = vector<vector<Room>>(l, vector<Room>(w));
	// randomly insert events (2 bats, 2 stalactites, 1 wumpus, 1 gold)
	// into the board
	
	roomx = rand() % l;
	roomy = rand() % w;
	grid[roomx][roomy].addplayer();
	p.setstartxy(roomx, roomy);
	p.setnowxy(roomx, roomy);


	while (numbats < 2){					// places events while there arent the desired number of them
		roomx = rand() % l;
		roomy = rand() % w;
		if (grid[roomx][roomy].geteventtf() == false && grid[roomx][roomy].getPlayer() == false){
			Bat* batEvent = new Bat();
			grid[roomx][roomy].setevent(batEvent);
			numbats++;
		}
	}
	while (numstals < 2){
		roomx = rand() % l;
		roomy = rand() % w;
		if (grid[roomx][roomy].geteventtf() == false && grid[roomx][roomy].getPlayer() == false){
			Stal* stalEvent = new Stal();
			grid[roomx][roomy].setevent(stalEvent);
			numstals++;
		}
	}
	while (numwumpus < 1){
		roomx = rand() % l;
		roomy = rand() % w;
		if (grid[roomx][roomy].geteventtf() == false && grid[roomx][roomy].getPlayer() == false){
			Wumpus* wumpusEvent = new Wumpus();
			grid[roomx][roomy].setevent(wumpusEvent);
			numwumpus++;
		}
	}
	while (numgold < 1){
		roomx = rand() % l;
		roomy = rand() % w;
		if (grid[roomx][roomy].geteventtf() == false && grid[roomx][roomy].getPlayer() == false){
			Gold* goldEvent = new Gold();
			grid[roomx][roomy].setevent(goldEvent);
			numgold++;
		}
	}
	while (numpassage < 2){
		roomx = rand() % l;
		roomy = rand() % w;
		if (grid[roomx][roomy].geteventtf() == false && grid[roomx][roomy].getPlayer() == false){
			Passage* passageEvent = new Passage();
			grid[roomx][roomy].setevent(passageEvent);
			if (numpassage == 0){
				Game::set_passage1x(roomx);
				Game::set_passage1y(roomy);				// sets passage 1 coordinates if it is the first one places
			}
			if (numpassage == 1){
				Game::set_passage2x(roomx);				// sets passage 2 coordinates if it is the second one placed
				Game::set_passage2y(roomy);
			}
			numpassage++;
		}
	}
}

/*********************************************************************
** Function: display_game()
** Description: Displays the game board to the terminal. Checks for debugging mode, and displays characters accordingly.
				Player can see events such as bats and wumpus on the display when in debug mode.
				Note: Player can still see closed rooms without debug mode.

** Parameters:	bool debug
** Pre-Conditions:	bool debug is true or false, has been chosen by user
** Post-Conditions:
*********************************************************************/


void Game::display_game(bool d) const{
	cout << endl << endl;
	cout << "Arrows remaining: " << this->num_arrows << endl;
	
	string line = "";
	for (int i = 0; i < this->width + 1; ++i)
		line += "-----";
	for (int i = 0; i < this->length; ++i)
	{																// displays grid
		cout << line << endl;
		for (int j = 0; j < this->width; ++j)
		{
			if (!d) {
				if (grid[i][j].getPlayer() == true){
					cout << " *";
				}
				else if(grid[i][j].get_closed() == true){
					cout << " #";
				}
				else {
					cout << "  ";
				}
			}
			else {
				if(grid[i][j].getPlayer() == true){							// outputs respective characters based on present event
					cout << " *";
				}
				else if(grid[i][j].get_closed() == true){
					cout << " #";
				}
				else if(dynamic_cast<Stal*>(grid[i][j].getEvent())){
					cout << " S";
				}
				else if(dynamic_cast<Bat*>(grid[i][j].getEvent())){
					cout << " B";
				}
				else if(dynamic_cast<Wumpus*>(grid[i][j].getEvent())){
					cout << " W";
				}
				else if(dynamic_cast<Gold*>(grid[i][j].getEvent())){
					cout << " G";
				}
				else if(dynamic_cast<Passage*>(grid[i][j].getEvent())){
					cout << "{}";
				}
				else{
					cout << "  ";
				}
			}
	
			cout << "  ||";
		}
		cout << endl;
	}
	cout << line << endl;
}

/*********************************************************************
** Function: check_win()
** Description: Checks if the win condition has been met to end the game. Checks if the wumpus has been shot, and if
				the player has returned to their starting position with the gold.
** Parameters:	
** Pre-Conditions:	Player wins
** Post-Conditions:	
*********************************************************************/

bool Game::check_win() const{					// checks if player has gold and is at their starting position, or checks if wumpus_win is true
	if ((p.getgoldtf() == true && grid[p.getstartx()][p.getstarty()].getPlayer() == true) || Game::get_wumpus_win() == true){
		if(p.getgoldtf() == true){
			cout << "You returned the gold safely to the exit rope!" << endl;
		}
		cout << "You win!" << endl;
		return true;
	}
	return false;
}

/*********************************************************************
** Function: check_lose()
** Description: Checks if the loss condition has been met. Checks if the player dies using p.getalive()
** Parameters:	
** Pre-Conditions:	player object exists
** Post-Conditions:
*********************************************************************/

bool Game::check_lose() const{
	if (p.getalive() == false){
		cout << "You lose." << endl;
		return true;
	}
	return false;
}

/*********************************************************************
** Function: move_up ()
** Description: Moves the player up when prompted. Takes their current coordinates, adjusts them based on movement.
				Checks if the player is confused, and reverts movement if true. Sets new room hasplayer bool to true,
				sets old room hasplayer bool to false.
** Parameters:	
** Pre-Conditions:	player inputs move key
** Post-Conditions:
*********************************************************************/

void Game::move_up() {
	int currentx = p.getnowx();
	int currenty = p.getnowy();

	if (p.getconfused() == 0){
		if (currentx > 0){													// checks that user is within bounds
			if (grid[currentx - 1][currenty].get_closed() == false){		// checks that desired room isnt closed
				grid[currentx - 1][currenty].addplayer();					// adds player to desired room
				grid[currentx][currenty].removeplayer();					// removes player from previous room
				p.setnowxy(currentx - 1, currenty);							// updates player coordinates
				Game::exepercepts();										// execute percepts if any
				Game::exeencounter();										// execute encounters if any
				p.set_turnstoclose(p.get_turnstoclose() - 1);				// reduces turns until a room is closed
				Game::close_room();											// closes room if applicable
			}
			else {
				cout << "This room's roof has been caved in..." << endl;	// output when player tries to enter closed room
			}
		}
	}
	else if (p.getconfused() > 0){											// if the player is confused, reverse their inputs
		if (currentx < width -1){
			if (grid[currentx + 1][currenty].get_closed() == false){
				grid[currentx + 1][currenty].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx + 1, currenty);
				p.reduceconfused();
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}		
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	return;
}

/*********************************************************************
** Function: move_down ()
** Description: Moves the player down when prompted. Takes their current coordinates, adjusts them based on movement.
				Checks if the player is confused, and reverts movement if true. Sets new room hasplayer bool to true,
				sets old room hasplayer bool to false.
** Parameters:	
** Pre-Conditions:	player inputs move key
** Post-Conditions:
*********************************************************************/

void Game::move_down() {
	int currentx = p.getnowx();
	int currenty = p.getnowy();

	if (p.getconfused() == 0){
		if (currentx < width - 1){
			if (grid[currentx + 1][currenty].get_closed() == false){
				grid[currentx + 1][currenty].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx + 1, currenty);
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	else if (p.getconfused() > 0){
		if (currentx > 0){
			if (grid[currentx - 1][currenty].get_closed() == false){
				grid[currentx - 1][currenty].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx - 1, currenty);
				p.reduceconfused();
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	return;
}

/*********************************************************************
** Function: move_left()
** Description: Moves the player left when prompted. Takes their current coordinates, adjusts them based on movement.
				Checks if the player is confused, and reverts movement if true. Sets new room hasplayer bool to true,
				sets old room hasplayer bool to false.
** Parameters:	
** Pre-Conditions:	player inputs move key
** Post-Conditions:
*********************************************************************/

void Game::move_left() {
	int currentx = p.getnowx();
	int currenty = p.getnowy();

	if (p.getconfused() == 0){
		if (currenty > 0){
			if (grid[currentx][currenty - 1].get_closed() == false){
				grid[currentx][currenty - 1].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx, currenty - 1);
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	else if (p.getconfused() > 0){
		if (currenty < length - 1){
			if (grid[currentx][currenty + 1].get_closed() == false){
				grid[currentx][currenty + 1].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx, currenty + 1);
				p.reduceconfused();
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	return;
}

/*********************************************************************
** Function: move_right()
** Description: Moves the player right when prompted. Takes their current coordinates, adjusts them based on movement.
				Checks if the player is confused, and reverts movement if true. Sets new room hasplayer bool to true,
				sets old room hasplayer bool to false.
** Parameters:	
** Pre-Conditions:	player inputs move key
** Post-Conditions:
*********************************************************************/

void Game::move_right() {
	int currentx = p.getnowx();
	int currenty = p.getnowy();

	if (p.getconfused() == 0){
		if (currenty < length - 1){
			if (grid[currentx][currenty + 1].get_closed() == false){
				grid[currentx][currenty + 1].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx, currenty + 1);
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	else if (p.getconfused() > 0){
		if (currenty > 0){
			if (grid[currentx][currenty - 1].get_closed() == false){
				grid[currentx][currenty - 1].addplayer();
				grid[currentx][currenty].removeplayer();
				p.setnowxy(currentx, currenty - 1);
				p.reduceconfused();
				Game::exepercepts();
				Game::exeencounter();
				p.set_turnstoclose(p.get_turnstoclose() - 1);
				Game::close_room();
			}
			else {
				cout << "This room's roof has been caved in..." << endl;
			}
		}
	}
	return;
}

/*********************************************************************
** Function: exepercepts()
** Description: executes percepts each time the player moves. Checks adjascent rooms for events, and executes their respective function
				using polymorphism.
** Parameters:	
** Pre-Conditions:	Player moves
** Post-Conditions:	
*********************************************************************/

void Game::exepercepts(){
	int currentx = p.getnowx();
	int currenty = p.getnowy();
	
	if (currentx + 1 < length) {
        Event* event = grid[currentx + 1][currenty].getEvent();
        if (event) {
            event->percept();
        }
    }
    if (currentx - 1 >= 0) {
        Event* event = grid[currentx - 1][currenty].getEvent();
        if (event) {
            event->percept();
        }
    }
    if (currenty + 1 < width) {
        Event* event = grid[currentx][currenty + 1].getEvent();
        if (event) {
            event->percept();
        }
    }
    if (currenty - 1 >= 0) {
        Event* event = grid[currentx][currenty - 1].getEvent();
        if (event) {
            event->percept();
        }
    }
}

/*********************************************************************
** Function: exeencounter()
** Description: executes encounter functions. Checks to see if players position has an event,
				uses if statements to see which event it is if returned positive. Executes that
				event.
** Parameters:	
** Pre-Conditions:	Player moves
** Post-Conditions:
*********************************************************************/

void Game::exeencounter(){
	int currentx = p.getnowx();
	int currenty = p.getnowy();
    Event* event = grid[currentx][currenty].getEvent(); // gets event when player enters a room with an event
        if (event) {
            event->encounter();
			if (dynamic_cast<Gold*>(event)){			// uses if statements to find which event it is, executes encounters
				p.pickupgold();
				delete event;
				grid[currentx][currenty].setevent(nullptr);
				return;
			}
			if (dynamic_cast<Bat*>(event)){
				p.setconfused5();
			}
			if (dynamic_cast<Stal*>(event)){
				int fifty = rand() % 2;
    				if (fifty == 1){
						cout << "A stalactite fell on you." << endl;
        				p.setdead();
					}
					else {
						cout << "You dodged a falling spike!" << endl;
					}
			}
			if (dynamic_cast<Wumpus*>(event)){
				p.setdead();
			}
			if (dynamic_cast<Passage*>(event)){		// if the user enters passage 1, teleport to passage 2.
				if(currentx == Game::get_passage1x() && currenty == Game::get_passage1y()){
					grid[currentx][currenty].removeplayer();
					grid[Game::get_passage2x()][Game::get_passage2y()].addplayer();
					p.setnowxy(Game::get_passage2x(), Game::get_passage2y());
				}									// if user enters passage 2, teleport to passage 1
				if(currentx == Game::get_passage2x() && currenty == Game::get_passage2y()){
					grid[currentx][currenty].removeplayer();
					grid[Game::get_passage1x()][Game::get_passage1y()].addplayer();
					p.setnowxy(Game::get_passage1x(), Game::get_passage1y());
				}
			}
        }
    }

/*********************************************************************
** Function: get_dir()
** Description: gets desired direction of arrow from the user, prompts and waits for input. Returns direction.
** Parameters:	
** Pre-Conditions:	User wants to fire an arrow
** Post-Conditions:
*********************************************************************/

char Game::get_dir(){
	//get direction of arrow:
	char dir;
	cout << "Fire an arrow...." << endl;
	cout << "W-up" << endl;
	cout << "A-left" << endl;
	cout << "S-down" << endl;
	cout << "D-right" << endl;
	
	cout << "Enter direction: " << endl;
	cin >> dir;
	cin.ignore(256, '\n');

	while (dir != 'w' && dir != 'a' && dir != 's' && dir != 'd'){
		cin >> dir;
		cin.ignore(256, '\n');
	}
	

	return dir;
}

/*********************************************************************
** Function: wumpus_move()
** Description: Rolls a 75% chance to move the wumpus to any empty room on the grid when the player shoots and misses
				an arrow.
** Parameters:	
** Pre-Conditions:	Player shoots and misses an arrow.
** Post-Conditions:
*********************************************************************/

void Game::wumpus_move(){
    int chance = rand() % 4;
    if (chance != 0) {
        int wumpusX = -1;
        int wumpusY = -1;

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (dynamic_cast<Wumpus*>(grid[i][j].getEvent())) {		// loops through grid to find the wumpus
                    wumpusX = i;										// stores its coordinates
                    wumpusY = j;
                    break;
                }
            }
            if (wumpusX != -1) {
                break;
            }
        }

        if (wumpusX != -1) {
            while (true) {
                int newRoomX = rand() % length;
                int newRoomY = rand() % width;
                if (!grid[newRoomX][newRoomY].getPlayer() && !grid[newRoomX][newRoomY].getEvent()) { // If the random room is empty
                    grid[wumpusX][wumpusY].setevent(nullptr); // Clear old room
                    grid[newRoomX][newRoomY].setevent(new Wumpus()); // Move the Wumpus to the new empty room
                    break;
                }
            }
        }
    }
	return;
}

/*********************************************************************
** Function: get_num_arrows() const
** Description: returns number of arrows that the player has remaining.
** Parameters:	
** Pre-Conditions:	Game is set up
** Post-Conditions:
*********************************************************************/

int Game::get_num_arrows() const{
	return num_arrows;
}

/*********************************************************************
** Function: set_num_arrows()
** Description: updates Game object's arrow count
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Game::set_num_arrows(int numarrows){
	this->num_arrows = numarrows;
}

/*********************************************************************
** Function: Fire_arrow()
** Description: Shoots an arrow. Uses direction from get_dir. Takes players current coordinates, uses a loop
				of length 3 to travel through 3 rooms in desired direction. If arrow hits either a wall or the wumpus,
				respective action is taken. If nothing is hit by the end of the loop, output miss message.
** Parameters:	
** Pre-Conditions:	User enters direction to fire arrow
** Post-Conditions:
*********************************************************************/

void Game::fire_arrow(){
	char dir = get_dir();
	int currentx = p.getnowx();
	int currenty = p.getnowy();
	bool hitwumpus = false;
	for (int i = 0; i < 3; i++){
		switch (dir){
			case 'w':
				currentx--;
				break;
			case 's':
				currentx++;
				break;
			case 'a':
				currenty--;
				break;
			case 'd':
				currenty++;
				break;
		}
		if (currentx < 0 || currentx >= width || currenty < 0 || currenty >= length){
			cout << "Arrow bounces off of a wall..." << endl;
			break;
		}
		
		Event* event = grid[currentx][currenty].getEvent();
		if (dynamic_cast<Wumpus*>(event)){
			cout << "You pierced the Wumpus through the heart!" << endl;
			hitwumpus = true;
			Game::set_wumpus_win();
			break;
		}
	}
	if (hitwumpus == false) {
        cout << "Arrow missed the Wumpus." << endl;
		Game::wumpus_move();
    }

	return;

}

/*********************************************************************
** Function: get_wumpus_win() const
** Description: returns wumpus win boolean, which states if the player has killed the wumpus
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

bool Game::get_wumpus_win()const{
	return wumpus_win;
}

/*********************************************************************
** Function: set_wumpus_win()
** Description: Sets the wumpus_win() boolean to true
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Game::set_wumpus_win(){
	this->wumpus_win = true;
}

/*********************************************************************
** Function: move(char)
** Description: Takes user imput, wasd or f, and outputs respectively. Executes fire arrow function for f and move_(direction)
				functions for wasd.
** Parameters:	character inputted from user
** Pre-Conditions:	user inputs character
** Post-Conditions:
*********************************************************************/

void Game::move(char c) {
	
	if (c == 'f'){
		if (Game::get_num_arrows() > 0){							// checks that user has arrows
			Game::fire_arrow();
			Game::set_num_arrows(Game::get_num_arrows() - 1);		// reduces arrow by 1 after shooting
		}
		else {
			cout << "Out of arrows!" << endl;
		}
		return;
	}
	switch(c){
		case 'w':
			Game::move_up();
			break;
		case 'a':
			Game::move_left();
			break;
		case 's':
			Game::move_down();
			break;
		case 'd':
			Game::move_right();
			break;
	}
}

/*********************************************************************
** Function: get_input()
** Description: prompts user with input options for movement and returns input
** Parameters:	
** Pre-Conditions:	
** Post-Conditions: user inputs character 
*********************************************************************/

char Game::get_input(){
	char c;

	cout << endl << endl << "Player move..." << endl << endl;
	cout << "W-up" << endl;
	cout << "A-left" << endl;
	cout << "S-down" << endl;
	cout << "D-right" << endl;
	cout << "f-fire an arrow" << endl;

	cout << "Enter input: " << endl;
	cin >> c;
	cin.ignore(256, '\n');

	while (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 'f'){
		cin >> c;
		cin.ignore(256, '\n');
	}

	
	return c;
}

/*********************************************************************
** Function: play_game()
** Description: Launches the game from inside game.cpp. Sets up game, sets debug view, waits for win or loss
				Repeats display, input, and move until the game is won or lost.
** Parameters:	w, l, d - width, length, debug - all inputed from user in main
** Pre-Conditions:	user inputs parameters
** Post-Conditions:
*********************************************************************/

void Game::play_game(int w, int l, bool d){

	Game::set_up(w, l);

	this->debug_view = d;

	char input;

	while (Game::check_win() == false && Game::check_lose() == false){		// will run game while user hasnt won or lost
		
		Game::display_game(d);

		input = Game::get_input();

		Game::move(input);
	}
	return;
}

/*********************************************************************
** Function: get_length() const
** Description: returns the length of the game board
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

int Game::get_length() const{
	return length;
}

/*********************************************************************
** Function: get_width()
** Description: returns width of the game board
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

int Game::get_width() const{
	return width;
}

/*********************************************************************
** Function: close_room()
** Description: Closes one random room every five turns, whcih the player can no longer enter. Checks
				that the room is empty, and that it isnt the player's starting room. Resets 5 move counter
				after closing a room.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Game::close_room(){
	while (p.get_turnstoclose() == 0){
		int randx = rand() % Game::get_length();
		int randy = rand() % Game::get_width();  	// checks if room has player, event, and that it isnt the starting pos
		if (!grid[randx][randy].getPlayer() && !grid[randx][randy].getEvent() && (randx != p.getstartx() && randy !=p.getstarty())){
			grid[randx][randy].set_closed();
			p.set_turnstoclose(5);
			break;
		}
	}
}

/*********************************************************************
** Function: get_passagexy and set_passagexy
** Description: Sets and returns the coordinates for the two passage events to be used in the passage encounter.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


int Game::get_passage1x() const{
	return passage1x;
}
int Game::get_passage1y() const{
	return passage1y;
}
int Game::get_passage2x() const{
	return passage2x;
}
int Game::get_passage2y() const{
	return passage2y;
}
void Game::set_passage1x(int x){
	this->passage1x = x;
}
void Game::set_passage1y(int y){
	this->passage1y = y;
}
void Game::set_passage2x(int x){
	this->passage2x = x;
}
void Game::set_passage2y(int y){
	this ->passage2y = y;
}






