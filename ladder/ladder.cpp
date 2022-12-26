#include "ladder.h"

Ladder::Ladder(int width, int height, int side) : QGraphicsItem() {
  this->height = height;
  this->width = width;
  this->side = side;
}

QRectF Ladder::boundingRect() const {
  return QRectF(-this->height * 0.5, -this->width * 0.5, this->height, this->width);
}

void Ladder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->setPen(Qt::SolidLine);
  int h = height - 2, w = width - 2;
  if (side == 1) {
    painter->drawLine(-0.5 * h, 0.5 * w, 0.5 * h, 0.5 * w);
    painter->drawLine(-0.5 * h, -0.5 * w, 0.5 * h, -0.5 * w);
    for (int i = 0.5 * h; i > -0.5 * h; i -= 10) {
      painter->drawLine(i, -0.5 * w, i, 0.5 * w);
    }
  } else if (side == 2) {
    painter->drawLine(0.5 * h, -0.5 * w, 0.5 * h, 0.5 * w);
    painter->drawLine(-0.5 * h, -0.5 * w, -0.5 * h, 0.5 * w);
    for (int i = 0.5 * w; i > -0.5 * w; i -= 10) {
      painter->drawLine(-0.5 * h, i, 0.5 * h, i);
    }
  }
}

void Ladder::set(int x, int y) {
  xf = x;
  yf = y;
}
