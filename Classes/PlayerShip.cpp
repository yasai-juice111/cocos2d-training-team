//
//  PlayerShip.cpp
//  SpaceGame
//
//  Created by GCREST on 2014/01/24.
//
//

#include "PlayerShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

const float kDefaultFrameRate = (1.0 / 24.0);

PlayerShip::PlayerShip()
{
    
}

PlayerShip::~PlayerShip()
{
    
}

bool PlayerShip::initWithFileName(const char* pszFileName)
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

bool PlayerShip::initWithFrameName(const char* pFrameName, int numFrame)
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

void PlayerShip::initBullets(cocos2d::CCNode* bulletLayer)
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


PlayerShip* PlayerShip::createShip(const char* pszFileName)
{
    PlayerShip *pobSprite = new PlayerShip();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

PlayerShip* PlayerShip::createShipFrame(const char* pszFileName, int numFrame)
{
    PlayerShip *pobSprite = new PlayerShip();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void PlayerShip::start()
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

void PlayerShip::end()
{
    if (_ship)
        _ship->stopAllActions();
}

void PlayerShip::update(float dt)
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

void PlayerShip::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BulletSprite *shipLaser = bulletList[_nextShipLaser++];
    if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(PlayerShip::setInvisible)), NULL));
}

void PlayerShip::setDamage()
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
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate*2);
    CCAnimate* animate = CCAnimate::create(animation);
    bombSprite->setPosition(ccp(0, 0));
    this->addChild(bombSprite);
    bombSprite->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(PlayerShip::setInvisible)), NULL));
}

void PlayerShip::setInvisible(CCNode * node)
{
    node->setVisible(false);
}

void PlayerShip::touchBeganProcess(cocos2d::CCPoint& pos)
{
    if (!_autoShooting)
    {
        shotBullet();
    }
}


