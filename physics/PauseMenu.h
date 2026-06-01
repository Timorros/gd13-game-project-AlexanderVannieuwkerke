#pragma once
//#include "pch.h"

class Texture;

class PauseMenu final
{
public:
	PauseMenu(const PauseMenu& other) = delete;
	PauseMenu(PauseMenu&& other);
	PauseMenu(Rectf viewport);
	~PauseMenu();
	PauseMenu& operator=(const PauseMenu& other) = delete;
	PauseMenu& operator=(PauseMenu&& other) = delete;

	void Draw() const;
	bool GetState() const;

	void ToggleState() { m_IsPaused = !m_IsPaused; };
	//void Update(float elapsedSec);

private:
	Texture* m_pTexture{};
	Rectf m_Viewport{};
	bool m_IsPaused{ false };
};

