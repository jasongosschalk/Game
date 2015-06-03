#include "board.h"
#include "mainwindow.h"
#include "ui_board.h"


Board::Board(QWidget *parent, size_t shipChoice, size_t difficulty) :
QWidget(parent),
ui(new Ui::Board)
{
    ui->setupUi(this);
    QWidget::setAttribute(Qt::WA_DeleteOnClose);    //instructs the compiler to delete this object when close() is called
    makeBoard(shipChoice, difficulty);//draws out the entire board
}


/**
    @brief this function draws the game board out and contains all timers, etc needed to make the game work.
    @param shipChoice is used to select the appropriate ship
    @param difficulty is used to set the speed of the asteroid and bullets.*/
void Board::makeBoard(size_t shipChoice, size_t difficulty){

    //default set values, which could be done in the header with c++11
    whichCollision = 0; //default set to zero, not in constructor in case user doesn't support c++11
    whenToStart = 0;    //in case user constructor doesn;t support c++11
    numberEnemies = 0;  //this is so that if there are ever more enemies added, there will automatically be a bullet shot from them as long as the ++numberEnemies is added
    boardSize = 10;
    numberAsteroids = 3;    //change this to add more asteroids to the game, shouldn't cause any code problems
    lifeCount=0;    //initialization of lifcount, determines how many lives user has
    boardShipChoice = shipChoice;
    boardDifficulty = difficulty;
    //winGameTracker = 0;


    masterLayout = new QVBoxLayout;                 //sets the masterLayout to be inside the Master widget



    //following code establishes the area where the enemies are and then adds th enemies in
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

    //the following code creates the center of the gameboard and then adds everything that needs to go there
    //create the gameplay area
    middle = new QWidget;               //this layout will contain all of the asteroids and the ship
    middle->setFixedHeight(375);        //sets the fixed height of the central widget
    gameplay = new QGridLayout(middle); //creates a grid layout that we can put things into later based on lcation
    gameplay->setGeometry(QRect());     //makes the type of grid a rectangle grid
    gameplay->setSpacing(0);            //makes the spacing between the rectangles zero

    //create asteroids
    //instructs to create a boardSize*BoardSize grid
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

    srand(time(NULL));    //random number generator sets default start

    //this loop adds asteroids onto the board by giving them their original starting point
    for (int i=0, j=numberAsteroids; i<j; ++i){
        int number = (rand() % 9)+1; //because the board is sized 10
        if(number == 0){        //we don't want anything starting in the 0 row because
            number+= rand() % 5;    //so that it's not directly above the ship
        }
        //below code adds a new asteroid to the vector at x = number, y=i (someplace on the board 1-10)
        asteroidLocations.push_back(new Asteroid(number, i));
    }



    //create the bullet that will move up the screen
    bullet.load(":/images/bullet.png");
    int number = rand() % 9 + 1; //is ten because the board is only ten units by ten units
    bulletLocations.push_back(new Bullets(number, 9));  //always start at bottom, random x value


    //set up the difficulty of the game, including how
    int asteroidTime = 0;
    int bulletTime = 0;
    //difficulty is a parameter passed from mainwindow.cpp when the game is started and Board object is created
    if(boardDifficulty == 1){    //if easy
        asteroidTime = 150; //interval between refreshes of the asteroid
        bulletTime = 150;   //interval between refreshed of the bullet.
        //this sets up the vector of artifacts
        winGame = (difficulty *= 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){   //only need 4 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }
    //difficulty is a parameter passed from mainwindow.cpp when the game is started and Board object is created
    else if(boardDifficulty == 2){   //if medium difficulty
        asteroidTime = 120;
        bulletTime = 120;
        winGame = (difficulty *= 3);
        winGameTracker = 6;
        for (int i=0, j=winGameTracker; i<j; ++i){   //need 6 artifacts for medium
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }
    else if (boardDifficulty == 3){   //if hard
        asteroidTime = 90;
        bulletTime = 90;
        winGame = (difficulty *= 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){  //more difficult, need to collect 10 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            artifacts.push_back(new Artifacts(number, i));
        }
    }

    //create the artifacts that have to be collected in order to win
    std::string randomLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(size_t i=0, j=artifacts.size(); i<j; ++i){
        int randNum = rand()%26;    //a random number between 0 and 25
        artifacts[i]->setLetter(randomLetters[randNum]);    //sets the private variable of artifact element equal to a letter in the alphabet
    }



    //create spaceship
    //this is dependent on user choice
    QString shipName;   //local variable to handle different file names
    if(shipChoice == 1){    //if the enterprise was selected
        shipName = ":/images/enterprise.png";
    }
    if(shipChoice == 2){    //if the cosmos ship was selected
        shipName = ":/images/sagan.png";
    }
    shipPic.load(shipName); //sets the ship to be the user's choice
    shipPosition = new Ship(0,9);   //default sets the ship to be in the lower left position
    int x = shipPosition->returnX();
    int y = shipPosition->returnY();

    //shows the ship for the first time on the board
    gamePlayLabel[y*boardSize+x]->setPixmap(shipPic);
    gamePlayLabel[y*boardSize+x]->setScaledContents(true);
    gamePlayLabel[y*boardSize+x]->setFixedSize(50,50);

    //create bottom score area
    lifeCount = 4;
    bottom = new QWidget;
    bottom->setFixedHeight(70);
    bottomInfo = new QGridLayout(bottom);  //for the lives
    lives = new QLabel*[lifeCount];    //, a pointer of pointers or the loop doesnt work
    heart.load(":/images/heart.png");
    livesDescription = new QLabel;
    livesDescription->setText("<font size = 8><font color = white>Lives:</font>");
    bottomInfo->addWidget(livesDescription, 1, 1);
    //change this for loop to make more lives
    for (int i=0, j=lifeCount; i<j; ++i){
        lives[i] = new QLabel;
        lives[i]->setScaledContents(true);
        lives[i]->setPixmap(heart);
        lives[i]->setFixedSize(65, 65);
        bottomInfo->addWidget(lives[i], 1, i+2);
    }



    quit = new QPushButton;
    quit->setText("Quit");
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *bottomStuff = new QVBoxLayout;
    bottomStuff->addWidget(bottom);
    bottomStuff->addWidget(quit);

    masterLayout->addWidget(top);
    masterLayout->addWidget(middle);
    masterLayout->addLayout(bottomStuff);
    this->setFixedSize(600,600);
    this->setLayout(masterLayout);

    //set the iterator equal to the beginning of the artifacts vector
    check = artifacts.begin();

    //create space junk and bullet timing, this area is controlled by difficulty choice
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAsteroids()));
    timer->start(asteroidTime);

    artifactVisible = false;    //must be set to false for the artifact code to work!
    //timer for showing artifacts on screen
    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(showArtifact()));
    timer3->start(asteroidTime+30);



}

