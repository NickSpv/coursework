#include "symbol.h"

Symbol::Symbol(int size, QString file_patch) : QGraphicsSvgItem(file_patch) {
  this->size = size;
  renderer = new QSvgRenderer(file_patch);
  this->file_path = file_patch;
  this->setSharedRenderer(renderer);
  this->scale = static_cast<qreal>(size) / std::max(this->renderer->defaultSize().width(), this->renderer->defaultSize().height());
  rotation = 0;
  isMovable = false;
}

QRectF Symbol::boundingRect() const {
  return QRectF(-0.5 * size, -0.5 * size, size, size);
}

void Symbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->translate(-0.5 * size ,-0.5 * size);
  painter->scale(scale, scale);
  QGraphicsSvgItem::paint(painter,option,widget);
}

void Symbol::setMovable(bool isMovable) {
  this->setFlag(QGraphicsItem::ItemIsMovable, isMovable);
  this->isMovable = isMovable;
}

void Symbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  if (this->isMovable) this->setRotation(this->rotation += 90);
  QGraphicsSvgItem::mouseDoubleClickEvent(event);
}
