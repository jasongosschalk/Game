#include "mainwindow.h"
#include "board.h"
#include <QApplication>
/*
echo "# QtSpaceGame" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/jasongosschalk/QtSpaceGame.git
git push -u origin master
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
