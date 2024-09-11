#include "graph.h"

namespace brickGame {
Graph::Graph(GraphType graph_type, QGraphicsView *parent)
    : QGraphicsView(parent), scene_(new QGraphicsScene(this)) {
  setScene(scene_);
  scene_->addRect(0, 0, parent->width(), parent->height());

  if (graph_type == GraphType::gameField) {
    rows_ = FIELD_ROWS;
    cols_ = FIELD_COLUMNS;
    cell_width_ = static_cast<qreal>(parent->width() / cols_);
    cell_height_ = static_cast<qreal>(parent->height() / rows_);
  } else if (graph_type == GraphType::nextFigureField) {
    rows_ = 2;
    cols_ = 4;
    cell_width_ = static_cast<qreal>(parent->width() / cols_);
    cell_height_ = static_cast<qreal>(parent->height() / rows_);
  }
}

void Graph::drawGameField(GameInfo_t info) {
  rectangles_.clear();
  scene_->clear();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (info.field[i][j] >= 1 && info.field[i][j] <= 7) {
        QGraphicsRectItem *rect = new QGraphicsRectItem(
            j * cell_width_, i * cell_height_, cell_width_, cell_height_);
        applyBrushing(rect, info.field[i][j]);
        rectangles_.push_back(rect);
        scene_->addItem(rect);
      }
    }
  }
}

void Graph::drawMoving(GameInfo_t info) {
  int row = info.moving->row, col = info.moving->col;
  int rows = info.moving->rows, columns = info.moving->columns;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (info.moving->figure[i][j] && row + i >= 0) {
        QGraphicsRectItem *rect = new QGraphicsRectItem(
            (col + j) * cell_width_, (row + i) * cell_height_, cell_width_,
            cell_height_);
        applyBrushing(rect, info.moving->figure[i][j]);
        rectangles_.push_back(rect);
        scene_->addItem(rect);
      }
    }
  }
}

void Graph::drawNextFigure(GameInfo_t info) {
  rectangles_.clear();
  scene_->clear();
  int j_shift = 0;
  if (info.next_idx == 4) {
    cols_ = 2;
    j_shift = 1;
  } else if (info.next_idx != 1) {
    cols_ = 3;
  } else if (info.next_idx == 1) {
    cols_ = 4;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (info.next[i][j]) {
        QGraphicsRectItem *rect =
            new QGraphicsRectItem((j_shift + j) * cell_width_, i * cell_height_,
                                  cell_width_, cell_height_);
        applyBrushing(rect, info.next[i][j]);
        rectangles_.push_back(rect);
        scene_->addItem(rect);
      }
    }
  }
}

void Graph::applyBrushing(QGraphicsRectItem *rect, int color) {
  switch (color) {
    case 1:
      rect->setBrush(QBrush(Qt::cyan));
      break;
    case 2:
      rect->setBrush(QBrush(Qt::blue));
      break;
    case 3:
      rect->setBrush(QBrush(Qt::white));
      break;
    case 4:
      rect->setBrush(QBrush(Qt::yellow));
      break;
    case 5:
      rect->setBrush(QBrush(Qt::green));
      break;
    case 6:
      rect->setBrush(QBrush(Qt::magenta));
      break;
    case 7:
      rect->setBrush(QBrush(Qt::red));
      break;
    default:
      break;
  }
}
}  // namespace brickGame
