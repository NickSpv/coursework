#include "plan.h"

Plan::Plan(QObject *parent) : QGraphicsScene{parent} {
  connect(this, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(addBackground(QRectF)));
  this->current_active = 1;
  this->is_clicked_left = false;
  this->is_clicked_right = false;
  this->current_item = nullptr;
}

void Plan::addBackground(QRectF rect) {
  this->background = new QGraphicsRectItem(rect);
  this->background->setPen(QPen(Qt::black));
  this->background->setBrush(QBrush(Qt::white));
  this->addItem(this->background);
}

void Plan::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "press" << std::endl;
  if (event->button() & Qt::LeftButton)
    this->is_clicked_left = true;
  else if (event->button() & Qt::RightButton)
    this->is_clicked_right = true;
  this->last_click_position = event->scenePos();
  emit press(event->scenePos());
    QGraphicsItem *item;
    int size = 30;
    if (current_active >= 6) {
      item = new Symbol(size, PATCH[current_active - 6]);
      connect(this, SIGNAL(setItemsMovable(bool)), static_cast<Symbol*>(item), SLOT(setMovable(bool)));
      item->setPos(event->scenePos());
      if (event->scenePos().x() + 0.5 * size >= 0 && event->scenePos().x() <= this->height() - 0.5 * size &&
          event->scenePos().y() + 0.5 * size >= 0 && event->scenePos().y() <= this->width() - 0.5 * size) {
        this->addItem(item);
      } else {
        delete item;
      }
    } else if (current_active == 1 && is_clicked_right) {
      this->current_item = nullptr;

    } else {
      QGraphicsScene::mousePressEvent(event);
      return;
    }
  QGraphicsScene::mousePressEvent(event);
}

void Plan::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  emit move(event->scenePos());
  if (event->scenePos().x() >= 0 && event->scenePos().x() <= this->height() &&
          event->scenePos().y() >= 0 && event->scenePos().y() <= this->width()) {
  if (current_item != nullptr) {
    delete current_item;
    current_item = nullptr;
  }
  if (this->current_active == 5 && this->is_clicked_left && this->itemAt(event->scenePos(), QTransform()) != background)
    delete this->itemAt(event->scenePos(), QTransform());
  else if (this->current_active == 4) {
    Ladder *ladder;
    int height = event->scenePos().x() - this->last_click_position.x();
    int width = event->scenePos().y() - this->last_click_position.y();
    //std::cout << height << " " << width << std::endl;
    if (width > 4 && height > 4) {
      if (this->is_clicked_left) ladder = new Ladder(width, height, 2);
      else if (this->is_clicked_right) ladder = new Ladder(width, height, 1);
      if (this->is_clicked_left || this->is_clicked_right) {
        ladder->setPos((int)this->last_click_position.x() + (int)height * 0.5, (int)this->last_click_position.y() + (int)width * 0.5);
        this->current_item = ladder;
        ladder->set(last_click_position.x(), last_click_position.y());
        this->addItem(ladder);
        std::cout << "move" << std::endl;
      }
    }
  } else if (this->current_active == 3 && this->is_clicked_left) {
    RailWay *railway = new RailWay(this->last_click_position.x(), this->last_click_position.y(),
                                   event->scenePos().x(), event->scenePos().y());
    railway->setPos((int)this->last_click_position.x() + ((int)event->scenePos().x() - (int)this->last_click_position.x()) * 0.5,
                    (int)this->last_click_position.y() + ((int)event->scenePos().y() - (int)this->last_click_position.y()) * 0.5);
    this->current_item = railway;
    this->addItem(railway);
  } else if (this->current_active == 2 && this->is_clicked_left) {
    QGraphicsLineItem *wall = new QGraphicsLineItem(this->last_click_position.x(),
                                                    this->last_click_position.y(),
                                                    event->scenePos().x(),
                                                    event->scenePos().y());
    this->current_item = wall;
    QPen pen;
    pen.setWidth(5);
    wall->setPen(pen);
    this->addItem(wall);
  } else if (this->current_active == 0 && this->is_clicked_left) {
    QGraphicsLineItem *wall = new QGraphicsLineItem(this->last_click_position.x(),
                                                    this->last_click_position.y(),
                                                    event->scenePos().x(),
                                                    event->scenePos().y());
    this->current_item = wall;
    QPen pen(Qt::gray);
    pen.setWidth(8);
    wall->setPen(pen);
    this->addItem(wall);
  }
  }
  QGraphicsScene::mouseMoveEvent(event);
}

void Plan::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "release" << std::endl;
  this->current_item = nullptr;
  if (event->button() & Qt::LeftButton)
    this->is_clicked_left = false;
  else if (event->button() & Qt::RightButton)
    this->is_clicked_right = false;
  emit release(event->scenePos());
  QGraphicsScene::mouseReleaseEvent(event);
}

void Plan::setCurrentActive(int index) {
  this->current_active = index;
  if (index == 1) emit setItemsMovable(true);
  else emit setItemsMovable(false);
}

int Plan::getCurrentActive() {
  return this->current_active;
}
