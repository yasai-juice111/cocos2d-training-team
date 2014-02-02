//
//  ShibuyaPlayerShip.cpp
//  cocos2dx-space-game
//
//  Created by c2:shibuya_shun on 14/02/02.
//
//

#include "ShibuyaPlayerShip.h"
#include "PlayerShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

const float kDefaultFrameRate = (1.0 / 24.0);

ShibuyaPlayerShip::ShibuyaPlayerShip()
{
    
}

ShibuyaPlayerShip::~ShibuyaPlayerShip()
{
    
}

bool ShibuyaPlayerShip::initWithFileName(const char* pszFileName)
{
    if (!CCNode::init())
        return false;
    
    _nextShipLaser = 0;
    _autoShooting = true;
    _shotInterval = 0.05;
    _lastShotTime = 0;
    _hasShipAnimation = false;
    _ship = CCSprite::create(pszFileName);
    this->addChild(_ship);
    
    return true;
    
}

bool ShibuyaPlayerShip::initWithFrameName(const char* pFrameName, int numFrame)
{
    if (!CCNode::init())
        return false;
    
    _nextShipLaser = 0;
    _autoShooting = true;
    _shotInterval = 0.05;
    _lastShotTime = 0;
    _hasShipAnimation = true;
    _imageName = new CCString(pFrameName);
    
    // Player機の作成
    CCString*  frameName = CCString::createWithFormat("%s.plist", pFrameName);
    
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile(frameName->getCString());
    
    CCString*   name = CCString::createWithFormat("%s_01.png", pFrameName);
    _ship = CCSprite::createWithSpriteFrameName(name->getCString());
    
    //    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //    _ship->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    _ship->setPosition(ccp(0, 0));
    this->addChild(_ship);
    
    return true;
    
}

void ShibuyaPlayerShip::initBullets(cocos2d::CCNode* bulletLayer)
{
#define KNUMLASERS 15
    for(int i = 0; i < KNUMLASERS; ++i)
    {
        BulletSprite *shipLaser = BulletSprite::createWithSpriteFrameName("shot_blue.png");
        shipLaser->setVisible(false);
        bulletLayer->addChild(shipLaser);
        bulletList.push_back(shipLaser);
    }
    
}


ShibuyaPlayerShip* ShibuyaPlayerShip::createShip(const char* pszFileName)
{
    ShibuyaPlayerShip *pobSprite = new ShibuyaPlayerShip();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

ShibuyaPlayerShip* ShibuyaPlayerShip::createShipFrame(const char* pszFileName, int numFrame)
{
    ShibuyaPlayerShip *pobSprite = new ShibuyaPlayerShip();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void ShibuyaPlayerShip::start()
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

void ShibuyaPlayerShip::end()
{
    if (_ship)
        _ship->stopAllActions();
}

void ShibuyaPlayerShip::update(float dt)
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

void ShibuyaPlayerShip::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BulletSprite *shipLaser = bulletList[_nextShipLaser++];
    if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(ShibuyaPlayerShip::setInvisible)), NULL));
}

void ShibuyaPlayerShip::setDamage()
{
    CCString*   bombName = new CCString("temp_explosion");
    CCString*   name = CCString::createWithFormat("%s_01.png", bombName->getCString());
    CCSprite* bombSprite = CCSprite::createWithSpriteFrameName(name->getCString());
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    int numFrames = 4;
    CCArray*    frames = CCArray::createWithCapacity(numFrames);
    for (int i = 1; i <= numFrames; i++)
    {
        CCString*   name = CCString::createWithFormat("%s_%02d.png", bombName->getCString(), i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate);
    CCAnimate* animate = CCAnimate::create(animation);
    bombSprite->setPosition(ccp(0, 0));
    this->addChild(bombSprite);
    bombSprite->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(ShibuyaPlayerShip::setInvisible)), NULL));
}

void ShibuyaPlayerShip::setInvisible(CCNode * node)
{
    node->setVisible(false);
}

void ShibuyaPlayerShip::touchBeganProcess(cocos2d::CCPoint& pos)
{
    if (!_autoShooting)
    {
        shotBullet();
    }
}

CCPoint ShibuyaPlayerShip::getBodySize()
{
    if (_ship)
    {
        return _ship->getContentSize();
    }
    
    return CCPointZero;
}

void ShibuyaPlayerShip::setLife(int life)
{
	_lives = life;
}

int ShibuyaPlayerShip::getLife()
{
	return _lives;
}