/**
    @brief this is called when the user advances a level, by the function levelUp.  it is used to speed up objects and increase the amount of
            artifacts required.
    @param shipChoice is used to make sure the ship choice is the same, but not needed
    @param difficulty is the new difficulty that will be used to update the speeds and overall difficulty of everything */
void Board::makeBoardAgain(size_t shipChoice, size_t difficulty){
    lifeCount=0;
    boardShipChoice = shipChoice;
    boardDifficulty = difficulty;

    //set up the difficulty of the game, including how
    int asteroidTime = 0;
    int bulletTime = 0;
    std::cout<<boardDifficulty;
    std::vector<Artifacts*> temp;  //temprary vector to fill with the values of artifacts

    //difficulty is a parameter passed from mainwindow.cpp when the game is started and Board object is created
    if(boardDifficulty == 1){    //if easy
        asteroidTime = 150; //interval between refreshes of the asteroid
        bulletTime = 150;   //interval between refreshed of the bullet.
        //this sets up the vector of artifacts
        winGame = (difficulty * 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){   //only need 4 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            temp.push_back(new Artifacts(number, i));
        }
    }
    //difficulty is a parameter passed from mainwindow.cpp when the game is started and Board object is created
    else if(boardDifficulty == 2){   //if medium difficulty
        std::cout<<"At 2";
        asteroidTime = 130;
        bulletTime = 130;
        winGame = (difficulty * 3);
        winGameTracker = winGame;
        for (int i=0, j=winGameTracker; i<j; ++i){   //need 6 artifacts for medium
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            temp.push_back(new Artifacts(number, i));
        }
    }
    else if (boardDifficulty == 3){   //if hard
        asteroidTime = 95;
        bulletTime = 95;
        winGame = (difficulty * 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){  //more difficult, need to collect 10 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            temp.push_back(new Artifacts(number, i));
        }
    }
    else if (boardDifficulty == 4){   //if hard
        asteroidTime = 75;
        bulletTime = 75;
        winGame = (difficulty * 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){  //more difficult, need to collect 10 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            temp.push_back(new Artifacts(number, i));
        }
    }
    else if (boardDifficulty == 5){   //if hard
        asteroidTime = 60;
        bulletTime = 60;
        winGame = (difficulty * 3); //first game would be 4
        winGameTracker = winGame;   //to keep track of how many there should have been
        for (int i=0, j=winGameTracker; i<j; ++i){  //more difficult, need to collect 10 artifacts
            int number = rand() % 10; //was 20
            if(number == 0){
                number+= rand() % 5;    //so that it's not directly above the ship
            }
            //below code adds a new artifact to the vector at x = number, y=0(top of grid) and boardSize is passed to monitor how long asteroid stays on screen
            temp.push_back(new Artifacts(number, i));
        }
    }

    //create the artifacts that have to be collected in order to win
    std::string randomLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(size_t i=0, j=temp.size(); i<j; ++i){
        int randNum = rand()%26;    //a random number between 0 and 25
        temp[i]->setLetter(randomLetters[randNum]);    //sets the private variable of artifact element equal to a letter in the alphabet
    }

    for(size_t i = 0, j = temp.size(); i<j; ++i){
        std::cout<<temp[i]->returnChar()<<std::endl;
    }

        std::swap(artifacts, temp);//swaps the two vectors

        lifeCount = 4;
        livesDescription->setText("<font size = 8><font color = white>Lives:</font>");
        bottomInfo->addWidget(livesDescription, 1, 1);
    //change this for loop to make more lives
        for (int i=0, j=lifeCount; i<j; ++i){
            lives[i]->setScaledContents(true);
            lives[i]->setPixmap(heart);
            lives[i]->setFixedSize(65, 65);
            bottomInfo->addWidget(lives[i], 1, i+2);
        }

    //set the iterator equal to the beginning of the artifacts vector
    check = artifacts.begin();

    std::cout<<"Asteroid Time is"<<asteroidTime;
    //create space junk and bullet timing, this area is controlled by difficulty choice
    //timer = new QTimer(this);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAsteroids()));
    timer->setInterval(asteroidTime);
    timer->start();

    artifactVisible = false;    //must be set to false for the artifact code to work!
    //timer for showing artifacts on screen
    //timer3 = new QTimer(this);
    timer3 = new QTimer;
    connect(timer3, SIGNAL(timeout()), this, SLOT(showArtifact()));
    timer3->setInterval(asteroidTime+40);
    timer3->start();
}

