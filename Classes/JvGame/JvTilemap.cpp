#include "JvTilemap.h"
#include "JvState.h"
#include "JvState.h"
#include <string>
using namespace std;

JvTilemap::JvTilemap()
{
	collideIndex = 1;
	startingIndex = 0;
	drawIndex = 1;
	widthInTiles = 0;
	heightInTiles = 0;
	totalTiles = 0;
	_tileWidth = 0;
	_tileHeight = 0;
	scale = 1;
	_pixels = NULL;
	SetFixed(true);
	colOffsets.reserve(50);
	
	_batchNode = NULL;
}

JvTilemap::~JvTilemap()
{
	if (_pixels != NULL)
	{
		_pixels->release();
		_pixels = NULL;
	}

	if (_batchNode != NULL)
	{
		_batchNode->release();
		_batchNode = NULL;
	}

	for (int i=0;i<_drawBuf.size();i++)
	{
		if(_drawBuf[i])
			_drawBuf[i]->release();
	}
}

JvTilemap* JvTilemap::loadMap(const char* dataFilename, const char* imgFilename,
							  unsigned int TileWidth/* =0 */, unsigned int TileHeight/* =0 */)
{
	unsigned long size=0;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(dataFilename,"r",&size);
	string strTmp = (char*)data;
	delete[] data;

	loadMap(strTmp, imgFilename,TileWidth,TileHeight);

	return this;
}

JvTilemap* JvTilemap::loadMap(string& DataStr, const char* imgFilename, 
							  unsigned int TileWidth/* =0 */, unsigned int TileHeight/* =0 */)
{
	char iotmp;
	string strTmp;
	int i = 0;
	int strlen = DataStr.size();

	while (i<strlen)
	{
		iotmp = DataStr.at(i);
		if (iotmp == '\n')
		{
			heightInTiles++;

			if (strTmp=="" || strTmp=="\n" || strTmp==",")
			{
				strTmp="0";
			}
			_data.push_back(strTmp);
			strTmp="";
		}
		else if (iotmp == ',')
		{
			if (heightInTiles ==0)
			{
				widthInTiles++;
			}
			_data.push_back(strTmp);
			strTmp="";
		}
		else
		{
			strTmp+=iotmp;
		}
		i++;
	}
	if (widthInTiles>0)
	{
		widthInTiles++;
	}

	//printf("widthintiles:%d,heightintiles:%d\n",widthInTiles,heightInTiles);
	
	CCImage* image = new CCImage;
	image->initWithImageFile(imgFilename);
	_pixels = new CCTexture2D;
	_pixels->initWithImage(image);
	_pixels->setAliasTexParameters();
	image->release();
	_batchNode = CCSpriteBatchNode::createWithTexture(_pixels);
	_batchNode->retain();
	_batchNode->setPosition(ccp(0,0));

	if (_pixels == NULL)
	{
		printf("load image file fail!\n");
		return NULL;
	}
	
	_tileWidth = TileWidth*scale;
	if (TileWidth==0)
	{
		_tileWidth = _pixels->getContentSize().width*scale;
		
	}
	_tileHeight = TileHeight*scale;
	if (TileHeight)
	{
		_tileHeight = _pixels->getContentSize().height*scale;
	}
	width = widthInTiles*_tileWidth;
	height = heightInTiles*_tileHeight;
	
	refreshHulls();

	makeBuffer();
	return this;
}

void JvTilemap::makeBuffer()
{
	float pixw = _pixels->getContentSize().width;
	float pixh = _pixels->getContentSize().height;

	int rx=0,ry=0,val=0;
	for (int i=0;i<_data.size();i++)
	{
		//	printf("y:%d,x:%d\n",i,j);
		val = atoi(_data[i].c_str());
		if (val==-1 || val==0)
		{
			_drawBuf.push_back(0);
			continue;
		}

		rx = (int)(val*_tileWidth/scale) % (int)pixw;
		ry =pixh - (val*_tileWidth/scale) / pixw - (float)(_tileHeight/(int)scale);

		CCSprite* drawsp = CCSprite::createWithTexture(_pixels);
		drawsp->setTextureRect(CCRectMake((float)rx, (float)ry,
			(float)(_tileWidth/(int)scale),(float)(_tileHeight/(int)scale)));
		drawsp->setAnchorPoint(ccp(0,1));
		drawsp->retain();
		_drawBuf.push_back(drawsp);
	}

}

void JvTilemap::render()
{
	//ֱ����Ⱦtile����Ļ����
	renderTile();
}

