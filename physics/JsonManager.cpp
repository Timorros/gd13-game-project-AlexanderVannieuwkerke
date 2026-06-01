#include "pch.h"
#include "JsonManager.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include "Matrix2x3.h"


void to_json(nlohmann::json& j, const Vector2f& v)
{
	j = nlohmann::json{ {"x",v.x}, {"y",v.y} };
}
void from_json(const nlohmann::json& j, Vector2f& v)
{
	v.x = j.value("x", 0.0f);
	v.y = j.value("y", 0.0f);
}

void to_json(nlohmann::json& j, const Hitbox& hitbox)
{
	j = nlohmann::json{ {"hitbox",hitbox.points}, {"elasticity",hitbox.elasticity} };
}
void from_json(const nlohmann::json& j, Hitbox& hitbox)
{
	j.at("elasticity").get_to(hitbox.elasticity);
	j.at("hitbox").get_to(hitbox.points);
}

void ReadMap(std::vector<Hitbox>& hitboxes, float scale)
{
	Matrix2x3 scaler;
	scaler.SetAsScale(1);

	nlohmann::json j;
	std::ifstream file("hitboxes.json");
	if (file.fail())
		return;
	file >> j;
	//std::cout << j.dump(2) << std::endl;
	std::vector<Hitbox> result{ j.get<std::vector<Hitbox>>() };
	for (Hitbox& hb : result)
	{
		hb.points = scaler.Transform(hb.points);
	}
	hitboxes = std::move(result);
}
void SaveMap(const std::vector<Hitbox> &hitboxes, float scale)
{
	Matrix2x3 scaler;
	scaler.SetAsScale(1);
	std::vector<Hitbox> saveHitboxes{};
	std::cout << hitboxes[0].points[0] << std::endl;
	for (Hitbox hb : hitboxes)
	{
		saveHitboxes.push_back(Hitbox{ scaler.Transform(hb.points), hb.elasticity });
	}

	nlohmann::json j;
	j = saveHitboxes;
	std::ofstream file("hitboxes.json");
	std::cout << file.fail() << std::endl;
	std::cout << file.is_open() << std::endl;
	file << j.dump();
}