/**
    @brief board destructor should delete all memory it creates, meaning delete needs to be called on all manually created memory
            which is various polymorhpic objects of BoardObject class
*/
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
/**
    @brief this defines what commands should be detected by the program from the keyboard or mouse
           all alphabetical key presses are valid as well as arrows, all others will have no affect*/
void Board::keyPressEvent(QKeyEvent *event){
    //std::cout<<"KeyPressEvent:"<<std::endl;
    int x = shipPosition->returnX();
    int y = shipPosition->returnY();


    switch (event->key()) {
    case Qt::Key_A:{
        {
            catchArtifact(char('A'));
        }
        break;
    }
    case Qt::Key_B:{
        {
            catchArtifact(char('B'));
        }
        break;
    }
    case Qt::Key_C:{
        {
            catchArtifact(char('C'));
        }
        break;
    }
    case Qt::Key_D:{
        {
            catchArtifact(char('D'));
        }
        break;
    }
    case Qt::Key_E:{
        {
            catchArtifact(char('E'));
        }
        break;
    }
    case Qt::Key_F:{
        {
            catchArtifact(char('F'));
        }
        break;
    }
    case Qt::Key_G:{
        {
            catchArtifact(char('G'));
        }
        break;
    }
    case Qt::Key_H:{
        {
            catchArtifact(char('H'));
        }
        break;
    }
    case Qt::Key_I:{
        {
            catchArtifact(char('I'));
        }
        break;
    }
    case Qt::Key_J:{
        {
            catchArtifact(char('J'));
        }
        break;
    }
    case Qt::Key_K:{
        {
            catchArtifact(char('K'));
        }
        break;
    }
    case Qt::Key_L:{
        {
            catchArtifact(char('L'));
        }
        break;
    }
    case Qt::Key_M:{
        {
            catchArtifact(char('M'));
        }
        break;
    }
    case Qt::Key_N:{
        {
            catchArtifact(char('N'));
        }
        break;
    }
    case Qt::Key_O:{
        {
            catchArtifact(char('O'));
        }
        break;
    }
    case Qt::Key_P:{
        {
            catchArtifact(char('P'));
        }
        break;
    }
    case Qt::Key_Q:{
       {
            catchArtifact(char('Q'));
        }
        break;
    }
    case Qt::Key_R:{
        {
            catchArtifact(char('R'));
        }
        break;
    }
    case Qt::Key_S:{
       {
            catchArtifact(char('S'));
        }
        break;
        }
    case Qt::Key_T:{
        {
            catchArtifact(char('T'));
        }
        break;
    }
    case Qt::Key_U:{
       {
            catchArtifact(char('U'));
        }
        break;
    }
    case Qt::Key_V:{
        {
            catchArtifact(char('V'));
        }
        break;
    }
    case Qt::Key_W:{
      {
            catchArtifact(char('W'));
        }
        break;
    }
    case Qt::Key_X:{
        {
            catchArtifact(char('X'));
        }
        break;
    }
    case Qt::Key_Y:{
        {
            catchArtifact(char('Y'));
        }
        break;
    }
    case Qt::Key_Z:{
        {
            catchArtifact(char('Z'));
        }
        break;
    }

    case Qt::Key_Left:{
        if(shipPosition->returnX() != 0)
            updateShip(x,y,x-1,y);
        break;
    }
    case Qt::Key_Right:{
        if(shipPosition->returnX() != boardSize-1)
            updateShip(x,y,x+1,y);
        break;
    }
    case Qt::Key_Up:{
        if(shipPosition->returnY() != 0)
            updateShip(x,y,x,y-1);
        break;
    }
    case Qt::Key_Down:{
        if(shipPosition->returnY() != boardSize-1)
            updateShip(x,y,x,y+1);
        break;
    }


    default:
        QWidget::keyPressEvent(event);
    }
    return;
}

