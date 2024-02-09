#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "util.h"
#include "Coin.h"



// Gia ta cubes
void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x+ m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);
	graphics::drawRect(x, y,m_block_size,m_block_size,m_block_brush);

	if(m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::checkCollisions()
{
	//Auto reference gia na paroume piso reference
	//for (auto& box : m_blocks)
	//{
	//	if (m_state->getPlayer()->intersect(box))
	//		printf("*");
	//}


	// Na epanaferei tin thesi tou player gia ta cubes 
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(box))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;
			break;

		}

	}

	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			break;

		}

	}

	Player* player = m_state->getPlayer();

	for (auto& obj : m_dynamic_objects) {
		MiniMushroom* mushroom = dynamic_cast<MiniMushroom*>(obj);
		if (mushroom && mushroom->isActive() && mushroom->intersect(*m_state->getPlayer())) {
			if (m_state->getPlayer()->intersectDown(*mushroom)) {
				mushroom->onCollision(m_state->getPlayer());
			}
			if (m_state->getPlayer()->intersectSideways(*mushroom)) {
				m_state->getPlayer()->markForDeath(); // Mark player for death instead of direct handling
				break;
			}
		}
	}

	for (auto& obj : m_dynamic_objects) {
		Coin* coin = dynamic_cast<Coin*>(obj);
		if (coin && coin->isActive() && coin->intersect(*m_state->getPlayer())) {
			if (m_state->getPlayer()->intersect(*coin)) {
				coin->onCollision(m_state->getPlayer());
			}
		}
	}
}

