#include "AppScreen.h"
#include "JvGame/JvH.h"
#include "LogoState.h"

static JvGame jvgame;

#ifdef WIN32
static void key_handler( UINT message,WPARAM wParam, LPARAM lParam )
{
	KEYCODE keychar;
	switch (wParam)
	{
	case VK_UP:
		keychar = UPCODE;
		break;
	case VK_DOWN:
		keychar = DOWNCODE;
		break;
	case VK_LEFT:
		keychar = LEFTCODE;
		break;
	case VK_RIGHT:
		keychar = RIGHTCODE;
		break;
	case VK_CONTROL:
		keychar = ACODE;
		break;
	case VK_BACK:
		keychar = BCODE;
		break;
	}

	switch (message)
	{
	case WM_KEYDOWN:
		jvgame.btnDown(keychar);
		break;
	case WM_KEYUP:
		jvgame.btnUp(keychar);
		break;
	}
}
#endif

bool AppScreen::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

#ifdef WIN32
	CCEGLView::sharedOpenGLView()->setAccelerometerKeyHook(key_handler);
#endif

	setTouchEnabled(true);

	jvgame.setScreenInfo(getContentSize().width,getContentSize().height);
	jvgame.setInitState(new LogoState);
	jvgame.run();

	return true;
}

CCScene* AppScreen::scene()
{
	AppScreen* appscreenlayer = AppScreen::create();
	CCScene* scene = CCScene::create();
	scene->addChild(appscreenlayer);
	return scene;
}

void AppScreen::visit( void )
{
	CCLayer::visit();
	jvgame.update();
}

void AppScreen::update( float delta )
{
	CCLayer::update(delta);
}

void AppScreen::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	for (CCSetIterator it = pTouches->begin();it!=pTouches->end();it++)
	{
		CCTouch* touch = (CCTouch*)(*it);
		int x = touch->getLocation().x;
		int y = touch->getLocation().y;
		int id = touch->getID();
		JvG::joystick->mouseDown(x,getContentSize().height-y,id);
	}
}

void AppScreen::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	for (CCSetIterator it = pTouches->begin();it!=pTouches->end();it++)
	{
		CCTouch* touch = (CCTouch*)(*it);
		int x = touch->getLocation().x;
		int y = touch->getLocation().y;
		int id = touch->getID();
		JvG::joystick->mouseMove(x,getContentSize().height-y,id);
	}
}

void AppScreen::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	for (CCSetIterator it = pTouches->begin();it!=pTouches->end();it++)
	{
		CCTouch* touch = (CCTouch*)(*it);
		int x = touch->getLocation().x;
		int y = touch->getLocation().y;
		int id = touch->getID();
		JvG::joystick->mouseUp(x,getContentSize().height-y,id);
	}
}

void AppScreen::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent )
{
	for (CCSetIterator it = pTouches->begin();it!=pTouches->end();it++)
	{
		CCTouch* touch = (CCTouch*)(*it);
		int x = touch->getLocation().x;
		int y = touch->getLocation().y;
		int id = touch->getID();
		JvG::joystick->mouseUp(x,getContentSize().height-y,id);
	}
}