/**
    @brief this is an overload of the paintevent functionality in the Qt namespace, and updates the locatin of the Board Objects on the screen
            by changing where they appear on the grid layout.  Different numbers are used so that when paint event is called, it doesn't repaint everything
            again, just the thing that called it (hend why the whichPainEvent value is always reset to zero before the PaintEvent overload is exited.
    @param e is nothing, just required by overload definition of this function.*/
void Board::paintEvent(QPaintEvent *e) {
    //std::cout<<"Paintevent"<<std::endl;
    return;
}

/**
    @brief overload of the showevent command in the Qt namespace
    @param e is just required by definition of the overload
*/
void Board::showEvent(QShowEvent *e) {
    //std::cout<<"ShowEvent"<<std::endl;

    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
    return;
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
    //std::cout<<"UpdateShip"<<std::endl;

    gamePlayLabel[py*boardSize+px]->clear();

    shipPosition->setOldX(shipPosition->returnX());
    shipPosition->setOldY(shipPosition->returnY());

    shipPosition->setX(nx);
    shipPosition->setY(ny);

    int x = shipPosition->returnX();
    int y = shipPosition->returnY();
    gamePlayLabel[y*boardSize+x]->setPixmap(shipPic);
    gamePlayLabel[y*boardSize+x]->setScaledContents(true);
    gamePlayLabel[y*boardSize+x]->setFixedSize(50,50);

    update();
    QCoreApplication::processEvents();
}

