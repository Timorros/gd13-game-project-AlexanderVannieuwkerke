#include "pch.h"
#include "Physics.h"
#include "Ball.h"
#include <iostream>
void CalcPhysics(Ball* ball, const Hitbox& hitbox, float elapsedSec)
{
	static const Vector2f gravity{ 0,-9.f };
	utils::HitInfo hitInfo{};
	const Vector2f& center{ ball->GetBounds().center };
	const Vector2f& velocity{ ball->GetVelocity() };

	if (utils::Raycast(hitbox.points, center, center + velocity.Normalized() * ball->GetBounds().radius * 1.5f, hitInfo))
	{
		Vector2f deltavector{ hitInfo.intersectPoint, center + velocity };		//line past intersection
		//ball->SetPosition(deltavector.Reflect(hitInfo.normal)*hitbox.elasticity + center);
		ball->SetVelocity(velocity.Reflect(hitInfo.normal) * hitbox.elasticity + gravity * elapsedSec);
		//std::cout << center << "\tcollision\n";
		for (int idx{ 1 }; idx < hitbox.points.size(); ++idx)
		{
			AvoidOverlap(*ball, hitbox.points[idx - 1], hitbox.points[idx], hitbox.elasticity > 1 ? true : false);
		}
	}
	else
	{
		ball->SetVelocity(velocity + gravity * elapsedSec);
	}
}

void AvoidOverlap(Ball& ball, Vector2f p1, Vector2f p2, bool IsPushing)
{
	const Vector2f& center{ ball.GetBounds().center };
	float distance{ utils::DistPointLineSegment(center, p1, p2) };
	if (distance < ball.GetBounds().radius)
	{
		Vector2f normal{ p2 - p1 };
		normal = normal.Orthogonal().Normalized();
		if (utils::DistPointLineSegment(center + normal, p1, p2) > utils::DistPointLineSegment(center - normal, p1, p2))
			normal = -normal;
		ball.SetPosition(center + normal * (distance - ball.GetBounds().radius));
		if (IsPushing)
			ball.SetVelocity(ball.GetVelocity() - normal * ball.GetVelocity().Length());
	}
}

void DrawEllipse(const Circlef& circle, float lineWidth)
{
	utils::DrawEllipse(circle.center, circle.radius, circle.radius, lineWidth);
}
