#ifndef _APPSCREEN_H
#define _APPSCREEN_H

#include <cocos2d.h>
using namespace cocos2d;

class AppScreen : public CCLayer
{
public:
	static CCScene* scene();

	CREATE_FUNC(AppScreen);

	virtual bool init();

	virtual void visit( void );

	virtual void update( float delta );

	virtual void ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent );

	virtual void ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent );

	virtual void ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent );

	virtual void ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent );

protected:
private:
	CCRenderTexture* m_screen;
};

#endif