void Level::spawnCoins() {
	Coin* coin1 = new Coin("Coin1");
	coin1->setPosition(6.0f, 4.0f); // Example position
	coin1->setImage("coin.png"); // Specify the image for the coin
	coin1->init();
	m_dynamic_objects.push_back(coin1);

	Coin* coin2 = new Coin("Coin2");
	coin2->setPosition(7.0f, 4.0f); // Example position
	coin2->setImage("coin.png"); // Specify the image for the coin
	coin2->init();
	m_dynamic_objects.push_back(coin2);

	Coin* coin3 = new Coin("Coin3");
	coin3->setPosition(8.0f, 4.0f); // Example position
	coin3->setImage("coin.png"); // Specify the image for the coin
	coin3->init();
	m_dynamic_objects.push_back(coin3);

	Coin* coin4 = new Coin("Coin4");
	coin4->setPosition(9.0f, 4.0f); // Example position
	coin4->setImage("coin.png"); // Specify the image for the coin
	coin4->init();
	m_dynamic_objects.push_back(coin4);

	Coin* coin5 = new Coin("Coin5");
	coin5->setPosition(19.0f, 4.0f); // Example position
	coin5->setImage("coin.png"); // Specify the image for the coin
	coin5->init();
	m_dynamic_objects.push_back(coin5);

	Coin* coin10 = new Coin("Coin10");
	coin10->setPosition(20.0f, 3.0f); // Example position
	coin10->setImage("coin.png"); // Specify the image for the coin
	coin10->init();
	m_dynamic_objects.push_back(coin10);

	Coin* coin6 = new Coin("Coin6");
	coin6->setPosition(21.0f, 2.0f); // Example position
	coin6->setImage("coin.png"); // Specify the image for the coin
	coin6->init();
	m_dynamic_objects.push_back(coin6);

	Coin* coin7 = new Coin("Coin7");
	coin7->setPosition(22.0f, 1.0f); // Example position
	coin7->setImage("coin.png"); // Specify the image for the coin
	coin7->init();
	m_dynamic_objects.push_back(coin7);

	Coin* coin8 = new Coin("Coin8");
	coin8->setPosition(34.0f, 2.0f); // Example position
	coin8->setImage("coin.png"); // Specify the image for the coin
	coin8->init();
	m_dynamic_objects.push_back(coin8);

	Coin* coin9 = new Coin("Coin9");
	coin9->setPosition(35.0f, 1.0f); // Example position
	coin9->setImage("coin.png"); // Specify the image for the coin
	coin9->init();
	m_dynamic_objects.push_back(coin9);

}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	checkCollisions();
	for (auto& obj : m_dynamic_objects) {
		obj->update(dt);
	}



	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background3.png");

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for(auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	m_blocks.push_back(Box(4 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(5* m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(9 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(10 * m_block_size, 5 * m_block_size, m_block_size, m_block_size)); //solinas
	m_blocks.push_back(Box(10 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(11 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(12 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(15 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(16 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(18 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(19 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(21 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(23 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(25 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(26 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(27 * m_block_size, 3 * m_block_size, m_block_size, m_block_size)); //solinas
	m_blocks.push_back(Box(27 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(28 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(29 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(31 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(32 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(33 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(34 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(36 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(37 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(38 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(39 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(42 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(43 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(44 * m_block_size, 1 * m_block_size, m_block_size, m_block_size)); // edo tha einai i simea
	m_blocks.push_back(Box(44 * m_block_size, 2 * m_block_size, m_block_size, m_block_size)); 
	m_blocks.push_back(Box(45 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	


	
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("flag.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	

	m_block_brush.outline_opacity = 0.0f;

	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

	spawnMiniMushrooms();
	spawnCoins();
	
}




void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	// Update the background texture based on game over state
	if (m_state->isGameOver) {
		m_brush_background.texture = m_state->getFullAssetPath("gameover.png");

		// Draw the game over background
		float offset_x = w / 2.0f;
		float offset_y = h / 2.0f;
		graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);
	}
	else if (m_state->isGameWon) {
		m_brush_background.texture = m_state->getFullAssetPath("win.png");

		// Draw the game over background
		float offset_x = w / 2.0f;
		float offset_y = h / 2.0f;
		graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);
	}
	else {
		m_brush_background.texture = m_state->getFullAssetPath("background3.png");
		// Sxediazei kentrarismena 
		float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
		float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

		// Draw to background				// 2.0f * w , 4.0f *w 
		graphics::drawRect(offset_x, offset_y, 8.0f * w, 2.0f * w, m_brush_background);

		// Ton player giati den einai ola ta levels idia 

		// Alla stoixeia piso apo ton paixti 
		for (int i = 0; i < m_blocks.size(); i++)
		{
			drawBlock(i);
		}

		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->draw();

		// Alla stoixeia brosta apo ton paixti 

		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->draw();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->draw();

		
	}
	

	
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

	
}

void Level::spawnMiniMushrooms() {
	MiniMushroom* miniMushroom = new MiniMushroom("MiniMushroom");

	float tubeX = 9.0f; // X-coordinate of the tube
	float cubeX = 4.0f;  // X-coordinate of the cube
	float mushroomX = (tubeX + cubeX) / 2.0f; // Midpoint X-coordinate
	float mushroomY = 5.0f; // Assuming ground level Y-coordinate

	// Set the position of the Mini Mushroom
	miniMushroom->setPosition(mushroomX, mushroomY);

	// Set horizontal movement boundaries 
	miniMushroom->setBoundaries(cubeX, tubeX); 

	miniMushroom->setSpeed(2.0f); // Ensure this is not set to 0
	miniMushroom->setDirection(1); // or -1, depending on the initial movement direction

	miniMushroom->setImage("goomba.png");
	miniMushroom->init();
	m_dynamic_objects.push_back(miniMushroom);


	MiniMushroom* sumo = new MiniMushroom("Sumo");

	float tubesX = 31.0f; // X-coordinate of the tube
	float cubesX = 34.0f;  // X-coordinate of the cube
	float sumoX = (tubesX + cubesX) / 2.0f; // Midpoint X-coordinate
	float sumoY = 3.0f; // Assuming ground level Y-coordinate

	// Set the position of the Mini Mushroom
	sumo->setPosition(sumoX, sumoY);

	// Set horizontal movement boundaries
	sumo->setBoundaries(tubesX, cubesX);
	sumo->setSpeed(2.0f); // Ensure this is not set to 0
	sumo->setDirection(1); // or -1, depending on the initial movement direction

	sumo->setImage("Sumo.png");
	sumo->init();
	m_dynamic_objects.push_back(sumo);


	MiniMushroom* goomba = new MiniMushroom("goomba");

	float tubesX2 = 36.0f; // X-coordinate of the tube
	float cubesX2 = 39.0f;  // X-coordinate of the cube
	float sumoX2 = (tubesX2 + cubesX2) / 2.0f; // Midpoint X-coordinate
	float sumoY2 = 1.0f; // Assuming ground level Y-coordinate

	// Set the position of the Mini Mushroom
	goomba->setPosition(sumoX2, sumoY2);

	// Set horizontal movement boundaries
	goomba->setBoundaries(tubesX2, cubesX2);
	goomba->setSpeed(2.0f); // Ensure this is not set to 0
	goomba->setDirection(1); // or -1, depending on the initial movement direction

	goomba->setImage("goomba2.png");
	goomba->init();
	m_dynamic_objects.push_back(goomba);



}





