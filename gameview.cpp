#include "gameview.h"

#include <eventhandling.h>

#include "gamescene.h"

GameView::GameView(GameScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
  setMouseTracking(true);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFrameStyle(QFrame::NoFrame);  
  event_handler_ = std::make_shared<EventHandler::View>(this);
}

void GameView::mouseMoveEvent(QMouseEvent *event) {
  event_handler_->MouseMoveEvent(event);
}
