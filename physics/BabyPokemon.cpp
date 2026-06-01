#include "pch.h"
#include "BabyPokemon.h"
#include "utils.h"
#include "Ball.h"

const std::vector<Vector2f> BabyPokemon::m_WanderPath = {
	Vector2f{68,217},
	Vector2f{112,186},
	Vector2f(165, 166),
	Vector2f(152, 110),
	Vector2f(86, 106),
	Vector2f(103, 152)
};

BabyPokemon::BabyPokemon(const Bumper& bumper) :
	Pokemon{ bumper }
{
	m_Velocity = Vector2f{ Bumper::GetBounds().center, m_WanderPath[m_CurrentPathIdx] }.Normalized() * 50.f;
	Bumper::SetAnimation(CalcAnimIdx(), 0.5f, AnimationMode::loop);
}

void BabyPokemon::Update(float elapsedSec)
{
	Bumper::Update(elapsedSec);

	// calc next point and new velocity
	const Vector2f& center{ Bumper::GetBounds().center };
	if(utils::GetDistance(center, m_WanderPath[m_CurrentPathIdx]) < 5.f)
	{
		if (++m_CurrentPathIdx >= m_WanderPath.size())
		{
			m_CurrentPathIdx = 0;
		}
		m_Velocity = Vector2f{center, m_WanderPath[m_CurrentPathIdx]}.Normalized() * m_Velocity.Norm();
		Bumper::SetAnimation(CalcAnimIdx(), 0.5f, AnimationMode::loop);
	}
	Bumper::SetBounds(Circlef{ center + m_Velocity * elapsedSec, Bumper::GetBounds().radius });
}
bool BabyPokemon::CalcPhysics(Ball& ball, float elapsedSec)
{
	m_Timer += elapsedSec;
	if (utils::GetDistance(ball.GetBounds().center, Bumper::GetBounds().center) < ball.GetBounds().radius + Bumper::GetBounds().radius)
	{
		Vector2f normal{ Bumper::GetBounds().center, ball.GetBounds().center };
		normal.Normalized();
		ball.SetVelocity(ball.GetVelocity().Reflect(normal) * Bumper::GetBounceForce());

		if (m_Timer >= 0.5f)
		{
			Bumper::SetAnimation(4, 0.5f, AnimationMode::once);
			if (++m_Hits > 1)
			{
				m_Hits = 0;
				m_Timer = 0;
				return true;
			}
		}
	}

	return false;
}

int BabyPokemon::CalcAnimIdx() const
{
	if (std::abs(m_Velocity.x) > std::abs(m_Velocity.y))
	{
		return m_Velocity.x > 0 ? 0 : 2;
	}
	else
	{
		return m_Velocity.y > 0 ? 1 : 3;
	}
}