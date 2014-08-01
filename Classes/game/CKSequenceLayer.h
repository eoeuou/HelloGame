#ifndef __CKSEQUENCELAYER_H__
#define __CKSEQUENCELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
typedef enum __ScrollType
{
	CKSCROLL_DIR_VERTICAL,
	CKSCROLL_DIR_HORIZONTAL,
	CKSCROLL_DIR_BOTH
}CKScrollType;

#define LandSpeed_DIS 3.0f

class CKLandLayer:public cocos2d::CCLayerColor
{
private:
	CC_SYNTHESIZE_READONLY(DrawNode*, m_drawNode, DrawNode);
	CCPoint m_prePoint;
	EventListenerTouchOneByOne* m_eventListener;
protected:
	CKLandLayer():
		m_drawNode(nullptr),
		m_eventListener(nullptr)
	{
	};

public:
	~CKLandLayer(){};

	static CKLandLayer * create(const Color4B& color, GLfloat width, GLfloat height)
	{
		CKLandLayer * layer = new CKLandLayer();
		if( layer && layer->initWithColor(color,width,height))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);

	void drawDotUpdate(float dt,CCPoint prePoint,CCPoint curPoint);

	void addTouchEvent()
	{
		m_eventListener = EventListenerTouchOneByOne::create();
		m_eventListener->setSwallowTouches(true);

		m_eventListener->onTouchBegan = [](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());

			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
				target->setOpacity(180);
				return true;
			}

			target->getParent()->reorderChild(target,100);
			return false;
		};

		m_eventListener->onTouchMoved = [](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
		};

		m_eventListener->onTouchEnded = [=](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			log("sprite onTouchesEnded.. ");
			target->setOpacity(255);
			target->getParent()->reorderChild(target,0);
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventListener, this);
	}

	void removeTouchEvent()
	{
		if (m_eventListener)
		{
			this->getEventDispatcher()->removeEventListener(m_eventListener);
		}
		
	}
};

class CKSequenceLayer:public cocos2d::Layer
{
private:
	CC_SYNTHESIZE(CKScrollType,m_scrollType,ScrollType);

	CC_SYNTHESIZE(Point,m_scrollDirection,ScrollDirection);
	CC_SYNTHESIZE_READONLY(float,m_scrollSpeed,ScrollSpeed);

	CC_SYNTHESIZE(CKLandLayer*,m_landLayerA,LandLayerA);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerB,LandLayerB);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerC,LandLayerC);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerD,LandLayerD);

	CC_SYNTHESIZE(Vector<CKLandLayer*>,m_landLayers,LandLayers);

	CC_SYNTHESIZE(bool,m_bIsPauseScrollLand,BIsPauseScrollLand);
	
	CC_SYNTHESIZE(CCPoint,m_startPoint,StartPoint);
	CC_SYNTHESIZE(CCPoint,m_prePoint,PrePoint);
	CC_SYNTHESIZE(CKLandLayer*,m_curLandLayer,CurLandLayer);
public:
	CREATE_FUNC(CKSequenceLayer);

	void startScrollLand();

	void stopScrollLand();

	void pauseScrollLand();

	void resumeScrollLand();

	void changeScrollDirection(CCPoint direction);

	void changeScrollSpeed(float speed);
protected:
	CKSequenceLayer(void);

	~CKSequenceLayer(void);

	virtual bool init();  

	void scrollLand(float dt);

	void horizontalScroll();

	void verticalScroll();

	void bothScroll();

	bool resetLandLayerHorizontal(Layer* landLayer);

	bool resetLandLayerVertical(Layer* landLayer);
	
};

#endif // __CKSEQUENCELAYER_H__