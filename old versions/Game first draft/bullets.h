#ifndef BULLETS_H
#define BULLETS_H
#include "asteroid.h"
//vector included in asteroid.h

class Bullets : public Asteroid {
public:
    Bullets(int x, int i) :  Asteroid(x,i) { }    //default constructor automatically constructs the asteroid object which is a misnormer for item on board

    virtual ~Bullets() {std::cout<<"Bullet deleted"<<std::endl;}
    bool ifBulletCollision(int x, int y);



private:

};

#endif // BULLETS_H

