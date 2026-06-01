#pragma once

#include "Animator.h"
#include "Physics.h"

class LPaddle
{
public:
	LPaddle();
	~LPaddle();

	void Draw() const;
	void Update(float elapsedSec);
	void CalcPhysics(Ball* ball, float elapsedSec);
	void PaddleUp();
	void PaddleDown();
private:
	Animator* m_pAnim{ nullptr };
	std::vector<Vector2f> m_PaddleHitbox{ Vector2f{ -4,3 }, Vector2f{ -2,5 }, Vector2f{ 7,5 }, Vector2f{ 26,2 }, Vector2f{ 26,-1 }, Vector2f{ 7,-4 }, Vector2f{ -2,-4 }, Vector2f{-4,-2 } };

	int m_State{};

	bool m_IsUp{ false };

	float GetAngle(float animationTime, bool isLeft) const;
};

