#include "gamestate.h"
#include "level.h"
#include "player.h"
#include  <thread>
#include <chrono>
#include <iostream>

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Mario");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()
{

	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::checkWinCondition()
{
	if (m_player && m_player->getPositionX() > 43.0f) {
		isGameWon = true;
	}
}


void GameState::update(float dt)
{

	// std::cout << "Mario Y: " << m_player->m_pos_y << std::endl;
	// Ensures updates do not run for excessively long frames
	if (dt > 500)
		return;

	// Update the current level and player
	if (m_current_level)
	{
		m_current_level->update(dt);
	}

	// Implement Mario's death logic due to falling
	float deathYPosition = 7.0f;
	if (m_player && m_player->isActive() && m_player->m_pos_y > deathYPosition) {
		m_player->markForDeath(); // Mark for death due to falling
	}

	// Check if the player is marked for death and handle it
	if (m_player && m_player->shouldDie()) {
		handleMarioDeath();
		m_player->resetDeathFlag(); // Reset the flag after handling death
	}

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

	checkWinCondition();
	if (isGameWon) {
		std::cout << "Mario X: " << m_player->getPositionX() << std::endl; // Use getPositionX() to access Mario's X position

		// Example values, adjust according to your flag's actual position
		float flagX = 44.0f; // X-coordinate of the flag
		float flagTopY = 2.0f; // Y-coordinate for the top of the flag in game world units

		// Convert game world position to canvas position
		float canvasFlagX = flagX + m_global_offset_x;
		float canvasFlagTopY = flagTopY + m_global_offset_y;

		// Calculate position for the "WINS" message to appear above the flag
		float messageX = canvasFlagX; // Align with flag's center
		float messageY = canvasFlagTopY - 1.0f; // Adjust this value to position above the flag as needed

		graphics::Brush br;
		br.fill_color[0] = 1.0f; // Color settings
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.0f;
		br.fill_opacity = 1.0f;

		// Ensure the font size and positioning are appropriate
		graphics::drawText(messageX - 50, messageY, 30, "WINS!", br);
		return;
	}
}




void GameState::resetGame() {
	if (m_current_level) {
		delete m_current_level; // Delete the current level to free up memory
		m_current_level = new Level(); // Create a new level instance
		m_current_level->init(); // Initialize the new level
	}

	if (m_player) {
		m_player->setPosition(5.0f, 5.0f); // Reset player's position to the start
		m_player->setActive(true); // Make sure the player is active
		m_player->init(); // Re-initialize player to reset any state
	}


	// Optionally reset any other state in the game that tracks progress, scores, etc.
}

void GameState::gameOver() {
	
	isGameOver = true;
}



void GameState::handleMarioDeath() {
	m_playerLives--; // Decrement the life count

	if (m_playerLives > 0) {
		// Reset the game while keeping the lives count updated
		// std::cout << "Hey";
		resetGame();
	}
	else {
		// No lives left, show the game over screen
		gameOver();
	}
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}


GameState* GameState :: m_unique_instance=nullptr;
