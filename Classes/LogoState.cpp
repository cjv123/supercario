#include "LogoState.h"
#include "JvGame/JvH.h"
#include "HomeState.h"
#include "GameState.h"

void LogoState::create()
{
	setBgColor(MAKE_RGBA_8888(255,255,255,255));
	_timer = 0;

	_zflogo = new JvSprite;
	_zflogo->loadGraphic("zf.png");
	_zflogo->x = JvG::width/2 - _zflogo->width/2;
	_zflogo->y = JvG::height/2 - _zflogo->height/2;
	add(_zflogo);
	
	_nge2logo = new JvSprite(0,0);
	_nge2logo->loadGraphic("nge2logo.png");
	_nge2logo->x = JvG::width/2-_nge2logo->width - 15;
	_nge2logo->y = JvG::height/2 - _nge2logo->height/2 - 10;
	add(_nge2logo);
	_nge2logo->visible = false;

	_jvgamelogo = new JvText(JvG::width/2+20,_zflogo->y+50,200,30,FONT_NAME,
		"JvGame");
	_jvgamelogo->setSize(25);
	add(_jvgamelogo);
	_jvgamelogo->visible = false;

	if (GameState::gameData == NULL)
	{
		GameState::gameData = new GameData;
	}

	JvG::save->bind("supercartiosave");
	JvG::save->load(GameState::gameData);
}

void LogoState::update()
{
	if (_timer <=0)
	{
		camera->flash(MAKE_RGBA_8888(255,255,255,255),1);
	}
	else if (_timer ==3*60)
	{
		camera->flash(MAKE_RGBA_8888(255,255,255,255),1);
		setBgColor(MAKE_RGBA_8888(0,0,0,255));
		_zflogo->visible = false;
		_nge2logo->visible = true;
		_jvgamelogo->visible = true;
	}
	else if (_timer ==6*60)
	{
		JvG::switchState(new HomeState);
	}
	
	if (_timer <=3*60 && JvG::joystick->isMouseUp())
	{
		camera->flash(MAKE_RGBA_8888(255,255,255,255),1);
		setBgColor(MAKE_RGBA_8888(0,0,0,255));
		_zflogo->visible = false;
		_nge2logo->visible = true;
		_jvgamelogo->visible = true;
		_timer =3*60;
	}
	else if (_timer <=6*60 && JvG::joystick->isMouseUp())
	{
		_timer =6*60;
		JvG::switchState(new HomeState);
	}

	_timer++;
}

