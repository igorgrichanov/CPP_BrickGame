#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace brickGame {

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(454, 704);
  controller_ = controller;
  game_field_ = new Graph(Graph::GraphType::gameField, ui->game_field);
  next_figure_ =
      new Graph(Graph::GraphType::nextFigureField, ui->next_figure_field);
  timer_ = new QTimer;

  setArrowIcons();
  setInputNameLine();
  setChooseGameLines();

  connect(user_game_choice, &QLineEdit::editingFinished, this,
          &MainWindow::slotChooseGame);
  connect(name_line_edit, &QLineEdit::editingFinished, this,
          &MainWindow::slotSaveUserName);
}

void MainWindow::setArrowIcons() {
  QIcon leftArrowIcon(":/icons/left.png");
  ui->leftButton->setIcon(leftArrowIcon);

  QIcon rightArrowIcon(":/icons/right.png");
  ui->rightButton->setIcon(rightArrowIcon);

  QIcon upArrowIcon(":/icons/up.png");
  ui->upButton->setIcon(upArrowIcon);

  QIcon downArrowIcon(":/icons/down.png");
  ui->downButton->setIcon(downArrowIcon);
}

void MainWindow::setChooseGameLines() {
  game_option_1 = new QLabel(ui->gameFrame);
  game_option_2 = new QLabel(ui->gameFrame);
  user_game_choice = new QLineEdit(ui->gameFrame);
  error_label = new QLabel(ui->gameFrame);

  QFont font;
  font.setFamilies({QString::fromUtf8("Charter")});

  game_option_1->setGeometry(40, 80, 171, 31);
  game_option_1->setFont(font);
  game_option_1->setText(QCoreApplication::translate(
      "MainWindow",
      "<html><head/><body><p><span style=\" font-size:18pt;\">Send 1 to play "
      "Tetris</span></p></body></html>",
      nullptr));

  game_option_2->setGeometry(40, 120, 171, 31);
  game_option_2->setFont(font);
  game_option_2->setText(QCoreApplication::translate(
      "MainWindow",
      "<html><head/><body><p><span style=\" font-size:18pt;\">Send 2 to play "
      "Snake</span></p></body></html>",
      nullptr));

  user_game_choice->setGeometry(107, 160, 31, 21);
  user_game_choice->setMaxLength(1);
  user_game_choice->setAlignment(Qt::AlignCenter);
  user_game_choice->setFont(font);
  user_game_choice->setFocus();
  font.setPointSize(15);

  error_label->setGeometry(30, 200, 181, 31);
  error_label->setFont(font);
  error_label->setAlignment(Qt::AlignCenter);
  error_label->setVisible(false);
}

void MainWindow::removeChooseGameLines() {
  game_option_1->hide();
  game_option_2->hide();
  user_game_choice->hide();
  user_game_choice->setReadOnly(true);
}

void MainWindow::slotChooseGame() {
  std::string game_str = user_game_choice->text().toStdString();
  int game = -1;
  try {
    game = std::stoi(game_str) - 1;
  } catch (const std::invalid_argument &e) {
    game = -1;
  }

  if (!(game == TETRIS_ID || game == SNAKE_ID) && !error_label->isVisible()) {
    error_label->setVisible(true);
    error_label->setText(QCoreApplication::translate(
        "MainWindow",
        "<html><head/><body><p><span style=\" font-size:18pt;\">Send correct "
        "digit</span></p></body></html>",
        nullptr));
  }
  if (game == TETRIS_ID || game == SNAKE_ID) {
    name_line_edit->setReadOnly(false);
    name_line_edit->setFocus();
    error_label->setVisible(false);
    removeChooseGameLines();
    game_ = game;
  }
}

void MainWindow::setInputNameLine() {
  QFont font;
  font.setFamilies({QString::fromUtf8("Charter")});
  font.setPointSize(15);

  name_line_edit = new QLineEdit(ui->gameFrame);
  name_line_edit->setGeometry(QRect(40, 260, 151, 21));
  name_line_edit->setMaxLength(12);
  name_line_edit->setFont(font);
  name_line_edit->setPlaceholderText("Your name:");
  name_line_edit->setReadOnly(true);
}

void MainWindow::removeInputNameLine() {
  name_line_edit->setReadOnly(true);
  name_line_edit->hide();
}

