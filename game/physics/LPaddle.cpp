#include "pch.h"
#include "LPaddle.h"
#include "Matrix2x3.h"
#include "Ball.h"

LPaddle::LPaddle()
	: m_pAnim{ new Animator{ "lPaddle.png", Rectf{85,13,32,28}, std::vector<int>{1,6,1,6} } }
{
}
LPaddle::~LPaddle()
{
	delete m_pAnim;
}

void LPaddle::CalcPhysics(Ball* ball, float elapsedSec)
{
	const Rectf& animBounds{ m_pAnim->GetBounds() };
	if (ball->GetBounds().center.y > animBounds.bottom + animBounds.height) return;

	const int& animIdx{ m_pAnim->GetAnimation().idx };
	Matrix2x3 rot;
	if (animIdx == 2)
		rot.SetAsRotate(30);
	else if (animIdx == 3)
		rot.SetAsRotate(30 - m_pAnim->GetFrameIdx() * 12.f);
	else
		rot.SetAsRotate(-30 + m_pAnim->GetFrameIdx() * 12.f);

	Hitbox hitbox{};
	hitbox.points = rot.Transform(m_PaddleHitbox);
	if (animIdx == 1) hitbox.elasticity = 1.5f;
	else hitbox.elasticity = 0.6f;

	if (animIdx == 1)
	{

	}

}

void LPaddle::PaddleUp()
{
	if (!m_IsUp)
	{
		m_pAnim->SetAnimation(1, 0.0333f, AnimationMode::once);
		m_pAnim->SetNextAnimation(2, 0.0333f, AnimationMode::loop);
		m_IsUp = true;
	}
}
void LPaddle::PaddleDown()
{
	m_pAnim->SetAnimation(3, 0.0333f, AnimationMode::once);
	m_IsUp = false;
}

void LPaddle::Draw() const
{
	m_pAnim->Draw();
}

void LPaddle::Update(float elapsedSec)
{
	m_pAnim->Update(elapsedSec);
}