//
//  EnemyShip.cpp
//  SpaceGame
//
//  Created by GCREST on 2014/01/24.
//
//

#include "EnemyShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;


const float kDefaultFrameRate = (1.0 / 24.0);

EnemyShip::EnemyShip()
{
    
}

EnemyShip::~EnemyShip()
{
    
}

bool EnemyShip::initWithFileName(const char* pszFileName)
{
    if (!CCNode::init())
        return false;
    
    _nextShipLaser = 0;
    _autoShooting = true;
    _attacked = false;
    _shotInterval = 0.4;
    _lastShotTime = 0;
    _ship = CCSprite::create(pszFileName);
    _ship->setPosition(ccp(0, 0));
    this->addChild(_ship);
    
    return true;
    
}

bool EnemyShip::initWithFrameName(const char* pFrameName, int numFrame)
{
    if (!CCNode::init())
        return false;
    
    _nextShipLaser = 0;
    _autoShooting = true;
    _attacked = false;
    _shotInterval = 0.4;
    _lastShotTime = 0;
    _imageName = new CCString(pFrameName);
    
    // 機体の作成
    CCString*  frameName = CCString::createWithFormat("%s.plist", pFrameName);
    
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile(frameName->getCString());
    
    CCString*   name = CCString::createWithFormat("%s_01.png", pFrameName);
    _ship = CCSprite::createWithSpriteFrameName(name->getCString());
    
    _ship->setPosition(ccp(0, 0));
    this->addChild(_ship);
    
    return true;
    
}

void EnemyShip::initBullets(cocos2d::CCNode* bulletLayer)
{
#define KNUMLASERS 5
    for(int i = 0; i < KNUMLASERS; ++i)
    {
        BulletSprite *shipLaser = BulletSprite::createWithSpriteFrameName("shot_red.png");
        shipLaser->setFlipX(true);
        shipLaser->setVisible(false);
        bulletLayer->addChild(shipLaser);
        bulletList.push_back(shipLaser);
    }
    
}


EnemyShip* EnemyShip::createShip(const char* pszFileName)
{
    EnemyShip *pobSprite = new EnemyShip();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

EnemyShip* EnemyShip::createShipFrame(const char* pszFileName, int numFrame)
{
    EnemyShip *pobSprite = new EnemyShip();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void EnemyShip::start()
{
    if (!_ship)
        return;
    
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

void EnemyShip::end()
{
    if (_ship)
        _ship->stopAllActions();
}

void EnemyShip::update(float dt)
{
    if (_autoShooting && !_attacked)
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

void EnemyShip::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BulletSprite *shipLaser = bulletList[_nextShipLaser++];
    if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(-winSize.width, 400)), CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
}

void EnemyShip::setInvisible(CCNode * node)
{
    node->stopAllActions();
    node->setVisible(false);
}

float EnemyShip::getMoveSpeed()
{
    return _moveSpeed;
}

void EnemyShip::setMoveSpeed(float speed)
{
    _moveSpeed = speed;
}

void EnemyShip::setDamage()
{
    _attacked = true;
    
    // 適機の移動アクションを停止
    _ship->stopAllActions();
    
#if 0
    CCString*   bombName = new CCString("explosion");
    //    CCString*   bombName = new CCString("explosion1_ss");
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    int numFrames = 84;
    CCArray*    frames = CCArray::createWithCapacity(numFrames);
    for (int i = 0; i <= numFrames; i++)
    {
        CCString*   name = CCString::createWithFormat("%s_%04d.png", bombName->getCString(), i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate*2);
    CCAnimate* animate = CCAnimate::create(animation);
    _ship->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
#else
    CCString*   bombName = new CCString("temp_explosion");
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    int numFrames = 16;
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
    _ship->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
#endif
}


