//
//  KawabataEnemy.cpp
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "KawabataEnemy.h"


using namespace CocosDenshion;

USING_NS_CC;

KawabataEnemy::KawabataEnemy()
{
	
}

KawabataEnemy::~KawabataEnemy()
{
	
}


KawabataEnemy* KawabataEnemy::createShip(const char* pszFileName)
{
    KawabataEnemy *pobSprite = new KawabataEnemy();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

KawabataEnemy* KawabataEnemy::createShipFrame(const char* pszFileName, int numFrame)
{
    KawabataEnemy *pobSprite = new KawabataEnemy();
    if (pobSprite && pobSprite->initWithFrameName(pszFileName, numFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/*
 弾をうつ
 */
void KawabataEnemy::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BulletSprite *shipLaser = bulletList[_nextShipLaser++];
    if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(-winSize.width, 1000)), CCCallFuncN::create(this, callfuncN_selector(EnemyShip::setInvisible)), NULL));
}












