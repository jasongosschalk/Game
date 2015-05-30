#include "asteroid.h"


/**
    @brief returns the value of the current X coordinate, used to update the new value of the asteroid
    @return is the int of the new coordinate.*/
int Asteroid::returnX(){
    return currentX;
}

/**
    @brief returns the value of the current Y coordinate, used to update the new value of the asteroid
    @return is the int of the new coordinate.*/
int Asteroid::returnY(){
    return currentY;
}

/**
    @brief returns the value of the old X coordinate, used to clear the asteroid off of the grid
    @return is the int of the old coordinate.*/
int Asteroid::returnOldX(){
    return oldX;
}
/**
    @brief returns the value of the old Y coordinate, used to clear the asteroid off of the grid
    @return is the int of the old coordinate.*/
int Asteroid::returnOldY(){
    return oldY;
}
/**
    @brief this function resets the value of X so that the asteorid can be updated to a new location (this is the current X position)
    @param is the value of new Y coordinate
    @return is void.*/
void Asteroid::setX(int newValue){
    currentX = newValue;
}
/**
    @brief this function resets the value of Y so that the asteorid can be updated to a new location (this is the current Y position)
    @param is the value of new Y coordinate
    @return is void.*/
void Asteroid::setY(int newValue){
    currentY = newValue;
}

/**
    @brief this function resets the value of oldX so that the asteorid can be cleared off of the grid
    @param is the value of the old X value of the object
    @return is void.*/
void Asteroid::setOldX(int newValue){
    oldX = newValue;
}

/**
    @brief this function resets the value of oldY so that the asteorid can be cleared off of the grid
    @param is the value of the old Y value of the object
    @return is void.*/
void Asteroid::setOldY(int newValue){
    oldY = newValue;
}


/**
@brief prefix increment operator overload for the Asteroid class which only decrements the life
@param there are no parameters for the prefix increment operator by convention
@return is the Asteroid object that has been incremented, not a copy of the previously incremented*/
Asteroid& Asteroid::operator++(){
    ++currentY;
    return *this;
}
/**
@brief prefix decrement operator overload for the Asteroid class which only decrements the life
@param there are no parameters for the prefix decrement operator by convention
@return is the Asteroid object that has been decremented, not a copy of the previously decremented*/
Asteroid& Asteroid::operator--(){
    --currentY;
    return *this;
}

/**
    @brief this function returns true if a location is shared by the asteroid and the ship
    @param x is the x value of the ship
    @param y is the y value of the ship
    @return is a boolean value and is true if they are at the same point, false otherwise*/
bool Asteroid::ifAsteroidCollision(int x, int y){
    if(currentX == x && currentY == y){  //if the ship and asteroid share the exact same coordinates
        return true;
    }
    else return false;
}

