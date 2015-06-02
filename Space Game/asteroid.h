#ifndef ASTEROID
#define ASTEROID

#include"boardobject.h"

class Asteroid : public BoardObject {
public:
    Asteroid(int x, int i) : BoardObject(x,i) {}    //default constructor automatically constructs the asteroid object which is a misnormer for item on board

    virtual ~Asteroid() {std::cout<<"Asteroid deleted"<<std::endl;}
   bool ifAsteroidCollision(int x, int y);



private:
    //BoardObject *asteroid;

};
#endif // ASTEROID

