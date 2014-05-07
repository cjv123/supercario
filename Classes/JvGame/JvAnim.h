#ifndef _JVANIM_H
#define _JVANIM_H

#include <string>
#include <vector>
using namespace std;

/**
*����
*����JvSprite�ﶯ����ʵ��,һ���ⲿ����Ҫֱ��ʹ��
*/
class JvAnim
{
public:
	string name;
	double delay;
	vector<int> frames;
	bool looped;
	
	/**
	 *���캯��
	 *@param string& Name,������
	 *@param vector<int>& Frames,���ö���ÿһ֡ͼƬ��index(��ͼ����)
	 *@param double FrameRate=0,��������(֡/��)
	 *@param bool Looped=true,�Ƿ�ѭ������
	 *@return ��
	 */
	JvAnim(string& Name, vector<int>& Frames, double FrameRate=0, bool Looped=true);
protected:
private:
};

#endif