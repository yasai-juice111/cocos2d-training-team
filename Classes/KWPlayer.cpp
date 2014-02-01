//
//  KWPlayer.cpp
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//
#include "KWPlayer.h"
#include "TimeUtils.h"
#include "cocos2d.h"

USING_NS_CC;

KWPlayer::KWPlayer()
{
    // 弾のスピード
	_bulletSpeed = 0.5;
	_bulletVariation = FOCUS;
	
	
	bulletInterval = CCRANDOM_0_1() * 0.1;
}

KWPlayer::~KWPlayer()
{
    
}


KWPlayer* KWPlayer::createShip(const char* pszFileName)
{
    KWPlayer *pobSprite = new KWPlayer();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

KWPlayer* KWPlayer::createShipFrame(const char* pszFileName, int numFrame)
{
    KWPlayer *pobSprite = new KWPlayer();
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
void KWPlayer::update(float dt)
{
    if (_autoShooting)
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

/**
 * 弾を打つ
 * バリエーションを出せるように
 */
void KWPlayer::shotBullet()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	switch (_bulletVariation)
	{
		case ONE:
			createLaser(bulletList[_nextShipLaser++], winSize, ONE, _bulletSpeed);
			break;
		case FOCUS:
			createLaser(bulletList[_nextShipLaser++], winSize, ONE, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, FOCUS, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, -FOCUS, _bulletSpeed);
			break;
		case THREE:
			createLaser(bulletList[_nextShipLaser++], winSize, ONE, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, FOCUS, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, -FOCUS, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, THREE, _bulletSpeed);
			createLaser(bulletList[_nextShipLaser++], winSize, -THREE, _bulletSpeed);
			break;
			
		default:
			createLaser(bulletList[_nextShipLaser++], winSize, ONE, _bulletSpeed);
			break;
	}
}


/**
 * レーザーを生成する
 */
void KWPlayer::createLaser(BulletSprite *shipLaser, cocos2d::CCSize winSize, float direction, float speed)
{
	// レーザーのリストと照合
	if ( _nextShipLaser >= bulletList.size() )
        _nextShipLaser = 0;
	// レーザーを設定する
    shipLaser->setPosition( ccpAdd( this->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
	// 方向を設定
	float directionPos = 200 * direction;
	shipLaser->runAction(CCSequence::create(CCMoveBy::create(speed, ccp(winSize.width, directionPos)), CCCallFuncN::create(this, callfuncN_selector(PlayerShip::setInvisible)), NULL));
}