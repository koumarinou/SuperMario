#pragma once
#include "gameobject.h"
#include "box.h"
#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"

class MiniMushroom : public GameObject, public Box {
    graphics::Brush m_brush;
    float m_speed = 1.0f; // Speed of the mushroom
    int m_direction; // Current moving direction (1 = right, -1 = left)
    float m_left_boundary; // Left boundary for movement
    float m_right_boundary; // Right boundary for movement

public:
    MiniMushroom(const std::string& name);
    void update(float dt) override;
    void draw() override;
    void onCollision(Player* player);

    void setBoundaries(float left, float right);
    void setSpeed(float speed);
    void setPosition(float x, float y);
    void setDirection(int direction);
    void setImage(const std::string& image_name); 
};


