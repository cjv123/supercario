#include "JvSprite.h"
#include "JvState.h"

JvSprite::JvSprite(double X /* =0 */,double Y/* =0 */,
				   CCSprite* SimpleGraphic /* = NULL */) : JvObject(X,Y)
{
	_pixels = NULL;
	_scale = 1;
	if (SimpleGraphic != NULL)
	{
		loadGraphic(SimpleGraphic);
	}

	_frameTimer =0;
	_curAnim = NULL;
	_curFrame = 0;
	facing = FACERIGHT;
	_isFillRect = false;
	_mask = 0;

	_ccFillLayer = CCLayerColor::create();
	_ccFillLayer->retain();
}

JvSprite::~JvSprite()
{
	if (_pixels != NULL)
	{
		_pixels->release();
		_pixels = NULL;
	}

	if (_ccFillLayer)
	{
		_ccFillLayer->release();
		_ccFillLayer = NULL;
	}

	//Çå³ý¶¯»­
	clearAnim();
}

JvSprite* JvSprite::loadGraphic(string FileName,bool Animated /* = false */,bool Reverse /* =false */,
								unsigned int Width /* = 0 */,unsigned int Height /* =0 */)
{
	if (_pixels != NULL)
	{
		_pixels->release();
		_pixels = NULL;
	}
	
	_pixels = CCSprite::create(FileName.c_str());
	_pixels->retain();
	_pixels->getTexture()->setAliasTexParameters();
	_pixels->setAnchorPoint(ccp(0,1));

	if (_pixels ==NULL)
	{
		printf("no this file: %s\n",FileName.c_str());
		return this;
	}

	if (!Animated)
	{
		frameWidth = _pixels->getContentSize().width;
		frameHeight = _pixels->getContentSize().height;
		width = _pixels->getContentSize().width*_scale;
		height = _pixels->getContentSize().height*_scale;
	}
	else
	{
		frameWidth = Width;
		frameHeight = Height;
		width = Width*_scale;
		height = Height*_scale;
	}
	origin.x = frameWidth/2;
	origin.y = frameHeight/2;
	return this;
}

JvSprite* JvSprite::loadGraphic(CCSprite* Graphic,bool Animated /* = false */,bool Reverse /* =false */,
								unsigned int Width /* = 0 */,unsigned int Height /* =0 */)
{
	if (_pixels != NULL)
	{
		_pixels->release();
		_pixels = NULL;
	}

	_pixels = CCSprite::createWithTexture(Graphic->getTexture());
	_pixels->retain();
	_pixels->getTexture()->setAliasTexParameters();
	_pixels->setAnchorPoint(ccp(0,1));

	if (!Animated)
	{
		frameWidth = _pixels->getContentSize().width;
		frameHeight = _pixels->getContentSize().height;
		width = _pixels->getContentSize().width*_scale;
		height = _pixels->getContentSize().height*_scale;
	}
	else
	{
		frameWidth = Width;
		frameHeight = Height;
		width = Width*_scale;
		height = Height*_scale;
	}
	origin.x = frameWidth/2;
	origin.y = frameHeight/2;
	return this;
}

void JvSprite::create()
{

}

void JvSprite::update()
{
	JvObject::update();
	updateAnimation();
}

void JvSprite::render()
{
	renderSprite();

	if (_isFillRect)
	{
		CCSize winsize = CCDirector::sharedDirector()->getRunningScene()->getContentSize();
		int r,g,b,a;
		GET_RGBA_8888(_rectColor,r,g,b,a);
		_ccFillLayer->setContentSize(CCSizeMake(width,height));
		_ccFillLayer->setColor(ccc3(r,g,b));
		_ccFillLayer->setOpacity(a);
		_ccFillLayer->setPosition(ccp(x,winsize.height-y-height));
		_ccFillLayer->visit();
	}
}

CCSprite* JvSprite::getPixels()
{
	return _pixels;
}

void JvSprite::renderSprite()
{
	JvG::stateP->camera.render(this);
	//printf("rendersprite");
}

void JvSprite::addAnimation(string Name, vector<int>& Frames,
							double FrameRate/* =0 */, bool Looped/* =true */)
{
	_animations.push_back(new JvAnim(Name,Frames,FrameRate,Looped));
}

void JvSprite::play(string Name ,bool Force /* = false */)
{
	if (!Force && (_curAnim != NULL))
	{
		if (Name == _curAnim->name)
		{
			return;
		}
	}

	_curFrame = 0;
	
	vector<JvAnim*>::iterator it = _animations.begin();
	for (;it!=_animations.end();it++)
	{
		if ((*it)->name == Name)
		{
			_curAnim = (*it);
		}
	}
}

void JvSprite::updateAnimation()
{
	if (_curAnim != NULL && (_curAnim->delay > 0) && (_curAnim->looped || !finished))
	{
		_frameTimer+=JvG::elapsed;
		if (_frameTimer > _curAnim->delay)
		{
			_frameTimer -= _curAnim->delay;
			if (_curFrame>=_curAnim->frames.size() - 1)
			{
				if(_curAnim->looped) _curFrame = 0;
				finished = true;
			}
			else
			{
				_curFrame++;
			}
		}
	}
}

unsigned int JvSprite::getCaf()
{
	if (_curAnim != NULL)
	{
		return _curAnim->frames[_curFrame];
	}
	else
	{
		return 0;
	}
}

void JvSprite::preCollide(JvObject* ObjectP)
{
	
}

void JvSprite::setScale(double Scale)
{
	_scale = Scale;
	width =_scale*frameWidth;
	height=_scale*frameHeight;

//	printf("scale:%lf,width:%lf,height:%lf\n",_scale,width,height);
	origin.x = x + width/2;
	origin.y = y + height/2;
}

double JvSprite::getScale()
{
	return _scale;
}

void JvSprite::clearAnim()
{
	vector<JvAnim*>::iterator it = _animations.begin();
	for (;it!=_animations.end();it++)
	{
		delete (*it);
	}
	_animations.clear();
	_curAnim = NULL;
}

void JvSprite::createRect(int X,int Y,int Width,int Height,int Color)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	_rectColor = Color;
	_isFillRect = true;
}

bool JvSprite::isPlayEnd()
{
	if (_curAnim != NULL)
	{
		if(_curFrame>=_curAnim->frames.size()-1)
			return true;
	}
	return false;
}

void JvSprite::setMask(int MaskColor)
{
	_mask = MaskColor;
}

int JvSprite::getMask()
{
	return _mask;
}

/*virtual*/
void JvSprite::onEmit()
{

}