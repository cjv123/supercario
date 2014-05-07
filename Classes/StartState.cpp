#include "JvH.h"
#include "StartState.h"
#include "GameState.h"

StartState::StartState()
{
	_time = 0;
	_ui = NULL;
	_txt = NULL;
}

void StartState::create()
{
	setBgColor(MAKE_RGBA_8888(87,196,247,255));

	JvSprite* bg = new JvSprite(0,0);
	bg->loadGraphic("bg.png");
	add(bg);

	_ui = new JvSprite(-87,150);
	_ui->loadGraphic("start.png");
	_ui->x = JvG::width/2 - _ui->width/2;
	add(_ui);
	
	char lvstr[10];
	sprintf(lvstr,"Level%d",GameState::nowLv);
	_txt = new JvText(JvG::width/2 - 6*20/2,335,200,30,FONT_NAME,lvstr);
	_txt->setColor(MAKE_RGBA_8888(255,0,0,255));
	_txt->setSize(20);
	add(_txt);
	
	_ui->velocity.y = -80;
	_txt->velocity.y = -80;

	JvG::stopMusic();
}

void StartState::update()
{
	JvRect rect(_ui->x,_ui->y,
			_ui->width,_ui->height);
	if (_ui->y>0 && JvG::joystick.isMouseDown(rect))
	{
		_ui->y=-70;
		_txt->y=235-120;
	}

	if (_ui->y<=-70)
	{
		_ui->velocity.y=0;
		_txt->velocity.y=0;
		_time++;
		if (_time>=120)
		{
			JvG::switchState(new GameState);
		}
	}

	JvState::update();
}
