#pragma once

#include "Animator.h"

struct Hitbox;

class Paddle final
{
public:
	Paddle(const Paddle& other);
	Paddle(Paddle&& other);
	Paddle();
	~Paddle();

	Paddle& operator=(const Paddle& other);
	Paddle& operator=(Paddle&& other);

	void Draw() const;
	Hitbox GetLeftHitbox() const;
	Hitbox GetRightHitbox() const;

	//void UseLeftPaddle();
	//void UseRightPaddle();
	void LeftPaddleUp();
	void RightPaddleUp();
	void LeftPaddleDown();
	void RightPaddleDown();

	void Update(float elapsedSec);


private:
	Animator* m_pLeftPaddle{ nullptr };
	Animator* m_pRightPaddle{ nullptr };

	int m_LeftState{};
	int m_RightState{};

	bool m_LeftIsUp{false};
	bool m_RightIsUp{false};

	float GetAngle(float animationTime, bool isLeft) const;
};

