#ifndef DOCUMENTATION
#define DOCUMENTATION

/**
    @mainpage PIC10C Qt game: Astronomical Political Destruction
    @author Jason Gosschalk
    @date June 2015
    @version 1.0
    @brief this is the documentation file for the Game.pro Qt program
    @section label_introduction This game is based on the idea that politicians are ruining the world which is probably pretty accurate.  The
            asteroids and bullets are the "debris" that the player must avoid in order to survive.  Every time there is a collision with an object, the user loses
            a life.  There are small letters that will be moving down the screen, when visible, the user needs to click the letter on the keyboard.  When all of
            those letters have been collected, the game gets more difficult (asteroids, bullets speed up)>  Every time the level increments, the user gets their lives
            refreshed.
    @section label_difficulties There were some major revelations had during the making of this game.  Useful resources that can be pulled from this game include:
            the ability to lose the game and return to the main screen.  Another difficulty was the refreshing methods -- instead of putting things into the
            paintEvent() function, which can cause a recursive error, that code needs to be put in another function that calls paintEvent() to repaint the screen.
            Another important thing is the incrementation of the game, which I tried to create a new object but then realized it was only possible to update what already existed.
    @section label_conclusion This game probably looks simple but actual tears went in to fixing errors that caused it to crash and not be the worst game ever.  If anyone can actually
            win this game, I will be amazed.
    */
#endif // DOCUMENTATION

