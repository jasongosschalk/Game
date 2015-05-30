#include "board.h"
#include "ui_board.h"

//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//std::default_random_engine generator (seed);

Board::Board(QWidget *parent, size_t shipChoice, size_t difficulty) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    //create the master widget
    // master = new QWidget;
    //master->setFixedSize(600,600);
    masterLayout = new QVBoxLayout(); //sets the masterLayout to be inside the Master widget
                                    //removed master from the parenthesis

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

    //create gameplay area
    middle = new QWidget;               //this layout will contain all of the asteroids and the ship
    middle->setFixedHeight(375);        //sets the fixed height of the central widget
    //middle->setFixedWidth(550);
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

    std::srand (time(NULL));    //random number generator
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
    //this loop creates all the bullets needed for the game

    std::srand (time(NULL));
    int number = rand() % 10; //was 20
    bulletLocations.push_back(new Bullets(number, 9));  //always start at top

    int asteroidTime = 0;
    int bulletTime = 0;
    if(difficulty == 1){    //if easy
        asteroidTime = 150;
        bulletTime = 200;
    }
    else if(difficulty == 2){   //if medium difficulty
        asteroidTime = 100;
        bulletTime = 150;
    }
    else{   //if hard
        asteroidTime = 50;
        bulletTime = 95;
    }
    //create space junk and bullet timing, this area is controlled by difficulty choice
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAsteroids()));
    timer->start(asteroidTime);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateBullets()));
    timer2->start(bulletTime);

    //create spaceship, this is dependent on user choice
    QString shipName;
    if(shipChoice == 1){
        shipName = ":/images/enterprise.png";
    }
    if(shipChoice == 2){
        shipName = ":/images/sagan.png";

    }
    ship.load(shipName);
    shipPosition = new QPoint;
    shipPosition->setX(0);
    shipPosition->setY(9);
    int x = shipPosition->rx();
    int y = shipPosition->ry();
    gamePlayLabel[y*boardSize+x]->setPixmap(ship);
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
    delete ui;

}

