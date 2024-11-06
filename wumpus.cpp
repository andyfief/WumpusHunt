#include "wumpus.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: percept() const
** Description: Outputs wumpus percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Wumpus::percept() const{
    cout << "You smell a terrible stench." << endl;
}

/*********************************************************************
** Function: encounter() const
** Description: Outputs wumpus encounter message
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Wumpus::encounter() const{
    cout << "You've been eaten by the wumpus!" << endl;
}

/*********************************************************************
** Function: ~Wumpus()
** Description: Destructor for Wumpus event
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Wumpus::~Wumpus() {
    
}