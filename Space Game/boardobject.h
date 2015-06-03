#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#include<iostream>
#include<vector>


/**
    @class  this class handles the asteroids: where they are on the screen and how long they are on the screen
    @brief this class contains the code required for everything having to do with objects on the board, including their location.*/
class BoardObject
{
public:
    //BoardObject() : currentX(0), currentY(0), oldX(0), oldY(0) {};
    BoardObject(int x, int i) : currentX(x), currentY(i), oldX(0), oldY(0) {} //boolean true is default and set to false once put on board //i is sent from the initialization loop!
    virtual ~BoardObject() {std::cout<<"BoardObject destroyed"<<std::endl;}
    size_t returnX();
    size_t returnY();
    void setX(int newValue);
    void setY(int newValue);
    void setOldX(int newValue);
    void setOldY(int newValue);
    size_t returnOldX();
    size_t returnOldY();
    bool asteroidLife();
    BoardObject& operator++(); //prefix operator decrement overload
    BoardObject& operator--(); //prefix operator decrement overload
    bool ifBoardObjectCollision(size_t x, size_t y);



private:
    size_t currentX;   //the current location
    size_t currentY;   //the current location
    size_t oldX;       //to delete old label
    size_t oldY;       //to delete old label
};

#endif // ASTEROID_H
