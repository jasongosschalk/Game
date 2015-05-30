#include"artifacts.h"

/**
    @brief sets the value of the artifact to false if it was collected
    @return none*/
void Artifacts::setTrue(){
    isGotten = true;
    return;
}

/**
    @brief returns true if isGotten is true
    @return bool true if the object has been gotten*/
bool Artifacts::isTrue(){
    return isGotten;
}

char Artifacts::returnChar(){
    return letter;
}

void Artifacts::setLetter(char passed){
    letter = passed;
    return;
}
