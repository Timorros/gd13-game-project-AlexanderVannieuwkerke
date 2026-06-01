#include "pch.h"
#include "Catcher.h"
#include "Texture.h"
#include "utils.h"
#include "Ball.h"
#include "Animator.h"

Catcher::Catcher(const std::string& spriteSheetPath, const Rectf& bounds, const Circlef& catchHitbox, Ball* pball, const std::vector<int>& animationFramesPerRow) :
	m_CatchHitbox{ catchHitbox },
	m_pBall{ pball }
{
	m_pAnimator = new Animator{ spriteSheetPath, bounds, animationFramesPerRow };
	m_pAnimator->SetDefaultAnimation(0, 0.5f, AnimationMode::loop);
	m_pAnimator->SetAnimation(0, 0.5f, AnimationMode::loop);
}
Catcher::Catcher(const Catcher& other)
	: m_CatchHitbox{other.m_CatchHitbox}
	, m_IsCought{other.m_IsCought}
	, m_pAnimator{ new Animator(*other.m_pAnimator) }
	, m_pBall{other.m_pBall}
{
	
}
Catcher::Catcher(Catcher&& other)
	: m_CatchHitbox{ other.m_CatchHitbox }
	, m_IsCought{ other.m_IsCought }
	, m_pAnimator{ other.m_pAnimator }
	, m_pBall{ other.m_pBall }
{
	other.m_pAnimator = nullptr;
	other.m_pBall = nullptr;
}
Catcher::~Catcher()
{
	delete m_pAnimator;
}

void Catcher::Draw() const
{
	m_pAnimator->Draw();

	//utils::DrawEllipse(m_CatchHitbox.center, m_CatchHitbox.radius, m_CatchHitbox.radius);
}

void Catcher::Update(float elapsedSec)
{
	m_pAnimator->Update(elapsedSec);
	if (utils::GetDistance(m_CatchHitbox.center, m_pBall->GetBounds().center) <= m_CatchHitbox.radius + m_pBall->GetBounds().radius)
	{
		m_IsCought = true;
		m_pBall->SetVisibility(false);
	}
	if (m_IsCought)
	{
		m_PhaseTimer += elapsedSec;
		if (m_PhaseTimer - elapsedSec <= 0.000001f)
		{
			m_pAnimator->SetAnimation(1, 0.333f, AnimationMode::once);
		}
		else if (m_PhaseTimer >= 2.f)
		{
			m_pBall->SetVelocity(Vector2f{ -100,-100 });
			m_pBall->SetPosition(m_CatchHitbox.center + Vector2f{-10,-10});
			m_pBall->SetVisibility(true);
			m_PhaseTimer = 0;
			m_IsCought = false;
		}
	}
}