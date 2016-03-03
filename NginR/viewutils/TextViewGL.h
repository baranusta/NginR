#ifndef _TEXTVIEWGL_H_
#define _TEXTVIEWGL_H_

#include "../Utils/Utils.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

class TextViewGL{
public:
	TextViewGL(float xMargin, float yMargin);
	TextViewGL(float xMargin, float yMargin,std::string t);
	virtual ~TextViewGL();
	virtual void draw();
	void SetColor(Color col);
	void SetText(char* text);

	static int GetItemCount();
	static void ResetItemCount();
private:
	void InitObject(float xMargin, float yMargin,Color c);
	std::string text;
	float xPos;
	float yPos;
	Color col;
	static int _itemCount;
};

#endif