//
//  ShibuyaScene.cpp
//  cocos2dx-space-game
//
//  Created by c2:shibuya_shun on 2014/01/26.
//
//
#include "ShibuyaScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

CCScene* ShibuyaScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ShibuyaScene *layer = ShibuyaScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

/**
 * 初期化
 */
bool ShibuyaScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(128,128,128,0)))
    {
        return false;
    }
    
    // クラス変数の初期化
    _touchFlag = false;
    _moveShipPos = ccp(0, 0);
    _nextEnemy = 0;
    
    // 画面サイズの取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 音声ファイル
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceGame.wav",true);
	SimpleAudioEngine::sharedEngine()->preloadEffect("explosion_large.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("laser_ship.wav");
    
    // plistの登録
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    //    frameCache->addSpriteFramesWithFile("dragon_ss.plist");
    frameCache->addSpriteFramesWithFile("temp_bullets.plist");
    frameCache->addSpriteFramesWithFile("temp_explosion.plist");
    frameCache->addSpriteFramesWithFile("explosion.plist"); // 今サイズが大きすぎて表示できない。
    frameCache->addSpriteFramesWithFile("explosion_boss.plist");
    // 背景レイヤーの設定
    _backgroundNode = ParallaxLayer::createLayer();
#if 0   // 背景は外部から取得したJSONデータから設定する
    _backgroundNode->addChildLayer("bglayer1.png", 0, 1.5, ccp(0.25, 1.0), CCPointZero);
    _backgroundNode->addChildLayer("bglayer2.png", 0, 1.5, ccp(0.5, 1.0), CCPointZero);
    _backgroundNode->addChildLayer("bglayer3.png", 0, 1.5, ccp(1.0, 1.0), CCPointZero);
#endif
    this->addChild(_backgroundNode, 0);
    
    StageScene::addChild(CCParticleSystemQuad::create("Stars1.plist"));
    StageScene::addChild(CCParticleSystemQuad::create("Stars2.plist"));
    StageScene::addChild(CCParticleSystemQuad::create("Stars3.plist"));
    
    // 弾丸表示用のBatchNodeを設定
    _batchNode = CCSpriteBatchNode::create("temp_bullets.png");
    this->addChild(_batchNode, 1);
    
    // Player機の作成
    CCString*   playerShipName = new CCString("temp_apple.png");
    _playerShip = ShibuyaPlayerShip::createShip(playerShipName->getCString());
    _playerShip->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.9));
    this->addChild(_playerShip, 3);
	
    _playerShipLife = 3;
	_playerShip->setLife(_playerShipLife);
	showPlayerLife();
    
    // Playerの砲撃弾の設定
    _playerShip->initBullets(_batchNode);
    
    // Playerの制御を開始
    _playerShip->start();

	
	// ボス機の作成
	CCString* shibuyaBossShipName = new CCString("Android_Robot_100.png");
	_shibuyaBossShip = ShibuyaBossShip::createShip(shibuyaBossShipName->getCString());
	_shibuyaBossShip->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.5));
	this->addChild(_shibuyaBossShip, 3);

    _bossShipLife = 5;
	_shibuyaBossShip->setLife(_bossShipLife);
	showBossLife();

	// ボス機の砲撃弾の設定
    _shibuyaBossShip->initBullets(_batchNode);
    
    // ボス機の制御を開始
    _shibuyaBossShip->start();

	
	// ボス子機上の作成
	CCString* sbBossChildUpperShipName = new CCString("Android_Robot_100.png");
	_sbBossChildUpperShip = ShibuyaBossShip::createShip(sbBossChildUpperShipName->getCString());
	_sbBossChildUpperShip->setScale(0.5);
	this->addChild(_sbBossChildUpperShip, 3);
	
	_sbBossChildUpperShip->setLife(1);
	
	// ボス子機の砲撃弾の設定
    _sbBossChildUpperShip->initBullets(_batchNode);
    
    // ボス子機の制御を開始
    _sbBossChildUpperShip->start();

	// ボス子機下の作成
	CCString* sbBossChildLowerShipName = new CCString("Android_Robot_100.png");
	_sbBossChildLowerShip = ShibuyaBossShip::createShip(sbBossChildLowerShipName->getCString());
	_sbBossChildLowerShip->setScale(0.5);
	this->addChild(_sbBossChildLowerShip, 3);
	
	_sbBossChildLowerShip->setLife(1);
	
	// ボス子機の砲撃弾の設定
    _sbBossChildLowerShip->initBullets(_batchNode);
    
    // ボス子機の制御を開始
    _sbBossChildLowerShip->start();
    
    // ライフ表示用画像
    CCSprite* _battery = CCSprite::create("battery-empty-256x256.png");
    _playerProgressTimer = CCProgressTimer::create(_battery);
    _playerProgressTimer->setType(kCCProgressTimerTypeBar);
    _playerProgressTimer->setMidpoint(ccp(0, 0));
    _playerProgressTimer->setBarChangeRate(ccp(1, 0));
    _playerProgressTimer->setPercentage(100.0);
    _playerProgressTimer->setPosition(ccp(winSize.width * 0.35, winSize.height * 0.9));
    this->addChild(_playerProgressTimer);
    _bossProgressTimer = CCProgressTimer::create(_battery);
    _bossProgressTimer->setType(kCCProgressTimerTypeBar);
    _bossProgressTimer->setMidpoint(ccp(0, 0));
    _bossProgressTimer->setBarChangeRate(ccp(1, 0));
    _bossProgressTimer->setPercentage(100.0);
    _bossProgressTimer->setPosition(ccp(winSize.width * 0.65, winSize.height * 0.9));
    this->addChild(_bossProgressTimer);

	
    // 更新スケジューラを設定
    this->scheduleUpdate();
    // タッチを有効化
    this->setTouchEnabled(true);
	
    return true;
}

