#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <iostream>

class Ladder : public QGraphicsItem
{
public:
  Ladder(int height, int width, int side);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  void set(int x, int y);

  int side;
  int xf;
  int yf;
  int width;
  int height;
private:
};

