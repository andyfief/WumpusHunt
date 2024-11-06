#include "bats.h"
#include <iostream>
using namespace std;

/*********************************************************************
** Function: percept() const
** Description: Outputs bat percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Bat::percept() const{
    cout << "You hear wings flapping." << endl;
}

/*********************************************************************
** Function: encounter() const
** Description: Outputs bat percept
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Bat::encounter() const{
    cout << "You've been confused by Super Bats!" << endl;
}

/*********************************************************************
** Function: ~Bat()
** Description: Bat object destructor
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/


Bat::~Bat(){
    
}