#include "JvSprite.h"
#include "JvCamera.h"

JvCamera::JvCamera()
{
	_fllowObjP = NULL;
	width = JvG::width;
	height = JvG::height;

	_shakeTimer =0;
	_shakeXtmp =0;
	_shakeYtmp=0;
	_flashDelay =0;
	_flashColor =0;
	_flashAlpha =0;
	_moveVelocity = 0;
	_moveX = 0;
	_moveY = 0;

	_ccflashlayer = CCLayerColor::create();
	_ccflashlayer->retain();
	_ccflashlayer->setContentSize(CCSizeMake(width,height));
}

JvCamera::JvCamera(unsigned int screenW,unsigned int screenH)
{
	width = screenW;
	height = screenH;
	_fllowObjP = NULL;

	_shakeTimer =0;
	_shakeXtmp =0;
	_shakeYtmp=0;
	_flashDelay =0;
	_flashColor =0;
	_flashAlpha =0;
	_moveVelocity = 0;
	_moveX = 0;
	_moveY = 0;

	_ccflashlayer = CCLayerColor::create();
	_ccflashlayer->retain();
	_ccflashlayer->setContentSize(CCSizeMake(width,height));
}

JvCamera::~JvCamera()
{
	_ccflashlayer->release();
}

void JvCamera::init(unsigned int screenW,unsigned int screenH)
{
	width = screenW;
	height = screenH;

}

bool JvCamera::checkInCamera(JvObject* ObjectP)
{
	JvPoint objPoint(ObjectP->x,ObjectP->y);
	JvPoint spoint = toScreenPoint(objPoint);
	spoint.x *= ObjectP->scrollFactor.x;
	spoint.y *= ObjectP->scrollFactor.y;
	
	if ( spoint.x + ObjectP->width<0 ||
		spoint.x > width ||
		spoint.y > height ||
		spoint.y + ObjectP->height < 0
		)
	{
		return false;
	}
	return true;
}

JvRect JvCamera::getCameraRect()
{
	//printf("%d\n",_fllowObjP);
	if (_fllowObjP == NULL)
	{
		return JvRect(x,y,width,height);
	}

	if (_shakeTimer!=0)
	{
		return JvRect(x,y,width,height);
	}

	if (x<_fllowBound.x)
	{
		x=_fllowBound.x;
	}

	if (y<_fllowBound.y)
	{
		y=_fllowBound.y;
	}

	if (GetRight()>_fllowBound.GetRight())
	{
		x=_fllowBound.GetRight() - width;
	}

	if (GetBottom()>_fllowBound.GetBottom())
	{
		y=_fllowBound.GetBottom()- height;
	}

	return JvRect(x,y,width,height);
}

void JvCamera::render(JvSprite* ObjectP)
{
	if (checkInCamera(ObjectP))
	{
		CCSprite* pixels = ObjectP->getPixels();
		if (pixels == NULL)
			return;

		unsigned int rx = ObjectP->getCaf()*ObjectP->frameWidth;
		unsigned int ry = 0;

	//	printf("%d\n",rx);
		
		unsigned int w = (unsigned int)pixels->getTexture()->getContentSize().width;
		if(rx >= w)
		{
			ry = (unsigned int)(rx/w)*ObjectP->frameHeight;
			rx %= w;
		}

		DRAWVH drawvh = NGE_FLIP_NONE;
		if(ObjectP->facing==FACELEFT)
		{
			drawvh=NGE_FLIP_H;
		}
		else if (ObjectP->facing==FACEDOWN)
		{
			drawvh=NGE_FLIP_V;
		}
		else if (ObjectP->facing==FACELEFT && ObjectP->facing==FACEDOWN)
		{
			drawvh=NGE_FLIP_HV;
		}

		JvPoint objPoint(ObjectP->x,ObjectP->y);
		JvPoint spoint = toScreenPoint(objPoint);

		spoint.x = (ObjectP->scrollFactor.x==0)?ObjectP->x:(ObjectP->scrollFactor.x*spoint.x);
		spoint.y = (ObjectP->scrollFactor.y==0)?ObjectP->y:(ObjectP->scrollFactor.y*spoint.y);

		int drawmask = ObjectP->getMask();

		draw(pixels,rx,ry,ObjectP->frameWidth,ObjectP->frameHeight,
			spoint.x-ObjectP->offset.x,spoint.y-ObjectP->offset.y,ObjectP->getScale(),ObjectP->getScale(),
			ObjectP->angle,drawvh,drawmask);


// 		RenderQuad(pixels,rx,ry,ObjectP->frameWidth,ObjectP->frameHeight,
// 			spoint.x-ObjectP->offset.x,spoint.y-ObjectP->offset.y,ObjectP->getScale(),ObjectP->getScale(),
// 			ObjectP->angle,drawmask);
	}
}

void JvCamera::shake(double Intensity/* =0.05 */,double Duration/* =0.5 */)
{
	stopShake();
	_intensity = Intensity;
	_shakeTimer = Duration;
	_shakeXtmp = x;
	_shakeYtmp = y;
}

void JvCamera::stopShake()
{
	if (_shakeTimer ==0)
	{
		return;
	}
	_shakeTimer = 0;
	_intensity = 0;
	x = _shakeXtmp;
	y = _shakeYtmp;
}

void JvCamera::flash(int Color/* =0 */, double Duration/* =1 */)
{
	_flashColor = Color;
	_flashDelay = Duration;
	_flashAlpha = 255;
}

