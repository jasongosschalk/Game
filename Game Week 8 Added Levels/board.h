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

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT


public:
    explicit Board(QWidget *parent = 0, size_t shipChoice = 1, size_t difficulty = 1);
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *c);
    void keyPressEvent(QKeyEvent *event);
    void updateShip(int px, int py, int nx, int ny);
    bool checkAsteroidCollision();  //checks to see if the bullet or asteroid collided with the ship
    bool checkBulletCollision();  //checks to see if the bullet or asteroid collided with the ship
    void catchArtifact(char lettre);
    void updateLives();
    void gameOver();

    ~Board();

public slots:
       void updateAsteroids();
       void updateBullets();
       void showArtifact();
       //void closeTime();

private:
    Ui::Board *ui;
    QWidget *master; //where the enemies go
    QWidget *top;  //where the gameplay occurs
    QWidget *middle;  //where the gameplay occurs
    QWidget *bottom;  //where the score is and everything else is black
    QVBoxLayout *masterLayout;
    QHBoxLayout *enemies;
    QGridLayout *gameplay;
    Ship *shipPosition;
    std::vector<Asteroid*> asteroidLocations;   //vector of pointers to Asteroid objects
    std::vector<Bullets*> bulletLocations;
    std::vector<Artifacts*> artifacts;
    QLabel **gamePlayLabel;
    QLabel *shipLabel;
    QLabel **lives;
    QPixmap asteroid;
    QPixmap shipPic;
    QPixmap bullet;
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
    int winGame;

};

#endif // BOARD_H
