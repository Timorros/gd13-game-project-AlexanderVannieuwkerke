#pragma once
#include "utils.h"

class Ball;

struct Hitbox
{
	std::vector<Vector2f> points{};
	float elasticity{};
};
struct CircleBox
{
	Circlef circle{};
	float elasticity{};
};

void CalcPhysics(Ball* ball, const Hitbox& hitbox, float elapsedSec);

void AvoidOverlap(Ball& ball, Vector2f p1, Vector2f p2, bool IsPushing);

void DrawEllipse(const Circlef& circle, float lineWith = 1.f);