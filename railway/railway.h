#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <iostream>
#include <cmath>

class RailWay : public QGraphicsItem
{
public:
  RailWay(int from_x, int from_y, int to_x, int to_y);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

  int from_x;
  int from_y;
  int to_x;
  int to_y;
private:
  int len;
  int trickness;
  int width;
  int height;
  int orientation;
};

