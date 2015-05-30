#include "bullets.h"


/**
    @brief this function returns true if a location is shared by the bullet and the ship
    @param x is the x value of the ship
    @param y is the y value of the ship
    @return is a boolean value and is true if they are at the same point, false otherwise*/
bool Bullets::ifBulletCollision(int x, int y){
    return ifBoardObjectCollision(x,y);
}
