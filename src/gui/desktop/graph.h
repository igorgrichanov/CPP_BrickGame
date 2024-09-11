#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>

#include "../../brick_game/common/common_classes.h"
#include "../../brick_game/common/common_defines.h"

/**
 * @file
 * @brief класс, отвечающий за отрисовку игрового поля и следующей фигуры
 */

namespace brickGame {
/**
 * @class Graph класс, отвечающий за отрисовку игрового поля и следующей фигуры
 *
 */
class Graph : public QGraphicsView {
 public:
  enum class GraphType : unsigned int { gameField, nextFigureField };

  Graph(GraphType graph_type, QGraphicsView *parent = nullptr);

  void drawGameField(GameInfo_t info);
  void drawMoving(GameInfo_t info);
  void drawNextFigure(GameInfo_t info);

 private:
  void applyBrushing(QGraphicsRectItem *rect, int color);

  QGraphicsScene *scene_;
  std::vector<QGraphicsRectItem *>
      rectangles_;  ///< указатели на кубики, выводимые на игровом поле и в поле
                    ///< следующей фигуры сохраняются, так как QGraphicsRectItem
                    ///< не привязываются ни к какому родителю и память не будет
                    ///< освобождена при очистке scene_

  int rows_;
  int cols_;

  qreal cell_width_;
  qreal cell_height_;
};
}  // namespace brickGame
#endif  // GRAPH_H