/**
 * 更新
 */
void ShibuyaScene::update(float dt)
{
    // 背景レイヤーの更新
    _backgroundNode->update(dt);
    
    // Player機の表示位置調整
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float maxX = winSize.width - _playerShip->getContentSize().width/2;
    float maxY = winSize.height - _playerShip->getContentSize().height/2;
    float minX = _playerShip->getContentSize().width/2;
    float minY = _playerShip->getContentSize().height/2;
    float newX = _playerShip->getPosition().x + _moveShipPos.x;
    float newY = _playerShip->getPosition().y + _moveShipPos.y;
    newX = MIN(MAX(newX, minX), maxX);
    newY = MIN(MAX(newY, minY), maxY);
    _playerShip->setPosition(ccp(newX, newY));
    _moveShipPos = ccp(0, 0);
    _playerShip->update(dt);
    	
	// ボス機の表示位置の更新
	float bossShipNextPositionX = _shibuyaBossShip->getPosition().x + _shibuyaBossShip->getPositionDx();
	float bossShipNextPositionY = _shibuyaBossShip->getPosition().y + _shibuyaBossShip->getPositionDy();
	_shibuyaBossShip->setPosition(ccp(bossShipNextPositionX, bossShipNextPositionY));
	
	if (bossShipNextPositionX < winSize.width * 0.3 || winSize.width * 0.9 < bossShipNextPositionX) {
		_shibuyaBossShip->turnPositionDx();
	}
	if (bossShipNextPositionY < winSize.height * 0.1 || winSize.height * 0.9 < bossShipNextPositionY) {
		_shibuyaBossShip->turnPositionDy();
	}
	
	// ボス機の更新処理
	_shibuyaBossShip->update(dt);

	
	// ボス子機の表示位置の更新
	if (_sbBossChildUpperShip->isVisible()) {
		_sbBossChildUpperShip->setPosition(ccp(bossShipNextPositionX, bossShipNextPositionY + winSize.height * 0.15));
		_sbBossChildUpperShip->update(dt);
	}
	
	// ボス子機の表示位置の更新
	if (_sbBossChildLowerShip->isVisible()) {
		_sbBossChildLowerShip->setPosition(ccp(bossShipNextPositionX, bossShipNextPositionY - winSize.height * 0.15));
		_sbBossChildLowerShip->update(dt);
	}
	
    
    // Playerの弾と敵機に対する当たり判定処理
	if (_shibuyaBossShip->isVisible()) {
		std::vector<BulletSprite *>::iterator iterPlayerBullet = _playerShip->bulletList.begin();
		while (iterPlayerBullet != _playerShip->bulletList.end())
		{
			BulletSprite* playerBullet = (BulletSprite*)(*iterPlayerBullet);
			if (playerBullet && playerBullet->isVisible())
			{
				CCRect  pBulletBounds = playerBullet->boundingBox();
				// Playerの弾とボス機との衝突判定
				CCRect shibuyaBossShipBounds = _shibuyaBossShip->boundingBox();
				if (pBulletBounds.intersectsRect(shibuyaBossShipBounds)) {
					_shibuyaBossShip->setDamage();
					SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
					
					int life = _shibuyaBossShip->getLife();
					life--;
					_shibuyaBossShip->setLife(life);
					CCLOG("_shibuyaBossShip life: %d", life);
					
					showBossLife();
                    updateBossProgressTimer();
					
                    if (life == 1) {
                        if (_sbBossChildUpperShip->isVisible() == false) {
                            _sbBossChildUpperShip->setVisible(true);
                        }
                        if (_sbBossChildLowerShip->isVisible() == false) {
                            _sbBossChildLowerShip->setVisible(true);
                        }
                    } else if (life == 0) {
						endScene();
					}
				}

				// Playerの弾とボス子機との衝突判定
				if (_sbBossChildUpperShip->isVisible()) {
					CCRect sbBossChildUpperShipBounds = _sbBossChildUpperShip->boundingBox();
					if (pBulletBounds.intersectsRect(sbBossChildUpperShipBounds)) {
						_sbBossChildUpperShip->setDamage();
						SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
						
						int life = _sbBossChildUpperShip->getLife();
						life--;
						_sbBossChildUpperShip->setLife(life);
						CCLOG("_sbBossChildUpperShip life: %d", life);
						
						if (life == 0) {
							_sbBossChildUpperShip->setVisible(false);
						}
					}
				}

				// Playerの弾とボス子機との衝突判定
				if (_sbBossChildLowerShip->isVisible()) {
					CCRect sbBossChildLowerShipBounds = _sbBossChildLowerShip->boundingBox();
					if (pBulletBounds.intersectsRect(sbBossChildLowerShipBounds)) {
						_sbBossChildLowerShip->setDamage();
						SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
						
						int life = _sbBossChildLowerShip->getLife();
						life--;
						_sbBossChildLowerShip->setLife(life);
						CCLOG("_sbBossChildLowerShip life: %d", life);
						
						if (life == 0) {
							_sbBossChildLowerShip->setVisible(false);
						}
					}
				}
			}
			iterPlayerBullet++;
		}
	}

	// ボスの弾とPlayerに対する当たり判定処理
	if (_playerShip->isVisible()) {
		std::vector<BulletSprite *>::iterator iterShibuyaBossShipBullet = _shibuyaBossShip->bulletList.begin();
		while (iterShibuyaBossShipBullet != _shibuyaBossShip->bulletList.end())
		{
			BulletSprite* shibuyaBossShipBullet = (BulletSprite*)(*iterShibuyaBossShipBullet);
			if (shibuyaBossShipBullet && shibuyaBossShipBullet->isVisible())
			{
				CCRect  pBulletBounds = shibuyaBossShipBullet->boundingBox();
				// Playerの弾とボス機との衝突判定
				CCRect playerShipBounds = _playerShip->boundingBox();
				if (pBulletBounds.intersectsRect(playerShipBounds)) {
					_playerShip->setDamage();
					SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");

					int life = _playerShip->getLife();
					life--;
					_playerShip->setLife(life);
					CCLOG("_playerShip life: %d", life);
					
					showPlayerLife();
                    updatePlayerProgressTimer();
					
					if (life == 0) {
						endScene();
					}
				}
			}
			iterShibuyaBossShipBullet++;
		}

		// ボス子機の弾とPlayerに対する当たり判定処理
		std::vector<BulletSprite *>::iterator iterSbBossChildUpperShipBullet = _sbBossChildUpperShip->bulletList.begin();
		while (iterSbBossChildUpperShipBullet != _sbBossChildUpperShip->bulletList.end())
		{
			BulletSprite* shibuyaBossShipBullet = (BulletSprite*)(*iterSbBossChildUpperShipBullet);
			if (shibuyaBossShipBullet && shibuyaBossShipBullet->isVisible())
			{
				CCRect  pBulletBounds = shibuyaBossShipBullet->boundingBox();
				// Playerの弾とボス機との衝突判定
				CCRect playerShipBounds = _playerShip->boundingBox();
				if (pBulletBounds.intersectsRect(playerShipBounds)) {
					_playerShip->setDamage();
					SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
					
					int life = _playerShip->getLife();
					life--;
					_playerShip->setLife(life);
					CCLOG("_playerShip life: %d", life);
					
					showPlayerLife();
                    updatePlayerProgressTimer();
					
					if (life == 0) {
						endScene();
					}
				}
			}
			iterSbBossChildUpperShipBullet++;
		}

		// ボス子機の弾とPlayerに対する当たり判定処理
		std::vector<BulletSprite *>::iterator iterSbBossChildLowerShipBullet = _sbBossChildLowerShip->bulletList.begin();
		while (iterSbBossChildLowerShipBullet != _sbBossChildLowerShip->bulletList.end())
		{
			BulletSprite* shibuyaBossShipBullet = (BulletSprite*)(*iterSbBossChildLowerShipBullet);
			if (shibuyaBossShipBullet && shibuyaBossShipBullet->isVisible())
			{
				CCRect  pBulletBounds = shibuyaBossShipBullet->boundingBox();
				// Playerの弾とボス機との衝突判定
				CCRect playerShipBounds = _playerShip->boundingBox();
				if (pBulletBounds.intersectsRect(playerShipBounds)) {
					_playerShip->setDamage();
					SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
					
					int life = _playerShip->getLife();
					life--;
					_playerShip->setLife(life);
					CCLOG("_playerShip life: %d", life);
					
					showPlayerLife();
                    updatePlayerProgressTimer();
					
					if (life == 0) {
						endScene();
					}
				}
			}
			iterSbBossChildLowerShipBullet++;
		}

	}
}

