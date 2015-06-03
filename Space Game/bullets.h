#ifndef BULLETS_H
#define BULLETS_H
#include "boardobject.h"
//vector included in asteroid.h

/**
    @class Bullets
    @brief this class is used to show a bullet on the screen and inherets from the boardObject class.*/
class Bullets : public BoardObject {
public:
    Bullets(size_t x, size_t i) :  BoardObject(x,i) { }    //default constructor automatically constructs the asteroid object which is a misnormer for item on board

    virtual ~Bullets() {std::cout<<"Bullet deleted"<<std::endl;}
    bool ifBulletCollision(int x, int y);



private:

};

#endif // BULLETS_H

