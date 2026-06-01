#pragma once
#include "vector"
#include "Paddle.h"
#include "Physics.h"
#include "utils.h"

class Texture;
class Ball;
class Lane;
class Catcher;
class Bumper;
class Pokemon;
class Animator;

enum class Phase
{
	Free,
	Bumper,
	Catch,
	Hatch,
	Evolve
};

class Map final
{
public:

	Map(Map& other) = delete;
	Map(Map&& other);
	Map(Ball* ball, float scale);
	~Map();

	Map& operator=(Map& other) = delete;
	Map& operator=(Map&& other);

	void DrawBG() const;
	void Draw() const;
	void Update(float elapsedSec);

	void KeyDownHandler(const SDL_KeyboardEvent& e);
	void KeyUpHandler(const SDL_KeyboardEvent& e);

private:
	std::vector<Hitbox> m_Hitboxes{};
	Paddle m_Paddle{};
	Phase m_CurrentPhase{ Phase::Free };

	Texture* m_pBGTexture{ nullptr };
	Texture* m_pCatchMarking{ nullptr };
	Texture* m_pHatchArrow{ nullptr };
	Texture* m_pBumperArrow{ nullptr };
	Texture* m_pMartArrow{ nullptr };
	Texture* m_pEvoArrow{ nullptr };
	Texture* m_pCatchArrow{ nullptr };
	Lane* m_pEvoLane{ nullptr };
	Lane* m_pMoneyLane{ nullptr };
	Lane* m_pCatchLane{ nullptr };
	Ball* m_pBall{ nullptr };
	Catcher* m_pCatcher{ nullptr };
	Bumper* m_pBumper{ nullptr };
	Pokemon* m_pPokemon{ nullptr };
	Animator* m_pSpoink{ nullptr };
	//Pokemon* m_pLaunchPokemon{ nullptr };
	float m_Scale{ 1.f };
	int m_TimesBumped{ 0 };
}

//pokemon
//	|_> freePokemon