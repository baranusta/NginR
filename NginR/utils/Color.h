#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	void SetAllColors(float r, float g, float b, float a);

	Color operator*(Color c);
	Color operator*(float c);
	Color operator+(Color c);

	float getR();
	float getG();
	float getB();
	float getOpacity();
	int rgbToInt();

private:

	void setColor(float& channel, float value);

	float red;
	float green;
	float blue;
	float alpha;
};

#endif