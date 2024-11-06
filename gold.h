#ifndef GOLD_H
#define GOLD_H 
#include "event.h"
//Gold Interface

class Gold : public Event {

public:
    void percept() const override;
    void encounter() const override;
    ~Gold() override;



};






#endif