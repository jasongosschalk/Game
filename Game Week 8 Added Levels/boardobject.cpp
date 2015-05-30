#include "boardobject.h"


/**
    @brief returns the value of the current X coordinate, used to update the new value of the asteroid
    @return is the int of the new coordinate.*/
size_t BoardObject::returnX(){
    return currentX;
}

/**
    @brief returns the value of the current Y coordinate, used to update the new value of the asteroid
    @return is the int of the new coordinate.*/
size_t BoardObject::returnY(){
    return currentY;
}

/**
    @brief returns the value of the old X coordinate, used to clear the asteroid off of the grid
    @return is the int of the old coordinate.*/
size_t BoardObject::returnOldX(){
    return oldX;
}
/**
    @brief returns the value of the old Y coordinate, used to clear the asteroid off of the grid
    @return is the int of the old coordinate.*/
size_t BoardObject::returnOldY(){
    return oldY;
}
/**
    @brief this function resets the value of X so that the asteorid can be updated to a new location (this is the current X position)
    @param is the value of new Y coordinate
    @return is void.*/
void BoardObject::setX(int newValue){
    currentX = newValue;
}
/**
    @brief this function resets the value of Y so that the asteorid can be updated to a new location (this is the current Y position)
    @param is the value of new Y coordinate
    @return is void.*/
void BoardObject::setY(int newValue){
    currentY = newValue;
}

/**
    @brief this function resets the value of oldX so that the asteorid can be cleared off of the grid
    @param is the value of the old X value of the object
    @return is void.*/
void BoardObject::setOldX(int newValue){
    oldX = newValue;
}

/**
    @brief this function resets the value of oldY so that the asteorid can be cleared off of the grid
    @param is the value of the old Y value of the object
    @return is void.*/
void BoardObject::setOldY(int newValue){
    oldY = newValue;
}


/**
@brief prefix increment operator overload for the Asteroid class which only decrements the life
@param there are no parameters for the prefix increment operator by convention
@return is the Asteroid object that has been incremented, not a copy of the previously incremented*/
BoardObject& BoardObject::operator++(){
    ++currentY;
    return *this;
}
/**
@brief prefix decrement operator overload for the Asteroid class which only decrements the life
@param there are no parameters for the prefix decrement operator by convention
@return is the Asteroid object that has been decremented, not a copy of the previously decremented*/
BoardObject& BoardObject::operator--(){
    --currentY;
    return *this;
}

/**
    @brief this function returns true if a location is shared by the asteroid and the ship
    @param x is the x value of the ship
    @param y is the y value of the ship
    @return is a boolean value and is true if they are at the same point, false otherwise*/
bool BoardObject::ifBoardObjectCollision(int x, int y){
    if(currentX == x && currentY == y){  //if the ship and asteroid share the exact same coordinates
        return true;
    }
    else return false;
}

