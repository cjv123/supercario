#include "JvH.h"
#include "GamePad.h"
#include "GameState.h"
#include "Hero.h"

void leftButtonDown(int par)
{
	JvG::jvGameP->btnDown(LEFTCODE);
}

void leftButtonUp(int par)
{
	JvG::jvGameP->btnUp(LEFTCODE);
}

void rightButtonDown(int par)
{
	JvG::jvGameP->btnDown(RIGHTCODE);
//	printf("rightdown\n");
}

void rightButtonUp(int par)
{
	JvG::jvGameP->btnUp(RIGHTCODE);
//	printf("rightup\n");
}

void upButtonDown(int par)
{
	JvG::jvGameP->btnDown(UPCODE);
}

void upButtonUp(int par)
{
	JvG::jvGameP->btnUp(UPCODE);
}

void downButtonDown(int par)
{
	JvG::jvGameP->btnDown(DOWNCODE);
}

void downButtonUp(int par)
{
	JvG::jvGameP->btnUp(DOWNCODE);
}

void ballButtonDown(int par)
{
	JvG::jvGameP->btnDown(BCODE);
}

void ballButtonUp(int par)
{
	JvG::jvGameP->btnUp(BCODE);
}

void jumpButtonDown(int par)
{
	JvG::jvGameP->btnDown(ACODE);
}

void jumpButtonUp(int par)
{
	JvG::jvGameP->btnUp(ACODE);
}

GamePad::GamePad()
{
	_leftButton = new JvButton(10,JvG::height-70,60,60);
	_rightButton = new JvButton(100,JvG::height-70,60,60);
	_ballButton = new JvButton(JvG::width-160,JvG::height-70,60,60);
	_jumpButton = new JvButton(JvG::width-70,JvG::height-70,60,60);
	
	_fLeftButton = new JvButton(10,JvG::height/2-30,60,60);
	_fRightButton = new JvButton(JvG::width-70,JvG::height/2-30,60,60);
	_fUpButton = new JvButton(JvG::width/2-30,10,60,60);
	_fDownButton = new JvButton(JvG::width/2-30,JvG::height-70,60,60);
	_fLeftButton->visible = false;
	_fRightButton->visible = false;
	_fUpButton->visible = false;
	_fDownButton->visible = false;
	_ballButton->visible = false;

	add(_leftButton);
	add(_rightButton);
	add(_ballButton);
	add(_jumpButton);
	add(_fLeftButton);
	add(_fRightButton);
	add(_fUpButton);
	add(_fDownButton);

	_leftButton->setCallback(leftButtonUp,leftButtonDown);
	_rightButton->setCallback(rightButtonUp,rightButtonDown);
	_ballButton->setCallback(ballButtonUp,ballButtonDown);
	_jumpButton->setCallback(jumpButtonUp,jumpButtonDown);

	_fLeftButton->setCallback(leftButtonUp,leftButtonDown);
	_fRightButton->setCallback(rightButtonUp,rightButtonDown);
	_fUpButton->setCallback(upButtonUp,upButtonDown);
	_fDownButton->setCallback(downButtonUp,downButtonDown);


	JvSprite* lbuttonimg = new JvSprite;
	lbuttonimg->loadGraphic("lbutton.png");
	JvSprite* lbuttomimg_sel = new JvSprite;
	lbuttomimg_sel->loadGraphic("lbutton_sel.png");
	_leftButton->loadGraphic(lbuttonimg,lbuttomimg_sel);

	JvSprite* rbuttonimg = new JvSprite;
	rbuttonimg->loadGraphic("rbutton.png");
	JvSprite* rbuttonimg_sel = new JvSprite;
	rbuttonimg_sel->loadGraphic("rbutton_sel.png");
	_rightButton->loadGraphic(rbuttonimg,rbuttonimg_sel);

	JvSprite* bbuttonimg = new JvSprite;
	bbuttonimg->loadGraphic("bbutton.png");
	JvSprite* bbuttonimg_sel = new JvSprite;
	bbuttonimg_sel->loadGraphic("bbutton_sel.png");
	_ballButton->loadGraphic(bbuttonimg,bbuttonimg_sel);

	JvSprite* jbuttonimg = new JvSprite;
	jbuttonimg->loadGraphic("jbutton.png");
	JvSprite* jbuttonimg_sel = new JvSprite;
	jbuttonimg_sel->loadGraphic("jbutton_sel.png");
	_jumpButton->loadGraphic(jbuttonimg,jbuttonimg_sel);


	JvSprite* flbuttonimg = new JvSprite;
	flbuttonimg->loadGraphic("lbutton.png");
	JvSprite* flbuttonimg_sel = new JvSprite;
	flbuttonimg_sel->loadGraphic("lbutton_sel.png");
	_fLeftButton->loadGraphic(flbuttonimg,flbuttonimg_sel);
	
	JvSprite* frbuttonimg = new JvSprite;
	frbuttonimg->loadGraphic("rbutton.png");
	JvSprite* frbuttonimg_sel = new JvSprite;
	frbuttonimg_sel ->loadGraphic("rbutton_sel.png");
	_fRightButton->loadGraphic(frbuttonimg,frbuttonimg_sel);

	JvSprite* ubuttonimg = new JvSprite;
	ubuttonimg->loadGraphic("ubutton.png");
	JvSprite* ubuttonimg_sel = new JvSprite;
	ubuttonimg_sel->loadGraphic("ubutton_sel.png");
	_fUpButton->loadGraphic(ubuttonimg,ubuttonimg_sel);

	JvSprite* dbuttonimg = new JvSprite;
	dbuttonimg->loadGraphic("dbutton.png");
	JvSprite* dbuttonimg_sel = new JvSprite;
	dbuttonimg_sel->loadGraphic("dbutton_sel.png");
	_fDownButton->loadGraphic(dbuttonimg,dbuttonimg_sel);
}

void GamePad::flyMode()
{
	_fLeftButton->visible = true;
	_fRightButton->visible = true;
	_fUpButton->visible = true;
	_fDownButton->visible = true;
	
	_leftButton->visible = false;
	_rightButton->visible = false;
	_ballButton->visible = false;
	_jumpButton->visible = false;
}

void GamePad::walkMode()
{
	_fLeftButton->visible = false;
	_fRightButton->visible = false;
	_fUpButton->visible = false;
	_fDownButton->visible = false;
	
	_leftButton->visible = true;
	_rightButton->visible = true;
	if (GameState::heroP!=NULL && GameState::heroP->isCanBall())
		_ballButton->visible = true;
	_jumpButton->visible = true;
}

void GamePad::hasBall()
{
	_ballButton->visible = true;
}
