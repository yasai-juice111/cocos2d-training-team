//
//  KawabataScene.cpp
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 2014/01/26.
//
//
#include "KawabataScene.h"

using namespace CocosDenshion;
USING_NS_CC;

CCScene* KawabataScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    KawabataScene *layer = KawabataScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

/**
 * 初期化
 */
bool KawabataScene::init()
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
    this->addChild(_enemyLayer, 2);
    KawabataEnemy *enemyShip;
    for(int i = 0; i < 30; ++i)
    {
        if (i < 10)
        {
            enemyShip = KawabataEnemy::createShip("android_pattern_3.png");
            enemyShip->setMoveSpeed(5);
        }
        else if (i < 20)
        {
            enemyShip = KawabataEnemy::createShip("android_pattern_5.png");
            enemyShip->setMoveSpeed(4);
        }
        else if (i < 25)
        {
            enemyShip = KawabataEnemy::createShip("android_pattern_3.png");
            enemyShip->setMoveSpeed(6);
        }
        else if (i < 30)
        {
            enemyShip = KawabataEnemy::createShip("android_pattern_5.png");
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
    
    // Playerの砲撃弾の設定
    _playerShip->initBullets(_batchNode);
    
    // Playerの制御を開始
    _playerShip->start();

    // 更新スケジューラを設定
    this->scheduleUpdate();
    // タッチを有効化
    this->setTouchEnabled(true);
    
    return true;
}
/**
 * 更新
 */
void KawabataScene::update(float dt)
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
    double curTimeMillis = TimeUtils::getTime() / 2.f;	// この値が大きければ、短いスパンで出現する
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
    KawabataEnemy *enemyShip;
    std::vector<KawabataEnemy *>::iterator iterEnemy = _enemyList.begin();
    while (iterEnemy != _enemyList.end())
    {
        enemyShip = (KawabataEnemy*)(*iterEnemy);
        if (enemyShip && enemyShip->isVisible())
        {
            enemyShip->update(dt);
        }
        iterEnemy++;
    }
    
    // Playerの弾と敵機に対する当たり判定処理
    std::vector<BulletSprite *>::iterator iterPlayerBullet = _playerShip->bulletList.begin();
    while (iterPlayerBullet != _playerShip->bulletList.end())
    {
        BulletSprite* playerBullet = (BulletSprite*)(*iterPlayerBullet);
        if (playerBullet && playerBullet->isVisible())
        {
            CCRect  pBulletBounds = playerBullet->boundingBox();
            iterEnemy = _enemyList.begin();
            while (iterEnemy != _enemyList.end())
            {
                enemyShip = (KawabataEnemy*)(*iterEnemy);
                if (enemyShip && enemyShip->isVisible())
                {
                    // 敵機の本体との衝突判定処理
                    CCRect  eShipBounds = enemyShip->boundingBox();
                    if (pBulletBounds.intersectsRect(eShipBounds))
                    {
                        enemyShip->setDamage();
                    }
                }
                
                // 敵機の弾とPlayerの衝突判定
                std::vector<BulletSprite *>::iterator iterEnemyBullet = enemyShip->bulletList.begin();
                while (iterEnemyBullet != enemyShip->bulletList.end())
                {
                    CCRect  eBulletBounds = (*iterEnemyBullet)->boundingBox();
                    if (pBulletBounds.intersectsRect(eBulletBounds))
                    {
                        _playerShip->setDamage();
                    }
                    iterEnemyBullet++;
                }
                
                iterEnemy++;
            }
        }
        iterPlayerBullet++;
    }
    CCLOG("Kawabata update");
}

/**
 * タッチ開始
 */
void KawabataScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = true;
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _startTouchPos = location;
    
    _playerShip->touchBeganProcess(location);
    
    _lastTouchPos = location;
    CCLOG("Kawabata touch began");
}

/**
 * スワイプ
 */
void KawabataScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    _moveShipPos = CCPointMake(location.x - _lastTouchPos.x, location.y - _lastTouchPos.y);
    
    _lastTouchPos = location;
    CCLOG("Kawabata touch moved");
}

/**
 * タッチ終了
 */
void KawabataScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = false;
    CCLOG("Kawabata touch ended");
}

/**
 * 表示設定
 */
void KawabataScene::setInvisible(cocos2d::CCNode * node)
{
    StageScene::setInvisible(node);
    CCLOG("Kawabata set invisible");
}

/**
 * ランダム値取得
 */
float KawabataScene::randomValueBetween(float low, float high)
{
    return StageScene::randomValueBetween(low, high);
}