JvPoint JvCamera::toScreenPoint(JvPoint& point)
{
	JvRect cameraRect = getCameraRect(); 
	JvPoint spoint;
	spoint.x = JvU::floor(point.x - cameraRect.x);
	spoint.y = JvU::floor(point.y - cameraRect.y);
	return spoint;
}

JvObject* JvCamera::getFllowObj()
{
	return _fllowObjP;
}

void JvCamera::followBounds(int X/* =0 */,int Y/* =0 */,int Width/* =0 */,int Height/* =0 */,bool UpdateWorldBounds/* =true*/)
{
	_fllowBound.x = (X<0)?0:X;
	_fllowBound.y = (Y<0)?0:Y;
	_fllowBound.width = Width;
	_fllowBound.height = Height;

	if (UpdateWorldBounds)
	{
		JvU::setWorldBounds(X,Y,Width,Height);
	}
}

void JvCamera::followAdjust(double LeadX /* = 0 */,double LeadY /* = 0 */)
{
	followLead.x = LeadX;
	followLead.y = LeadY;
}

void JvCamera::update()
{
	if (_moveVelocity!=0)
	{
		int xflag = (_moveX - x>0)?1:-1;
		int yflag = (_moveY - y>0)?1:-1;
		int xd = xflag*JvG::elapsed*_moveVelocity;
		int yd = yflag*JvG::elapsed*_moveVelocity;
		x+=xd;
		y+=yd;
		
		if (JvU::abs(x - _moveX) <= xd)
		{
			x = _moveX;
		}
		if (JvU::abs(y - _moveY) <= yd)
		{
			y = _moveY;
		}
		if (x==_moveX && y==_moveY )
		{
			_moveVelocity = 0;
			if(_moveFun != NULL) _moveFun();
		}

		return;
	}

	if(_shakeTimer > 0)
	{
		_shakeTimer -= JvG::elapsed;
		if(_shakeTimer <= 0)
		{
			_shakeTimer = 0;
			x = _shakeXtmp;
			y = _shakeYtmp;
		}
		else
		{
			x =_shakeXtmp + (JvU::random()*_intensity*JvG::width*2-_intensity*JvG::width);
			y =_shakeYtmp + (JvU::random()*_intensity*JvG::height*2-_intensity*JvG::height);
		}
		return;
	}

	doFollow();
}

void JvCamera::renderFlash()
{
	if (_flashDelay==0)
	{
		return;
	}

	_flashAlpha -= (int)((double)(JvG::elapsed/_flashDelay)*(double)255);
	int r,b,g,a;
	GET_RGBA_8888(_flashColor,r,g,b,a);
	if(_flashAlpha <= 0)
	{
		_flashAlpha = 0;
		_flashDelay = 0;
		return;
	}
	
	//flash
	_ccflashlayer->setColor(ccc3(r,g,b));
	_ccflashlayer->setOpacity(_flashAlpha);
	_ccflashlayer->visit();
}

void JvCamera::draw(CCSprite* texture,float sx ,float sy ,float sw ,float sh ,float dx ,float dy ,
	float xscale ,float yscale ,float angle ,DRAWVH flag,int mask)
{
	int maskcolor = mask;
	
	CCSize winsize = CCDirector::sharedDirector()->getRunningScene()->getContentSize();
	float pixh =texture->getContentSize().height;
	texture->setPositionX(dx);
	texture->setPositionY(winsize.height - dy);
	float ty = pixh-sy - sh;
	texture->setTextureRect(CCRectMake(sx,ty,sw,sh));
	texture->setScaleX(xscale);
	texture->setScaleY(yscale);
	texture->setRotation(angle);
	if(maskcolor!=0)
	{
		int r,g,b,a;
		GET_RGBA_8888(maskcolor,r,g,b,a);
		texture->setColor(ccc3(r,g,b));
		texture->setOpacity(a);
	}
	switch(flag)
	{
	case NGE_FLIP_NONE:
		texture->setFlipX(false);
		texture->setFlipY(false);
		break;
	case NGE_FLIP_H:
		texture->setFlipX(true);
		break;
	case NGE_FLIP_V:
		texture->setFlipY(true);
		break;
	case NGE_FLIP_HV:
		texture->setFlipX(true);
		texture->setFlipY(true);
		break;
	default:
		break;
	}

	texture->visit();
}

void JvCamera::move(double X,double Y,double Velocity,MOVEOVERFUN MoveOverCallBack)
{
	_moveX = X;
	_moveY = Y;
	_moveVelocity = Velocity;
	_fllowObjP = NULL;
	_moveFun = MoveOverCallBack;

}

void JvCamera::follow(JvObject* ObjectP,double Lerp /*1.0f*/)
{
	_fllowObjP = ObjectP;
	followLerp = Lerp;
	_scrollTarget.x = (_fllowObjP->x+_fllowObjP->origin.x)-width/2;
	_scrollTarget.y = (_fllowObjP->y+_fllowObjP->origin.y)-height/2;
	x = _scrollTarget.x;
	y = _scrollTarget.y;
	
	doFollow();
}


void JvCamera::doFollow()
{
	if(_fllowObjP != NULL)
	{
		_scrollTarget.x = (_fllowObjP->x+_fllowObjP->origin.x)-width/2;
		_scrollTarget.y = (_fllowObjP->y+_fllowObjP->origin.y)-height/2;
	
		_scrollTarget.x += _fllowObjP->velocity.x*followLead.x;
		_scrollTarget.y += _fllowObjP->velocity.y*followLead.y;
	
		x += JvU::ceil((_scrollTarget.x-x)*followLerp*JvG::elapsed);
		y += JvU::ceil((_scrollTarget.y-y)*followLerp*JvG::elapsed);
		
	}
}