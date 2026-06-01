#include "pch.h"
#include "Map.h"
#include "Texture.h"
#include "utils.h"
#include "Ball.h"
#include "Matrix2x3.h"
#include "JsonManager.h"
#include "Lane.h"
#include "Catcher.h"
#include "Bumper.h"
#include "Pokemon.h"
#include "BabyPokemon.h"
#include <iostream>

Map::Map(Map&& other)
	: m_Hitboxes{ other.m_Hitboxes }
	, m_Paddle{ other.m_Paddle }
	, m_CurrentPhase{ other.m_CurrentPhase }
	, m_pBGTexture{ other.m_pBGTexture }
	, m_pCatchMarking{ other.m_pCatchMarking }
	, m_pHatchArrow{ other.m_pHatchArrow }
	, m_pBumperArrow{ other.m_pBumperArrow }
	, m_pMartArrow{ other.m_pMartArrow }
	, m_pEvoArrow{ other.m_pEvoArrow }
	, m_pCatchArrow{ other.m_pCatchArrow }
	, m_pEvoLane{ other.m_pEvoLane }
	, m_pMoneyLane{ other.m_pMoneyLane }
	, m_pCatchLane{ other.m_pCatchLane }
	, m_pBall{ other.m_pBall }
	, m_pCatcher{ other.m_pCatcher }
	, m_pBumper{ other.m_pBumper }
	, m_pPokemon{ other.m_pPokemon }
	, m_Scale{ other.m_Scale }
	, m_TimesBumped{ other.m_TimesBumped }
{
	other.m_pBGTexture = nullptr;
	other.m_pCatchMarking = nullptr;
	other.m_pHatchArrow = nullptr;
	other.m_pBumperArrow = nullptr;
	other.m_pMartArrow = nullptr;
	other.m_pEvoArrow = nullptr;
	other.m_pCatchArrow = nullptr;
	other.m_pEvoLane = nullptr;
	other.m_pMoneyLane = nullptr;
	other.m_pCatchLane = nullptr;
	other.m_pBall = nullptr;
	other.m_pCatcher = nullptr;
	other.m_pBumper = nullptr;
	other.m_pPokemon = nullptr;
}
Map::Map(Ball* ball, float scale)
	: m_pBGTexture{ new Texture("MapSpriteSheet.png") }
	, m_pCatchMarking{ new Texture("catchMarkings.png") }
	, m_pEvoLane{ new Lane{"EvoLane.png", Circlef{63/2,365/2,5}, Circlef{75/2,600/2,5}, Vector2f{64,308} / 2, Vector2f{84,276}/2, Vector2f{104,244} / 2 } }
	, m_pMoneyLane{ new Lane{"MoneyLane.png", Circlef{125/2,480/2,5}, Circlef{66,300,5}, Vector2f{120,420} / 2, Vector2f{130,384}/2, Vector2f{146,350} / 2 } }
	, m_pCatchLane{ new Lane{"CatchLane.png", Circlef{211,182.5f,5}, Circlef{404/2,611/2,5}, Vector2f{384,308} / 2, Vector2f{364,276}/2, Vector2f{344, 244} / 2 } }
	, m_pBall(ball)
	, m_pCatcher{ new Catcher{"pokemon/sharpedoSpriteSheet.png", Rectf{180,200,114/3,42}, Circlef{195,200,5}, m_pBall, std::vector<int>{2,3} } }
	, m_Scale{scale}
	, m_pBumper{ new Bumper{"lampPokemonSpriteSheet.png", 2, Rectf{145,270, 32,32}, std::vector<int>{2,2,6,6} } }
	, m_pHatchArrow{ new Texture("hatchArrow.png") }
	, m_pBumperArrow{ new Texture("bumperArrow.png") }
	, m_pMartArrow{ new Texture("martArrow.png") }
	, m_pEvoArrow{ new Texture("evoArrow.png") }
	, m_pCatchArrow{ new Texture("catchArrow.png") }
	, m_pSpoink{ new Animator{"pokemon/spoinkSpriteSheet.png",Rectf{232,15,22,42}, std::vector<int>{4,2}} }
{
	ReadMap(m_Hitboxes, m_Scale);
	m_pSpoink->SetAnimation(0, 0.5f, AnimationMode::loop);
	m_pSpoink->SetDefaultAnimation(0, 0.5f, AnimationMode::loop);
}
Map::~Map()
{
	delete m_pBGTexture;
	delete m_pCatchMarking;
	delete m_pHatchArrow;
	delete m_pBumperArrow;
	delete m_pMartArrow;
	delete m_pEvoArrow;
	delete m_pCatchArrow;
	delete m_pEvoLane;
	delete m_pMoneyLane;
	delete m_pCatchLane;
	delete m_pCatcher;

	delete m_pBumper;
	delete m_pPokemon;
	delete m_pSpoink;
}

