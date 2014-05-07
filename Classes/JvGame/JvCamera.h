#ifndef _JVCAMERA_H
#define _JVCAMERA_H

#include "JvObject.h"
#include "JvRect.h"
#include <cocos2d.h>
using namespace cocos2d;

enum DRAWVH{
	NGE_FLIP_NONE = 0,
	NGE_FLIP_H,
	NGE_FLIP_V,
	NGE_FLIP_HV
};
class JvSprite;

typedef void (*MOVEOVERFUN) ();

/**
*�����
*ʵ�־�ͷ���棬�Լ�һЩ��ͷ��Ч,һ�㲻���Լ�ʵ����ʹ��
*ͨ��JvG::camera->xxx����JvG::stateP->camera.xxx������غ���
*/
class JvCamera : public JvRect
{
public:
	JvCamera();

	/**
	 *���캯��
	 *@param unsigned int screenW,��Ļ���
	 *@param unsigned int screenH,��Ļ�߶�
	 *@return void
	 */
	JvCamera(unsigned int screenW,unsigned int screenH);

	~JvCamera();

	/**
	 *��ʼ��
	 *@param unsigned int screenW,��Ļ���
	 *@param unsigned int screenH,��Ļ�߶�
	 *@return void
	 */
	void init(unsigned int screenW,unsigned int screenH);

	/**
	 *���þ�ͷ�������
	 *@param JvObject* Object,Ҫ����Ķ���
	 *@return void
	 */
	void follow(JvObject* Object,double Lerp = 1.0f);

	/**
	 *�ж��Ƿ��ھ�ͷ��
	 *@param JvObject* Object,���жϵĶ���
	 *@return bool
	 */
	bool checkInCamera(JvObject* ObjectP);

	/**
	 *��ȡ�������ǰ��������
	 *@return JvRect
	 */
	JvRect getCameraRect();

	/**
	 *�ѳ�������ת������Ļ����
	 *@param JvPoint& point,��ת�������
	 *@return pointf
	 */
	JvPoint toScreenPoint(JvPoint& point);

	/**
	 *�ѳ�������ת������Ļ����
	 *@param JvPoint& point,��ת�������
	 *@return pointf
	 */
	void render(JvSprite* ObjectP);

	/**
	 *�𶯾�ͷ
	 *@param double Intensity=0.05,�𶯷���(��Ļ���*Intensity)
	 *@param double Duration=0.5,��ʱ��(��)
	 *@return void
	 */
	void shake(double Intensity=0.05,double Duration=0.5);

	/**
	 *ֹͣ��
	 *@return void
	 */
	void stopShake();

	/**
	 *����
	 *@param int Color=0,��ɫ(Ҫ��MAKE_RGBA_8888()��ת����ɫ)
	 *@param double Duration=1,����ʱ��(��)
	 *@return void
	 */
	void flash(int Color=0, double Duration=1);

	/**
	 *�ƶ���ͷ��
	 *@param X,�ƶ�Ŀ��x
	 *@param Y,�ƶ�Ŀ��y
	 *@param Velocity,�ƶ��ٶ�
	 *@param MoveCallBack,�ƶ���ɺ���õĺ���
	 *@return void
	 */
	void move(double X,double Y,double Velocity, MOVEOVERFUN MoveCallBack=NULL);
	
	/**
	 *��ȡ���������
	 *@return JvObject
	 */
	JvObject* getFllowObj();
	
	/**
	 *���ø���ľ��η�Χ(���������Χ��ֹͣ����)
	 *@param int X=0,����x����
	 *@param int Y=0,����y����
	 *@param int Width=0,���ο��
	 *@param int Height=0,���θ߶�
	 *@return void
	 */
	void followBounds(int X=0,int Y=0,int Width=0,int Height=0,bool UpdateWorldBounds = true);
	
	/**
	 *���ø��滺������
	 *@param double LeadX = 0,x���򻺶�����
	 *@param double LeadY = 0,y���򻺶�����
	 *@return void
	 */
	void followAdjust(double LeadX = 0,double LeadY = 0);
	
	virtual void update();

	/**
	 *��Ⱦ������Ч���ⲿ���õ���
	 *@return void
	 */
	void renderFlash();
	
	/**
	 *ͼƬ��ʾ����Ļ����ʵ�ַ�ת,һ���ⲿ���õ���
	 *@param image_p img,
	 *@param double sx,ͼƬx
	 *@param double sy,ͼƬy
	 *@param double sw,ͼƬ��
	 *@param double sh,ͼƬ��
	 *@param double dx,��Ļx
	 *@param double dy,��Ļy
	 *@param double dw,��Ļ��
	 *@param double dh,��Ļ��
	 *@param DRAWVH flag,��ת����
	 *@return void
	 */
	void draw(CCSprite* texture,float sx ,float sy ,float sw ,float sh ,float dx ,
		float dy ,float xscale ,float yscale ,float angle ,DRAWVH flag,int mask=0);

	double followLerp;
	JvPoint followLead;
protected:
	void doFollow();

	JvObject* _fllowObjP;
	JvPoint _scrollTarget;
	JvRect _fllowBound;

	double _intensity;
	double _shakeTimer;
	double _shakeXtmp;
	double _shakeYtmp;

	double _flashDelay;
	int _flashColor;
	int _flashAlpha;

	double _moveX;
	double _moveY;
	double _moveVelocity;
	MOVEOVERFUN _moveFun;

	CCLayerColor* _ccflashlayer;
private:
	
};

#endif