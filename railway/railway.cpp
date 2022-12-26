#include "railway.h"

RailWay::RailWay(int from_x, int from_y, int to_x, int to_y) : QGraphicsItem() {
  this->from_x = from_x;
  this->from_y = from_y;
  this->to_x = to_x;
  this->to_y = to_y;
  this->height = to_x - from_x;
  this->width = to_y - from_y;
  this->len = std::sqrt(std::pow(to_x - from_x, 2) + std::pow(to_y - from_y, 2));
  this->trickness = 5;
}

QRectF RailWay::boundingRect() const {
  return QRectF(-0.5 * std::abs(height) - trickness, -0.5 * std::abs(width) - trickness,
                std::abs(height) + 2 * trickness, std::abs(width) + 2 * trickness);
}

void RailWay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  QPen pen_0(Qt::black);
  pen_0.setWidth(trickness + 2);
  painter->setPen(pen_0);
  painter->drawLine(-height * 0.5, -width * 0.5, height * 0.5, width * 0.5);
  QPen pen_1(Qt::gray);
  pen_1.setWidth(trickness);
  pen_1.setStyle(Qt::DashLine);
  painter->setPen(pen_1);
  painter->drawLine(-height * 0.5, -width * 0.5, height * 0.5, width * 0.5);
}
