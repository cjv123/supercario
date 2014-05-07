#ifndef _JVRECT_H
#define _JVRECT_H

#include "JvPoint.h"

/**
*����
*JvObject�Ļ���
*/
class JvRect : public JvPoint
{
public:
	JvRect(double X=0,double Y=0,double Width=0,double Height=0);
	virtual ~JvRect();
	double GetLeft();
	double GetRight();
	double GetTop();
	double GetBottom();
	bool checkPointIn(double pointX,double pointY);

	double width;
	double height;
protected:
private:
};

#endif
