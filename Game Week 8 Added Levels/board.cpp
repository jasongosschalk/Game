#include "board.h"
#include "mainwindow.h"
#include "ui_board.h"

//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//std::default_random_engine generator (seed);

Board::Board(QWidget *parent, size_t shipChoice, size_t difficulty) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    QWidget::setAttribute(Qt::WA_DeleteOnClose);    //deletes this object when close is called
    masterLayout = new QVBoxLayout; //sets the masterLayout to be inside the Master widget
                                    //removed master from the parenthesis
    whichCollision = 0; //default set to zero, not in constructor in case user doesn't support c++11
    whenToStart = 0;    //in case user constructor doesn;t support c++11
    numberEnemies = 0;  //this is so that if there are ever more enemies added, there will automatically be a bullet shot from them as long as the ++numberEnemies is added
    //create area where enemies go on top of game play area
    top = new QWidget;
    top->setFixedHeight(100);
    enemies = new QHBoxLayout(top);

    //input in the image of Hillary texting
    QLabel *hillaryLabel = new QLabel;
    hillaryLabel->setScaledContents(true);
    QPixmap hillary(":/images/hillary.bmp");
    hillaryLabel->setPixmap(hillary);
    ++numberEnemies;
    hillaryLabel->setFixedSize(130,100);
    enemies->addWidget(hillaryLabel);

    //input image of obama taking a selfie
    QLabel *obamaLabel = new QLabel;
    obamaLabel->setScaledContents(true);
    QPixmap obama(":/images/obama.bmp");
    obamaLabel->setPixmap(obama);
    ++numberEnemies;
    obamaLabel->setFixedSize(150,100);
    enemies->addWidget(obamaLabel);

    //input image of bush and his painting of a dog
    QLabel *bushLabel = new QLabel;
    bushLabel->setScaledContents(true);
    QPixmap bush(":/images/bush.bmp");
    bushLabel->setPixmap(bush);
    ++numberEnemies;
    bushLabel->setFixedSize(150,100);
    enemies->addWidget(bushLabel);

    //input image of fey and poehler on SNL
    QLabel *palinLabel = new QLabel;
    palinLabel->setScaledContents(true);
    QPixmap palin(":/images/palin.bmp");
    palinLabel->setPixmap(palin);
    palinLabel->setFixedSize(150,100);
    enemies->addWidget(palinLabel);
    ++numberEnemies;
    enemies->addStretch();
    enemies->setSpacing(0);

    //add a spacer to the right of the enemies to center the images
    QSpacerItem *enemiesRightSpacer = new QSpacerItem(20, 1);
    enemies->addSpacerItem(enemiesRightSpacer);

    //create the gameplay area
    middle = new QWidget;               //this layout will contain all of the asteroids and the ship
    middle->setFixedHeight(375);        //sets the fixed height of the central widget
    gameplay = new QGridLayout(middle); //creates a grid layout that we can put things into later based on lcation
    gameplay->setGeometry(QRect());     //makes the type of grid a rectangle grid
    gameplay->setSpacing(0);            //makes the spacing between the rectangles zero

    //create asteroids
    boardSize = 10;                                     //instructs to create a boardSize*BoardSize grid
    asteroid.load(":/images/asteroid.png");             //opens the image of the asteroid
    gamePlayLabel = new QLabel*[boardSize*boardSize];   //creates an array of labels


    //this loops fill in the grid layout for gameplay
    /*
     *  note the following style for accessing the position of a label to update it:
     *  to put a label in at  a certain point, then you set that widget = label[i*boardSize+j] where i is y and j is x
     * for example, to add something at the position 2,3 on a 10*10 grid layout, update the label at position label[3*10+2]
     */
    for(size_t i=0; i<boardSize; ++i){
        for(size_t j=0; j<boardSize; ++j){
            gamePlayLabel[i*boardSize+j] = new QLabel;  //creates all of the labels
            gameplay->addWidget(gamePlayLabel[i*boardSize+j], i, j);  //adds the empty label into the grid
        }
    }

     srand(time(NULL));    //random number generator

    //this loop places the asteroids in the appropriate place
    numberAsteroids = 7;    //change this to add more asteroid to the game

    for (int i=0, j=numberAsteroids; i<j; ++i){
        int number = rand() % 10; //was 20
        if(number == 0){
            number+= rand() % 5;    //so that it's not directly above the ship
        }
        //below code adds a new asteroid to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
        asteroidLocations.push_back(new Asteroid(number, i));
    }




    bullet.load(":/images/bullet.png");

    int number = rand() % 10; //was 20
    bulletLocations.push_back(new Bullets(number, 9));  //always start at top

    int asteroidTime = 0;
    int bulletTime = 0;
    if(difficulty == 1){    //if easy
        asteroidTime = 150;
        bulletTime = 150;
        //this sets up the vector of artifacts
        winGame = 4;
        for (int i=0, j=4; i<j; ++i){   //only need 4 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }
    else if(difficulty == 2){   //if medium difficulty
        asteroidTime = 100;
        bulletTime = 100;
        winGame = 6;
        for (int i=0, j=6; i<j; ++i){   //need 6 artifacts for medium
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }
    else{   //if hard
        asteroidTime = 50;
        bulletTime = 50;
        winGame = 10;
        for (int i=0, j=10; i<j; ++i){  //more difficult, need to collect 10 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }

    std::string randomLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(size_t i=0, j=artifacts.size(); i<j; ++i){
        int randNum = rand()%25;    //a random number between 0 and 25
        artifacts[i]->setLetter(randomLetters[randNum]);    //sets the private variable of artifact element equal to a letter in the alphabet
    }
    for(size_t i=0, j=artifacts.size(); i<j; ++i){
    std::cout<<artifacts[i]->returnChar()<<std::endl;    //sets the private variable of artifact element equal to a letter in the alphabet
    }
    check = artifacts.end();

    //create space junk and bullet timing, this area is controlled by difficulty choice
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAsteroids()));
    timer->start(asteroidTime);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateBullets()));
    timer2->start(bulletTime);

    artifactVisible = false;
    //timer for showing artifacts on screen
    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(showArtifact()));
    timer3->start(100);


    //create spaceship, this is dependent on user choice
    QString shipName;
    if(shipChoice == 1){
        shipName = ":/images/enterprise.png";
    }
    if(shipChoice == 2){
        shipName = ":/images/sagan.png";
    }
    shipPic.load(shipName);
    shipPosition = new Ship(0,9);
    //shipPosition->setX(0);
    //shipPosition->setY(9);
    int x = shipPosition->returnX();
    int y = shipPosition->returnY();

    gamePlayLabel[y*boardSize+x]->setPixmap(shipPic);
    gamePlayLabel[y*boardSize+x]->setScaledContents(true);
    gamePlayLabel[y*boardSize+x]->setFixedSize(50,50);

    //create bottom score area
    bottom = new QWidget;
    bottom->setFixedHeight(100);
    QGridLayout *bottomInfo = new QGridLayout(bottom);
    lives = new QLabel*[3];    //, a pointer of pointers or the loop doesnt work
    QPixmap heart(":/images/heart.png");
    QLabel *livesDescription = new QLabel;
    livesDescription->setText("<font size = 8><font color = white>Lives:</font>");
    bottomInfo->addWidget(livesDescription, 1, 1);
    lifeCount=0;    //initialization of int
    for (int i=0, j=3; i<j; ++i){
        lives[i] = new QLabel;
        lives[i]->setScaledContents(true);
        lives[i]->setPixmap(heart);
        lives[i]->setFixedSize(80, 80);
        bottomInfo->addWidget(lives[i], 1, i+2);
        ++lifeCount;
    }


    masterLayout->addWidget(top);
    masterLayout->addWidget(middle);
    masterLayout->addWidget(bottom);

    this->setFixedSize(600,600);
    this->setLayout(masterLayout);

}

