#ifndef BOARD_H
#define BOARD_H

#include"boardobject.h"
#include"bullets.h"
#include"asteroid.h"
#include"ship.h"
#include"artifacts.h"
#include <QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QRadioButton>
#include<QPushButton>
#include<QGridLayout>
#include<QSpacerItem>
#include<QPixmap>
#include<QTimer>
#include<QPaintEvent>
#include<QString>
#include<QLCDNumber>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<QPalette>
#include<QKeyEvent>
#include<QPoint>
#include<cmath>
#include<vector>
#include<QMessageBox>
#include<QProcess>
#include<QStackedWidget>

namespace Ui {
class Board;
}
/**
    @class Board
    @brief this class created the gameplay board and is called from the mainwindow.cpp file.  it is used to draw every part of the game and contains code
            for the interactivity, etc.  It uses boardObjects.*/
class Board : public QWidget
{
    Q_OBJECT


public:
    explicit Board(QWidget *parent = 0, size_t shipChoice = 1, size_t difficulty = 1);
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void updateShip(int px, int py, int nx, int ny);
    bool checkAsteroidCollision();  //checks to see if the bullet or asteroid collided with the ship
    bool checkBulletCollision();  //checks to see if the bullet or asteroid collided with the ship
    void catchArtifact(char lettre);
    void updateLives();
    void gameWon();
    void gameLost();
    void makeBoard(size_t shipChoice, size_t difficulty);//draws the board out
    void makeBoardAgain(size_t shipChoice, size_t difficulty);

    void levelUp();
    void levelUpAlert();

    ~Board();

public slots:
       void updateAsteroids();
       void updateBullets();
       void showArtifact();
       void gameOver(int whichOne);

       //void closeTime();

private:
    Ui::Board *ui;
    QWidget *master; //where the enemies go
    QWidget *top;  //where the gameplay occurs
    QWidget *middle;  //where the gameplay occurs
    QWidget *bottom;  //where the score is and everything else is black
    QVBoxLayout *masterLayout;
    QHBoxLayout *enemies;
    QPushButton *quit;
    QGridLayout *gameplay;
    Ship *shipPosition;
    std::vector<Asteroid*> asteroidLocations;   //vector of pointers to Asteroid objects
    std::vector<Bullets*> bulletLocations;
    std::vector<Artifacts*> artifacts;
    QLabel **gamePlayLabel;
    QLabel *shipLabel;
    QLabel **lives;
    QLabel *livesDescription;
    QGridLayout *bottomInfo;
    QPixmap asteroid;
    QPixmap shipPic;
    QPixmap bullet;
    QPixmap heart;
    size_t numberAsteroids;
    int lifeCount;
    size_t boardSize;
    int whenToStart;
    int numberEnemies;
    int whichPaintEvent;
    int whichCollision; //which object to check for collision with
    bool artifactVisible;
    std::vector<Artifacts*>::iterator check;
    //QLabel *artifactString;
    int winGame;            //tracks how many artifacts are collected.
    QTimer *timer;  //for the asteroids
    QTimer *timer3; //for the artifacts
    size_t boardDifficulty;
    size_t boardShipChoice;
    size_t winGameTracker;  //helper value to remember what the value of artifact collection was

};

#endif // BOARD_H
