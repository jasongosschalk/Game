#ifndef ARTIFACTS
#define ARTIFACTS
#include"boardobject.h"

/**
    @class Artifacts
    @brief class that handles the letters that appear on the screen and are "artifacts." This class inherets from the "boardObject" class so it can be
            moved throughout the screen.*/
class Artifacts : public BoardObject{
public:
    Artifacts(int x, int y) : BoardObject(x,y), isGotten(false), isShowing(false) {}
    ~Artifacts() {}
    void setTrue();
    bool isTrue();
    char returnChar();
    void setLetter(char passed);
    void setIsShowing(bool option);
    bool informIsShowing();
private:
    bool isGotten;  //if the user got the artifact
    char letter;
    bool isShowing; //true if the object is on the screen.
};

#endif // ARTIFACTS

