#pragma once
#include "Bumper.h"

class Pokemon : public Bumper
{
public:
	Pokemon(const Bumper& bumper);
	virtual ~Pokemon() = default;

	virtual bool CalcPhysics(Ball& ball, float elapsedSec) override;
	int GetHits() const { return m_Hits; }
protected:
	int m_Hits{0};
	float m_Timer{ 0 };
};

