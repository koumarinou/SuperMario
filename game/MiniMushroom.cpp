#include "MiniMushroom.h"

MiniMushroom::MiniMushroom(const std::string& name) : GameObject(name) {
   // m_brush.texture = m_state->getFullAssetPath("goomba.png");
    m_brush.fill_opacity = 1.0f;
    m_brush.outline_opacity = 0.0f;
    m_width = 1.0f; // Set the size of the mushroom
    m_height = 1.0f;
}

void MiniMushroom::update(float dt) {
    if (!isActive()) return;

    float delta_time = dt / 1000.0f; // Convert to seconds

    m_pos_x += m_direction * m_speed * delta_time;

    // Boundary check
    if (m_pos_x < m_left_boundary || m_pos_x > m_right_boundary) {
        m_direction = -m_direction;
        m_pos_x = std::max(m_left_boundary, std::min(m_pos_x, m_right_boundary));
    }
}




void MiniMushroom::draw() {
    if (!isActive()) return;
    graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush);
}

void MiniMushroom::onCollision(Player* player) {
    setActive(false); // Deactivate the mushroom when Mario lands on it
}

void MiniMushroom::setBoundaries(float left, float right) {
    m_left_boundary = left;
    m_right_boundary = right;
}


void MiniMushroom::setSpeed(float speed) {
    m_speed = speed;
}

void MiniMushroom::setPosition(float x, float y) {
    m_pos_x = x;
    m_pos_y = y;
}

void MiniMushroom::setDirection(int direction) {
    m_direction = direction;
}

void MiniMushroom::setImage(const std::string& image_name) {
    // Use GameState's getFullAssetPath method to get the complete path
    m_brush.texture = m_state->getFullAssetPath(image_name);
}
