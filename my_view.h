#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <plan/plan.h>
#include <cmath>
#include <iostream>

class MyView : public QGraphicsView
{
  Q_OBJECT
public:
  MyView(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

private:
  int m_originX;
  int m_originY;
};
