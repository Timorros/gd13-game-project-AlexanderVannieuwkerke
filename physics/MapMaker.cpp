#include "pch.h"
#include "MapMaker.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include "JsonManager.h"

MapMaker::MapMaker(const MapMaker& other)
	: m_Hitboxes{ other.m_Hitboxes }
	, m_Scale{ other.m_Scale }
	, m_CurrentHitbox{ other.m_CurrentHitbox }
{
}
MapMaker::MapMaker(MapMaker&& other)
	: m_Hitboxes{ std::move(other.m_Hitboxes) }
	, m_Scale{ other.m_Scale }
	, m_CurrentHitbox{ other.m_CurrentHitbox }
{
}
MapMaker::MapMaker( float scale )
	: m_CurrentHitbox{0}
	, m_Scale{scale}
{
	ReadMap(m_Hitboxes, m_Scale);
}

void MapMaker::Draw() const
{
	for (int index{}; index<m_Hitboxes.size(); ++index)
	{
		if (index == m_CurrentHitbox)
			utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		else
			utils::SetColor(Color4f{ 1.f,0.f,1.f,1.f });

		utils::DrawPolygon(m_Hitboxes[index].points);
		for (Vector2f point : m_Hitboxes[index].points)
		{
			utils::DrawPoint(point, 4.f);
		}
	}
}

void MapMaker::MouseHandler(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_Hitboxes[m_CurrentHitbox].points.push_back(Vector2f{float(e.x) / m_Scale, float(e.y) / m_Scale });
		std::cout << "Vector2f{" << std::to_string(e.x/3) << "," << std::to_string(e.y/3) << "}\n";
		std::cout << "point:" << m_Hitboxes[m_CurrentHitbox].points.back() << std::endl;
		break;

	case SDL_BUTTON_RIGHT:
		int closestPointIDX{};
		for (int idx{}; idx < m_Hitboxes[m_CurrentHitbox].points.size(); ++idx)
		{
			if (utils::GetDistance(m_Hitboxes[m_CurrentHitbox].points[idx], Vector2f{ float(e.x) / m_Scale, float(e.y) / m_Scale }) <=
				utils::GetDistance(m_Hitboxes[m_CurrentHitbox].points[closestPointIDX], Vector2f{ float(e.x) / m_Scale, float(e.y) / m_Scale }))
			{
				closestPointIDX = idx;
			}
		}
		m_Hitboxes[m_CurrentHitbox].points[closestPointIDX] = Vector2f{ float(e.x) / m_Scale, float(e.y) / m_Scale };
		break;
	}
}
void MapMaker::KeyboardHandler(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
		case SDLK_LEFT:
			if (m_CurrentHitbox - 1 >= 0)
				--m_CurrentHitbox;
			break;
		case SDLK_RIGHT:
			if (m_Hitboxes.size() <= m_CurrentHitbox + 1)
			{
				std::cout << "elasticity: ";
				std::cin >> m_Hitboxes[m_CurrentHitbox].elasticity;
				m_Hitboxes.push_back(Hitbox{});
			}
			++m_CurrentHitbox;
			break;
		case SDLK_s:
			SaveMap(m_Hitboxes, m_Scale);
			break;
	}
}