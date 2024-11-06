#ifndef ADVENTURER_H
#define ADVENTURER_H 

//Bats Interface
class Adv {

    private:
        int confused;
        int turnstoclose;
        bool hasgold;
        int startx;
        int starty;
        int nowx;
        int nowy;
        bool alive;

    public:
        Adv();
        ~Adv();
        void setconfused5();
        void reduceconfused();
        int getconfused() const;
        void setstartxy(int, int);
        int getstartx() const;
        int getstarty() const;
        void setnowxy(int, int);
        int getnowx() const;
        int getnowy() const;
        void pickupgold();
        bool getgoldtf() const;
        void setdead();
        bool getalive() const;
	    int get_turnstoclose() const;
        void set_turnstoclose(int t);

};

#endif