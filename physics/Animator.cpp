#include "pch.h"
#include "Animator.h"
#include "Texture.h"
#include "utils.h"

Animator::Animator(const Animator& other)
	: m_AnimFramesPerRow{ other.m_AnimFramesPerRow }
	, m_Path{ other.m_Path }
	, m_SpriteSheet{new Texture{m_Path}}
	, m_CurrentAnim{other.m_CurrentAnim}
	, m_NextAnim{other.m_NextAnim}
	, m_DefaultAnim{ other.m_DefaultAnim }
	, m_SpriteBounds{ other.m_SpriteBounds }
	, m_NextPos{ other.m_NextPos }
	, m_Velocity{ other.m_Velocity }

	, m_AnimationTime{ other.m_AnimationTime }
	, m_FrameIdx{ other.m_FrameIdx }
	, m_IsLoopingForward{ other.m_IsLoopingForward }
	, m_IsVisible{ other.m_IsVisible }
	, m_IsMoving{ other.m_IsMoving }
{
	
}
Animator::Animator(Animator&& other)
	: m_AnimFramesPerRow{ other.m_AnimFramesPerRow }
	, m_Path{ other.m_Path }
	, m_SpriteSheet{ other.m_SpriteSheet }
	, m_CurrentAnim{ other.m_CurrentAnim }
	, m_NextAnim{ other.m_NextAnim }
	, m_DefaultAnim{ other.m_DefaultAnim }
	, m_SpriteBounds{ other.m_SpriteBounds }
	, m_NextPos{ other.m_NextPos }
	, m_Velocity{ other.m_Velocity }

	, m_AnimationTime{ other.m_AnimationTime }
	, m_FrameIdx{ other.m_FrameIdx }
	, m_IsLoopingForward{ other.m_IsLoopingForward }
	, m_IsVisible{ other.m_IsVisible }
	, m_IsMoving{ other.m_IsMoving }
{
	other.m_SpriteSheet = nullptr;
}
Animator::Animator(const std::string& spriteSheetPath, const Rectf& spriteDimensions) 
	: m_SpriteSheet{ new Texture(spriteSheetPath) }
	, m_SpriteBounds{ spriteDimensions }
	, m_Path{ spriteSheetPath }
{
	for (int idx{}; idx< int(m_SpriteSheet->GetHeight() / m_SpriteBounds.height); ++idx)
		m_AnimFramesPerRow.push_back(int(m_SpriteSheet->GetWidth() / m_SpriteBounds.width));
}
Animator::Animator(const std::string& spriteSheetPath, const Rectf& spriteDimensions, const std::vector<int>& animationFramesPerRow)
	: m_SpriteSheet{ new Texture(spriteSheetPath) }
	, m_SpriteBounds{ spriteDimensions }
	, m_AnimFramesPerRow{animationFramesPerRow}
	, m_Path{ spriteSheetPath }
{

}
Animator::~Animator()
{
	delete m_SpriteSheet;
}

Animator& Animator::operator=(const Animator& other)
{
	if (&other != this)
	{
		m_AnimFramesPerRow = other.m_AnimFramesPerRow;
		m_Path = other.m_Path;
		delete m_SpriteSheet;
		m_SpriteSheet = new Texture{m_Path};
		m_CurrentAnim = other.m_CurrentAnim;
		m_NextAnim = other.m_NextAnim;
		m_DefaultAnim = other.m_DefaultAnim;
		m_SpriteBounds = other.m_SpriteBounds;
		m_NextPos = other.m_NextPos;
		m_Velocity = other.m_Velocity;

		m_AnimationTime = other.m_AnimationTime;
		m_FrameIdx = other.m_FrameIdx;
		m_IsLoopingForward = other.m_IsLoopingForward;
		m_IsVisible = other.m_IsVisible;
		m_IsMoving = other.m_IsMoving;
	}
	return *this;
}
Animator& Animator::operator=(Animator&& other)
{
	if (&other != this)
	{
		m_AnimFramesPerRow = other.m_AnimFramesPerRow;
		m_Path = std::move(other.m_Path);
		delete m_SpriteSheet;
		m_SpriteSheet = other.m_SpriteSheet;
		other.m_SpriteSheet = nullptr;
		m_CurrentAnim = other.m_CurrentAnim;
		m_NextAnim = other.m_NextAnim;
		m_DefaultAnim = other.m_DefaultAnim;
		m_SpriteBounds = other.m_SpriteBounds;
		m_NextPos = other.m_NextPos;
		m_Velocity = other.m_Velocity;

		m_AnimationTime = other.m_AnimationTime;
		m_FrameIdx = other.m_FrameIdx;
		m_IsLoopingForward = other.m_IsLoopingForward;
		m_IsVisible = other.m_IsVisible;
		m_IsMoving = other.m_IsMoving;
	}
	return *this;
}