void Board::keyPressEvent(QKeyEvent *event){

    int x = shipPosition->rx();
    int y = shipPosition->ry();


    switch (event->key()) {
    case Qt::Key_Left:
        if(shipPosition->rx() != 0)
            updateShip(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(shipPosition->rx() != boardSize-1)
            updateShip(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(shipPosition->ry() != 0)
            updateShip(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(shipPosition->ry() != boardSize-1)
            updateShip(x,y,x,y+1);

        break;

   //case Qt::Key_Space:
     //   munchNumber(x,y);
        //break;

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

void Board::paintEvent(QPaintEvent *e) {
    std::cout<<"Broke at paintevent"<<std::endl;


    if(whichPaintEvent == 2){       //paintevent was called by updateShip

        //update the ship location
        int x = shipPosition->rx();
        int y = shipPosition->ry();
        gamePlayLabel[y*boardSize+x]->setPixmap(ship);
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
            std::cout<<"BULLET UPDATE!" <<std::endl;

            gamePlayLabel[oldY*boardSize+oldX]->clear();
            gamePlayLabel[py*boardSize+px]->setPixmap(bullet);
            gamePlayLabel[py*boardSize+px]->setScaledContents(true);
            gamePlayLabel[py*boardSize+px]->setFixedSize(15,25);
        }
        whichPaintEvent = 0;

    }

    //if(whichPaintEvent == 4){   //paint event was called to update lives
    //}
    return;
}


void Board::showEvent(QShowEvent *e) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}




void Board::updateAsteroids() {
    std::cout<<"Broke at updateAsteroid"<<std::endl;

    whenToStart = 1;  //indicates to paintEvent it is now  OK to update asteroid paint event

   // std::srand (time(NULL));    //random number generator

    for (int i=0, j=numberAsteroids; i<j; ++i){
        //or if the asteroid is out of lives, it is time to move it back to the top!

        if(asteroidLocations[i]->returnY() == 9){ //meaning it is back at the top of the widget
            //int numberY = rand() % 10;
            std::srand (time(NULL));    //random number generator
            int numberX = rand() % 10;
            std::cout<<"Resetting" << i << std::endl;
            asteroidLocations[i]->setOldX(asteroidLocations[i]->returnX());
            asteroidLocations[i]->setOldY(asteroidLocations[i]->returnY());
            asteroidLocations[i]->setX(numberX);
            asteroidLocations[i]->setY(0);
        }
        else{  //if asteroid is in the middle of the gameplay area, not at Y=0
            std::cout<<asteroidLocations[i]->returnY() << std::endl;    //temporary for code writing purposes
            asteroidLocations[i]->setOldX(asteroidLocations[i]->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
            asteroidLocations[i]->setOldY(asteroidLocations[i]->returnY()); //same as above
            ++(*asteroidLocations[i]); //increments the Y value of asteroid so that it gets repainted one lower
            //if(asteroidLocations[i]->returnY() == boardSize){   //if the asteroid is at the bottom of the screen (where y = boardSize since board is a square
              //  asteroidLocations[i]->setY(0); //reset the Y value to b zero so the asteroid get's painted again at the top of the screen
            //}
        }
    }
    whichCollision = 1;
    checkCollision(1);
    whichPaintEvent = 1;
    repaint();
    QCoreApplication::processEvents();
    std::cout<< "Calling updateAsteroids()\n"<<std::endl;
}


void Board::updateShip(int px, int py, int nx, int ny) {
    std::cout<<"Broke at updateShip"<<std::endl;

    gamePlayLabel[py*boardSize+px]->clear();

    shipPosition->setX(nx);
    shipPosition->setY(ny);

    whichPaintEvent = 2;
    //checkCollision();

    repaint();
    QCoreApplication::processEvents();
//    return (px==nx)&&(py==ny);
}

void Board::updateBullets(){
    std::cout<<"Broke at updateBullets"<<std::endl;

    std::srand (time(NULL));    //random number generator

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
            std::cout<<bulletLocations[i]->returnY() << std::endl;    //temporary for code writing purposes
            bulletLocations[i]->setOldX(bulletLocations[i]->returnX()); //sets oldX so that the old grid spot can be cleared in paintevent
            bulletLocations[i]->setOldY(bulletLocations[i]->returnY()); //same as above
            --(*bulletLocations[i]); //increments the Y value of asteroid so that it gets repainted one lower
        }
    }
    whichCollision = 3;
    whichPaintEvent = 3;
    checkCollision(3);

    repaint();
    QCoreApplication::processEvents();
}

void Board::updateLives(){
    std::cout<<"Broke at updateLives, lifecount = "<< lifeCount << std::endl;
    if(lifeCount == 0){
        //gameOver();
    }
    else{
        if(lifeCount>0){
            --lifeCount;
            lives[lifeCount]->clear();
            std::cout<<"Broke after clear"<< lifeCount << std::endl;

        }
    }
    //whichPaintEvent = 4;
    return;
}

void Board::checkCollision(int which){
    std::cout<<"Broke at checkCollision"<<std::endl;

    bool monitor = false;
    int x = shipPosition->x();
    int y = shipPosition->y();

    if(which == 3){ //bullet was updated
        for(size_t i=0, j=bulletLocations.size(); i<j;++i){ //run through the vector of bullets
            monitor = bulletLocations[i]->ifBulletCollision(x, y);  //check each bullet for overlap
            if(monitor){
                updateLives();
                monitor = false;    //reset monitor so that it doesn't remove multiple lives per collision

                std::cout<<"Broke at 1"<<std::endl;

            }
        }
        which = 0;
    }

    if(which == 1){ //asteroud was updated
        for(size_t i=0, j=asteroidLocations.size();i<j;++i){
            monitor = asteroidLocations[i]->ifAsteroidCollision(x, y);
            if(monitor){
                updateLives();
                monitor = false;    //reset monitor so that it doesn't remove multiple lives per collision
                std::cout<<"Broke at 2"<<std::endl;

            }
        }
        which = 0;
    }
    return;
}

void Board::gameOver(){
    /*QMessageBox lose;
    lose.setText("You lost!");
    lose.exec();*/

    //this->set setLayout(this->parent());
}

/*
void GameBoard::updateAfterMunch(bool flag) {
    int x = muncher_position->rx();
    int y = muncher_position->ry();

    if(flag)
        values[y*board_size+x] = 0;
    else {
        values[y*board_size+x] = 0;
        if(lives_remaining > 1) {
            lives_remaining--;
            lives[lives_remaining-1]->clear();
        }
        else {
            this->game_over();
            // Game Over
        }
    }
}
*/

