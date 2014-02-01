//
//  ShibuyaScene.cpp
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 2014/01/26.
//
//
#include "ShibuyaScene.h"

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
    
    // plistの登録
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    //    frameCache->addSpriteFramesWithFile("dragon_ss.plist");
    frameCache->addSpriteFramesWithFile("temp_bullets.plist");
    frameCache->addSpriteFramesWithFile("temp_explosion.plist");
    frameCache->addSpriteFramesWithFile("explosion.plist"); // 今サイズが大きすぎて表示できない。
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
    
    // 適機の設定
    _enemyLayer = new CCNode();
//    this->addChild(_enemyLayer, 2);
    EnemyShip *enemyShip;
    for(int i = 0; i < 30; ++i)
    {
        if (i < 10)
        {
            enemyShip = EnemyShip::createShip("android_pattern_3.png");
            enemyShip->setMoveSpeed(5);
        }
        else if (i < 20)
        {
            enemyShip = EnemyShip::createShip("android_pattern_5.png");
            enemyShip->setMoveSpeed(4);
        }
        else if (i < 25)
        {
            enemyShip = EnemyShip::createShip("android_pattern_3.png");
            enemyShip->setMoveSpeed(6);
        }
        else if (i < 30)
        {
            enemyShip = EnemyShip::createShip("android_pattern_5.png");
            enemyShip->setMoveSpeed(8);
        }
        enemyShip->initBullets(_batchNode);
        enemyShip->setVisible(false);
        _enemyLayer->addChild(enemyShip);
        _enemyList.push_back(enemyShip);
    }
	
	
    
    // Player機の作成
//    _playerShip = PlayerShip::createShipFrame("dragon_ss", 4);
    CCString*   playerShipName = new CCString("temp_apple.png");
    _playerShip = PlayerShip::createShip(playerShipName->getCString());
    _playerShip->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    this->addChild(_playerShip, 3);
	
	_playerShip->setLife(2);
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

	_shibuyaBossShip->setLife(2);
	showBossLife();

	// ボス機の砲撃弾の設定
    _shibuyaBossShip->initBullets(_batchNode);
    
    // ボス機の制御を開始
    _shibuyaBossShip->start();

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
    
    // 適機の自動生成処理
    double curTimeMillis = TimeUtils::getTime();
    if (curTimeMillis > _nextEnemySpawn)
    {
        float randMillisecs = randomValueBetween(0.20,1.0);
        _nextEnemySpawn = ((double)(randMillisecs)) + curTimeMillis;
        
        float randY = randomValueBetween(0.0, winSize.height);
        EnemyShip *enemyShip = (EnemyShip *)_enemyList[_nextEnemy];
        _nextEnemy++;
        
        if (_nextEnemy >= _enemyList.size())
            _nextEnemy = 0;
        
        enemyShip->stopAllActions();
        enemyShip->setPosition( ccp(winSize.width+enemyShip->getContentSize().width/2, randY));
        enemyShip->setVisible(true);
        enemyShip->runAction(CCSequence::create(CCMoveBy::create(enemyShip->getMoveSpeed(), ccp(-winSize.width - enemyShip->getContentSize().width, 0)), CCCallFuncN::create(this, callfuncN_selector(StageScene::setInvisible)), NULL));
    }
    
    // 敵機の表示位置の更新
    EnemyShip *enemyShip;
    std::vector<EnemyShip *>::iterator iterEnemy = _enemyList.begin();
    while (iterEnemy != _enemyList.end())
    {
        enemyShip = (EnemyShip*)(*iterEnemy);
        if (enemyShip && enemyShip->isVisible())
        {
//            enemyShip->update(dt);
        }
        iterEnemy++;
    }
	
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
					
					int life = _shibuyaBossShip->getLife();
					life--;
					_shibuyaBossShip->setLife(life);
					CCLOG("_shibuyaBossShip life: %d", life);
					
					showBossLife();
					
					if (life == 0) {
						endScene();
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

					int life = _playerShip->getLife();
					life--;
					_playerShip->setLife(life);
					CCLOG("_playerShip life: %d", life);
					
					showPlayerLife();
					
					if (life == 0) {
						endScene();
					}
				}
			}
			iterShibuyaBossShipBullet++;
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
		lifeLabel->setPosition(ccp(winSize.width * 0.2, winSize.height * 0.9));
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
		lifeLabel->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.9));
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
}