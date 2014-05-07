#ifndef _JVEMITTER_H
#define _JVEMITTER_H

#include "JvGroup.h"
#include <cocos2d.h>
using namespace cocos2d;

/**
*���ӷ�����
*ʹ��ͼƬ��ν���ӵ�λ������ʵ��������Ч
*/
class JvEmitter : public JvGroup
{
public:
	JvPoint minParticleSpeed;
	JvPoint maxParticleSpeed;
	JvPoint particleDrag;
	double minRotation;
	double maxRotation;
	double gravity;
	bool on;
	double delay;
	unsigned int quantity;
	int scale;

	JvEmitter(double X=0,double Y=0);
	
	/**
	 *�������ӵ�λ��sprite
	 *@param const char* Filename, ͼƬ�ļ���
	 *@param unsigned int Quantity=50,sprite����
	 *@param int BakeRotations=16,sprite��ʼ�Ƕ� 
	 *@param bool Multiple=true,���Ϊtrue,������ͼƬ�߶������ȡ��ͼ
	 *@param double Collide=0,0��ʾ���Ӳ���ײ(Ч�ʸ�),Collideȡֵ��0-1��Χ������ײ����
	 *@return JvEmitter* ����thisʵ����ʽ����
	 */
	JvEmitter* createSprites(const char* Filename,unsigned int Quantity=50,
				int BakedRotations=16,bool Multiple=true, double Collide=0);

	/**
	 *�������ӵ�λ��sprite
	 *@param image_p Graphics, ͼƬ����
	 *@param unsigned int Quantity=50,sprite����
	 *@param int BakeRotations=16,sprite��ʼ�Ƕ� 
	 *@param bool Multiple=true,���Ϊtrue,������ͼƬ�߶������ȡ��ͼ
	 *@param double Collide=0,0��ʾ���Ӳ���ײ(Ч�ʸ�),Collideȡֵ��0-1��Χ������ײ����
	 *@return JvEmitter* ����thisʵ����ʽ����
	 */
	JvEmitter* createSprites(CCSprite* Graphics,unsigned int Quantity=50,
				int BakedRotations=16,bool Multiple=true, double Collide=0);
	
	/**
	 *�������ӳ�ʼ���ַ�Χ
	 *@param unsigned int Width, ��Χ��
	 *@param unsigned int Height,��Χ��
	 *@return void
	 */
	void setSize(unsigned int Width,unsigned int Height);
	
	/**
	 *����x���������ٶ�
	 *@param double Min=0,����x������С�ٶ�
	 *@param double Max=0,����x��������ٶ�
	 *@return void
	 */
	void setXSpeed(double Min=0,double Max=0);
	
	/**
	 *����y���������ٶ�
	 *@param double Min=0,����y������С�ٶ�
	 *@param double Max=0,����y��������ٶ�
	 *@return void
	 */
	void setYSpeed(double Min=0,double Max=0);

	/**
	 *�������ӽ��ٶ�
	 *@param double Min=0,������С���ٶ�
	 *@param double Max=0,���������ٶ�
	 *@return void
	 */
	void setRotation(double Min=0,double Max=0);

	virtual void update();

	/**
	 *�������ӽ��ٶ�
	 *@param bool Explode=true,�Ƿ�һ���Ա���
	 *@param double Delay=0,�����ӳٱ���(��)
	 *@param unsigned int Quantity=0,��ʼ������
	 *@return void
	 */
	void start(bool Explode=true,double Delay=0,unsigned int Quantity=0);

	/*updateEmitter()����,�ⲿ��ʹ��*/
	void emitParticle();
	
	/**
	 *ֹͣ����
	 *@param double Delay=3,�����kill����
	 *@return void
	 */
	void stop(double Delay=3);

	/**
	 *����ĳ��object���÷�������λ��
	 *@param JvObject* ObjectP,Ҫ����λ�õ�object
	 *@return void
	 */
	void at(JvObject* ObjectP);
	
	/**
	 *kill������
	 *@return void
	 */
	virtual void kill();
protected:
	void updateEmitter();

	bool _explode;
	double _timer;
	unsigned int _particle;
	unsigned int _counter;
	
};

#endif