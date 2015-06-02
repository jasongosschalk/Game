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
    @return bool true if the object has been gotten
*/
bool Artifacts::isTrue(){
    return isGotten;
}

/**
    @brief returns the char of that element
    @return letter is the stored private variable
*/
char Artifacts::returnChar(){
    return letter;
}

/**
    @brief sets the letter (private variable) to the passed char, which is random from the board.cpp file
    @param passed is the char to set letter (private variable) to
*/
void Artifacts::setLetter(char passed){
    letter = passed;
    return;
}
/**
    @brief this function sets the boolean value of the isShowing private variable and is used to determine whether the artifact is being shown
            or not.  this is used to determine at key press time whether the artifact can be collected.
    @param option is the boolean value to set the private variable isShowing to.
*/
void Artifacts::setIsShowing(bool option){
    isShowing = option;
    return;
}

/**
    @brief is used to determine whether an atifact is showing at the moment.  This is used to determine whether an artifact was collected while shown
            on the screen, to make sure users don't get to win by clicking the key when the artifact isn't on the screen.
    @return is boolean isShowing.
*/
bool Artifacts::informIsShowing(){
    return isShowing;
}
