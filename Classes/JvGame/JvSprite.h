#ifndef _JVSPRITE_H
#define _JVSPRITE_H

#include "JvObject.h"
#include "JvAnim.h"

#include <cocos2d.h>
using namespace cocos2d;

enum FACEDIRECT{FACELEFT=0,FACERIGHT=1,FACEUP=2,FACEDOWN=3};

/**
*����
*ʵ�ֶ�������
*/
class JvSprite : public JvObject
{
public:
	JvSprite(double X =0,double Y=0,CCSprite* SimpleGraphic = NULL);
	virtual ~JvSprite();

	/**
	 *����ͼ��
	 *@param string FileName,ͼƬ�ļ���
	 *@param bool Animated,�Ƿ�ʵ�ֶ���
	 *@param bool Reverse,�Ƿ�ʵ�ַ�ת
	 *@param unsigned int Width,������
	 *@param unsigned int Height,����߶�
	 *@param int DisplayMode,�μ�NGE2��image_load
	 *@return JvSprite*,����ʵ����ʽ����
	 */
	JvSprite* loadGraphic(string FileName,bool Animated = false,bool Reverse =false,
			unsigned int Width = 0,unsigned int Height =0);

	/**
	 *����ͼ��
	 *@param image_p Graphic,ͼƬ����(��image_clone()����һ�����ݽ���)
	 *@param bool Animated,�Ƿ�ʵ�ֶ���
	 *@param bool Reverse,�Ƿ�ʵ�ַ�ת
	 *@param unsigned int Width,������
	 *@param unsigned int Height,����߶�
	 *@param int DisplayMode,�μ�NGE2��image_load
	 *@return JvSprite*,����ʵ����ʽ����
	 */
	JvSprite* loadGraphic(CCSprite* Graphic,bool Animated = false,bool Reverse =false,
		unsigned int Width = 0,unsigned int Height =0);
	

	virtual void create();
	virtual void update();
	virtual void render();
	CCSprite* getPixels();

	/**
	 *���һ������
	 *@param string Name,������
	 *@param vector<int>& Frames,����֡
	 *@param double FrameRate,֡��
	 *@param bool Looped,�Ƿ�ѭ������
	 *@return void
	 */
	void addAnimation(string Name, vector<int>& Frames, double FrameRate=0, bool Looped=true);
	
	/**
	 *����һ������
	 *@param string Name,������
	 *@param bool Force,ÿ�ε����Ƿ����¿�ʼ����
	 *@return void
	 */
	void play(string Name ,bool Force = false);

	unsigned int getCaf();

	virtual void preCollide(JvObject* ObjectP);
	//����
	double getScale();
	void setScale(double Scale);

	virtual void onEmit();

	void clearAnim();

	void createRect(int X,int Y,int Width,int Height,int Color);

	bool isPlayEnd();

	void setMask(int MaskColor);
	int getMask();
	
	JvPoint offset;
	unsigned int frameWidth;
	unsigned int frameHeight;
	FACEDIRECT facing;

	bool finished;
protected:
	void renderSprite();
	void updateAnimation();
	//���ԭʼͼ
	CCSprite* _pixels;

	vector<JvAnim*> _animations;
	JvAnim* _curAnim;
	unsigned int _curFrame;
	double _frameTimer;
	
	double _scale;

	int _mask;

	bool _isFillRect;
	int _rectColor;
private:
};

#endif 