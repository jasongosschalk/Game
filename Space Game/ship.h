#ifndef SHIP_H
#define SHIP_H
#include"boardobject.h"

/**
    @class Ship
    @brief this class inherets from the BoardObject class.  It has all of the same functionality but is used only to display a ship.*/
class Ship : public BoardObject {
public:
    Ship(int x, int i) :  BoardObject(x,i) { }    //default constructor automatically constructs the asteroid object which is a misnormer for item on board
    virtual ~Ship() {std::cout<<"Ship deleted"<<std::endl;}
    //bool ifBulletCollision(int x, int y);



private:

};
#endif // SHIP

