#ifndef EVENT_H
#define EVENT_H 

using namespace std;

//Event Interface
//Note: this must be an abstract class!

class Event
{

protected:
	// random number function

public:
	virtual void percept() const = 0;
	virtual void encounter() const = 0;
	virtual ~Event();

};
#endif