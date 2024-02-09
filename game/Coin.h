#pragma once
#include "gameobject.h"
#include "box.h"
#include "player.h" // Include the Player header
#include "sgg/graphics.h"

class Coin : public GameObject, public Box {
    graphics::Brush m_brush;

public:
    Coin(const std::string& name);
    void update(float dt) override;
    void draw() override;
    void onCollision(Player* player); // Now Player is recognized

    void setPosition(float x, float y);
    void setImage(const std::string& image_name);
};
