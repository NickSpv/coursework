#include "my_view.h"

MyView::MyView(QWidget *parent) : QGraphicsView(parent) {
  m_originX = 0;
  m_originY = 0;
}

void MyView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        // Store original position.
        m_originX = event->x();
        m_originY = event->y();
    }
    QGraphicsView::mousePressEvent(event);
}

void MyView::mouseMoveEvent(QMouseEvent* event)
{
  if (static_cast<Plan*>(this->scene())->getCurrentActive() == 1) {
    if (event->buttons() & Qt::RightButton)
    {
        QPointF oldp = mapToScene(m_originX, m_originY);
        QPointF newP = mapToScene(event->pos());
        QPointF translation = newP - oldp;

        translate(translation.x(), translation.y());
        setTransformationAnchor(QGraphicsView::NoAnchor);

        m_originX = event->x();
        m_originY = event->y();
    }
  }
  QGraphicsView::mouseMoveEvent(event);
}

void MyView::wheelEvent(QWheelEvent* event) {

  const QPointF p0scene = mapToScene(event->pos());

  qreal factor = std::pow(1.01, event->delta());
  scale(factor, factor);

  const QPointF p1mouse = mapFromScene(p0scene);
  const QPointF move = p1mouse - event->pos(); // The move
  this->horizontalScrollBar()->setValue(move.x() + this->horizontalScrollBar()->value());
  this->verticalScrollBar()->setValue(move.y() + this->verticalScrollBar()->value());
}
