#ifndef _JVLIST_H
#define _JVLIST_H

#include "JvObject.h"

/**
*�Ĳ����ڵ�
*��JvQuadTree�Ĳ�������ʹ�ã��ⲿ����ʹ��
*/
class JvList
{
public:
	JvObject* objectP;
	JvList* nextP;

	JvList();
	virtual ~JvList();
protected:
private:
};

#endif
