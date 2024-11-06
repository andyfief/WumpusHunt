#include "gold.h"
#include "room.h"
#include "game.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: percept() const
** Description: Outputs gold percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Gold::percept() const{
    cout << "You see a glimmer nearby." << endl;
}

/*********************************************************************
** Function: encounter() const
** Description: Outputs gold encounter message
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Gold::encounter() const{
    cout << "You picked up the gold!" << endl;
}

/*********************************************************************
** Function: ~Gold()
** Description: Gold object destructor
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Gold::~Gold() {
   
}