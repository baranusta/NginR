#include "Color.h"

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}

Color::Color(float r, float g, float b)
{
	SetAllColors(r, g, b, 1);
}

Color::Color(float r, float g, float b, float a)
{
	SetAllColors(r, g, b, a);
}


void Color::setColor(float& channel, float value)
{
	channel = value > 1 ? 1 : (value < 0 ? 0 : value);
}

void Color::SetAllColors(float r, float g, float b, float a)
{
	setColor(red, r);
	setColor(green, g);
	setColor(blue, b);
	setColor(alpha, a);
}

Color Color::operator*(Color c)
{
	return Color(c.red*red, c.green*green, c.blue*blue);
}

Color Color::operator*(float c)
{
	return Color(c*red, c*green, c*blue);
}

Color Color::operator+(Color c)
{
	return Color(c.red+red, c.green+green, c.blue+blue);
}


float Color::getR()
{
	return red;
}

float Color::getG()
{
	return green;
}

float Color::getB()
{
	return blue;
}

float Color::getOpacity()
{
	return alpha;
}

int Color::rgbToInt()
{
	return (int(red * 255) << 16) | (int(green * 255) << 8) | int(blue * 255);
}