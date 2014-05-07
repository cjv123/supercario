#ifndef _JVGAME_H
#define _JVGAME_H

#include "JvJoystick.h"

class JvState;

/**
*���
*���Զ���һ�������͵�ȫ�ֱ���
*/
class JvGame
{
public:
	/**
	 *���캯��
	 *@param unsigned int GameSizeX,��Ļ���
	 *@param unsigned int GameSizeY,��Ļ�߶�
	 *@return void
	 */
	JvGame(unsigned int GameSizeX,unsigned int GameSizeY);

	JvGame();

	virtual ~JvGame();

	void setScreenInfo(unsigned int Width,unsigned int Height);
	
	/**
	 *���ó�ʼ����
	 *@param JvState* initState,��ʼstate��ָ��
	 *@return void
	 */
	void setInitState(JvState* initState);

	/**
	 *��ʼ����
	 *@return void
	 */
	void run();

	/**
	 *ֹͣ����
	 *@return void
	 */
	void stopRun();

	/**
	 *�˳�����
	 *@return void
	 */
	void exit();

	/**
	 *�л�����
	 *@param JvState* StateP,���л���state
	 *@return void
	 */
	void switchState(JvState* StateP);

	/**
	 *����ѭ�������update()
	 *@return bool,ֹͣ����ʱ����false������true
	 */
	bool update();
	
	void create();
	void btnDown(KEYCODE keycode);
	void btnUp(KEYCODE keycode);
	void mouseClick(int type,int x,int y);
	void mouseMove(int x,int y);

protected:
	bool _run;
	
	double _total;
	double _elapsed;

	JvState* _delState;
	JvState* _switchState;
};

#endif