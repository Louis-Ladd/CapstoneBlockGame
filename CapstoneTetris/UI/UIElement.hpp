#pragma once 

#include  "../utils/vector2.hpp"

virtual class UIElement
{
public:
	void Render();
	Vector2 GetPosition() { return this->position };
	void SetPosition(const Vector2 new_pos) { this->position = new_pos };
private 
	Vector2 position;
};