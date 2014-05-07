#ifndef _JVGROUP_H
#define _JVGROUP_H

#include "JvObject.h"
#include <vector>
using namespace std;

/**
*��
*���԰�object��ӵ�һ��group���ٰ�group��ӵ�state
*/
class JvGroup : public JvObject
{
public:
	/*��Ա����*/
	vector<JvObject*> members;

	JvGroup();
	virtual ~JvGroup();

	/**
	 *���object
	 *@param JvObject* ObjectP
	 *@return void
	 */
	void add(JvObject* ObjectP);
	
	/**
	 *�Ƴ�object
	 *@param JvObject* ObjectP
	 *@return void
	 */
	void remove(JvObject* ObjectP);


	virtual void update();
	virtual void render();
	virtual void kill();
protected:
	virtual void updateMembers();
	void renderMembers();
	void killMembers();
private:
};

#endif