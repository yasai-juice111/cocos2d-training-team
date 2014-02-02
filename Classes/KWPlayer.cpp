//
//  KWPlayer.cpp
//  cocos2dx-space-game
//
//  Created by c7:kawabata_satoshi on 2014/02/01.
//
//
#include "KWPlayer.h"
#include "TimeUtils.h"
#include "cocos2d.h"

USING_NS_CC;

const float kDefaultFrameRate = (1.0 / 24.0);

KWPlayer::KWPlayer()
{
    // 弾のスピード
	_bulletSpeed = 0.5;
	_bulletVariation = FOCUS;
	// ライフ
    _life = 3;
    
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
 * 志望フラグゲッター
 */
bool KWPlayer::getDead()
{
    if (_life > 0)
        return false;
    else
        return true;
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
            // 死んでいなければ弾を撃つ
            if (!getDead())
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
	shipLaser->runAction(CCSequence::create(CCMoveBy::create(speed, ccp(winSize.width, directionPos)), CCCallFuncN::create(this, NULL), NULL));
}

/**
 * ダメージ処理
 */
void KWPlayer::setDamage()
{
    
    
    CCString*   bombName = selectExplosionFrame();
    CCString*   name = CCString::createWithFormat("%s_00001.png", bombName->getCString());
    CCSprite* bombSprite = CCSprite::createWithSpriteFrameName(name->getCString());
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
    bombSprite->setPosition(ccp(0, 0));
    this->addChild(bombSprite);
    bombSprite->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(KWPlayer::decreaseLife)), NULL));
}



/**
 * ライフを減らす
 */
void KWPlayer::decreaseLife(CCNode * node)
{
    _life--;
    if (getDead())
    {
        // 移動アクションを停止
        _ship->stopAllActions();
        _ship->setVisible(false);
    }
    node->setVisible(false);
    
    CCLOG("player decrease life");
}

/**
 * 爆発エフェクトのセレクタ
 */
CCString* KWPlayer::selectExplosionFrame()
{
    if (_life <= 1)
        return new CCString("explosion_boss");
    else
        return new CCString("explosion");
}





