#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <iostream> 
#include "room.h"
#include "adventurer.h"

using namespace std;

class Game {
	
	private:
	
	vector<vector<Room>> grid;
	Adv p;

	int length; 			//length of the board
	int width;  			//width of the board
	int num_arrows; 		//keep track of number of errors remaining
	bool debug_view;		//debug mode or not
	int numbats;
	int numstals;
	int numwumpus;
	int numgold;
	int numpassage;
	bool wumpus_win;

	int passage1x;
	int passage1y;
	int passage2x;
	int passage2y;

public:

	Game();
	~Game();
	
	void set_up(int, int);
	void play_game(int, int, bool);
	void display_game(bool d) const;

	Adv& getAdv();

	bool check_win() const;
	bool check_lose() const;

	char get_dir();
	char get_input();
	void wumpus_move();
	void fire_arrow();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void move(char);

	void exepercepts();
	void exeencounter();
	
	int get_num_arrows() const;
	void set_num_arrows(int);
	
	bool get_wumpus_win() const;
	void set_wumpus_win();
	
	int get_length() const;
	int get_width() const;
	
	void close_room();

	int get_passage1x() const;
	int get_passage1y() const;
	int get_passage2x() const;
	int get_passage2y() const;
	void set_passage1x(int x);
	void set_passage1y(int y);
	void set_passage2x(int x);
	void set_passage2y(int y);

};
#endif