void Animator::Draw() const
{
	if(m_IsVisible)
		m_SpriteSheet->Draw(m_SpriteBounds, GetSpriteSrc());
}
void Animator::Update(float elapsedSec)
{
	m_AnimationTime += elapsedSec;
	if (m_AnimationTime >= m_CurrentAnim.frameTime)
	{
		m_AnimationTime -= m_CurrentAnim.frameTime;
		if (m_IsLoopingForward && m_FrameIdx<m_AnimFramesPerRow[m_CurrentAnim.idx]-1)
			++m_FrameIdx;
		else if (!m_IsLoopingForward && m_FrameIdx > 0)
			--m_FrameIdx;
		else
		{
			if (m_NextAnim.frameTime > 0)
			{
				SetAnimation(m_NextAnim);
				m_NextAnim = AnimationCmd{};
			}
			switch (m_CurrentAnim.animMode)
			{
			case AnimationMode::loop:
				m_FrameIdx = 0;
				break;
			case AnimationMode::once:
				SetAnimation(m_DefaultAnim);
				break;
			case AnimationMode::pingPong:
				if (m_IsLoopingForward)
				{
					--m_FrameIdx;
					m_IsLoopingForward = false;
				}
				else
				{
					++m_FrameIdx;
					m_IsLoopingForward = true;
				}
				break;
			}
		}
	}

	if (m_IsMoving)
	{
		m_SpriteBounds.left += m_Velocity.x;
		m_SpriteBounds.bottom += m_Velocity.y;
		if (GetDistance() <= 0.1f)
		{
			m_IsMoving = false;
			m_Velocity = Vector2f{ 0,0 };
		}
	}

}

bool Animator::GetIsVisible() const
{
	return m_IsVisible;
}
void Animator::SetIsVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
int Animator::GetFrameIdx()
{
	return m_FrameIdx;
}
Rectf Animator::GetBounds() const
{
	return m_SpriteBounds;
}
float Animator::GetAnimationTime() const
{
	return m_AnimationTime;
}

const AnimationCmd& Animator::GetAnimation() const
{
	return m_CurrentAnim;
}
void Animator::SetAnimation(int animationIdx, float frameTime, AnimationMode animMode)
{
	SetAnimation(AnimationCmd{ animationIdx,frameTime,animMode });
}
void Animator::SetAnimation(AnimationCmd animCmd)
{
	m_CurrentAnim = animCmd;
	m_FrameIdx = 0;
	m_IsLoopingForward = true;
	m_NextAnim = AnimationCmd{};
}
void Animator::SetNextAnimation(int animationIdx, float frameTime, AnimationMode animMode)
{
	m_NextAnim = AnimationCmd{ animationIdx, frameTime, animMode };
}
void Animator::SetNextAnimation(AnimationCmd animCmd)
{
	m_NextAnim = animCmd;
	m_FrameIdx = 0;
	m_IsLoopingForward = true;
}
const AnimationCmd& Animator::GetDefaultAnimation() const
{
	return m_DefaultAnim;
}
void Animator::SetDefaultAnimation(int idx, float frameTime, AnimationMode animMode)
{
	SetDefaultAnimation(AnimationCmd{ idx,frameTime,animMode });
}
void Animator::SetDefaultAnimation(const AnimationCmd& animCmd)
{
	m_DefaultAnim = animCmd;
}


void Animator::SetPosition(const Vector2f& pos)
{
	m_SpriteBounds.left = pos.x;
	m_SpriteBounds.bottom = pos.y;
}
void Animator::SlideTo(const Vector2f& pos, float time)
{
	m_NextPos = pos;
	m_Velocity = (pos - Vector2f{ m_SpriteBounds.left, m_SpriteBounds.bottom }) / time;
}

Rectf Animator::GetSpriteSrc() const
{
	return Rectf{
		m_SpriteBounds.width * m_FrameIdx,
		m_SpriteBounds.height * m_CurrentAnim.idx,
		m_SpriteBounds.width,
		m_SpriteBounds.height };
}
float Animator::GetDistance() const
{
	float x{ m_SpriteBounds.left - m_NextPos.x };
	float y{ m_SpriteBounds.bottom - m_NextPos.y };
	return sqrt(x * x + y * y);
}