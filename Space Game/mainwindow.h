#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"board.h"


#include<QLabel>
#include<QLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QRadioButton>
#include<QPushButton>
#include<QGridLayout>
#include<QSpacerItem>
#include<QButtonGroup>
#include<QMessageBox>
#include<QMovie>
#include<QRadioButton>
#include<QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //void createWindow();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void setDifficulty(size_t choice);
    void setShip(size_t choice);

public slots:
    void createWindow();    //draws the mainwindow that we see to start the game
    void gameBegin();       //calls creation of new Board Object
    void showInstructions();    //shows instructions in a new window
    void enterpriseChoice();    //sets the choice of ship to enterprise
    void cosmosChoice();        //sets the choice of the ship to the cosmos
    void setEasy();             //sets the difficulty
    void setMedium();           //sets the difficulty
    void setHard();             //sets the difficulty

private:
    Ui::MainWindow *ui;
    Board *aboard;

    QWidget *welcomePage; //main page
    QWidget *topWidget;
    QWidget *middleWidget;
    QWidget *bottomWidget;
    QLabel *titleText;          //welcome to space survival
    QLabel *explanationText;    //intro below the title of the game
    QVBoxLayout *allLayouts;    //contains all allTop, middle, bottom
    QHBoxLayout *top;           //contains top and explanation
    QHBoxLayout *middle;        //contains leftSide and rightSide
    QVBoxLayout *bottom;        //contains the start button
    QVBoxLayout *leftSide;      //contains ship options
    QVBoxLayout *rightSide;     //contains difficulty level options
    QHBoxLayout *title;         //contains title
    QHBoxLayout *explanation;   //contains explanation of game
    QRadioButton *cosmos;       //radio button for cosmos selection
    QRadioButton *enterprise;   //radio button for enterprise selection
    QRadioButton *easy;         //radio button for easy difficulty
    QRadioButton *medium;       //radio button for medium difficulty
    QRadioButton *hard;         //radio button for hard difficulty
    QPushButton *start;         //starts a new game by calling slot gameBegin()
    QPushButton *directions;    //calls slot to show directions
    QButtonGroup *shipGroup;    //creates a button group so that only one is selected at a time even though compiler will do this for you
    QButtonGroup *difficultyGroup;  //creates button group

    size_t shipChoice; //1==cosmos, 2==enterprise
    size_t difficulty;  //sets difficulty
    //bool mustRemake;    //this is nothing, needs to be deleted.
};

#endif // MAINWINDOW_H
