#include "stalactites.h"

#include <iostream>

using namespace std;

//Stalactites Implementation

/*********************************************************************
** Function: percept() const
** Description: Outputs stalactite percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


void Stal::percept() const{
    cout << "You hear water dripping" << endl;
}

/*********************************************************************
** Function: encounter() const
** Description: Outputs stalactite encounter message, nothing.
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Stal::encounter() const{
    return;
}

/*********************************************************************
** Function: ~Stal()
** Description: Destructor for stalactite event
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Stal::~Stal() {
  
}