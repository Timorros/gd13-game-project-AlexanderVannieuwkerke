#include "pch.h"
#include "PauseMenu.h"
#include "Texture.h"

PauseMenu::PauseMenu(PauseMenu&& other)
	: m_Viewport{ other.m_Viewport }
	, m_pTexture{ other.m_pTexture }
	, m_IsPaused{ other.m_IsPaused }
{
	other.m_pTexture = nullptr;
}
PauseMenu::PauseMenu(Rectf viewport) :
	m_Viewport{viewport},
	m_pTexture{ new Texture("PauseMenu.png") }
{

}

PauseMenu::~PauseMenu()
{
	delete m_pTexture;
}

void PauseMenu::Draw() const
{
	if (m_IsPaused)
	{
		m_pTexture->Draw(Vector2f{ m_Viewport.width / 2 - m_pTexture->GetWidth() / 2, m_Viewport.height / 2 - m_pTexture->GetHeight() / 2 });
	}
}

bool PauseMenu::GetState() const
{
	return m_IsPaused;
}