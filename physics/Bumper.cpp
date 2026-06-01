#include "pch.h"
#include "Bumper.h"
#include "Physics.h"
#include "Ball.h"


Bumper::Bumper(const Bumper& other)
	: m_Bounds{ other.m_Bounds }
	, m_BounceForce{ other.m_BounceForce }
	, m_pAnimator{ new Animator{*other.m_pAnimator} }
{
}
Bumper::Bumper(Bumper&& other)
	: m_Bounds{ other.m_Bounds }
	, m_BounceForce{ other.m_BounceForce }
	, m_pAnimator{ other.m_pAnimator }
{
	other.m_pAnimator = nullptr;
}
Bumper::Bumper(const std::string& path, float bounceForce, Rectf bounds, const std::vector<int>& animationFramesPerRow, float radius)
	: m_BounceForce{ bounceForce }
	, m_pAnimator{ new Animator{path, bounds, animationFramesPerRow} }
	, m_Bounds{ Vector2f{bounds.left,bounds.bottom}, radius}
{
	m_pAnimator->SetAnimation(0, 0.5f, AnimationMode::loop);
	m_pAnimator->SetDefaultAnimation(0, 0.5f, AnimationMode::loop);
}
Bumper::~Bumper()
{
	delete m_pAnimator;
}

Bumper& Bumper::operator=(const Bumper& other)
{
	if (this != &other)
	{
		m_Bounds = other.m_Bounds;
		m_BounceForce = other.m_BounceForce;
		delete m_pAnimator;
		m_pAnimator = new Animator{ *other.m_pAnimator };
	}
	return *this;
}
Bumper& Bumper::operator=(Bumper&& other)
{
	if (this != &other)
	{
		m_Bounds = other.m_Bounds;
		m_BounceForce = other.m_BounceForce;
		delete m_pAnimator;
		m_pAnimator = other.m_pAnimator;
		other.m_pAnimator = nullptr;
	}
	return *this;
}

void Bumper::Draw() const
{
	m_pAnimator->Draw();
}
void Bumper::Update(float elapsedSec)
{
	m_pAnimator->SetPosition(m_Bounds.center - Vector2f{ m_Bounds.radius,m_Bounds.radius }*1.5f);
	m_pAnimator->Update(elapsedSec);
}

bool Bumper::CalcPhysics(Ball& ball, float elapsedSec)
{
	if (utils::GetDistance(ball.GetBounds().center, m_Bounds.center) < ball.GetBounds().radius + m_Bounds.radius)
	{
		Vector2f normal{ m_Bounds.center, ball.GetBounds().center };
		normal.Normalized();
		ball.SetVelocity(ball.GetVelocity().Reflect(normal) * m_BounceForce);
		m_pAnimator->SetAnimation(1, 0.3333f, AnimationMode::once);
		return true;
	}
	return false;
}
CircleBox Bumper::GetHitbox() const
{
	return CircleBox{ m_Bounds, m_BounceForce };
}
void Bumper::SetAnimation(int idx, float frameTime, AnimationMode mode)
{
	m_pAnimator->SetAnimation(idx, frameTime, mode);
}