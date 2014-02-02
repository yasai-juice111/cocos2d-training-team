//
//  KWEnemy.cpp
//  cocos2dx-space-game
//
//  Created by c7:kawabata_satoshi on 2014/02/01.
//
//
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "KWEnemy.h"


//using namespace CocosDenshion;

USING_NS_CC;
const float kDefaultFrameRate = (1.0 / 24.0);

KWEnemy::KWEnemy()
{
	bulletDirection = int(CCRANDOM_0_1() * 4);
	bulletInterval = CCRANDOM_0_1() * 0.1;
	
}

KWEnemy::~KWEnemy()
{
	
}


KWEnemy* KWEnemy::createShip(const char* pszFileName)
{
	KWEnemy *pobSprite = new KWEnemy();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

KWEnemy* KWEnemy::createShipFrame(const char* pszFileName, int numFrame)
{
    KWEnemy *pobSprite = new KWEnemy();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * 更新処理
 */
void KWEnemy::update(float dt)
{
    if (_autoShooting && !_attacked)
    {
        double   curTime = TimeUtils::getTime() * bulletInterval;
        double   diffTime = curTime - _lastShotTime;
        if (diffTime > _shotInterval)
        {
            shotBullet();
            
            _lastShotTime = curTime;
        }
        
    }
}

/*
 弾をうつ
 */
void KWEnemy::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	createLaser(bulletList[_nextShipLaser++], winSize, bulletDirection);
	createLaser(bulletList[_nextShipLaser++], winSize, -bulletDirection);
}

/**
 * レーザーを生成する
 */
void KWEnemy::createLaser(BulletSprite *shipLaser, CCSize winSize, int direction)
{
	// レーザーのリストと照合
	if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
	// レーザーを設定する
    shipLaser->setPosition(ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
	// 方向を設定
	float directionPos = 200 * direction;
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(2.0, ccp(-winSize.width, directionPos)), CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
}

/**
 * ダメージ処理
 */
void KWEnemy::setDamage()
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
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate);
    CCAnimate* animate = CCAnimate::create(animation);
    _ship->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
#else
    CCString*   bombName = new CCString("explosion");
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    int numFrames = 16;
    CCArray*    frames = CCArray::createWithCapacity(numFrames);
    for (int i = 1; i <= numFrames; i++)
    {
        CCString*   name = CCString::createWithFormat("%s_000%02d.png", bombName->getCString(), i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate);
    CCAnimate* animate = CCAnimate::create(animation);
    _ship->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
#endif
}











