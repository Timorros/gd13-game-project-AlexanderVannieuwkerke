#include "pch.h"
#include "Paddle.h"
#include "Texture.h"
#include "Map.h"
#include "Matrix2x3.h"
#include "iostream"

Paddle::Paddle(const Paddle& other)
	: m_pLeftPaddle{ new Animator(*other.m_pLeftPaddle) }
	, m_pRightPaddle{ new Animator(*other.m_pRightPaddle) }
	, m_LeftState{ other.m_LeftState }
	, m_RightState{ other.m_RightState }
	, m_LeftIsUp{ other.m_LeftIsUp }
	, m_RightIsUp{ other.m_RightIsUp }
{
}
Paddle::Paddle(Paddle&& other)
	: m_pLeftPaddle{ other.m_pLeftPaddle }
	, m_pRightPaddle{ other.m_pRightPaddle }
	, m_LeftState{ other.m_LeftState }
	, m_RightState{ other.m_RightState }
	, m_LeftIsUp{ other.m_LeftIsUp }
	, m_RightIsUp{ other.m_RightIsUp }
{
	m_pLeftPaddle = nullptr;
	m_pRightPaddle = nullptr;
}
Paddle::Paddle()
	: m_pLeftPaddle{ new Animator{ "lPaddle.png", Rectf{85,13,32,28}, std::vector<int>{1,6,1,6} } }
	, m_pRightPaddle{ new Animator{ "rPaddle.png", Rectf{125,13,32,28}, std::vector<int>{1,6,1,6} } }
{
}
Paddle::~Paddle()
{
	delete m_pLeftPaddle;
	delete m_pRightPaddle;
}

Paddle& Paddle::operator=(const Paddle& other)
{
	if (this != &other)
	{
		delete m_pLeftPaddle;
		delete m_pRightPaddle;
		m_pLeftPaddle = new Animator(*other.m_pLeftPaddle);
		m_pRightPaddle = new Animator(*other.m_pRightPaddle);
		m_LeftState = other.m_LeftState;
		m_RightState = other.m_RightState;
		m_LeftIsUp = other.m_LeftIsUp;
		m_RightIsUp = other.m_RightIsUp;
	}
	return *this;
}
Paddle& Paddle::operator=(Paddle&& other)
{
	if (this != &other)
	{
		delete m_pLeftPaddle;
		delete m_pRightPaddle;
		m_pLeftPaddle = other.m_pLeftPaddle;
		other.m_pLeftPaddle = nullptr;
		m_pRightPaddle = other.m_pRightPaddle;
		other.m_pRightPaddle = nullptr;
		m_LeftState = other.m_LeftState;
		m_RightState = other.m_RightState;
		m_LeftIsUp = other.m_LeftIsUp;
		m_RightIsUp = other.m_RightIsUp;
	}
	return *this;
}

Hitbox Paddle::GetLeftHitbox() const
{
	std::vector<Vector2f> paddleHitbox{ Vector2f{ -4,3 }, Vector2f{ -2,5 }, Vector2f{ 7,5 }, Vector2f{ 26,2 }, Vector2f{ 26,-1 }, Vector2f{ 7,-4 }, Vector2f{ -2,-4 }, Vector2f{-4,-2 } };

	Matrix2x3 rot;
	if (m_pLeftPaddle->GetAnimation().idx == 2)
		rot.SetAsRotate(30);
	else
	{
		float angle{ (m_pLeftPaddle->GetFrameIdx() * 12.f + 12.f * (m_pLeftPaddle->GetAnimationTime() / m_pLeftPaddle->GetAnimation().frameTime)) };
		if (m_pLeftPaddle->GetAnimation().idx == 3)
			rot.SetAsRotate(30 - angle);
		else
			rot.SetAsRotate(-30 + angle);
	}


	Hitbox hitbox{};
	hitbox.points = rot.Transform(paddleHitbox);
	if (m_pLeftPaddle->GetAnimation().idx == 1) hitbox.elasticity = 2.f;
	else hitbox.elasticity = 0.6f;

	return hitbox;
}
Hitbox Paddle::GetRightHitbox() const
{
	std::vector<Vector2f> paddleHitbox{ Vector2f{4,3}, Vector2f{2,5}, Vector2f{-7,5}, Vector2f{-26,2}, Vector2f{-26,-1}, Vector2f{-7,-4}, Vector2f{2,-4}, Vector2f{4,-2} };

	Matrix2x3 rot;
	if (m_pRightPaddle->GetAnimation().idx == 2)
		rot.SetAsRotate(-30);
	else
	{
		float angle{ (m_pRightPaddle->GetFrameIdx() * 12.f + 12.f * (m_pRightPaddle->GetAnimationTime() / m_pRightPaddle->GetAnimation().frameTime)) };
		if (m_pRightPaddle->GetAnimation().idx == 3)
			rot.SetAsRotate(-30 + angle);
		else
			rot.SetAsRotate(30 - angle);
	}

	Hitbox hitbox{};
	hitbox.points = rot.Transform(paddleHitbox);
	if (m_pRightPaddle->GetAnimation().idx == 1) hitbox.elasticity = 2.f;
	else hitbox.elasticity = 0.6f;

	return hitbox;
}

void Paddle::LeftPaddleUp()
{
	if (!m_LeftIsUp)
	{
		m_pLeftPaddle->SetAnimation(1, 0.0333f, AnimationMode::once);
		m_pLeftPaddle->SetNextAnimation(2, 0.0333f, AnimationMode::loop);
		m_LeftIsUp = true;
	}
}
void Paddle::RightPaddleUp()
{
	if (!m_RightIsUp)
	{
		m_pRightPaddle->SetAnimation(1, 0.0333f, AnimationMode::once);
		m_pRightPaddle->SetNextAnimation(2, 0.0333f, AnimationMode::loop);
		m_RightIsUp = true;
	}
}
void Paddle::LeftPaddleDown()
{
	m_pLeftPaddle->SetAnimation(3, 0.0333f, AnimationMode::once);
	m_LeftIsUp = false;
}
void Paddle::RightPaddleDown()
{
	m_pRightPaddle->SetAnimation(3, 0.0333f, AnimationMode::once);
	m_RightIsUp = false;
}

void Paddle::Draw() const
{
	glPushMatrix();
	{
		m_pLeftPaddle->Draw();
		m_pRightPaddle->Draw();
	}
	glPopMatrix();
}

void Paddle::Update(float elapsedSec)
{
	m_pLeftPaddle->Update(elapsedSec);
	m_pRightPaddle->Update(elapsedSec);
}