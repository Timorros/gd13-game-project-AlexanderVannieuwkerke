#pragma once
class Texture;
class Ball;

class Lane final
{
public:
	Lane(const Lane& other);
	Lane(Lane&& other);
	Lane(std::string path, Circlef trigger1, Circlef trigger2, Vector2f pos1, Vector2f pos2, Vector2f pos3);
	~Lane();

	Lane& operator=(const Lane& other);
	Lane& operator=(Lane&& other);

	bool Update(float elapsedSec, const Circlef& ballBounds);
	void Draw();

	int GetPasses() const { return m_Passes; }
	void ResetPasses();
private:
	std::string m_Path{};
	Texture* m_pTexture{};
	Vector2f m_LightPos[3]{};
	Circlef m_FirstTrigger{};
	Circlef m_SecondTrigger{};
	float m_Timer{};
	int m_Passes{0};
	bool m_FirstTriggerTriggered{ false };
};

