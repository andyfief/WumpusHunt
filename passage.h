#ifndef PASSAGE_H
#define PASSAGE_H 
#include "event.h"

class Passage : public Event {

public:
    void percept() const override;
    void encounter() const override;
    ~Passage() override;

};






#endif