/**
 * タッチ開始
 */
void ShibuyaScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = true;
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _startTouchPos = location;
    
    _playerShip->touchBeganProcess(location);
    
    _lastTouchPos = location;
}

/**
 * スワイプ
 */
void ShibuyaScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    _moveShipPos = CCPointMake(location.x - _lastTouchPos.x, location.y - _lastTouchPos.y);
    
    _lastTouchPos = location;
}

/**
 * タッチ終了
 */
void ShibuyaScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = false;
}

/**
 * 表示設定
 */
void ShibuyaScene::setInvisible(cocos2d::CCNode * node)
{
    StageScene::setInvisible(node);
}

/**
 * ランダム値取得
 */
float ShibuyaScene::randomValueBetween(float low, float high)
{
    return StageScene::randomValueBetween(low, high);
}

/*
 * Player残機表示
 */
void ShibuyaScene::showPlayerLife()
{
	const int tagPlayerLifeLabel = 101;
	int life = _playerShip->getLife();
	CCString* lifeString = CCString::createWithFormat("Player life: %d", life);
	CCLabelTTF* lifeLabel = (CCLabelTTF*)this->getChildByTag(tagPlayerLifeLabel);
	if (lifeLabel)
	{
		lifeLabel->setString(lifeString->getCString());
	}
	else
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		lifeLabel = CCLabelTTF::create(lifeString->getCString(), "Arial", 24.0);
		lifeLabel->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.9));
		lifeLabel->setTag(tagPlayerLifeLabel);
		this->addChild(lifeLabel);		
	}
}

