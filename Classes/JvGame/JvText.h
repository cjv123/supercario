#ifndef _JVTEXT_H
#define _JVTEXT_H

#include "JvSprite.h"
#include <string>
using namespace std;

/**
*文本
*实现文本显示,支持\n换行
*/
class JvText : public JvObject
{
public:
	JvText(double X, double Y, double Width,double Height,const char* fontname,
		const char* Text="");
	virtual ~JvText();
	void setText(string& Text);
	string& getText();
	void setFont(const char* fontname);
	void setSize(int Size);
	int getSize();
	void setColor(int color);
	ccColor4B getColor();
	void setLineHeight(int Height);
	int getLineHeight();

	virtual void render();

	CCLabelTTF* getCCLabel();
protected:
	CCLabelTTF* _cclabel;
	string _text;
	int _size;
	int _color;
	int _lineHeight;
	string _fontname;
	string _aname;
	string _cname;
private:
};
#endif
