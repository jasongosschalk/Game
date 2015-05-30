#ifndef BOARD_H
#define BOARD_H

#include"asteroid.h"
#include"bullets.h"
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
    void keyPressEvent(QKeyEvent *event);
    void updateShip(int px, int py, int nx, int ny);
    void checkCollision(int which);  //checks to see if the bullet or asteroid collided with the ship
    void updateLives();
    void gameOver();

    ~Board();

public slots:
       void updateAsteroids();
       void updateBullets();


private:
    Ui::Board *ui;
    QWidget *master; //where the enemies go
    QWidget *top;  //where the gameplay occurs
    QWidget *middle;  //where the gameplay occurs
    QWidget *bottom;  //where the score is and everything else is black
    QVBoxLayout *masterLayout;
    QHBoxLayout *enemies;
    QGridLayout *gameplay;
    QPoint *shipPosition;
    std::vector<Asteroid*> asteroidLocations;   //vector of pointers to Asteroid objects
    std::vector<Bullets*> bulletLocations;
    QLabel **gamePlayLabel;
    QLabel *shipLabel;
    QLabel **lives;
    QPixmap asteroid;
    QPixmap ship;
    QPixmap bullet;
    size_t numberAsteroids;
    int lifeCount;
    int boardSize;
    int whenToStart = 0;
    int numberEnemies;
    int whichPaintEvent;
    int whichCollision = 0; //which object to check for collision with

};

#endif // BOARD_H