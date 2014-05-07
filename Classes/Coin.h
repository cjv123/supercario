#ifndef _COIN_H
#define _COIN_H

#include "JvSprite.h"
class JvEmitter;

class Coin : public JvSprite
{
public:
	Coin(double X,double Y);
	virtual void update();
	
protected:
	bool _isPlayAnim;
	int _animFrame;

	JvEmitter* _em;

	double _ox;
	double _oy;
	int _alpha;
private:
};

#endif