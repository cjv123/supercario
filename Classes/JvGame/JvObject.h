#ifndef _JVOBJECT_H
#define _JVOBJECT_H

#include "JvRect.h"
#include "JvU.h"
#include "JvG.h"
#include <vector>
using namespace std;

/**
*����
*����Ļ���
*/
class JvObject : public JvRect
{
public:
	/*����Ŀ��أ���Ļ�������*/
	bool exists;
	/*���flase��update()�����ᱻ�������*/
	bool active;
	/*���flase,render()�����ᱻ�������*/
	bool visible;

	/*�����ٶ�*/
	JvPoint velocity;
	/*���ٶ�*/
	JvPoint acceleration;
	/*����*/
	JvPoint drag;
	/*����ٶ�*/
	JvPoint maxVelocity;
	/*��ת�Ƕ�*/
	double angle;
	/*��ת�ٶ�*/
	double angularVelocity;
	/*��ת���ٶ�*/
	double angularAcceleration;
	/*��ת����*/
	double angularDrag;
	/*���Ƕ�*/
	double maxAngular;
	/*ԭ��*/
	JvPoint origin;
	/*����*/
	double thrust;
	/*�������*/
	double maxThrust;
	/*��������*/
	JvPoint scrollFactor;
	/*����ֵ*/
	double health;
	/*�Ƿ�����*/
	bool dead;
	/*���false�����潫����ִ��updateMotion()*/
	bool moves;
	/*x����ײ�������*/
	JvRect colHullX;
	/*y����ײ�������*/
	JvRect colHullY;
	/*��ײ��*/
	JvPoint colVector;
	/*ƫ����*/
	vector<JvPoint> colOffsets;

	/*�Ƿ��ڵ���*/
	bool onFloor;
	/*�Ƿ�������ײ*/
	bool collideLeft;
	/*�Ƿ�������ײ*/
	bool collideRight;
	/*�Ƿ�������ײ��*/
	bool collideTop;
	/*�Ƿ�������ײ��*/
	bool collideBottom;
	/*�Ƿ���*/
	bool _group;
	string name;

	JvObject(double X=0,double Y=0,double Width=0,double Height=0);
	virtual ~JvObject();
	bool GetSolid();

	/**
	*������Ϊtrue�󣬾Ͳ��ᱻ��ײ���
	*@param bool Solid
	*@return void
	*/
	void SetSolid(bool Solid);
	
	bool GetFixed();

	/**
	*������Ϊtrue��object�����̶�,���ᱻ�ı�λ��
	*@param bool Fixed
	*@return void
	*/
	void SetFixed(bool Fixed);

   /**
	*������ײ�������,������updateMotion()
	*@return bool
	*/
	virtual void refreshHulls();

	virtual void update();
	virtual void render();

	/**
	*��ײ���(���������ཻ��ʱ��,�����ٶ�Ԥ�ж�)
	*@param JvObject* ObjectP,��������һ������
	*@return bool
	*/
	bool overlaps(JvObject* ObjectP);

	/**
	*��ײ��⣬collideΪtrueʱ
	*@param JvObject* ObjectP = NULL
	*@return bool
	*/
	virtual bool collide(JvObject* ObjectP = NULL);

	/**
	*�������ʱ����
	*@param JvObject* Contact,��ײ��
	*@param double Velocity,��ײ�ߵ��ٶ�
	*@return void
	*/
	virtual void hitLeft(JvObject* Contact,double Velocity);
	/*�����ұ�ʱ����*/
	virtual void hitRight(JvObject* Contact,double Velocity);
	/*������ʱ����*/
	virtual void hitTop(JvObject* Contact,double Velocity);
	/*������ʱ����*/
	virtual void hitBottom(JvObject* Contact,double Velocity);
	/*����*/
	virtual void hurt(int Damage);
	/*ɱ��,��ɾ�����object*/
	virtual void kill();

	/*�ж��Ƿ�����Ļ*/
	bool onScreen();
	/*����*/
	void reset(double X,double Y);
	
	virtual void preCollide(JvObject* ObjectP);

	void setCollide(bool canCollide);
	
protected:
	/*�Ƿ���ײ*/
	bool _solid;
	/*�Ƿ�̶�*/
	bool _fixed;
	/*λ����ʱ����*/
	JvPoint _point;
	/*ָ����������*/
	JvRect _rect;
	
	
	/*�����ƶ�*/
	void updateMotion();

private:
};

#endif