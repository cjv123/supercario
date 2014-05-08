#include "JvText.h"
#include "JvU.h"

JvText::JvText(double X,double Y, double Width,double Height,const char* fontname,
			   const char* Text)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	_text = Text;
	_size = 8;
	_lineHeight = 1;
	setCollide(false);
	_fontname = fontname; 

	
	_cclabel = CCLabelTTF::create(Text,fontname,_size);
	_cclabel->retain();
	_cclabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	_cclabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	_cclabel->setAnchorPoint(ccp(0,1));
}

JvText::~JvText()
{
	if (_cclabel != NULL)
	{
		_cclabel->release();
		_cclabel = NULL;
	}

}

void JvText::setText(string& Text)
{
	_text = Text;
	_cclabel->setString(_text.c_str());
}

string& JvText::getText()
{
	return _text;
}

void JvText::setFont(const char* fontname)
{
	_fontname = fontname;
	_cclabel->setFontName(fontname);
}

void JvText::setSize(int Size)
{
	_size = Size;
	_cclabel->setFontSize(_size);
}

int JvText::getSize()
{
	return _size;
}

void JvText::setColor(int color)
{
	_color = color;
	int r,g,b,a;
	GET_RGBA_8888(_color,r,g,b,a);
	_cclabel->setColor(ccc3(r,g,b));
	_cclabel->setOpacity(a);
}

void JvText::setLineHeight(int Height)
{
	_lineHeight = Height;

}

int JvText::getLineHeight()
{
	return _lineHeight;
}

void JvText::render()
{
	CCSize winsize = CCDirector::sharedDirector()->getRunningScene()->getContentSize();
	_cclabel->setDimensions(CCSizeMake(width,height));
	_cclabel->setPosition(ccp(x,winsize.height - y));
	_cclabel->visit();
}

CCLabelTTF* JvText::getCCLabel()
{
	return _cclabel;
}