void MainWindow::slotSaveUserName() {
  std::string str = name_line_edit->text().toStdString();
  if (str.length() > 1) {
    char *user_name = (char *)calloc((str.length() + 1), sizeof(char));
    std::strcpy(user_name, str.c_str());

    removeInputNameLine();

    initGame(user_name);
  } else if (!error_label->isVisible()) {
    error_label->setVisible(true);
    error_label->setText(QCoreApplication::translate(
        "MainWindow",
        "<html><head/><body><p><span style=\" font-size:18pt;\">At least 2 "
        "characters</span></p></body></html>",
        nullptr));
  }
}

void MainWindow::initGame(char *user_name) {
  if (game_ == TETRIS_ID) {
    GameInfo_t *info = init_game_info_tetris(user_name);
    current_game_info(info);
    current_state_machine(init_state_machine_tetris());

    controller_ = new TetrisController;
  } else if (game_ == SNAKE_ID) {
    controller_ = new SnakeController(user_name);
  }
  ui->pauseButton->setCheckable(true);
  ui->userNameLabel->setText(user_name);
  connectButtons();
  error_label->setVisible(false);

  timer_->start(50);
  setFocus();
}

void MainWindow::connectButtons() {
  connect(ui->leftButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(LEFT); });
  connect(ui->rightButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(RIGHT); });
  connect(ui->downButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(DOWN); });
  connect(ui->upButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(UP); });
  connect(ui->startButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(START); });
  connect(ui->pauseButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(PAUSE); });
  connect(ui->exitButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(TERMINATE); });
  connect(ui->actionButton, &QPushButton::clicked, this,
          [this]() { inputProcessing(ACTION); });
  connect(timer_, &QTimer::timeout, this,
          [this]() { inputProcessing(NO_ACTION); });
}

void MainWindow::inputProcessing(UserAction_t action) {
  if (!controller_) return;

  controller_->userInput(action);
  info_ = updateCurrentState();

  if (info_.score == -1) {
    QApplication::instance()->quit();
  } else {
    drawWrapper();
    printGameInfo();
  }
}

void MainWindow::printGameInfo() {
  ui->currentScoreLabel->setText(QString::number(info_.score));
  ui->bestScoreLabel->setText(QString::number(info_.high_score));
  ui->currentLevelLabel->setText(QString::number(info_.level));
}

void MainWindow::drawWrapper() {
  if (info_.game_won) {
    error_label->setVisible(true);
    error_label->setText(QCoreApplication::translate(
        "MainWindow",
        "<html><head/><body><p><span style=\" font-size:18pt;\">YOU "
        "WON</span></p></body></html>",
        nullptr));
    game_field_->drawGameField(info_);
  } else if (info_.game_over) {
    error_label->setVisible(true);
    error_label->setText(QCoreApplication::translate(
        "MainWindow",
        "<html><head/><body><p><span style=\" font-size:18pt;\">GAME "
        "OVER</span></p></body></html>",
        nullptr));
    game_field_->drawGameField(info_);
  } else if (!info_.pause) {
    ui->pauseButton->setChecked(false);
    error_label->setVisible(false);
    game_field_->drawGameField(info_);
    game_field_->drawMoving(info_);
    if (game_ == TETRIS_ID) next_figure_->drawNextFigure(info_);
  } else if (info_.pause)
    ui->pauseButton->setChecked(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      inputProcessing(LEFT);
      break;
    case Qt::Key_Right:
      inputProcessing(RIGHT);
      break;
    case Qt::Key_Down:
      inputProcessing(DOWN);
      break;
    case Qt::Key_Up:
      inputProcessing(UP);
      break;
    case Qt::Key_Return:
      inputProcessing(START);
      break;
    case Qt::Key_P:
      inputProcessing(PAUSE);
      break;
    case Qt::Key_Q:
      inputProcessing(TERMINATE);
      break;
    case Qt::Key_Space:
      inputProcessing(ACTION);
      break;
    default:
      QWidget::keyPressEvent(event);
      break;
  }
}

MainWindow::~MainWindow() {
  delete ui;
  if (game_ == TETRIS_ID) {
    destroy_game_info();
    destroy_state_machine();
  }
  delete controller_;
  delete game_field_;
  delete next_figure_;
  delete timer_;
}

}  // namespace brickGame