/*
 * ボス残機表示
 */
void ShibuyaScene::showBossLife()
{
	const int tagBossLifeLabel = 102;
	int life = _shibuyaBossShip->getLife();
	CCString* lifeString = CCString::createWithFormat("Boss life: %d", life);
	CCLabelTTF* lifeLabel = (CCLabelTTF*)this->getChildByTag(tagBossLifeLabel);
	if (lifeLabel)
	{
		lifeLabel->setString(lifeString->getCString());
	}
	else
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		lifeLabel = CCLabelTTF::create(lifeString->getCString(), "Arial", 24.0);
		lifeLabel->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.9));
		lifeLabel->setTag(tagBossLifeLabel);
		this->addChild(lifeLabel);
	}
}

/*
 * リトライボタンタップ次の処理
 */
void ShibuyaScene::tapRetryButton(CCNode *node)
{
	CCScene* gameScene = (CCScene*)ShibuyaScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}

/*
 * リトライボタンを作成
 */
void ShibuyaScene::makeRetryButton()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCLabelTTF* retryLabel = CCLabelTTF::create("Retry", "Arial", 24.0);
	CCMenuItemLabel* retryItem = CCMenuItemLabel::create(retryLabel, this, menu_selector(ShibuyaScene::tapRetryButton));
	retryItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.3));
	
	CCMenu* menu = CCMenu::create(retryItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
}


