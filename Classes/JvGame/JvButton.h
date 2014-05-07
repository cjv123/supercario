#ifndef _JVBUTTON_H
#define _JVBUTTON_H

#include "JvGroup.h"

class JvSprite;
class JvText;

typedef void (*BUTTON_CALLBACK)(int);
typedef void (*BUTTON_DOWN_CALLBACK)(int);

/**
*��ť
*�����ڳ�������ӵİ�ť������ͨ����괥���¼�
*/
class JvButton : public JvGroup
{
public:
	JvButton(double X,double Y,double Width,double Height);

	/**
	 *����ͼ��
	 *@param JvSprite* ImageP,��̬�µ�sprite
	 *@param JvSprite* ImageHighlightP=NULL,����sprite
	 *@return JvButton* ����this��������ʽ����
	 */
	JvButton* loadGraphic(JvSprite* ImageP,JvSprite* ImageHighlightP=NULL);

	/**
	 *���ûص�����ָ��
	 *@param BUTTON_CALLBACK Fun,���clickup�󴥷��ĺ���
	 *@param BUTTON_DOWN_CALLBACK DFun = NULL,���clickdown�ʹ����ĺ���
	 *@return void
	 */
	void setCallback(BUTTON_CALLBACK Fun,BUTTON_DOWN_CALLBACK DFun = NULL,
		int ParCallBack=0,int ParDown = 0);

	void setTitle(const char* Title,const char* FontFilename,int X=0,int Y=0,
		int Size = 8);

	void setPosition(int X,int Y);

	virtual void  update();
protected:
	JvSprite* _offP;
	JvSprite* _onP;
	bool _isPress;
	BUTTON_CALLBACK _callBackFun;
	BUTTON_DOWN_CALLBACK _downCallBackFun;
	int _parCallBack;
	int _parDown;
	
	JvText* _text;
	int _textX;
	int _textY;
private:
};

#endif