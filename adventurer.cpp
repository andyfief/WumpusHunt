#include "adventurer.h"
#include <iostream>
using namespace std;

/*********************************************************************
** Function: Adv()
** Description: Adventurer object constructor. Intializes coordinates, hasgold to false, alive to true, and confused to 0.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


Adv::Adv() : confused(0), hasgold(false), startx(-1), starty(-1), nowx(-1), nowy(-1), alive(true){}

/*********************************************************************
** Function: ~Adv()
** Description: Adventurer object destructor
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Adv::~Adv(){

}

/*********************************************************************
** Function: setstartxy(int, int)
** Description: stores the player's starting coordinates
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::setstartxy(int x, int y){
    this->startx = x;
    this->starty = y;
}

/*********************************************************************
** Function: getstartx, getstarty
** Description: Returns the player's starting coordinates
** Parameters:	
** Pre-Conditions:	player has started playing the game and has starting coordinates.
** Post-Conditions:
*********************************************************************/


int Adv::getstartx() const {
return startx;
}

int Adv::getstarty() const {
return starty;
}

/*********************************************************************
** Function: setnowxy(int, int)
** Description: Updates the players current coordinates.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::setnowxy(int x, int y){
    this->nowx = x;
    this-> nowy = y;
}

/*********************************************************************
** Function: getnowx(), getnowy()
** Description: returns the player's current x and y values
** Parameters:	
** Pre-Conditions: Game has started, user at least is in their starting position
** Post-Conditions:
*********************************************************************/


int Adv::getnowx() const {
    return nowx;
}

int Adv::getnowy() const {
return nowy;
}

/*********************************************************************
** Function: pickupgold()
** Description: Sets the player's hasgold boolean to true
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


void Adv::pickupgold(){
    this->hasgold = true;
}

/*********************************************************************
** Function: getgoldtf() const
** Description: Checks whether the player has the gold.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

bool Adv::getgoldtf() const{
    return hasgold;
}

/*********************************************************************
** Function: setconfused5()
** Description: Sets the player's confusion turn cooldown to 5
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::setconfused5(){
    this->confused = 5;
}

/*********************************************************************
** Function: reduceconfused()
** Description: reduces the confused int/confused turn cooldown by 1
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::reduceconfused(){
    this->confused--;
}

/*********************************************************************
** Function: getconfused()
** Description: returns the players confused int value
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

int Adv::getconfused() const{
    return confused;
}

/*********************************************************************
** Function: setdead()
** Description: Sets the players's alive bool to false
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::setdead(){
    this->alive = false;
}
    
/*********************************************************************
** Function: getalive()
** Description: Returns the player's alive boolean
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

bool Adv::getalive() const{
    return alive;
}

/*********************************************************************
** Function: percept() const
** Description: Sets turnstoclose variable to t. Will make rooms close off after t amount of turns.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Adv::set_turnstoclose(int t){
    this->turnstoclose = t;
}

/*********************************************************************
** Function: get_turnstoclose() const
** Description: Returns remaining number of moves before a room is closed off.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


int Adv::get_turnstoclose() const{
    return turnstoclose;
}