Board::~Board()
{
    for (int i=0, j=numberAsteroids; i<j; ++i){
        delete asteroidLocations[i];   //adds a new asteroid to the vector
    }

    for (int i=0, j=bulletLocations.size(); i<j; ++i){
        delete bulletLocations[i];   //adds a new asteroid to the vector
    }

    for (int i=0, j=artifacts.size(); i<j; ++i){
        delete artifacts[i];
    }

    delete shipPosition;

    delete ui;

}

void Board::keyPressEvent(QKeyEvent *event){

    int x = shipPosition->returnX();
    int y = shipPosition->returnY();


    switch (event->key()) {
    case Qt::Key_A:{
        if((*check)->returnChar() == 'A'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_B:{
        if((*check)->returnChar() == 'B'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_C:{
        if((*check)->returnChar() == 'C'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_D:{
        if((*check)->returnChar() == 'D'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_E:{
        if((*check)->returnChar() == 'E'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_F:{
        if((*check)->returnChar() == 'F'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_G:{
        if((*check)->returnChar() == 'G'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_H:{
        if((*check)->returnChar() == 'H'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_I:{
        if((*check)->returnChar() == 'I'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_J:{
        if((*check)->returnChar() == 'J'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_K:{
        if((*check)->returnChar() == 'K'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_L:{
        if((*check)->returnChar() == 'L'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_M:{
        if((*check)->returnChar() == 'M'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_N:{
        if((*check)->returnChar() == 'N'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_O:{
        if((*check)->returnChar() == 'O'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_P:{
        if((*check)->returnChar() == 'P'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_Q:{
        if((*check)->returnChar() == 'Q'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_R:{
        if((*check)->returnChar() == 'R'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_S:{
        if((*check)->returnChar() == 'S'){
            --winGame;
            (*check)->setTrue();
        }
        break;
        }
    case Qt::Key_T:{
        if((*check)->returnChar() == 'T'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_U:{
        if((*check)->returnChar() == 'U'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_V:{
        if((*check)->returnChar() == 'V'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_W:{
        if((*check)->returnChar() == 'W'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_X:{
        if((*check)->returnChar() == 'X'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_Y:{
        if((*check)->returnChar() == 'Y'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }
    case Qt::Key_Z:{
        if((*check)->returnChar() == 'Z'){
            --winGame;
            (*check)->setTrue();
        }
        break;
    }


    case Qt::Key_Left:
        if(shipPosition->returnX() != 0)
            updateShip(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(shipPosition->returnX() != boardSize-1)
            updateShip(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(shipPosition->returnY() != 0)
            updateShip(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(shipPosition->returnY() != boardSize-1)
            updateShip(x,y,x,y+1);

        break;


    default:
        QWidget::keyPressEvent(event);
    }

    // Need both lines to force a repaint.

    // This line forces processor to process all previously promised events.


    // This one QUEUES up a repaint
    repaint();
    QCoreApplication::processEvents();

    return;
}

/**
    @brief this is an overload of the paintevent functionality in the Qt namespace, and updates the locatin of the Board Objects on the screen
            by changing where they appear on the grid layout.  Different numbers are used so that when paint event is called, it doesn't repaint everything
            again, just the thing that called it (hend why the whichPainEvent value is always reset to zero before the PaintEvent overload is exited.
    @param e is nothing, just required by overload definition of this function.*/
void Board::paintEvent(QPaintEvent *e) {
    std::cout<<"Paintevent"<<std::endl;
    if(whichPaintEvent == 2){       //paintevent was called by updateShip

        //update the ship location
        int x = shipPosition->returnX();
        int y = shipPosition->returnY();
        gamePlayLabel[y*boardSize+x]->setPixmap(shipPic);
        gamePlayLabel[y*boardSize+x]->setScaledContents(true);
        gamePlayLabel[y*boardSize+x]->setFixedSize(50,50);
        whichPaintEvent = 0;
    }
    //we don't want asteroids getting added before their time of proper initialization at game beginning!
    //paintevent gets called before it's time to initialize the asteroids, so this if statement protects placement errors
    //the syntax of this for loop is designed to prevent code repeats.  instead of having multiples of code to paint asteroids, this just only calls the code if it's time.

    if(whichPaintEvent == 1){   //paintevent was called by updateAsteroids
        if (whenToStart != 0){

            //update the asteroid positions via a standard for loop
            for(size_t i=0, j = asteroidLocations.size(); i<j; ++i) {
                int px = asteroidLocations[i]->returnX();
                int py = asteroidLocations[i]->returnY();
                int oldX = asteroidLocations[i]->returnOldX();
                int oldY = asteroidLocations[i]->returnOldY();


                gamePlayLabel[oldY*boardSize+oldX]->clear();
                gamePlayLabel[py*boardSize+px]->setPixmap(asteroid);
                gamePlayLabel[py*boardSize+px]->setScaledContents(true);
                gamePlayLabel[py*boardSize+px]->setFixedSize(60,60);
            }
        }
        whichPaintEvent = 0;
    }

    if(whichPaintEvent == 3){    //paint event was called by updateBullet

        for(size_t i=0, j = bulletLocations.size(); i<j; ++i) {
            int px = bulletLocations[i]->returnX();
            int py = bulletLocations[i]->returnY();
            int oldX = bulletLocations[i]->returnOldX();
            int oldY = bulletLocations[i]->returnOldY();

            gamePlayLabel[oldY*boardSize+oldX]->clear();
            gamePlayLabel[py*boardSize+px]->setPixmap(bullet);
            gamePlayLabel[py*boardSize+px]->setScaledContents(true);
            gamePlayLabel[py*boardSize+px]->setFixedSize(15,25);
        }
        whichPaintEvent = 0;
    }


    if(check != artifacts.end() && whichPaintEvent == 4){   //if there is an artifact to show
        if(winGame <= 0){
            this->close();
            QMessageBox winner;
            winner.setText("You won!");
            winner.exec();
        }

        QChar theChar = (*check)->returnChar(); //creates a Qt character with the letter from the object of choice
        //artifactString->setText(theChar);   //sets the label to add to the char of choice

        //reset the board to move the object down
        int px = (*check)->returnX();
        int py = (*check)->returnY();
        int oldX = (*check)->returnOldX();
        int oldY = (*check)->returnOldY();

        gamePlayLabel[oldY*boardSize+oldX]->clear();
        gamePlayLabel[oldY*boardSize+oldX]->setStyleSheet("background-color: rgba(0,0,0,0%)");
        gamePlayLabel[py*boardSize+px]->setText(theChar);
        gamePlayLabel[py*boardSize+px]->setTextFormat(Qt::RichText);
        gamePlayLabel[py*boardSize+px]->setStyleSheet("QLabel { background-color : white; color : blue; }");
        gamePlayLabel[py*boardSize+px]->setScaledContents(true);
        gamePlayLabel[py*boardSize+px]->setFixedSize(15,25);

    }


    return;
}

/**
    overload of the showevent command in the Qt namespace*/
void Board::showEvent(QShowEvent *e) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}



/**
    @brief this function updates the location of the asteroids and calls repaint to change the appearance on the screen.  If the asteroids are at the
            bottom of the screen, then there will be a random call to create a new x value and the asteroid will begin again at the top of the
            screen at a new *random* x value
    */
void Board::updateAsteroids() {
    std::cout<<"Update asteroids"<<std::endl;

    whenToStart = 1;  //indicates to paintEvent it is now  OK to update asteroid paint event

    for (int i=0, j=numberAsteroids; i<j; ++i){
        //or if the asteroid is out of lives, it is time to move it back to the top!

        if(asteroidLocations[i]->returnY() == 9){ //meaning it is back at the top of the widget
            //int numberY = rand() % 10;
            // (time(NULL));    //random number generator
            int numberX = rand() % 10;
            asteroidLocations[i]->setOldX(asteroidLocations[i]->returnX());
            asteroidLocations[i]->setOldY(asteroidLocations[i]->returnY());
            asteroidLocations[i]->setX(numberX);
            asteroidLocations[i]->setY(0);
        }
        else{  //if asteroid is in the middle of the gameplay area, not at Y=0
            asteroidLocations[i]->setOldX(asteroidLocations[i]->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
            asteroidLocations[i]->setOldY(asteroidLocations[i]->returnY()); //same as above
            ++(*asteroidLocations[i]); //increments the Y value of asteroid so that it gets repainted one lower
            //if(asteroidLocations[i]->returnY() == boardSize){   //if the asteroid is at the bottom of the screen (where y = boardSize since board is a square
              //  asteroidLocations[i]->setY(0); //reset the Y value to b zero so the asteroid get's painted again at the top of the screen
            //}
        }
    }

    if(checkAsteroidCollision()){//if the asteroid is in the same position as the ship
        updateLives();
        int x = shipPosition->returnX();
        int y = shipPosition->returnY();

        updateShip(x, y, x+1, y);
    }


    whichPaintEvent = 1;
    repaint();
    QCoreApplication::processEvents();
}

/**
    @brief this function updates the location of the ship with the keys are pressed and the keyevent function calls this.  repaint is needed
            to show the actual change on the screen.
    @param px is the old x
    @param py is the old y
    @param nx is the new x
    @param ny is the new y
    @return is none*/
void Board::updateShip(int px, int py, int nx, int ny) {
    std::cout<<"Update ship"<<std::endl;

    gamePlayLabel[py*boardSize+px]->clear();

    shipPosition->setOldX(shipPosition->returnX());
    shipPosition->setOldY(shipPosition->returnY());

    shipPosition->setX(nx);
    shipPosition->setY(ny);

    whichPaintEvent = 2;
    //checkCollision();


    repaint();
    QCoreApplication::processEvents();
//    return (px==nx)&&(py==ny);
}

/**
    @brief this function updates the location of the bullets and calls repaint to change where they appear on the screen.  the function deals
            with the BoardObject type object and randomly creates a new x position that the bullet should be in, if it has reached the top
            of the screen.  Otherwise, it increments upward the bullet's position until it gets to the top.
*/
void Board::updateBullets(){
    std::cout<<"Update bullets"<<std::endl;

    // (time(NULL));    //random number generator

    for (int i=0, j=bulletLocations.size(); i<j; ++i){
        //or if the asteroid is out of lives, it is time to move it back to the top!

        if(bulletLocations[i]->returnY() == 0){ //meaning it is back at the top of the widget
            int numeroX = rand() % 10;
            bulletLocations[i]->setOldX(bulletLocations[i]->returnX());
            bulletLocations[i]->setOldY(bulletLocations[i]->returnY());
            bulletLocations[i]->setX(numeroX);
            bulletLocations[i]->setY(9);
        }
        else{  //if asteroid is in the middle of the gameplay area, not at Y=0
            bulletLocations[i]->setOldX(bulletLocations[i]->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
            bulletLocations[i]->setOldY(bulletLocations[i]->returnY()); //same as above
            --(*bulletLocations[i]); //increments the Y value of asteroid so that it gets repainted one lower
        }
    }
    whichCollision = 3;
    whichPaintEvent = 3;
    //checkCollision(3);
    if(checkBulletCollision()){ //if the bullet is in the same place as the ship
        updateLives();
        int x = shipPosition->returnX();
        int y = shipPosition->returnY();

        updateShip(x, y, x+1, y);
    }
    repaint();
    QCoreApplication::processEvents();
}

/**
    @brief this function updates the life of the player.  when there are no lives left the gamOver function gets called which deletes the object
    @return void because it's only an operations function*/
void Board::updateLives(){    
    if(lifeCount == 0){
        gameOver();
    }
    else{
        if(lifeCount>0){
            std::cout<<"decrement"<<std::endl;
            --lifeCount;
            lives[lifeCount]->clear();
            if (lifeCount == 0){
                gameOver();
            }
            return;
        }
    }
    //whichPaintEvent = 4;
    return;
}

/**
    @brief this function calls close, which will delete the board and open a new mainwindow
    */
void Board::gameOver(){
    this->close();
    //QMessageBox warning;
    //warning.setText("You lost!");
    //warning.exec();
}

/**
    @brief this is an overload of the closevent function.  This will create a new mainWidow object to start the game over.
    @param c means nothing, is just required by definition
    @return void*/
void Board::closeEvent(QCloseEvent *c){   
    //MainWindow *w = new MainWindow; //creates new main window
    //w->show();  //shows the new mainwindow
    return;
}


/**
    @brief this function checks to see whether the ship and an asteroid have collided
    @param none
    @return is boolean type true if there was a collision and false if there wasn't*/
bool Board::checkAsteroidCollision(){
    //bool monitor = false;
    size_t x = shipPosition->returnX();
    size_t y = shipPosition->returnY();

    for(size_t i=0, j=asteroidLocations.size(); i<j;++i){ //run through the vector of bullets
        if(asteroidLocations[i]->returnX() == x && asteroidLocations[i]->returnY() == y){
            return true; //remove so you only subtract one at a time!
        }
    }
    return false;
}
/**
    @brief this function checks to see whether the ship and the bullet have collided
    @param none
    @return is boolean type true if there was a collision and false if there wasn't*/
bool Board::checkBulletCollision(){
    //bool monitor = false;
    size_t x = shipPosition->returnX();
    size_t y = shipPosition->returnY();

    for(size_t i=0, j=bulletLocations.size(); i<j;++i){ //run through the vector of bullets
        if(bulletLocations[i]->returnX() == x && bulletLocations[i]->returnY() == y){
            return true; //return so that you don't remove multiple at once!
        }
    }
    return false;
}

void Board::showArtifact(){
    size_t shouldShow = 5;//rand() % 100;   //create a probability that the artifact will be shown
    if(!artifactVisible){
        if(shouldShow < 25){    //1/4 chance that the artifact will be shown, don't do this if there is one showing
            artifactVisible = true; //means go through code to set up artifact
        }
        else{
            artifactVisible = false;    //don't do the artifact code
        }

    if(artifactVisible){    //if the odds said show an artifact
        check = artifacts.begin();  //resets the member of Board class to be the beginning
        while((*check)->isTrue()){  //while the artifacts are true, meaning they have been gotten
            ++check;    //stops at the element that has not been shown yet
        }
        //toShow = (*check)->returnChar();   //sets the char to put on the board
        //whichPaintEvent = 4;
    }
    }

    if((*check)->returnY() == 9){ //meaning it is back at the top of the widget
        int px = (*check)->returnX();
        int py = (*check)->returnY();
        gamePlayLabel[py*boardSize+px]->setStyleSheet("background-color: rgba(0,0,0,0%)");
        (*check)->setX(rand()%9);
        (*check)->setY(0);
        artifactVisible = false;
        check = artifacts.end();    //they lost their opportunity to get the artifact

        return;             //return to main
    }
    else{  //if asteroid is in the middle of the gameplay area, not at Y=0
        (*check)->setOldX((*check)->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
        (*check)->setOldY((*check)->returnY()); //same as above
        ++(*(*check)); //increments the Y value of asteroid so that it gets repainted one lower
        //if(asteroidLocations[i]->returnY() == boardSize){   //if the asteroid is at the bottom of the screen (where y = boardSize since board is a square
        //  asteroidLocations[i]->setY(0); //reset the Y value to b zero so the asteroid get's painted again at the top of the scr
    }
    whichPaintEvent = 4;
    repaint();
    QCoreApplication::processEvents();

    return;
}

void Board::catchArtifact(char lettre){
    if ((*check)->returnChar() == lettre){
        --winGame;
        (*check)->setTrue();
    }


}

