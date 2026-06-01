#pragma once

#include "Map.h"
#include <vector>

#ifdef next
#undef next
#endif

class MapMaker final
{
public:
	MapMaker(const MapMaker& other);
	MapMaker(MapMaker&& other);
	MapMaker( float scale );

	MapMaker& operator=(const MapMaker& other) = delete;
	MapMaker& operator=(MapMaker&& other) = delete;
	void Draw() const;

	void MouseHandler(const SDL_MouseButtonEvent& e);
	void KeyboardHandler(const SDL_KeyboardEvent& e);

private:
	std::vector<Hitbox> m_Hitboxes{};
	const float m_Scale{ 1.f };
	int m_CurrentHitbox{};

};

