#ifndef ROOM_H
#define ROOM_H 

#include "event.h"
#include "adventurer.h"

using namespace std;

//Room Interface
//Note: Each room may be empty or has an event (bat, gold, pit, or wumpus);
//		Use event polymorphically

class Room{

private: 
	bool hasevent;
    bool hasplayer;
    bool adjtoplayer;
    Adv* player;
    Event* event;
    int roomnumber;
    bool closed;

    // vector<Room> adjrooms; be careful with this infinite recusion IG

public:
    Room();
    ~Room();

    bool geteventtf() const;
    bool getPlayer() const;
    Event* getEvent() const;
    void setevent(Event* newEvent);
    void addplayer();
    void removeplayer();
    void set_closed();
    bool get_closed() const;


};

#endif