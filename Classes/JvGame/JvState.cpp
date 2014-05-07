#include "JvState.h"
#include "JvText.h"
#include "GameState.h"

JvState::JvState()
{
	_bgColor =0;
	m_ccbglayer = CCLayerColor::create();
	m_ccbglayer->retain();
}

JvState::~JvState()
{
	m_ccbglayer->release();
}

void JvState::create()
{
	camera.init(JvG::width,JvG::height);
	JvG::camera = &camera;

	m_ccbglayer->setContentSize(CCSizeMake(JvG::width,JvG::height));
}

void JvState::update()
{
	if (JvG::pause)
	{
		pause();
		return;
	}

	defaultGroup.update();
	camera.update();
}

void JvState::render()
{
	if (_bgColor!=0)
	{
		m_ccbglayer->visit();
	}
	defaultGroup.render();
	camera.renderFlash();
}

void JvState::collide()
{
	JvU::collide(&defaultGroup,&defaultGroup);
}

void JvState::add(JvObject* ObjectP)
{
	defaultGroup.add(ObjectP);
}

void JvState::setBgColor(int Color)
{
	_bgColor = Color;
	int r,g,b,a;
	GET_RGBA_8888(Color,r,g,b,a);
	m_ccbglayer->setColor(ccc3(r,g,b));
	m_ccbglayer->setOpacity(a);
}

void JvState::pause()
{

}

void JvState::loading()
{
	JvText* loadtxt = new JvText(25,JvG::height-50,300,50,FONT_NAME,"Loading...");
	loadtxt->setSize(20);
	add(loadtxt);
}
