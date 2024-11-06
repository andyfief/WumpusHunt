#ifndef WUMPUS_H
#define WUMPUS_H 

#include "event.h"
//Wumpus Interface

class Wumpus : public Event {
    private:



    public:
    void percept() const override;
    void encounter() const override;
    ~Wumpus() override;



};


#endif