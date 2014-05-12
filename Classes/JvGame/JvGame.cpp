#include "JvGame.h"
#include "JvState.h"
#include "JvSave.h"

JvGame::JvGame()
{
	JvG::save = new JvSave;
	JvG::joystick = new JvJoystick;

	_run=false;
	_delState = NULL;
}


JvGame::JvGame(unsigned int GameSizeX,unsigned int GameSizeY)
{
// 	JvG::save = new JvSave;
// 	JvG::joystick = new JvJoystick;

	JvG::setGameData(this,GameSizeX,GameSizeY);
	_run = false;
	_delState = NULL;
	_switchState = NULL;
}

JvGame::~JvGame()
{
	if (JvG::stateP != NULL)
	{
		delete JvG::stateP;
	}

	delete JvG::save;
	delete JvG::joystick;
}

void JvGame::setInitState(JvState* initState)
{
	_switchState = initState;
}

void JvGame::setScreenInfo(unsigned int Width,unsigned int Height)
{
	JvG::setGameData(this,Width,Height);
}

void JvGame::run()
{

  
    //SetScreenType(2);
	create();
	_run = true;
}

void JvGame::stopRun()
{
	_run = false;
}

void JvGame::switchState(JvState* StateP)
{
	
	_switchState = StateP;

}

void JvGame::create()
{
	JvU::setWorldBounds(0,0,JvG::width,JvG::height);	
}

bool JvGame::update()
{
	if (!_run) return false;

	JvG::elapsed = CCDirector::sharedDirector()->getDeltaTime();
	//Frame timing
	if(JvG::elapsed > JvG::maxElapsed)
	{
		JvG::elapsed = JvG::maxElapsed;
	}
	
//	JvG::elapsed = 1.0f/JvG::frameRate;

	JvG::elapsed *= JvG::timeScale;

	//printf("%f\n",JvG::elapsed);

	if (_switchState!=NULL)
	{
		if(JvG::stateP!=NULL)
			delete JvG::stateP;

		JvG::stateP = _switchState;
		JvG::stateP->loading();
		JvG::stateP->render();
		JvG::stateP->defaultGroup->kill();
		JvG::stateP->defaultGroup->exists = true;
		JvG::stateP->defaultGroup->dead = false;
		JvG::stateP->create();
		_switchState = NULL;
		JvG::joystick->reSet();
	}

	if (JvG::stateP != NULL)
	{
		JvG::stateP->update();
		JvG::stateP->render();
	}
	JvG::joystick->update();

	return true;
}

void JvGame::btnDown(KEYCODE keycode)
{
	JvG::joystick->pressDown(keycode);
}


void JvGame::btnUp(KEYCODE keycode)
{
	JvG::joystick->pressUp(keycode);
}

void JvGame::mouseClick(int type,int x,int y)
{
	switch (type) {
	case 0:
		JvG::joystick->mouseUp(x,y);
		break;
	case 1:
		JvG::joystick->mouseDown(x,y);
		break;
	default:
		break;
	}
}

void JvGame::mouseMove(int x,int y)
{
	JvG::joystick->mouseMove(x,y);
}

void JvGame::exit()
{
	
}
