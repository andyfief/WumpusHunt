#include "passage.h"
#include "room.h"
#include "game.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: percept() const
** Description: Outputs passage percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Passage::percept() const{
    cout << "You feel a breeze." << endl;
}

/*********************************************************************
** Function: enocunter() const
** Description: Outputs passage encounter message
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


void Passage::encounter() const{
    cout << "You entered the secret passage!" << endl;
}

/*********************************************************************
** Function: ~Passage()
** Description: Passage object destructor
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Passage::~Passage() {
   
}