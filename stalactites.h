#ifndef STALACTITES_H
#define STALACTITES_H 
#include "event.h"
//Stalactites Interface


class Stal : public Event{
    private:




    public:

    void percept() const override;
    void encounter() const override;
    ~Stal() override;

};



#endif
