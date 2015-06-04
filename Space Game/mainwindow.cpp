#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWindow(); //paints the board with the entry screen
}

/**
    @brief this function draws the mainwindow
    */
void MainWindow::createWindow(){
    shipChoice = 0; //default set to zero in case user does not have c++11
    difficulty = 0; //default set to zero in case user does not have c++11

    //this portion of code sets up the master layout and main Widget and 3 sub widgets
    welcomePage = new QWidget;  //master widget
    welcomePage->setFixedSize(600,600); //size of the game is fixed
    this->setFixedSize(650,650);
    allLayouts = new QVBoxLayout(welcomePage);  //the only thing that should be connected to the welcomePage widget
    topWidget = new QWidget;    //will contain title and explanation
    middleWidget = new QWidget; //will contain the difficulty options and the ship options
    bottomWidget = new QWidget; //will contain the start button and anything added later
    QPixmap bkgnd(":/images/images/space.jpg");
    bkgnd.scaledToHeight(600);
    bkgnd.scaledToWidth(600);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    //fix size of mainwindow widgets
    topWidget->setFixedSize(600, 200);
    middleWidget->setFixedHeight(450);
    bottomWidget->setFixedHeight(50);

    //addwidgets to the master layout
    allLayouts->addWidget(topWidget);
    allLayouts->addWidget(middleWidget);
    allLayouts->addWidget(bottomWidget);

    //create the layouts for the top, middle and bottom
    top = new QHBoxLayout(topWidget);           //creates the layout to put the two Top layouts in
    middle = new QHBoxLayout(middleWidget);       //creates the layout to put all the middle layouts in
    bottom = new QVBoxLayout(bottomWidget);      //where the start button goes--all the bottom layouts


    //this portion of code sets up the top title and explanation of the game
    QWidget *titleExplanationVerticalWidget = new QWidget;//widget to put the top vertical layout into and to put into the "top" horizontal layout
    QVBoxLayout *titleExplanationVertical = new QVBoxLayout(titleExplanationVerticalWidget);    //layout to put the two titles in
    title = new QHBoxLayout;            //top where the title goes
    explanation = new QHBoxLayout;      //top below the title where the explaination goes
    titleExplanationVertical->addLayout(title);              //adds the title to the top layout
    titleExplanationVertical->addLayout(explanation);        //adds the explanation to the top layout
    top->addWidget(titleExplanationVerticalWidget);   //adds the verticallayoutwidget that contains the vertical widget with the title and explanation to the horizontal layout
    QSpacerItem *topRightSpacer = new QSpacerItem(50,1);
    top->addSpacerItem(topRightSpacer);


    //set the title of the main window
    titleText = new QLabel;             //where the title text goes
    titleText->setText("<font face = Times New Roman> <font size = 30><font color = white>Welcome to Space Survival!</font>");
    title->addWidget(titleText);        //sets the title hboxlayout to the text in the QLabel
    title->setAlignment(Qt::AlignCenter);   //aligns the text to the center
    explanationText = new QLabel;       //where the explanation text goes
    explanationText->setText("<font face = Times New Roman> <font size = 5><font color = white>The universe has been destroyed by politicians and you're trying to escape it!  "
                             "Don't crash into any space junk during your getaway, and avoid friendly fire!</font>");
    explanationText->setWordWrap(true); //makes it so that text does not go off the screen and fits into the widgets set size
    explanationText->setAlignment(Qt::AlignCenter);   //aligns the text to the center
    explanation->addWidget(explanationText);//adds the explanation text to the explanation layout

    QPalette *fontColor = new QPalette;
    fontColor->setColor(QPalette::Foreground, Qt::white);
    QWidget *middleWidgetLeft= new QWidget;     //creates a widget to contain the grid on the left side of the screen
    middleWidgetLeft->setFixedWidth(290);       //sets fixed width of the left side
    QWidget *middleWidgetRight= new QWidget;    //creates a widget to contain the grid on the right side of the screen
    middleWidgetRight->setFixedWidth(290);      //sets fixed width of the right side
    QVBoxLayout *leftVBox = new QVBoxLayout;
    QVBoxLayout *rightVBox = new QVBoxLayout;
    middle->addLayout(leftVBox);        //Add the left widget to the middle layout
    QSpacerItem *horizontalMiddle = new QSpacerItem(20, 1);
    middle->addSpacerItem(horizontalMiddle);
    middle->addLayout(rightVBox);       //add the right widget to the middle layout

    //create the left side of the middle of the program using a GRID layout
    leftSide = new QVBoxLayout(middleWidgetLeft);    //where the options for space ship style goes
    //create name of the ships to use
    QLabel *leftColumnExplanation = new QLabel;
    leftColumnExplanation->setText("<font color = white>Choose your ship to navigate the abyss:</font>");
    leftColumnExplanation->setAlignment(Qt::AlignCenter);
    leftColumnExplanation->setWordWrap(true);
    leftVBox->addWidget(leftColumnExplanation);
    leftVBox->addWidget(middleWidgetLeft);
    //create the radioButtons to choose the ship
    cosmos = new QRadioButton;
    cosmos->setText("Neil Degrasse Tyson's ship in cosmos");
    cosmos->setPalette(*fontColor);
    enterprise = new QRadioButton;
    enterprise->setText("The Enterprise from Star Trek");
    enterprise->setPalette(*fontColor);
    shipGroup = new QButtonGroup(this);
    shipGroup->addButton(cosmos);
    shipGroup->addButton(enterprise);
    leftSide->addWidget(cosmos);         //place radio button in first row first column
    leftSide->addWidget(enterprise);     //place radio button in second row, first column
    QSpacerItem *verticalSpaceLeft = new QSpacerItem(1, 272);
    leftVBox->addSpacerItem(verticalSpaceLeft);

    //detect input from use about choice of ship
    connect(cosmos, SIGNAL(clicked()), this, SLOT(cosmosChoice()));
    connect(enterprise, SIGNAL(clicked()), this, SLOT(enterpriseChoice()));




    //create the right side of the middle of the program using a layout
    rightSide = new QVBoxLayout(middleWidgetRight);   //where the options for difficulty levels go
    QLabel *rightColumnExplanation = new QLabel;
    rightColumnExplanation->setText("<font color = white>Choose your preferred difficulty:</font>");
    rightColumnExplanation->setWordWrap(true);  //so words don't run off the screen/out of the layout that's shown
    rightColumnExplanation->setAlignment(Qt::AlignCenter);  //align the label in the center
    rightVBox->addWidget(rightColumnExplanation);
    rightVBox->addWidget(middleWidgetRight);
    easy = new QRadioButton;    //when clicked will set difficulty to easy
    easy->setText("Easy");
    easy->setPalette(*fontColor);
    medium = new QRadioButton;  //when clicked will set difficulty to medium
    medium->setText("Medium");
    medium->setPalette(*fontColor);
    hard = new QRadioButton;
    hard->setText("Hard");  //when clicked will set difficulty to hard
    hard->setPalette(*fontColor);
    difficultyGroup = new QButtonGroup(this);
    difficultyGroup->addButton(easy);   //adds button to the difficulty layout
    difficultyGroup->addButton(medium);
    difficultyGroup->addButton(hard);
    rightSide->addWidget(easy);         //place radio button in first row first column
    rightSide->addWidget(medium);     //place radio button in second row, first column
    rightSide->addWidget(hard);     //place radio button in second row, first column
    QSpacerItem *verticalSpaceRight = new QSpacerItem(1, 267);  //to align to area desired
    rightVBox->addSpacerItem(verticalSpaceRight);

    //to detect user input about choice of difficulty
    connect(easy, SIGNAL(clicked()), this, SLOT(setEasy()));
    connect(medium, SIGNAL(clicked()), this, SLOT(setMedium()));
    connect(hard, SIGNAL(clicked()), this, SLOT(setHard()));


    //Create the bottom of the game
    start = new QPushButton;    //button used to start the game
    start->setText("Start!");
    bottom->addWidget(start);
    QObject::connect(start, SIGNAL(clicked()), this, SLOT(gameBegin()));

    directions = new QPushButton;   //if the user wants instructions on how to play the game
    directions->setText("Instructions");
    bottom->addWidget(directions);
    QObject::connect(directions, SIGNAL(clicked()), this, SLOT(showInstructions()));

    this->setCentralWidget(welcomePage);        //adds the master layout to the central widget
    this->setWindowTitle("Astronomical Political Destruction");
    return;
}