Map& Map::operator=(Map&& other)
{
	if (this == &other)
		return *this;
	m_Hitboxes = other.m_Hitboxes;
	m_Paddle = other.m_Paddle;
	m_CurrentPhase = other.m_CurrentPhase;
	delete m_pBGTexture;
	m_pBGTexture = other.m_pBGTexture;
	other.m_pBGTexture = nullptr;
	delete m_pCatchMarking;
	m_pCatchMarking = other.m_pCatchMarking;
	other.m_pCatchMarking = nullptr;
	delete m_pHatchArrow;
	m_pHatchArrow = other.m_pHatchArrow;
	other.m_pHatchArrow = nullptr;
	delete m_pBumperArrow;
	m_pBumperArrow = other.m_pBumperArrow;
	other.m_pBumperArrow = nullptr;
	delete m_pMartArrow;
	m_pMartArrow = other.m_pMartArrow;
	other.m_pMartArrow = nullptr;
	delete m_pEvoArrow;
	m_pEvoArrow = other.m_pEvoArrow;
	other.m_pEvoArrow = nullptr;
	delete m_pCatchArrow;
	m_pCatchArrow = other.m_pCatchArrow;
	other.m_pCatchArrow = nullptr;
	delete m_pEvoLane;
	m_pEvoLane = other.m_pEvoLane;
	other.m_pEvoLane = nullptr;
	delete m_pMoneyLane;
	m_pMoneyLane = other.m_pMoneyLane;
	other.m_pMoneyLane = nullptr;
	delete m_pCatchLane;
	m_pCatchLane = other.m_pCatchLane;
	other.m_pCatchLane = nullptr;
	m_pBall = other.m_pBall;
	delete m_pCatcher;
	m_pCatcher = other.m_pCatcher;
	other.m_pCatcher = nullptr;
	delete m_pBumper;
	m_pBumper = other.m_pBumper;
	other.m_pBumper = nullptr;
	delete m_pPokemon;
	m_pPokemon = other.m_pPokemon;
	other.m_pPokemon = nullptr;
	m_Scale = other.m_Scale;
	m_TimesBumped = other.m_TimesBumped;
	return *this;
}

