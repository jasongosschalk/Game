#ifndef ASTEROID
#define ASTEROID

#include"boardobject.h"
/**
    @class class Asteroid
    @brief this class is used to handle all objects that look like asteroids on the Board.
            It inherets from the boardObject class, and has little extra functionality.  It is used only for asteroids.*/
class Asteroid : public BoardObject {
public:
    Asteroid(int x, int i) : BoardObject(x,i) {}    //default constructor automatically constructs the asteroid object which is a misnormer for item on board

    virtual ~Asteroid() {std::cout<<"Asteroid deleted"<<std::endl;}
   bool ifAsteroidCollision(int x, int y);  //checks the collision of asteroid



private:
    //BoardObject *asteroid;

};
#endif // ASTEROID

