//
//  ShibuyaBossShip.cpp
//  cocos2dx-space-game
//
//  Created by c2:shibuya_shun on 14/02/01.
//
//

#include "ShibuyaBossShip.h"
#include "PlayerShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

const float kDefaultFrameRate = (1.0 / 24.0);

ShibuyaBossShip::ShibuyaBossShip()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	positionDx = - winSize.width / 100;
	positionDy = - winSize.height / 100;
}

ShibuyaBossShip::~ShibuyaBossShip()
{
    
}

bool ShibuyaBossShip::initWithFileName(const char* pszFileName)
{
    if (!CCNode::init())
        return false;
    
    _nextShipLaser = 0;
    _autoShooting = true;
    _shotInterval = 0.5;
    _lastShotTime = 0;
    _hasShipAnimation = false;
    _ship = CCSprite::create(pszFileName);
    this->addChild(_ship);
    
    return true;
    
}

void ShibuyaBossShip::initBullets(cocos2d::CCNode* bulletLayer)
{
#define KNUMLASERS 15
    for(int i = 0; i < KNUMLASERS; ++i)
    {
        BulletSprite *shipLaser = BulletSprite::createWithSpriteFrameName("shot_red.png");
		shipLaser->setFlipX(true);
        shipLaser->setVisible(false);
        bulletLayer->addChild(shipLaser);
        bulletList.push_back(shipLaser);
    }
    
}


ShibuyaBossShip* ShibuyaBossShip::createShip(const char* pszFileName)
{
    ShibuyaBossShip *pobSprite = new ShibuyaBossShip();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

ShibuyaBossShip* ShibuyaBossShip::createShipFrame(const char* pszFileName, int numFrame)
{
    ShibuyaBossShip *pobSprite = new ShibuyaBossShip();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void ShibuyaBossShip::start()
{
    if (!_ship)
        return;
    
    if (_hasShipAnimation)
    {
        CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        int numFrames = 4;
        CCArray*    frames = CCArray::createWithCapacity(numFrames);
        for (int i = 1; i <= numFrames; i++)
        {
            CCString*   name = CCString::createWithFormat("%s_%02d.png", _imageName->getCString(), i);
            CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
            if (spriteFrame)
                frames->addObject(spriteFrame);
        }
        CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate*2);
        CCAnimate* animate = CCAnimate::create(animation);
        _ship->runAction(CCRepeatForever::create(animate));
    }
    
}

void ShibuyaBossShip::end()
{
    if (_ship)
        _ship->stopAllActions();
}

void ShibuyaBossShip::update(float dt)
{
    if (_autoShooting)
    {
        double   curTime = TimeUtils::getTime();
        double   diffTime = curTime - _lastShotTime;
        if (diffTime > _shotInterval)
        {
            shotBullet();
            
            _lastShotTime = curTime;
        }
		
    }
}

void ShibuyaBossShip::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BulletSprite *shipLaser = bulletList[_nextShipLaser++];
    if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(-1 * winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(ShibuyaBossShip::setInvisible)), NULL));
}

void ShibuyaBossShip::setDamage()
{
    CCString* bombName = new CCString("explosion_boss");
    CCString* name = CCString::createWithFormat("temp_explosion_01.png");
    CCSprite* bombSprite = CCSprite::createWithSpriteFrameName(name->getCString());
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    int numFrames = 4;
    CCArray* frames = CCArray::createWithCapacity(numFrames);
    for (int i = 1; i <= numFrames; i++)
    {
        CCString* name = CCString::createWithFormat("%s_000%02d.png", bombName->getCString(), i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate);
    CCAnimate* animate = CCAnimate::create(animation);
    bombSprite->setPosition(ccp(0, 0));
    this->addChild(bombSprite);
    bombSprite->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(ShibuyaBossShip::setInvisible)), NULL));
}

void ShibuyaBossShip::setInvisible(CCNode * node)
{
    node->setVisible(false);
}

CCPoint ShibuyaBossShip::getBodySize()
{
    if (_ship)
    {
        return _ship->getContentSize();
    }
    
    return CCPointZero;
}

float ShibuyaBossShip::getPositionDx()
{
	return positionDx;
}

float ShibuyaBossShip::getPositionDy()
{
	return positionDy;
}

void ShibuyaBossShip::turnPositionDx()
{
	positionDx *= -1;
}

void ShibuyaBossShip::turnPositionDy()
{
	positionDy *= -1;
}

void ShibuyaBossShip::setLife(int life)
{
	_lives = life;
}

int ShibuyaBossShip::getLife()
{
	return _lives;
}