/**
    @brief destructor for the MainWindow class that deletes the ui and all of its children (RAII)*/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
    @brief a public slot that begins a new game by creating a board object.  The user cannot create a new game unless they
            have selected a shipChoice and difficulty level
    @param none
    @return none*/
void MainWindow::gameBegin(){
    if(shipChoice == 0 || difficulty == 0){
        QMessageBox warning;
        warning.setText("You must specify a ship and difficulty choice!");
        warning.exec();
        return;
    }
    aboard = new Board(this, shipChoice, difficulty);
    this->setCentralWidget(aboard);

    //when the aboard object is deleted, which happens when the game is lost, it will send out the destroyed signal and recreate the window!
    connect(aboard, SIGNAL(destroyed()), this, SLOT(createWindow()));
    connect(aboard, SIGNAL(destroyed()), this, SLOT(repaint()));
    QCoreApplication::processEvents();
}
/**
    @brief a public slot that shows a new window with instructions when the "Instructions" button is clicked
    @param none
    @return none*/
void MainWindow::showInstructions(){
    QWidget *instructionsPage = new QWidget;
    instructionsPage->setFixedSize(500,500);
    QPixmap bkgnd(":/images/images/putin.jpg");
    bkgnd = bkgnd.scaled(instructionsPage->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    instructionsPage->setPalette(palette);



    QVBoxLayout *mainInstructions = new QVBoxLayout(instructionsPage);
    QLabel *instructionsText = new QLabel;
    instructionsText->setText("<font color = white><font size = 5>"
                              "The goal is simple: survive.  The politicians have finally destroyed the planet and humanity has looked to space "
                              "for refuge.  Your friends behind you aren't the best shot!  Watch out for friendly fire as their bullets may almost "
                              "get you.  In order to win, you must collect"
                              " all of the letters on the screen by pressing the letter you see on the keyboard.  Once you've collected enough artifacts, you win."
                              " the more you collect, the faster the game starts to go.  Good luck!</font>");
    mainInstructions->addWidget(instructionsText);
    instructionsText->setWordWrap(true);

    QPushButton *closeButton = new QPushButton;
    closeButton->setText("Return to Start Screen");
    mainInstructions->addWidget(closeButton);
    QObject::connect(closeButton, SIGNAL(clicked()), instructionsPage, SLOT(close()));

    instructionsPage->show();
}



/**
    @brief a public slot. this function calls setShip to make the gameplay ship the Star Trek Enterprise
    @param none
    @return none*/
void MainWindow::enterpriseChoice(){
    setShip(1);
}
/**
    @brief a public slot. this function calls setShip to make the gameplay ship the ship from the Cosmos
    @param none
    @return none*/
void MainWindow::cosmosChoice(){
   setShip(2);
}
/**
    @brief a public slot that sets the difficulty value of the game to 1, which is passed to the board object
    @param none
    @return none*/
void MainWindow::setEasy(){
    difficulty = 1;
}

/**
    @brief a public slot that sets the difficulty value of the game to 2, which is passed to the board object
    @param none
    @return none*/
void MainWindow::setMedium(){
    difficulty = 2;
}
/**
    @brief a public slot that sets the difficulty value of the game to 3, which is passed to the board object
    @param none
    @return none*/
void MainWindow::setHard(){
    difficulty = 3;
}
/**
    @brief a helper function that sets the ship to either the cosmos ship or the enterprise
    @param none
    @return none*/
void MainWindow::setShip(size_t choice){
    shipChoice = choice;
}
