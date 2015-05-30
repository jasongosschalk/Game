#ifndef ASTEROID_H
#define ASTEROID_H

#include<iostream>
#include<vector>


/**@brief this class handles the asteroids: where they are on the screen and how long they are on the screen*/
class Asteroid
{
public:
    Asteroid(int x, int i) : currentX(x), currentY(i), oldX(0), oldY(0) {} //boolean true is default and set to false once put on board //i is sent from the initialization loop!
    virtual ~Asteroid() {std::cout<<"Asteroid destroyed"<<std::endl;}
    int returnX();
    int returnY();
    void setX(int newValue);
    void setY(int newValue);
    void setOldX(int newValue);
    void setOldY(int newValue);
    int returnOldX();
    int returnOldY();
    bool asteroidLife();
    Asteroid& operator++(); //prefix operator decrement overload
    Asteroid& operator--(); //prefix operator decrement overload
    bool ifAsteroidCollision(int x, int y);



private:
    int currentX;   //the current location
    int currentY;   //the current location
    int oldX;       //to delete old label
    int oldY;       //to delete old label
};

#endif // ASTEROID_H
