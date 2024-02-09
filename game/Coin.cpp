#include "Coin.h"
#include "gamestate.h"

Coin::Coin(const std::string& name) : GameObject(name) {
    m_brush.fill_opacity = 1.0f;
    m_brush.outline_opacity = 0.0f;
    m_width = 0.5f; // Adjust size as needed
    m_height = 0.5f;
}

void Coin::update(float dt) {
    // Coins may not need to update their state, but you can implement animations here
}

void Coin::draw() {
    if (!isActive()) return;
    graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush);
}

void Coin::onCollision(Player* player) {
    // Logic for when the player collects a coin, e.g., increase score
    setActive(false); // Deactivate the coin upon collection
}

void Coin::setPosition(float x, float y) {
    m_pos_x = x;
    m_pos_y = y;
}

void Coin::setImage(const std::string& image_name) {
    m_brush.texture = m_state->getFullAssetPath(image_name);
}
