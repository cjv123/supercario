#ifndef _LOGOSTATE_H
#define _LOGOSTATE_H

#include "JvState.h"

class JvText;
class JvSprite;

class LogoState : public JvState
{
public:
	virtual void create();
	virtual void update();
protected:
	int _timer;
	JvSprite* _zflogo;
	JvSprite* _nge2logo;
	JvText* _jvgamelogo;
private:
};
#endif