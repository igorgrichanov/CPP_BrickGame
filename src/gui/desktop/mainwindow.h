#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTimer>
#include <cstring>
#include <iostream>
#include <string>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/tetris/controller.h"
#include "graph.h"

/**
 * @file
 * @brief класс главного окна приложения
 */

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace brickGame {

/**
 * @class MainWindow класс главного окна приложения
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief конструктор главного окна приложения
   *
   * @param controller класс, удовлетворяющий интерфейсу Controller. Контроллер
   * инициализируется в зависимости от того, каую игру выберет пользователь
   * после запуска
   * @param parent родительский виджет. Не передается для главного окна
   */
  MainWindow(Controller *controller = nullptr, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void slotSaveUserName();
  void slotChooseGame();

 private:
  Ui::MainWindow *ui;
  Controller *controller_;

  Graph *game_field_;  ///< объект, осуществляющий печать игрового поля
  Graph *next_figure_;  ///< объект, осуществляющий печать следующей фигуры,
                        ///< если она предусмотрена в игре
  QTimer *timer_;  ///< таймер обновления интерфейса

  QLabel *game_option_1 =
      nullptr;  ///< поле для вывода вспомогательного текста в начале игры
  QLabel *game_option_2 =
      nullptr;  ///< поле для вывода вспомогательного текста в начале игры
  QLineEdit *user_game_choice =
      nullptr;  ///< поле, принимающее ID игры от пользователя
  QLabel *error_label = nullptr;  ///< поле для вывода ошибок и вспомогательной
                                  ///< информации по ходу игры
  QLineEdit *name_line_edit =
      nullptr;  ///< поле, принимающее никнейм от пользователя

  int game_;  ///<  ID игры
  GameInfo_t info_;

  /**
   * @brief установка иконок-стрелок на кнопках BrickGame
   *
   */
  void setArrowIcons();

  /**
   * @brief инициализация полей для ввода порядкового номера игры и
   * дополнительной информации, необходимо для принятия пользователем решения
   *
   */
  void setChooseGameLines();

  /**
   * @brief сокрытие полей, предназначенных для приема номера игры
   *
   */
  void removeChooseGameLines();

  /**
   * @brief инициализация поля, принимающего имя пользователя
   *
   */
  void setInputNameLine();

  /**
   * @brief сокрытие поля, принимающего имя пользователя
   *
   */
  void removeInputNameLine();

  /**
   * @brief инициализация контроллера и GameInfo_t в соответствии с полученной
   * от пользователя информацией (никнейм и ID игры)
   *
   * @param user_name имя пользователя
   */
  void initGame(char *user_name);

  /**
   * @brief подключение кнопок на панели BrickGame к конечному автомату
   *
   */
  void connectButtons();

  /**
   * @brief центральная функция обработки запросов, приходящих с интерфейса
   *
   * @param action действие пользователя
   */
  void inputProcessing(UserAction_t action);

  /**
   * @brief вывод на экран дополнительной информации об игре
   *
   */
  void printGameInfo();

  /**
   * @brief функция, отвечающая за печать на игровом поле
   *
   */
  void drawWrapper();

  /**
   * @brief обработка ввода с клавиатуры
   *
   * @param event событие, произошедшее на MainWindow
   */
  void keyPressEvent(QKeyEvent *event) override;
};
}  // namespace brickGame
#endif  // MAINWINDOW_H