void JvTilemap::renderTile()
{
	JvRect cameraRect = JvG::stateP->camera->getCameraRect();
	int screenXInTile = (int)(cameraRect.x/_tileWidth);
	int screenYInTile = (int)(cameraRect.y/_tileHeight);
	int screenWInTile = JvU::ceil(JvG::width/_tileWidth);
	int screenHInTile = JvU::ceil(JvG::height/_tileHeight);
	CCSize winsize = CCDirector::sharedDirector()->getRunningScene()->getContentSize();

	double offsetX = JvU::ceil(cameraRect.x - screenXInTile*(double)_tileWidth);
	double offsetY = JvU::ceil(cameraRect.y - screenYInTile*(double)_tileHeight);

	_batchNode->removeAllChildrenWithCleanup(true);

	//printf("%f,%f\n",offsetX,offsetY);
	int rx=0,ry=0,val=0,col=0,row=0;
	for (int i = screenYInTile;i<=screenYInTile+screenHInTile;i++)
	{
		for (int j=screenXInTile;j<=screenXInTile+screenWInTile+1;j++)
		{
		//	printf("y:%d,x:%d\n",i,j);
			val = getTile(j,i);
			if (val==-1 || val==0)
			{
				row++;
				continue;
			}
			
// 			rx = (int)(val*(_tileWidth/scale)) % (int)_pixels->getContentSize().width;
// 			ry = (val*(_tileWidth/scale)) / _pixels->getContentSize().height;
// 
// 			rx +=x;
// 			ry +=y;

// 			DrawImage(_pixels, (float)rx, (float)ry,
// 				(float)(_tileWidth/(int)scale),(float)(_tileHeight/(int)scale),
// 				(row*_tileWidth)-(float)offsetX,(col*_tileHeight)-(float)offsetY,
// 				(float)_tileWidth,(float)_tileHeight);

			CCSprite* drawsp = _drawBuf[i*widthInTiles+j];
			drawsp->setPositionX((row*_tileWidth)-(float)offsetX);
			drawsp->setPositionY(winsize.height - (col*_tileHeight-(float)offsetY));
			drawsp->setScale(scale);
			_batchNode->addChild(drawsp);

			row++;
		}
		row=0;
		col++;
	}

	_batchNode->visit();
}

void JvTilemap::refreshHulls()
{
	colHullX.x = 0;
	colHullX.y = 0;
	colHullX.width = _tileWidth;
	colHullX.height = _tileHeight;
	colHullY.x = 0;
	colHullY.y = 0;
	colHullY.width = _tileWidth;
	colHullY.height = _tileHeight;
}

void JvTilemap::preCollide(JvObject* ObjectP)
{
	int r;
	int c;
	int rs;
	int col = 0;
	int ix = JvU::floor((ObjectP->x - x)/_tileWidth);
	int iy = JvU::floor((ObjectP->y - y)/_tileHeight);
	int iw = ix + JvU::ceil(ObjectP->width/_tileWidth)+1;
	int ih = iy + JvU::ceil(ObjectP->height/_tileHeight)+1;
	if(ix < 0)
		ix = 0;
	if(iy < 0)
		iy = 0;
	if(iw > widthInTiles)
		iw = widthInTiles;
	if(ih > heightInTiles)
		ih = heightInTiles;
	rs = iy*widthInTiles;
	
	int size = _data.size();
	colOffsets.resize(0);
	for(r = iy; r < ih; r++)
	{
		for(c = ix; c < iw; c++)
		{
			
			if (rs+c>=size)
			{
				continue;
			}
				
			if( atoi(_data[rs+c].c_str())>= collideIndex)
			{
				JvPoint point = JvPoint(x+(double)(c*_tileWidth), y+(double)(r*_tileHeight));
				colOffsets.push_back(point);
			}
		}
		rs += widthInTiles;
	}
	
}

int JvTilemap::getTile(int X,int Y)
{
	int index = Y*widthInTiles+X;
	if (index <0 || X>=widthInTiles || Y>=heightInTiles)
	{
		return -1;
	}
	int size = _data.size();
	if (index>=size)
	{
		return 0;
	}
	
	int val = atoi(_data[index].c_str());
	return val;
}

void JvTilemap::setTile(int X,int Y,char Value)
{
	int index = Y*widthInTiles+X;
	if (index <0 || X>=widthInTiles || Y>=heightInTiles)
	{
		return;
	}

	_data[index] = Value;
}

int JvTilemap::getTileWidth()
{
	return _tileWidth;
}

int JvTilemap::getTileHeight()
{
	return _tileHeight;
}