/*
 * メニューへ遷移ボタンタップ次の処理
 */
void ShibuyaScene::tapMoveTopButton(CCNode *node)
{
	CCScene* gameScene = (CCScene*)StartMenuScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}

/*
 * メニューへ遷移ボタンを作成
 */
void ShibuyaScene::makeMoveTopButton()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCLabelTTF* retryLabel = CCLabelTTF::create("Menu", "Arial", 24.0);
	CCMenuItemLabel* retryItem = CCMenuItemLabel::create(retryLabel, this, menu_selector(ShibuyaScene::tapMoveTopButton));
	retryItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
	
	CCMenu* menu = CCMenu::create(retryItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
}

/*
 * プログレスタイマーの更新
 */
void ShibuyaScene::updatePlayerProgressTimer()
{
    float percentage = _playerProgressTimer->getPercentage();
    percentage -= (100/_playerShipLife);
    _playerProgressTimer->setPercentage(percentage);
}
void ShibuyaScene::updateBossProgressTimer()
{
    float percentage = _bossProgressTimer->getPercentage();
    percentage -= (100/_bossShipLife);
    _bossProgressTimer->setPercentage(percentage);
}

/*
 * 終了処理
 */
void ShibuyaScene::endScene()
{
	// stop schedule
	this->unscheduleUpdate();

	// show result
	char message[10];
	if (_shibuyaBossShip->getLife() == 0) {
        strcpy(message,"You Win");
	} else if (_playerShip->getLife() == 0) {
        strcpy(message,"You Lose");
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelBMFont * label ;
    label = CCLabelBMFont::create(message, "Arial.fnt");
    label->setScale(5);
    label->setPosition(ccp(winSize.width/2 , winSize.height*0.6));
    this->addChild(label, 100);
	
	// show retry button
	makeRetryButton();
    
    makeMoveTopButton();
}