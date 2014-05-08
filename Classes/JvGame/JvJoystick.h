#ifndef _JOYSTICK_H
#define _JOYSTICK_H
#include <map>
using namespace std;

#include "JvGroup.h"

enum KEYCODE{UPCODE,DOWNCODE,LEFTCODE,RIGHTCODE,ACODE,BCODE,XCODE,YCODE};
enum KEYSTATUS{NOPRESS,JUSTPRESS,PRESS};
enum MOUSESTATUS{MOUSENONE,MOUSEDOWN,MOUSEUP,MOUSEMOVE};

typedef map<KEYCODE,KEYSTATUS> KeyMapType;

struct MousePoint
{
	int x;
	int y;
	MOUSESTATUS status;
	int id;

	MousePoint()
	{
		x = y = -1;
		status = MOUSENONE;
		id = -1;
	}
};

/**
*�����豸
*�ṩһЩ������ж�����
*/
class JvJoystick : public JvGroup
{
public:
	JvJoystick();
	virtual ~JvJoystick();
	void pressDown(KEYCODE keycode);
	void pressUp(KEYCODE keycode);
	void mouseDown(int x, int y,int id = 0);
	void mouseUp(int x,int y,int id = 0);
	void mouseMove(int x,int y,int id =0);
	MousePoint* getMousePoint();
	void reSet();
	
	/**
	 *�ж��Ƿ񰴼�������
	 *@param KEYCODE keycode,�ĸ�����
	 *@return bool
	 */
	bool isPress(KEYCODE keycode);

	/**
	 *�ж��Ƿ񰴼���������(����ֻ����Ӧһ��)
	 *@param KEYCODE keycode,�ĸ�����
	 *@return bool
	 */
	bool isJustPreess(KEYCODE keycode);

	/**
	 *�ж���걻����
	 *@return bool
	 */
	bool isMouseDown();

	/**
	 *�ж������ĳ����������
	 *@param JvRect Rect,����
	 *@return bool
	 */
	bool isMouseDown(JvRect Rect);

	/**
	 *�ж�����Ƿ�clickup
	 *@return bool
	 */
	bool isMouseUp();

	/**
	 *�ж������ĳ��������clickup
	 *@param JvRect Rect,����
	 *@return bool
	 */
	bool isMouseUp(JvRect Rect);


	/**
	 *�ж��Ƿ���ĳ�����ڵ��(����)��Ļ��
	 *@param JvRect Rect,����
	 *@return bool
	 */
	bool isMouseIn(JvRect Rect);

	void updatePoints(int index,int id,int x, int y);

	void clearPoints();
	
	virtual void update();
protected:
//	pointf _mousePoint;
//	MOUSESTATUS _mouseStatus;
	MousePoint _mousePoint[5];
	int _pointIndex;

	KeyMapType _keyMap;
private:
};

#endif