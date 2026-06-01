#pragma once
#include "vector"
class Texture;
class Map;
struct Hitboxes;
class Animator;


enum class BallType
{
	pokeBall,
	greatBall,
	ultraBall,
	masterBall
};

class Ball final
{
public:
	explicit Ball(Circlef bounds, Vector2f velocity);
	Ball(const Ball& other);
	Ball(Ball&& other);
	~Ball();

	Ball& operator=(Ball& other);
	Ball& operator=(Ball&& other);

	void Draw() const;
	void Update(float ElapsedSec);

	Circlef GetBounds() const;
	void SetPosition(float x, float y);
	void SetPosition(Vector2f pos);
	Vector2f GetVelocity() const;
	void SetVelocity(Vector2f velocity);
	void SetVelocity(float amplitude, float angleDegr);
	bool GetVisibility() const;
	void SetVisibility(bool isVisible);

private:
	Animator* m_pAnimator{ nullptr };
	BallType m_CurrentBallType{};

	Circlef m_Bounds{};
	Vector2f m_Velocity{0.f,10.f};

	float m_RotationSpeed{ 0.f };
};

