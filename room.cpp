#include "room.h"
using namespace std;

/*********************************************************************
** Function: Room()
** Description: Room constructor, initializes values
** Parameters:	
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

Room::Room() : hasevent(false), hasplayer(false), adjtoplayer(false), event(nullptr), roomnumber(-1) {}

/*********************************************************************
** Function: ~Room()
** Description: Room object destructor
** Parameters:	
** Pre-Conditions: Room object exists and leaves scope
** Post-Conditions:
*********************************************************************/

Room::~Room(){
    delete event;
    event = nullptr;
}

/*********************************************************************
** Function: geteventtf()
** Description: returns whether a room has an event
** Parameters:	
** Pre-Conditions: Room exists
** Post-Conditions:
*********************************************************************/

bool Room::geteventtf() const {
    return hasevent;
}

/*********************************************************************
** Function: setevent(Event* newEvent)
** Description: places a new event in a room
** Parameters:	Event object
** Pre-Conditions:	Event object exists
** Post-Conditions:
*********************************************************************/

void Room::setevent(Event* newEvent){
    event = newEvent;
    hasevent = true;
}

/*********************************************************************
** Function: getEvent()
** Description: returns the event that a room has
** Parameters:	
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/

Event* Room::getEvent() const {
    return event;
}

/*********************************************************************
** Function: addplayer()
** Description: sets a room's player value to true
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Room::addplayer(){
    hasplayer = true;
}

/*********************************************************************
** Function: removeplayer()
** Description: sets a room's player value to false
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Room::removeplayer(){
    hasplayer = false;
}

/*********************************************************************
** Function: getPlayer() const
** Description: returns whether a room has a player or not
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

bool Room::getPlayer() const {
    return hasplayer;
}

/*********************************************************************
** Function: set_closed()
** Description: sets a room's closed value to true
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

void Room::set_closed(){
    this->closed = true;
}

/*********************************************************************
** Function: get_closed()
** Description: returns a room's closed value
** Pre-Conditions:	
** Post-Conditions:
*********************************************************************/

bool Room::get_closed() const{
    return closed;
}
