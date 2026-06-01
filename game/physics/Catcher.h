#pragma once
class Ball;
class Texture;
class Animator;

class Catcher final
{
public:
	explicit Catcher(const std::string& spriteSheetPath, const Rectf& bounds, const Circlef& catchHitbox, Ball* pball, const std::vector<int>& animationFramesPerRow);
	Catcher(const Catcher& other);
	Catcher(Catcher&& other);
	~Catcher();

	Catcher& operator=(Catcher& other) = delete;
	Catcher& operator=(Catcher&& other) = delete;

	void Draw() const;
	void Update(float ElapsedSec);
	bool GetIsCought() const { return m_IsCought; };
protected:
	Animator* m_pAnimator{ nullptr };
	Ball* m_pBall{ nullptr };
	const Circlef m_CatchHitbox;
	float m_PhaseTimer{};
	bool m_IsCought{ false };
};

