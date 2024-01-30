#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "util.h"


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
}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	checkCollisions();

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

	m_blocks.push_back(Box(5* m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(2 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));
	
	m_blocks.push_back(Box(1 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(9 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(10 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));


	m_blocks.push_back(Box(10 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(11 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(12 * m_block_size, 7 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(13 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(14 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(15 * m_block_size, 10 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(16 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(16 * m_block_size, 10 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 10 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(18 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(19 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(20 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(21 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));

	m_blocks.push_back(Box(18 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(16 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));





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

	m_block_brush.outline_opacity = 0.0f;

	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	// Sxediazei kentrarismena 
	float offset_x = m_state->m_global_offset_x/2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y/2.0f + h / 2.0f;

	// Draw to background				// 2.0f * w , 4.0f *w 
	graphics::drawRect(offset_x, offset_y, 4.0f * w , 2.0f * w, m_brush_background);

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
