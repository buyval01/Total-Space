#include "bot.h"

Bot::Bot(int type, std::shared_ptr<Planet> planet)
    : PlayerBase(planet), type_(type) {}

int Bot::Type() { return type_; }