void Map::DrawBG() const
{
	glPushMatrix();
	//glScalef(GLfloat(2.f), GLfloat(2.f), GLfloat(2.f));
	m_pBGTexture->Draw(Vector2f{ 0,0 }, Rectf{ 0,0,m_pBGTexture->GetWidth() / 3, m_pBGTexture->GetHeight() });
	m_pEvoLane->Draw();
	m_pMoneyLane->Draw();
	m_pCatchLane->Draw();

	if (m_pCatchLane->GetPasses() > 1)
		m_pCatchArrow->Draw(Vector2f{ 154,142 });
	if (m_pEvoLane->GetPasses() > 2)
		m_pEvoArrow->Draw(Vector2f{ 144,169 });
	if (m_CurrentPhase == Phase::Bumper)
		m_pBumperArrow->Draw(Vector2f{ 120,196 });
	if (m_CurrentPhase == Phase::Catch)
	{
		m_pCatchMarking->Draw(Vector2f{ 96,79 }, Rectf{ 0,0,m_pCatchMarking->GetWidth(), m_pCatchMarking->GetHeight() / 2 });
		if(m_pPokemon->GetHits()>0)
			m_pCatchMarking->Draw(Vector2f{ 96,79 }, Rectf{ 0,m_pCatchMarking->GetHeight() / 2,(m_pCatchMarking->GetWidth() / 3) * m_pPokemon->GetHits(), m_pCatchMarking->GetHeight() / 2 });
	}

	glPopMatrix();
}
void Map::Draw() const
{
	glPushMatrix();
	{
		m_Paddle.Draw();
		m_pBGTexture->Draw(Vector2f{ 0,0 }, Rectf{ m_pBGTexture->GetWidth() / 3, 0, m_pBGTexture->GetWidth() / 3, m_pBGTexture->GetHeight() });
		m_pBGTexture->Draw(Vector2f{ 0,0 }, Rectf{ (m_pBGTexture->GetWidth() / 3) * 2, 0, m_pBGTexture->GetWidth() / 3, m_pBGTexture->GetHeight() });
		m_pCatcher->Draw();
		m_pBumper->Draw();
		m_pSpoink->Draw();

		if(m_pPokemon != nullptr)
			m_pPokemon->Draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(GLfloat(92*m_Scale), GLfloat(28*m_Scale), GLfloat(0));
		utils::DrawPolygon(m_Paddle.GetLeftHitbox().points);

		glTranslatef(GLfloat(60*m_Scale), GLfloat(0), GLfloat(0));
		utils::DrawPolygon(m_Paddle.GetRightHitbox().points);
	}
	glPopMatrix();
}
void Map::Update(float elapsedSec)
{
	m_Paddle.Update(elapsedSec);
	m_pCatcher->Update(elapsedSec);
	m_pBumper->Update(elapsedSec);
	m_pSpoink->Update(elapsedSec);
	switch (m_CurrentPhase)
	{
	case Phase::Free:
		if (m_pCatcher->GetIsCought() && m_pCatchLane->GetPasses() > 1)
		{
			m_CurrentPhase = Phase::Bumper;
			m_TimesBumped = 0;
			m_pCatchLane->ResetPasses();
		}
		break;
	case Phase::Bumper:
		if (m_TimesBumped > 2)
		{
			m_CurrentPhase = Phase::Catch;
			if (m_pPokemon == nullptr)
			{
				m_pPokemon = new Pokemon{ Bumper{"pokemon/catch/zigzagoonSpriteSheet.png", 1, Rectf{118.f, 108.f,31,46}, std::vector<int>{2,3}, 10.f} };
			}
			m_TimesBumped = 0;
		}
		break;
	case Phase::Catch:
		m_pPokemon->Update(elapsedSec);
		m_pPokemon->CalcPhysics(*m_pBall, elapsedSec);
		if (m_pPokemon->GetHits() > 2)
		{
			m_CurrentPhase = Phase::Free;
			delete m_pPokemon;
			m_pPokemon = nullptr;
		}
		break;
	}
	if (m_CurrentPhase == Phase::Free && m_pPokemon != nullptr)
	{
		m_pPokemon->Update(elapsedSec);
		if (m_pPokemon->CalcPhysics(*m_pBall, elapsedSec))
		{
			delete m_pPokemon;
			m_pPokemon = nullptr;
		}
	}

	if (m_pBall->GetVisibility())
	{
		for (int poly{}; poly < m_Hitboxes.size(); ++poly)
		{
			CalcPhysics(m_pBall, m_Hitboxes[poly], elapsedSec);
		}
		if (m_pBall->GetVelocity().Norm() > 400.f)
		{
			m_pBall->SetVelocity( m_pBall->GetVelocity().Normalized() * 400.f);
		}
		m_pBall->SetPosition(m_pBall->GetBounds().center + m_pBall->GetVelocity() * elapsedSec);

		Matrix2x3 translation;
		translation.SetAsTranslate(Vector2f{ 92,28 });
		Matrix2x3 scale;
		scale.SetAsScale(1);
		Matrix2x3 result;
		result = scale * translation;
		CalcPhysics(m_pBall, Hitbox{ result.Transform(m_Paddle.GetLeftHitbox().points), m_Paddle.GetLeftHitbox().elasticity }, elapsedSec);
		translation.SetAsTranslate(Vector2f{ (92+60),28 });
		result = scale * translation;
		CalcPhysics(m_pBall, Hitbox{ result.Transform(m_Paddle.GetRightHitbox().points), m_Paddle.GetRightHitbox().elasticity }, elapsedSec);

		if (m_pBumper->CalcPhysics(*m_pBall, elapsedSec))
			++m_TimesBumped;
		m_pEvoLane->Update(elapsedSec, m_pBall->GetBounds());
		m_pMoneyLane->Update(elapsedSec, m_pBall->GetBounds());
		m_pCatchLane->Update(elapsedSec, m_pBall->GetBounds());
		//std::cout << m_pEvoLane->GetPasses() << "\t" << m_pMoneyLane->GetPasses() << "\t" << m_pCatchLane->GetPasses() << std::endl;
	}
}

void Map::KeyDownHandler(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_q:
		m_Paddle.LeftPaddleUp();
		break;
	case SDLK_d:
		m_Paddle.RightPaddleUp();
		if(utils::GetDistance(m_pBall->GetBounds().center, Vector2f{ 243, 60 }) < 10 && m_pSpoink->GetAnimation().idx != 1 )
			m_pSpoink->SetAnimation(1, 0.1f, AnimationMode::loop);
		break;
	}
}
void Map::KeyUpHandler(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_q:
		m_Paddle.LeftPaddleDown();
		break;
	case SDLK_d:
		m_Paddle.RightPaddleDown();
		if (utils::GetDistance(m_pBall->GetBounds().center, Vector2f{ 243, 60 }) < 10)
		{
			m_pBall->SetVelocity(400, 90);
			m_pSpoink->SetAnimation(0, 0.5f, AnimationMode::loop);
		}
		break;
	case SDLK_m:
		if (m_pPokemon == nullptr)
		{
			m_pPokemon = new BabyPokemon{ Bumper{"pokemon/catch/babyPokemonSpriteSheet.png", 1.f, Rectf{100,100,25,26}, std::vector<int>{3,3,3,3,1}, 5.f} };
		}
	}
}