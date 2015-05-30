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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void setDifficulty(size_t choice);
    void setShip(size_t choice);

public slots:
    void GameBegin();
    void showInstructions();
    void enterpriseChoice();
    void cosmosChoice();
    void setEasy();
    void setMedium();
    void setHard();

private:
    Ui::MainWindow *ui;
    Board *aboard;

    QWidget *welcomePage; //main page
    QWidget *topWidget;
    QWidget *middleWidget;
    QWidget *bottomWidget;
    QLabel *titleText;     //welcome to space survival
    QLabel *explanationText; //intro below the title of the game
    QVBoxLayout *allLayouts; //contains all allTop, middle, bottom
    QHBoxLayout *top;    //contains top and explanation
    QHBoxLayout *middle;    //contains leftSide and rightSide
    QVBoxLayout *bottom;    //contains the start button
    QVBoxLayout *leftSide;  //contains ship options
    QVBoxLayout *rightSide; //contains difficulty level options
    QHBoxLayout *title;       //contains title
    QHBoxLayout *explanation;   //contains explanation of game
    QRadioButton *cosmos;
    QRadioButton *enterprise;
    QRadioButton *easy;
    QRadioButton *medium;
    QRadioButton *hard;
    QPushButton *start;
    QPushButton *directions;
    QButtonGroup *shipGroup;
    QButtonGroup *difficultyGroup;

    size_t shipChoice; //1==cosmos, 2==enterprise
    size_t difficulty;

};

#endif // MAINWINDOW_H
