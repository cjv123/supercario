#ifndef _FAN_H
#define _FAN_H

#include "JvSprite.h"

class Fan : public JvSprite
{
public:
	Fan(double X,double Y);
	virtual void update();
protected:
private:
};

#endif