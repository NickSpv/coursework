#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  plan = new Plan();
  int size_plan_x = 500;
  int size_plan_y = 500;
  plan->setSceneRect(0, 0, size_plan_x, size_plan_y);
  plan->setBackgroundBrush(Qt::gray);
  ui->graphicsView->setScene(plan);
  ui->graphicsView->setMouseTracking(true);
  connect(plan, SIGNAL(press(QPointF)), this, SLOT(pressScene(QPointF)));
  connect(plan, SIGNAL(move(QPointF)), this, SLOT(moveScene(QPointF)));
  connect(plan, SIGNAL(release(QPointF)), this, SLOT(releaseScene(QPointF)));
  connect(ui->action_3, SIGNAL(triggered()), this, SLOT(createNewPlan()));
  connect(ui->action_4, SIGNAL(triggered()), this, SLOT(savePlanToImage()));
  connect(ui->action_2, SIGNAL(triggered()), this, SLOT(save()));
  connect(ui->action_1, SIGNAL(triggered()), this, SLOT(load()));
  id_item = 0;
  start_position = QPointF(-1, -1);
  current_item = nullptr;
}

MainWindow::~MainWindow()
{
  delete ui;
  delete plan;
}

void MainWindow::pressScene(QPointF point) {

}

void MainWindow::moveScene(QPointF point) { 

}

void MainWindow::releaseScene(QPointF point) {
}

void MainWindow::createNewPlan() {
  bool ok_0, ok_1;
  int x = QInputDialog::getInt(this, tr("Введите размеры нового плана"),
                               tr("Ширина:"), 500, 200, 1500, 1, &ok_0);
  int y = QInputDialog::getInt(this, tr("Введите размеры нового плана"),
                               tr("Высота:"), 500, 200, 1500, 1, &ok_1);
  if (ok_0 && ok_1) {
    delete plan;
    plan = new Plan();
    plan->setSceneRect(0, 0, x, y);
    ui->graphicsView->setScene(plan);
    plan->setBackgroundBrush(Qt::gray);
    connect(plan, SIGNAL(press(QPointF)), this, SLOT(pressScene(QPointF)));
    connect(plan, SIGNAL(move(QPointF)), this, SLOT(moveScene(QPointF)));
    connect(plan, SIGNAL(release(QPointF)), this, SLOT(releaseScene(QPointF)));
  }
}

void MainWindow::on_toolButton_clicked() {
  this->plan->setCurrentActive(1);
}


void MainWindow::on_pushButton_2_clicked() {
  this->plan->setCurrentActive(2);
}


void MainWindow::on_pushButton_clicked() {
  this->plan->setCurrentActive(3);
}


void MainWindow::on_pushButton_4_clicked() {
  this->plan->setCurrentActive(4);
}


void MainWindow::on_pushButton_3_clicked() {
  int index = ui->comboBox->currentIndex();
  switch (index) {
    case 0:
      this->plan->setCurrentActive(6);
      break;
    case 1:
      this->plan->setCurrentActive(7);
      break;
    case 2:
      this->plan->setCurrentActive(8);
      break;
    case 3:
      this->plan->setCurrentActive(9);
      break;
    case 4:
      this->plan->setCurrentActive(10);
      break;
    case 5:
      this->plan->setCurrentActive(11);
      break;
  }
}


void MainWindow::on_pushButton_5_clicked() {
  this->plan->setCurrentActive(5);
}

void MainWindow::savePlanToImage() {
  QString file_name = QFileDialog::getSaveFileName(this, "Сохранить", "", ".png");
  QImage image(plan->width(), plan->height(), QImage::Format_ARGB32_Premultiplied);
  QPainter painter(&image);
  plan->render(&painter);
  image.save(file_name);
  std::cout << file_name.toStdString() << std::endl;
}

void MainWindow::on_pushButton_6_clicked() {
  this->plan->setCurrentActive(0);
}

