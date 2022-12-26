#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QGraphicsSvgItem>
#include <constants.h>
#include <symbol/symbol.h>
#include <ladder/ladder.h>
#include <railway/railway.h>
#include <iostream>

class Plan : public QGraphicsScene
{
  Q_OBJECT
public:
  explicit Plan(QObject *parent = nullptr);

  void setCurrentActive(int index);
  int getCurrentActive();

signals:
  void press(QPointF);
  void move(QPointF);
  void release(QPointF);
  void setItemsMovable(bool);
  void removeItems(bool);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
  void addBackground(QRectF rect);

private:
  int current_active;
  bool is_clicked_left;
  bool is_clicked_right;
  QGraphicsRectItem *background;
  QGraphicsItem *current_item;
  QPointF last_click_position;
};

