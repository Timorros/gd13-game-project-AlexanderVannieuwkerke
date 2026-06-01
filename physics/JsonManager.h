#pragma once
struct Hitbox;

void to_json(nlohmann::json& j, const Vector2f& v);
void from_json(const nlohmann::json& j, Vector2f& v);

void to_json(nlohmann::json& j, const Hitbox& hitbox);
void from_json(const nlohmann::json& j, Hitbox& hitbox);

void ReadMap(std::vector<Hitbox>& hitboxes, float scale);
void SaveMap(const std::vector<Hitbox>& hitboxes, float scale);