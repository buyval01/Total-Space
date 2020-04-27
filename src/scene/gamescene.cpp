#include "scene/gamescene.h"

#include <QApplication>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QScreen>
#include <functional>
#include <memory>

#include "graphics/drawer.h"
#include "data/loader.h"
#include "objects/planet.h"
#include "objects/player.h"
#include "core/statemachine.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent) {
  drawer_ = std::make_shared<Drawer>(this);
}

void GameScene::Destroy() {
  QListIterator<QGraphicsItem*> it(StateMachine::scene->items());
  while (it.hasNext()) {
    StateMachine::scene->removeItem(it.next());
  }
  player_ = nullptr;
}

void GameScene::HideAll() {
  QListIterator<QGraphicsItem*> it(StateMachine::scene->items());
  while (it.hasNext()) {
    it.next()->hide();
  }
}

void GameScene::ShowAll() {
  QListIterator<QGraphicsItem*> it(StateMachine::scene->items());
  while (it.hasNext()) {
    it.next()->show();
  }
}

void GameScene::NewGame() {
  const double kWidth = views()[0]->sceneRect().width();

  // TODO
  // Надо выбрать радиус
  Planet *start_planet = new Planet(QPointF(0, 0), kWidth / 16 * 3);
  std::shared_ptr<Planet> player_planet(start_planet);

  drawer_->DrawPlanet(player_planet);

  player_ = std::make_shared<Player>(player_planet);

  player_planet->SetOwner(player_);
  SetSceneSettings();
  GenerateMap();

  // TODO
  //Здесь должна происходить генерация ботов и присвоение им планет
}

void GameScene::SetSceneSettings() {
  int32_t width = qApp->screens()[0]->size().width();
  int32_t height = qApp->screens()[0]->size().height();
  background =
      new ImageItem(Loader::GetButtonImage(ButtonsEnum::kMainBackground),
                    width * 8, height * 8);
  background->setZValue(-5);
  StateMachine::scene->addItem(background);
}

void GameScene::GenerateMap() {
  std::function<double(QGraphicsItem*, QPointF)> distance =
      [](QGraphicsItem *left, QPointF right) {
        return (left->pos().x() - right.x()) * (left->pos().x() - right.x()) +
               (left->pos().y() - right.y()) * (left->pos().y() - right.y());
      };

  int32_t width = qApp->screens()[0]->size().width();

  uint32_t number_of_planets = 0;
  uint32_t required_number_of_planets =
      QRandomGenerator::global()->generate() % 10 + 20;

  while (number_of_planets < required_number_of_planets) {
    for (QGraphicsItem* planet : items()) {
      if (number_of_planets > required_number_of_planets) {
        break;
      }

      int32_t angle = QRandomGenerator::global()->generate() % 360;
      // TODO
      // Разбежку расстояний между планетами также нужно выбрать
      uint32_t distance_between = QRandomGenerator::global()->generate() %
                                      static_cast<uint32_t>(width / 8) +
                                  static_cast<uint32_t>(width / 3);

      QPointF coordinates(
          planet->pos().x() + distance_between * cos(angle * M_PI / 180),
          planet->pos().y() + distance_between * sin(angle * M_PI / 180));

      bool is_allowed_distance = true;
      for (QGraphicsItem* another_planet : items()) {
        if (distance(another_planet, coordinates) <
            distance_between * distance_between) {
          is_allowed_distance = false;
          break;
        }
      }

      if (is_allowed_distance) {
        // TODO
        // Надо выбрать радиус, возможно рандомный
        drawer_->DrawPlanet(
            std::make_shared<Planet>(coordinates, width / 16 * 3));
        number_of_planets++;
      }
    }
  }
}