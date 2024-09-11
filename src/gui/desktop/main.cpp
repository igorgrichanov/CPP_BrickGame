#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/icons/brick_game_icon.png"));
  brickGame::MainWindow w;
  w.show();
  return a.exec();
}
