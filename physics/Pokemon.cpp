#include "pch.h"
#include "pokemon.h"

Pokemon::Pokemon(const Bumper& bumper)
	: Bumper(bumper)
{
}

bool Pokemon::CalcPhysics(Ball& ball, float elapsedSec)
{
	m_Timer += elapsedSec;
	if (Bumper::CalcPhysics(ball, elapsedSec) && m_Timer >=0.5f)
	{
		m_Timer = 0;
		if (++m_Hits >= 3)
			return true;
	}
	return false;
}