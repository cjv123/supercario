#ifndef _JVSTATE_H
#define _JVSTATE_H

#include "JvCamera.h"
#include "JvGroup.h"

class JvText;

/**
*����
*����object��add��state�ֻ��ͬʱ����һ������
*/
class JvState
{
public:
	JvGroup defaultGroup;
	JvCamera camera;

	JvState();
	virtual ~JvState();
	virtual void update();
	virtual void create();
	virtual void loading();
	virtual void pause();
	virtual void render();
	void collide();
	

	/**
	 *���һ��object������
	 *@param JvObject* ObjectP,����Ӷ����ָ��
	 *@return void
	 */
	void add(JvObject* ObjectP);

	/**
	 *���ñ�����ɫ
	 *@param int Color,������ɫ,��MAKE_RGBA_8888()����
	 *@return void
	 */
	void setBgColor(int Color);
protected:
	int _bgColor;

	CCLayerColor* m_ccbglayer;
private:
};

#endif