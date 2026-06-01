#include "pch.h"
#include "Lane.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

Lane::Lane(const Lane& other)
	: m_Path{ other.m_Path }
	, m_pTexture{ new Texture{m_Path} }
	, m_LightPos{ other.m_LightPos[0], other.m_LightPos[1], other.m_LightPos[2] }
	, m_FirstTrigger{ other.m_FirstTrigger }
	, m_SecondTrigger{ other.m_SecondTrigger }
	, m_Timer{ other.m_Timer }
	, m_Passes{ other.m_Passes }
	, m_FirstTriggerTriggered{ other.m_FirstTriggerTriggered }
{
}
Lane::Lane(Lane&& other)
	: m_Path{ std::move(other.m_Path) }
	, m_pTexture{ other.m_pTexture }
	, m_LightPos{ other.m_LightPos[0], other.m_LightPos[1], other.m_LightPos[2] }
	, m_FirstTrigger{ other.m_FirstTrigger }
	, m_SecondTrigger{ other.m_SecondTrigger }
	, m_Timer{ other.m_Timer }
	, m_Passes{ other.m_Passes }
	, m_FirstTriggerTriggered{ other.m_FirstTriggerTriggered }
{
	other.m_pTexture = nullptr;
}
Lane::Lane(std::string path, Circlef trigger1, Circlef trigger2, Vector2f pos1, Vector2f pos2, Vector2f pos3)
	: m_Path(path)
	, m_pTexture(new Texture(path))
	, m_LightPos{pos1,pos2,pos3}
	, m_FirstTrigger{trigger1}
	, m_SecondTrigger{trigger2}
{
}
Lane::~Lane()
{
	delete m_pTexture;
}

Lane& Lane::operator=(const Lane& other)
{
	if (this != &other)
	{
		m_Path = other.m_Path;
		delete m_pTexture;
		m_pTexture = new Texture{ m_Path };
		m_LightPos[0] = other.m_LightPos[0];
		m_LightPos[1] = other.m_LightPos[1];
		m_LightPos[2] = other.m_LightPos[2];
		m_FirstTrigger = other.m_FirstTrigger;
		m_SecondTrigger = other.m_SecondTrigger;
		m_Timer = other.m_Timer;
		m_Passes = other.m_Passes;
		m_FirstTriggerTriggered = other.m_FirstTriggerTriggered;
	}
	return *this;
}
Lane& Lane::operator=(Lane&& other)
{
	if (this != &other)
	{
		m_Path = std::move(other.m_Path);
		delete m_pTexture;
		m_pTexture = other.m_pTexture;
		other.m_pTexture = nullptr;
		m_LightPos[0] = other.m_LightPos[0];
		m_LightPos[1] = other.m_LightPos[1];
		m_LightPos[2] = other.m_LightPos[2];
		m_FirstTrigger = other.m_FirstTrigger;
		m_SecondTrigger = other.m_SecondTrigger;
		m_Timer = other.m_Timer;
		m_Passes = other.m_Passes;
		m_FirstTriggerTriggered = other.m_FirstTriggerTriggered;
	}
	return *this;
}

bool Lane::Update(float elapsedSec, const Circlef& ballBounds)
{
	m_Timer += elapsedSec;
	if (utils::IsOverlapping(m_FirstTrigger, ballBounds))
	{
		//std::cout << "trigger 1 time:" << m_Timer << std::endl;
		m_FirstTriggerTriggered = true;
		m_Timer = 0;
	}
	if (utils::IsOverlapping(m_SecondTrigger, ballBounds) && m_FirstTriggerTriggered)
	{
		//std::cout << "trigger 2 time:" << m_Timer << std::endl;
		if (++m_Passes >= 4)
		{
			--m_Passes;
			return true;
		}
		m_FirstTriggerTriggered = false;
	}
	if (m_Timer >= 5.f)
	{
		m_Timer = 0;
		m_FirstTriggerTriggered = false;
	}
	return false;
}
void Lane::Draw()
{
	utils::DrawEllipse(m_FirstTrigger.center, m_FirstTrigger.radius, m_FirstTrigger.radius);
	utils::DrawEllipse(m_SecondTrigger.center, m_SecondTrigger.radius, m_SecondTrigger.radius);
	for (int idx{}; idx < 4; ++idx)
	{
		if (m_Passes > idx)
		{
			m_pTexture->Draw(
				m_LightPos[idx],
				Rectf{ m_pTexture->GetWidth() / 3 * idx,0,m_pTexture->GetWidth() / 3, m_pTexture->GetHeight() }
			);
		}
	}
}
void Lane::ResetPasses()
{
	m_Passes = 0;
}