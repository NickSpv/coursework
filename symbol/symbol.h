#pragma once

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPainter>
#include <iostream>

class Symbol : public QGraphicsSvgItem
{
  Q_OBJECT
public:
  Symbol(int size, QString file_patch);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
  void setMovable(bool);

public:
  int size;
  QString file_path;

private:
  qreal rotation;
  bool isMovable;
  qreal scale;
  QSvgRenderer *renderer;
};

