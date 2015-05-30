#ifndef ARTIFACTS
#define ARTIFACTS
#include"boardobject.h"
class Artifacts : public BoardObject{
public:
    Artifacts(int x, int y) : BoardObject(x,y), isGotten(false), isShowing(false) {}
    ~Artifacts() {}
    void setTrue();
    bool isTrue();
    char returnChar();
    void setLetter(char passed);
private:
    bool isGotten;  //if the user got the artifact
    char letter;
    bool isShowing; //true if the object is on the screen.
};

#endif // ARTIFACTS