/**
    @brief this function updates the location of the asteroids and calls repaint to change the appearance on the screen.  If the asteroids are at the
            bottom of the screen, then there will be a random call to create a new x value and the asteroid will begin again at the top of the
            screen at a new *random* x value
    */
void Board::updateAsteroids() {
    //std::cout<<"updateAsteroids"<<std::endl;

    updateBullets(); //update the bullet.  this was previously its own timer but there's no need.

    whenToStart = 1;  //indicates to paintEvent it is now  OK to update asteroid paint event and bullet paint event
    for (int i=0, j=numberAsteroids; i<j; ++i){
        //or if the asteroid is out of lives, it is time to move it back to the top!

        if(asteroidLocations[i]->returnY() == 9){ //meaning it is back at the top of the widget
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
        }

        //update the location of the asteroid
        int px = asteroidLocations[i]->returnX();
        int py = asteroidLocations[i]->returnY();
        int oldX = asteroidLocations[i]->returnOldX();
        int oldY = asteroidLocations[i]->returnOldY();
        gamePlayLabel[oldY*boardSize+oldX]->clear();
        gamePlayLabel[py*boardSize+px]->setPixmap(asteroid);
        gamePlayLabel[py*boardSize+px]->setScaledContents(true);
        gamePlayLabel[py*boardSize+px]->setFixedSize(60,60);

    }



    if(checkAsteroidCollision()){//if the asteroid is in the same position as the ship
        updateLives();
        int x = shipPosition->returnX();
        int y = shipPosition->returnY();

        updateShip(x, y, x+1, y);
    }
    update();
    QCoreApplication::processEvents();
;
;
    return;
}



