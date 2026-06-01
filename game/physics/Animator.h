#pragma once

#include <vector>
class Texture;

enum class AnimationMode
{
	loop,
	once,
	pingPong,
	variablePingPong
};
struct AnimationCmd
{
	int idx{0};
	float frameTime{0};
	AnimationMode animMode{AnimationMode::loop};
};

/// <summary>
/// An animator that supposes that every row is an animation which you can loop
/// </summary>
class Animator final
{
public:
	Animator(const Animator& other);
	Animator(Animator&& other);
	explicit Animator(const std::string& spriteSheetPath, const Rectf& spriteDimensions);
	explicit Animator(const std::string& spriteSheetPath, const Rectf& spriteDimensions, const std::vector<int>& animationFramesPerRow);
	~Animator();

	Animator& operator=(const Animator& other);
	Animator& operator=(Animator&& other);

	void Draw() const;
	void Update(float elapsedSec);

	bool GetIsVisible() const;
	void SetIsVisible(bool isVisible);
	int GetFrameIdx();
	Rectf GetBounds() const;
	float GetAnimationTime() const;

	const AnimationCmd& GetAnimation() const;
	void SetAnimation(int idx, float frameTime, AnimationMode animMode = AnimationMode::loop);
	void SetAnimation(AnimationCmd animCmd);
	void SetNextAnimation(int idx, float frameTime, AnimationMode animMode = AnimationMode::loop);
	void SetNextAnimation(AnimationCmd animCmd);
	const AnimationCmd& GetDefaultAnimation() const;
	void SetDefaultAnimation(int idx, float frameTime, AnimationMode animMode);
	void SetDefaultAnimation(const AnimationCmd& animCmd);

	void SetPosition(const Vector2f& pos);
	void SlideTo(const Vector2f& pos, float time);

private:
	std::vector<int> m_AnimFramesPerRow{};
	std::string m_Path{};
	Texture* m_SpriteSheet{ nullptr };
	AnimationCmd m_CurrentAnim{0,0.0333f,AnimationMode::loop};
	AnimationCmd m_NextAnim{};
	AnimationCmd m_DefaultAnim{ 0, 0.0333f, AnimationMode::loop };
	Rectf m_SpriteBounds{};
	Vector2f m_NextPos{};
	Vector2f m_Velocity{};

	float m_AnimationTime{};
	int m_FrameIdx{};
	bool m_IsLoopingForward{true};
	bool m_IsVisible{true};
	bool m_IsMoving{};

	Rectf GetSpriteSrc() const;
	float GetDistance() const;
};