void MainWindow::save() {
  std::cout << "SAVE" << std::endl;
  QJsonArray figures;
  QList<QGraphicsItem*> all = this->plan->items();
  for (int i = 0; i < all.size(); i++) {
    QGraphicsItem *obj = all[i];
    QJsonObject jsonObject;
    if (dynamic_cast<Symbol *>(obj) != nullptr) {
      Symbol *symbol = dynamic_cast<Symbol *>(obj);
      jsonObject["type"] = 6;
      jsonObject["size"] = symbol->size;
      jsonObject["file_patch"] = symbol->file_path;
      jsonObject["pos_x"] = static_cast<int>(symbol->scenePos().x());
      jsonObject["pos_y"] = static_cast<int>(symbol->scenePos().y());
    } else if (dynamic_cast<RailWay *>(obj) != nullptr) {
      RailWay *railway = dynamic_cast<RailWay*>(obj);
      jsonObject["type"] = 5;
      jsonObject["xfr"] = railway->from_x;
      jsonObject["yfr"] = railway->from_y;
      jsonObject["xto"] = railway->to_x;
      jsonObject["yto"] = railway->to_y;
    } else if (dynamic_cast<QGraphicsLineItem *>(obj) != nullptr) {
      QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem*>(obj);
      jsonObject["type"] = 3;
      jsonObject["fromx"] = line->line().x1();
      jsonObject["fromy"] = line->line().y1();
      jsonObject["tox"] = line->line().x2();
      jsonObject["toy"] = line->line().y2();
      jsonObject["width"] = line->pen().width();
    } else if (dynamic_cast<Ladder *>(obj) != nullptr) {
      Ladder *ladder = dynamic_cast<Ladder*>(obj);
      jsonObject["type"] = 4;
      jsonObject["width"] = ladder->width;
      jsonObject["height"] = ladder->height;
      jsonObject["xf"] = ladder->xf;
      jsonObject["yf"] = ladder->yf;
      jsonObject["side"] = ladder->side;
    }
    if (!jsonObject.empty())
    figures.append(jsonObject);
  }
  QJsonDocument document(figures);
  QByteArray bytes = document.toJson(QJsonDocument::Indented);
  QString fileName = QFileDialog::getSaveFileName(
      this, "Сохранить", QCoreApplication::applicationDirPath(),
      "") + ".json";
  if (!fileName.isNull()) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
      QTextStream iStream(&file);
      iStream.setCodec("utf-8");
      iStream << bytes;
      file.close();
    } else {
      std::cout << "file open failed" << std::endl;
    }
  }
}

void MainWindow::load() {
  std::cout << "LOAD\n";
  QString fileName = QFileDialog::getOpenFileName(
      this, "Load base", QCoreApplication::applicationDirPath(),
      "");
  if (!fileName.isNull()) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
      QByteArray bytes = file.readAll();
      file.close();

      QJsonParseError jsonError;
      QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);
      if (jsonError.error != QJsonParseError::NoError) {
        std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
        return;
      }
      if (document.isArray()) {
        QJsonArray jsonArr = document.array();
        this->plan->clear();
        //plan->setSceneRect(0, 0, 500, 500);
        plan->addBackground(this->plan->sceneRect());
        for (int i = 0; i < jsonArr.count(); ++i) {
          QJsonObject jsonObj = jsonArr.at(i).toObject();
          int type = jsonObj.take("type").toInt();
          //QGraphicsItem* figure = nullptr;
          if (type == 3) {
              int from_x = jsonObj.take("fromx").toInt();
              int from_y = jsonObj.take("fromy").toInt();
              int to_x = jsonObj.take("tox").toInt();
              int to_y = jsonObj.take("toy").toInt();
              QGraphicsLineItem *figure = new QGraphicsLineItem(from_x, from_y, to_x, to_y);
              //figure->setEndPoint(QPointF(end_x, end_y));
              //std::cout << jsonObj.take("from_x").toInt() << std::endl;
              int width = jsonObj.take("width").toInt();
              QPen pen(width == 5 ? Qt::black : Qt::gray);
              pen.setWidth(width);
              static_cast<QGraphicsLineItem*>(figure)->setPen(pen);
              this->plan->addItem(figure);
              std::cout << from_x << " " << from_y << " " <<
                           to_x << " " << to_y << std::endl;
            } else if (type == 4) {
              int xf = jsonObj.take("xf").toInt();
              int yf = jsonObj.take("yf").toInt();
              int height = jsonObj.take("height").toInt();
              int width = jsonObj.take("width").toInt();
              int side = jsonObj.take("side").toInt();
              Ladder *figure = new Ladder(width, height, side);
              figure->setPos(xf + height * 0.5, yf + width * 0.5);
              //figure->setPos(100, 100);
              this->plan->addItem(figure);
              std::cout << xf << " " << yf << std::endl;
            } else if (type == 5) {
              int xfr = jsonObj.take("xfr").toInt();
              int yfr = jsonObj.take("yfr").toInt();
              int xto = jsonObj.take("xto").toInt();
              int yto = jsonObj.take("yto").toInt();
              RailWay *figure = new RailWay(xfr, yfr, xto, yto);
              //figure->setPos(xPos, yPos);
              figure->setPos(xfr + (xto - xfr) * 0.5, yfr + (yto - yfr) * 0.5);
              //std::cout << jsonObj.take("from_x").toInt() << std::endl;
              this->plan->addItem(figure);
            } else if (type == 6) {

              Symbol *figure = new Symbol(jsonObj.take("size").toInt(), jsonObj.take("file_patch").toString());
              this->plan->addItem(figure);
              figure->setPos(jsonObj.take("pos_x").toInt(), jsonObj.take("pos_y").toInt());
              std::cout << jsonObj.take("file_patch").toString().toStdString() << std::endl;
            }
          }
        }
      }
    }
}
