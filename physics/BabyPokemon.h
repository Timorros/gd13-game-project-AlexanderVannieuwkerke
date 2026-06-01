#pragma once
#include "Pokemon.h"
#include <vector>

class BabyPokemon final : public Pokemon
{
public:
	BabyPokemon(const Bumper& bumper);
	~BabyPokemon() = default;

	void Update(float elapsedSec) override;
	bool CalcPhysics(Ball& ball, float elapsedSec) override;

private:
	static const std::vector<Vector2f> m_WanderPath;
	int m_CurrentPathIdx{ 0 };
	Vector2f m_Velocity{ 0,0 };

	int CalcAnimIdx() const;
};

