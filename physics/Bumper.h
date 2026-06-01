#pragma once
#include "Animator.h"
class Ball;
struct CircleBox;

class Bumper
{
public:
	Bumper(const Bumper& other);
	Bumper(Bumper&& other);
	Bumper(const std::string& path, float bounceForce, Rectf bounds, const std::vector<int>& animationFramesPerRow, float radius = 7.5f);
	virtual ~Bumper();

	Bumper& operator=(const Bumper& other);
	Bumper& operator=(Bumper&& other);

	void Draw() const;
	virtual void Update(float elapsedSec);

	virtual bool CalcPhysics(Ball& ball, float elapsedSec);
	CircleBox GetHitbox() const;
protected:
	Circlef GetBounds() const { return m_Bounds; };
	void SetBounds(const Circlef& bounds) { m_Bounds = bounds; };
	void SetAnimation(int idx, float frameTime, AnimationMode mode);
	float GetBounceForce() const { return m_BounceForce; };
private:
	Animator* m_pAnimator{ nullptr };
	Circlef m_Bounds{};
	float m_BounceForce{};
};

