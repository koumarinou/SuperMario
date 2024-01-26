#pragma once
#include <string>
#include "sgg/graphics.h"

class GameState
{
private:
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 6.f;
	float m_canvas_height = 6.f;


	static GameState* m_unique_instance;

	GameState();

	class Player* m_player = 0;
	class Level* m_current_level = 0;


public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);


	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() { return m_player; }
};
