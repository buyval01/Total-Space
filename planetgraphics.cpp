#include "planetgraphics.h"

#include <QPainter>

#include "planet.h"

PlanetGraphics::PlanetGraphics(const std::shared_ptr<Planet>& planet)
    : planet_(planet) {
}

QRectF PlanetGraphics::boundingRect() const {
  return QRectF(planet_->Coordinates().x() - planet_->Radius(),
                planet_->Coordinates().y() - planet_->Radius(),
                2 * planet_->Radius(), 2 * planet_->Radius());
}

void PlanetGraphics::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget) {
  painter->setBrush(Qt::green);
  painter->drawEllipse(QRectF(planet_->Coordinates().x() - planet_->Radius(),
                              planet_->Coordinates().y() - planet_->Radius(),
                              2 * planet_->Radius(), 2 * planet_->Radius()));
  Q_UNUSED(widget)
  Q_UNUSED(option)
}