/**
    @brief this function updates the location of the bullets and calls repaint to change where they appear on the screen.  the function deals
            with the BoardObject type object and randomly creates a new x position that the bullet should be in, if it has reached the top
            of the screen.  Otherwise, it increments upward the bullet's position until it gets to the top.
*/
void Board::updateBullets(){
    //std::cout<<"updateBullets"<<std::endl;

    for (int i=0, j=bulletLocations.size(); i<j; ++i){
        //or if the asteroid is out of lives, it is time to move it back to the top!
        if(bulletLocations[i]->returnY() == 0){ //meaning it is back at the top of the widget
            int numeroX = rand() % 10;  //random number
            bulletLocations[i]->setOldX(bulletLocations[i]->returnX()); //sets old x value to clear
            bulletLocations[i]->setOldY(bulletLocations[i]->returnY()); //sets old y value to clear
            bulletLocations[i]->setX(numeroX);  //sets the new x value
            bulletLocations[i]->setY(9);        //sets the new y value
        }
        else{  //if asteroid is in the middle of the gameplay area, not at Y=0
            bulletLocations[i]->setOldX(bulletLocations[i]->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
            bulletLocations[i]->setOldY(bulletLocations[i]->returnY()); //same as above
            --(*bulletLocations[i]); //increments the Y value of asteroid so that it gets repainted one higher
            //kind of confusing notation that operator -- is actually moving the bullet up the screen
        }

        //update location of the bullet
        int px = bulletLocations[i]->returnX();
        int py = bulletLocations[i]->returnY();
        int oldX = bulletLocations[i]->returnOldX();
        int oldY = bulletLocations[i]->returnOldY();

        gamePlayLabel[oldY*boardSize+oldX]->clear();
        gamePlayLabel[py*boardSize+px]->setPixmap(bullet);
        gamePlayLabel[py*boardSize+px]->setScaledContents(true);
        gamePlayLabel[py*boardSize+px]->setFixedSize(45,55);
    }

    whichCollision = 3;
    if(checkBulletCollision()){     //if the bullet is in the same place as the ship
        updateLives();
        int x = shipPosition->returnX();
        int y = shipPosition->returnY();
        updateShip(x, y, x+1, y);
    }
    return;
}

/**
    @brief this function checks to see whether the ship and an asteroid have collided
    @param none
    @return is boolean type true if there was a collision and false if there wasn't
*/
bool Board::checkAsteroidCollision(){
    //std::cout<<"checkAsteroidCollision"<<std::endl;

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
    //std::cout<<"checkBulletCollision"<<std::endl;
    size_t x = shipPosition->returnX();
    size_t y = shipPosition->returnY();

    for(size_t i=0, j=bulletLocations.size(); i<j;++i){ //run through the vector of bullets
        if(bulletLocations[i]->returnX() == x && bulletLocations[i]->returnY() == y){
            return true; //return so that you don't remove multiple at once!
        }
    }
    return false;
}

/**
    @brief this function updates the life of the player.  when there are no lives left the gamOver function gets called which deletes the object
    @return void because it's only an operations function
*/
void Board::updateLives(){
    //std::cout<<"updateLives"<<std::endl;
    if(lifeCount>0){
        --lifeCount;
        lives[lifeCount]->clear();
    }

    if (lifeCount <= 0){
        gameOver(1);
    }
    return;
}

/**
    @brief this function calls close, which will delete the board and open a new mainwindow by returning control to mainwindow.cpp
    @param whichOne informs the function whether the game is over because the user won or lost, and displays the appropriate message
*/
void Board::gameOver(int whichOne){
    //std::cout<<"gameOver"<<std::endl;

    if(whichOne == 1) {//lost the game
        gameLost();
    }
    else{ //gamewon
        gameWon();
    }

    timer->stop();  //stops the timer "timer"
    timer3->stop(); //stops the second timer "timer3"
    this->close();  //delete the object
}

/**
    @brief this function displays a notice that says */
void Board::gameWon(){
    //std::cout<<"gameWon"<<std::endl;

    QMessageBox winner;
    winner.setText("You won!");
    winner.exec();
    return;
}

void Board::gameLost(){
    //std::cout<<"gameLost"<<std::endl;

    QMessageBox loser;
    loser.setText("You lost!");
    loser.exec();
    return;
}




void Board::showArtifact(){
    //std::cout<<"showArtifact"<<std::endl;

    whenToStart = 1;

    if(!artifactVisible){ //if artifact is not visible
        //std::cout<<"probability";
        size_t shouldShow = rand() % 550;   //create a probability that the artifact will be shown fix this
        if(shouldShow < 25){    //1/4 chance that the artifact will be shown, don't do this if there is one showing
            artifactVisible = true; //means go through code to set up artifact
        }
        else{
            artifactVisible = false;    //don't do the artifact code
            return; //return so that we don't do the other code
        }

        if(artifactVisible){    //if the odds said show an artifact
            check = artifacts.begin();  //resets the member of Board class to be the beginning
            while((*check)->isTrue()){  //while the artifacts are true, meaning they have been gotten
                ++check;    //stops at the element that has not been shown yet
            }
            if((check) != artifacts.end()){
                (*check)->setIsShowing(true);   //sets the identify of the artifact to showing
            }
        }
    }

    if (check == artifacts.end()){ return; }
    if((*check)->returnY() == 9){ //meaning it is back at the bottom of the widget
        int px = (*check)->returnX();   //current position
        int py = (*check)->returnY();   //current position
        gamePlayLabel[py*boardSize+px]->setStyleSheet("background-color: rgba(0,0,0,0%)");  //clear that area
        (*check)->setX(rand()%10);
        (*check)->setY(0);
        (*check)->setIsShowing(false);  //means that artifact is no longer being shown.
        artifactVisible = false;
        check = artifacts.end();    //they lost their opportunity to get the artifact
        return;             //return to main
    }
    else{  //if asteroid is in the middle of the gameplay area, not at Y=9
        (*check)->setOldX((*check)->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
        (*check)->setOldY((*check)->returnY()); //same as above
        ++(*(*check)); //increments the Y value of asteroid so that it gets repainted one lower
        //if(asteroidLocations[i]->returnY() == boardSize){   //if the asteroid is at the bottom of the screen (where y = boardSize since board is a square
        //  asteroidLocations[i]->setY(0); //reset the Y value to b zero so the asteroid get's painted again at the top of the scr
    }

    if(check != artifacts.end() && ((*check)->informIsShowing() == true)){   //if there is an artifact to show and it should be shown
        QChar theChar = (*check)->returnChar(); //creates a Qt character with the letter from the object of choice

        //reset the board to move the object down
        int px = (*check)->returnX();
        int py = (*check)->returnY();
        int oldX = (*check)->returnOldX();
        int oldY = (*check)->returnOldY();

        gamePlayLabel[oldY*boardSize+oldX]->clear();
        gamePlayLabel[oldY*boardSize+oldX]->setStyleSheet("background-color: rgba(0,0,0,0%)");
        gamePlayLabel[py*boardSize+px]->setText(theChar);
        gamePlayLabel[py*boardSize+px]->setFixedSize(15,25);
        gamePlayLabel[py*boardSize+px]->setTextFormat(Qt::RichText);
        gamePlayLabel[py*boardSize+px]->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : yellow; }");
        gamePlayLabel[py*boardSize+px]->setScaledContents(true);
    }


    update();
    QCoreApplication::processEvents();
;
;

    return;
}
/**
    @brief is called if one of the alphabetical keys are pressed, and will bring the user closer to winning
            if they pressed the correct letter that is shown on the screen at the time they pressed the key.
    @param lettre (french, not a typo) is the letter that the user pressed, which is compared to the letter that the iterator
            is pointing to currently.*/
void Board::catchArtifact(char lettre){
    //std::cout<<"catchArtifact"<<std::endl;

    if(check != artifacts.end()){   //JUST IN CASE THIS GETS CALLED WHEN *CHECK IS NULLPTR
        //if the letter pressed is the correct letter and the artifact is actually showing at the moment
        if ((*check)->returnChar() == lettre && (*check)->informIsShowing() && (!(*check)->isTrue())){
            //std::cout<<"catchArtifact3"<<std::endl;

            --winGame;  //decrements the number of artifacts required to win the game now.
            (*check)->setTrue();    //means it has been collected, so that next time, the iterator will be set to the next element in the vector.
            //std::cout<<"catchArtifact4"<<std::endl;

        }
        else{return;}
        if(winGame <= 0){
            //std::cout<<"catchArtifact5"<<std::endl;
            levelUp();
        }
    }
        //std::cout<<"catchArtifact6"<<std::endl;

    return;
}
/**
    @brief this function will level up the game to make it more difficult.  it is called by the collect artifact function which monitors how many of the artifacts have been collected */
void Board::levelUp(){
    winGameTracker +=3; //adds three more artifacts that need to be collected
    ++boardDifficulty;  //makes the level go up one
    if(boardDifficulty == 6){
        gameOver(2);    //you won!
    }
    else {
        timer->stop();  //stop the timer
        timer3->stop(); //stop the timer
        levelUpAlert(); //"you leveled up!
        makeBoardAgain(boardShipChoice, boardDifficulty);
    }

    return;
}
/**
    @brief this function displays an alert that the user has leveled up, and is called by the levelUp function.  After this warning, the game speeds up.*/
void Board::levelUpAlert(){
    //std::cout<<"levelUpAlert"<<std::endl;

    QMessageBox levelUpMessage;
    levelUpMessage.setText("You leveled up!");
    levelUpMessage.exec();
    return;
}


