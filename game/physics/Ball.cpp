#include "pch.h"
#include "utils.h"
#include "Ball.h"
#include "Texture.h"
#include "Map.h"
#include "Animator.h"

Ball::Ball(Circlef bounds, Vector2f velocity) :
	m_Bounds{bounds},
	m_Velocity{velocity},
	m_pAnimator{ new Animator{ "balls/balls.png", Rectf{0,0,17,17} } }
{
	m_pAnimator->SetPosition(bounds.center);
}
Ball::Ball(const Ball& other)
	: m_pAnimator{ new Animator{*other.m_pAnimator}}
	, m_CurrentBallType{ other.m_CurrentBallType}
	, m_Bounds{other.m_Bounds}
	, m_Velocity{other.m_Velocity}
	, m_RotationSpeed{other.m_RotationSpeed}
{

}
Ball::Ball(Ball&& other)
	: m_pAnimator{ other.m_pAnimator }
	, m_CurrentBallType{ other.m_CurrentBallType }
	, m_Bounds{ other.m_Bounds }
	, m_Velocity{ other.m_Velocity }
	, m_RotationSpeed{ other.m_RotationSpeed }
{
	other.m_pAnimator = nullptr;
}
Ball::~Ball()
{
	delete m_pAnimator;
}

Ball& Ball::operator=(Ball& other)
{
	delete m_pAnimator;
	m_pAnimator = new Animator{*other.m_pAnimator};
	m_CurrentBallType = other.m_CurrentBallType;
	m_Bounds = other.m_Bounds;
	m_Velocity = other.m_Velocity;
	m_RotationSpeed = other.m_RotationSpeed;
	return *this;
}
Ball& Ball::operator=(Ball&& other)
{
	delete m_pAnimator;
	m_pAnimator = new Animator{ *other.m_pAnimator };
	other.m_pAnimator = nullptr;
	m_CurrentBallType = other.m_CurrentBallType;
	m_Bounds = other.m_Bounds;
	m_Velocity = other.m_Velocity;
	m_RotationSpeed = other.m_RotationSpeed;
	return *this;
}

void Ball::Draw() const
{
	m_pAnimator->SetPosition(Vector2f{ m_Bounds.center.x - m_pAnimator->GetBounds().width / 2, m_Bounds.center.y - m_pAnimator->GetBounds().height / 2 });
	m_pAnimator->Draw();

	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::DrawEllipse(m_Bounds.center, m_Bounds.radius, m_Bounds.radius);
	utils::DrawLine(m_Bounds.center, m_Bounds.center + m_Velocity.Normalized()*m_Bounds.radius*1.5f, 2.f);
}
void Ball::Update(float elapsedSec)
{

	//m_pAnimator->Update(elapsedSec);
}

Circlef Ball::GetBounds() const
{
	return m_Bounds;
}

void Ball::SetPosition(float x, float y)
{
	SetPosition(Vector2f{ x,y });
}
void Ball::SetPosition(Vector2f pos)
{
	m_Bounds.center = pos;
}

Vector2f Ball::GetVelocity() const
{
	return m_Velocity;
}
void Ball::SetVelocity(Vector2f velocity)
{
	m_Velocity = velocity;
}
void Ball::SetVelocity(float amplitude, float angleDegr)
{
	m_Velocity = Vector2f{ amplitude * cosf(angleDegr/180*3.14), amplitude * sinf(angleDegr/180*3.14) };
}

bool Ball::GetVisibility() const
{
	return m_pAnimator->GetIsVisible();
}
void Ball::SetVisibility(bool isVisible)
{
	m_pAnimator->SetIsVisible(isVisible);
}