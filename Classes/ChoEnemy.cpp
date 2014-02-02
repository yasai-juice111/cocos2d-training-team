//
//  ChoEnemy.cpp
//  cocos2dx-space-game
//
//  Created by c7:cho_takumi on 2014/02/01.
//
//
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ChoEnemy.h"


//using namespace CocosDenshion;

USING_NS_CC;

ChoEnemy::ChoEnemy()
{
	bulletDirection = int(CCRANDOM_0_1() * 4);
	bulletInterval = CCRANDOM_0_1() * 0.1;
	
}

ChoEnemy::~ChoEnemy()
{
	
}


ChoEnemy* ChoEnemy::createShip(const char* pszFileName)
{
	ChoEnemy *pobSprite = new ChoEnemy();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

ChoEnemy* ChoEnemy::createShipFrame(const char* pszFileName, int numFrame)
{
    ChoEnemy *pobSprite = new ChoEnemy();
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
void ChoEnemy::update(float dt)
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
void ChoEnemy::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	createLaser(bulletList[_nextShipLaser++], winSize, bulletDirection);
	createLaser(bulletList[_nextShipLaser++], winSize, -bulletDirection);
}

/**
 * レーザーを生成する
 */
void ChoEnemy::createLaser(BulletSprite *shipLaser, CCSize winSize, int direction)
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