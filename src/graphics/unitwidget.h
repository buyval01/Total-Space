#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QApplication>
#include <QScreen>

#include "graphics/buttonitem.h"
#include "util/utility.h"

class Planet;

class UnitWidget : public ButtonItem {
  Q_OBJECT
 public:
  UnitWidget(Planet* planet, UnitType unit, int32_t width, int32_t height);
  void MouseClicked() override;
  Planet* GetPlanet() const;
  UnitType GetUnit() const;

 private:
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void SwitchColor();

  Planet* unit_planet_;
  QColor current_color_ = Qt::black;
  UnitType cell_unit_;
  const QString caption_;
  bool is_chosen_ = false;
  const int32_t kWidth = qApp->screens()[0]->size().width();
  const int32_t kHeight = qApp->screens()[0]->size().height();

 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
};

#endif  // UNITWIDGET_H