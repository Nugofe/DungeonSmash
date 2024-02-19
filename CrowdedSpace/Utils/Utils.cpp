#include "Utils.h"

Vector2D Vector2D::ZeroVector = Vector2D{ 0.0f, 0.0f };
Transform2D Transform2D::ZeroTransform = Transform2D{ 0.0f, 0.0f, 0.0f, 1.0f };

RGBColor RGBColor::White = RGBColor{ 1.0f, 1.0f, 1.0f };
RGBColor RGBColor::Red = RGBColor{ 1.0f, 0.0f, 0.0f };
RGBColor RGBColor::Blue = RGBColor{ 0.0f, 1.0f, 0.0f };
RGBColor RGBColor::Green = RGBColor{ 0.0f, 0.0f, 1.0f };
RGBColor RGBColor::Orange = RGBColor{ 1.0f, 0.6f, 0.0f };
RGBColor RGBColor::Cyan = RGBColor{ 0.0f, 1.0f, 1.0f };
RGBColor RGBColor::Pink = RGBColor{ 1.0f, 0.6f, 1.0f };

Vector2D::Vector2D() : x(0.0f), y(0.0f)
{
}

Vector2D::Vector2D(float pos_x, float pos_y) : x(pos_x), y(pos_y)
{
}

void Vector2D::Normalize()
{
	float length = sqrt(x*x + y*y);
	if (length != 0)
	{
		x /= length;
		y /= length;
	}
	else
	{
		x = 0.0f;
		y = 0.0f;
	}
}

float Vector2D::Distance(const Vector2D& v1, const Vector2D& v2)
{
	float first = v2.x - v1.x;
	float second = v2.y - v1.y;
	return sqrt(first * first + second * second);
}

float Vector2D::DistanceSquare(const Vector2D& v1, const Vector2D& v2)
{
	float first = v2.x - v1.x;
	float second = v2.y - v1.y;
	return first * first + second * second;
}

Transform2D::Transform2D() : position(Vector2D()), rotation(0.0f), scale(0.0f)
{
}

Transform2D::Transform2D(float pos_x, float pos_y, float rotation, float scale)
{
	this->position = Vector2D(pos_x, pos_y);
	this->rotation = rotation;
	this->scale = scale;
}

Transform2D::Transform2D(Vector2D position, float rotation, float scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

RGBColor::RGBColor() : R(1.0f), G(1.0f), B(1.0f)
{
}

RGBColor::RGBColor(float r, float g, float b) : R(r), G(g), B(b)
{
}

Vector2D HelperFunctions::GetRandomPositionInRange(int maxX, int maxY)
{
	return { static_cast<float>(rand() % maxX), static_cast<float>(rand() % maxY) };
}