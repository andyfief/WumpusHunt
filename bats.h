#ifndef BATS_H
#define BATS_H 
#include "event.h"
//Bats Interface
class Bat : public Event {
    private:

    public:
        void percept() const override;
        void encounter() const override;
        ~Bat() override;

};

#endif