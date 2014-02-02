//
//  StageScene.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/01/15.
//
//

#include "StageScene.h"
#include "ParallaxLayer.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "BulletSprite.h"
#include "ConfigGame.h"
#include "GameConst.h"
#include "TimeUtils.h"
#include "JSONToDictConverter.h"
#include "SimpleAudioEngine.h"
#include "CCJSONConverter.h"

using namespace CocosDenshion;

USING_NS_CC;

const float kDefaultFrameRate = (1.0 / 24.0);

CCScene* StageScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StageScene *layer = StageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageScene::init()
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
    
    _score = 0;
    _playerHP = 100;
    _bossHP = 100;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCDictionary* configDict = NULL;
    // File path.
    const char* fileName = "episode_hiramatsu.json";
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    
    // File open mode. (See "fopen" in the "stdio.h")
    const char* openMode = "r";
    
    // File size (will be set when open the file).
    unsigned long fileSize = 0;
    
    // Open the file and get the data.
    unsigned char* json_str = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), openMode, &fileSize);
    if (json_str)
    {
        //        configDict = JSONToDictConverter::queryDictionary((const char *)json_str);
        configDict = CCJSONConverter::sharedConverter()->dictionaryFrom((const char *)json_str);
    }
    
    _config = new ConfigGame(configDict);
    
    // plistの登録
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    //    frameCache->addSpriteFramesWithFile("dragon_ss.plist");
    frameCache->addSpriteFramesWithFile("temp_bullets.plist");
    frameCache->addSpriteFramesWithFile("temp_explosion.plist");
    //    frameCache->addSpriteFramesWithFile("explosion.plist"); // 今サイズが大きすぎて表示できない。エラーが出るので今だけコメントアウト
    
    // 背景レイヤーの設定
    _backgroundNode = ParallaxLayer::createLayer();
#if 1  // 背景は外部から取得したJSONデータから設定する
    _backgroundNode->addChildLayer("1A2_normalBG01.jpeg", 0, 1.0, ccp(0.25, 1.0), CCPointZero);
    //    _backgroundNode->addChildLayer("bglayer2.png", 0, 1.5, ccp(0.5, 1.0), CCPointZero);
    //    _backgroundNode->addChildLayer("bglayer3.png", 0, 1.5, ccp(1.0, 1.0), CCPointZero);
#endif
    this->addChild(_backgroundNode, 0);
    
    //    HiramatsuScene::addChild(CCParticleSystemQuad::create("Stars1.plist"));
    //    HiramatsuScene::addChild(CCParticleSystemQuad::create("Stars2.plist"));
    //    HiramatsuScene::addChild(CCParticleSystemQuad::create("Stars3.plist"));
    
    // 弾丸表示用のBatchNodeを設定
    _batchNode = CCSpriteBatchNode::create("temp_bullets.png");
    this->addChild(_batchNode, 1);
    
    // 適機の設定
    _enemyLayer = new CCNode();
    this->addChild(_enemyLayer, 2);
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
    //    CCString*   playerShipName = new CCString("apple_hero.png");
    CCString*   playerShipName = new CCString("apple_hero_2.png");
    _playerShip = PlayerShip::createShip(playerShipName->getCString());
    _playerShip->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    _playerShip->setScale(0.25);
    this->addChild(_playerShip, 3);
    
    // エフェクト表示レイヤー
    _effectLayer = new CCNode;
    this->addChild(_effectLayer, 4);
    
    // UIレイヤー
    createUIItems();
    
    // Playerの砲撃弾の設定
    _playerShip->initBullets(_batchNode);
    
    // スコアの初期化
    _score = 0;
    
    // Playerの制御を開始
    _playerShip->start();
    
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    
    // BGM再生
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_stage_01.caf", true);
    
    return true;
}

// 画面のスケジューラの更新処理
void StageScene::update(float dt)
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
    
    // 敵機の自動生成処理
    checkPopupEnemy();
    
    // 敵機の表示位置の更新
    EnemyShip *enemyShip;
    std::vector<EnemyShip *>::iterator iterEnemy = _enemyList.begin();
    while (iterEnemy != _enemyList.end())
    {
        enemyShip = (EnemyShip*)(*iterEnemy);
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
                enemyShip = (EnemyShip*)(*iterEnemy);
                if (enemyShip && enemyShip->isActive())
                {
                    // 敵機の本体との衝突判定処理
                    CCRect  eShipBounds = enemyShip->boundingBox();
                    if (pBulletBounds.intersectsRect(eShipBounds))
                    {
                        damageEnemy(enemyShip);
                    }
                    
                    CCRect  playerShipBounds = _playerShip->boundingBox();
                    if (playerShipBounds.intersectsRect(eShipBounds))
                    {
                        damagePlayer(enemyShip);
                    }
                }
                
                // 敵機の弾とPlayerの衝突判定
                std::vector<BulletSprite *>::iterator iterEnemyBullet = enemyShip->bulletList.begin();
                while (iterEnemyBullet != enemyShip->bulletList.end())
                {
                    CCRect  eBulletBounds = (*iterEnemyBullet)->boundingBox();
                    if (pBulletBounds.intersectsRect(eBulletBounds))
                    {
                        damagePlayer(enemyShip);
                    }
                    iterEnemyBullet++;
                }
                
                iterEnemy++;
            }
        }
        iterPlayerBullet++;
    }
    
    
#if 0
    // Asteroids
    CCObject* asteroid;
    CCObject* shipLaser;
    CCARRAY_FOREACH(_asteroids, asteroid){
        if (!((CCSprite *) asteroid)->isVisible() )
            continue;
        CCARRAY_FOREACH(_shipLasers, shipLaser){
            if (!((CCSprite *) shipLaser)->isVisible())
                continue;
            if (((CCSprite *) shipLaser)->boundingBox().intersectsRect(((CCSprite *)asteroid)->boundingBox()) ) {
                SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
                ((CCSprite *)shipLaser)->setVisible(false);
                ((CCSprite *)asteroid)->setVisible(false);
                continue;
            }
        }
        if (_ship->boundingBox().intersectsRect(((CCSprite *)asteroid)->boundingBox()) ) {
            ((CCSprite *)asteroid)->setVisible(false);
            _ship->runAction( CCBlink::create(1.0, 9));
            _lives--;
        }
    }
    
    if (_lives <= 0) {
        _ship->stopAllActions();
        _ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    } else if (curTimeMillis >= _gameOverTime) {
        this->endScene(KENDREASONWIN);
    }
#endif
}

// 敵機のポップ表示処理
void StageScene::checkPopupEnemy()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 敵機の自動生成処理
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
        
        enemyShip->reset();
        enemyShip->setPosition( ccp(winSize.width+enemyShip->getContentSize().width/2, randY));
        enemyShip->setVisible(true);
        enemyShip->runAction(CCSequence::create(CCMoveBy::create(enemyShip->getMoveSpeed(), ccp(-winSize.width - enemyShip->getContentSize().width, 0)), CCCallFuncN::create(this, callfuncN_selector(StageScene::setInvisible)), NULL));
    }
}

// 画面タッチ開始処理
void StageScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = true;
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _startTouchPos = location;
    
    _playerShip->touchBeganProcess(location);
    
    _lastTouchPos = location;
}

// 画面タッチ移動処理
void StageScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    _moveShipPos = CCPointMake(location.x - _lastTouchPos.x, location.y - _lastTouchPos.y);
    
    _lastTouchPos = location;
}


// 画面タッチ終了処理
void StageScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = false;
}

void StageScene::createUIItems()
{
    // UIレイヤー
    _uiLayer = new CCNode;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    float   ratio = getDispResolution();
    float   fontSize = 36.0 * ratio;
    // Score
    CCLabelTTF *scoreTitle = CCLabelTTF::create("Score:", "", fontSize);
	scoreTitle->setPosition(ccp(size.width/2-(50*ratio), size.height - (20*ratio)));
    _uiLayer->addChild(scoreTitle);
    
    _scoreItem = CCLabelTTF::create("0", "", fontSize);
	_scoreItem->setPosition(ccp(size.width/2+(50*ratio), size.height - (20*ratio)));
    _uiLayer->addChild(_scoreItem);
    
    // Player HP
    CCLabelTTF *playerTitle = CCLabelTTF::create("PlayerHP:", "", fontSize);
	playerTitle->setPosition(ccp(80*ratio, size.height - (20*ratio)));
    _uiLayer->addChild(playerTitle);
    
    _playerHPItem = CCLabelTTF::create("100", "", fontSize);
	_playerHPItem->setPosition(ccp(200*ratio, size.height - (20*ratio)));
    _uiLayer->addChild(_playerHPItem);
    
    // Boss HP
    CCLabelTTF *bossTitle = CCLabelTTF::create("BossHP:", "", fontSize);
	bossTitle->setPosition(ccp(size.width-(200*ratio), size.height - (20*ratio)));
    _uiLayer->addChild(bossTitle);
    
    _bossHPItem = CCLabelTTF::create("100", "", fontSize);
	_bossHPItem->setPosition(ccp(size.width-(100*ratio), size.height - (20*ratio)));
    _uiLayer->addChild(_bossHPItem);
    
    this->addChild(_uiLayer, 5);
}

void StageScene::doBombEffect(CCPoint pos, CCNode* dispLayer)
{
#if 0
    const char* bombEfectName = "explosion";   // "explosion"
    int numFrames = 84;
    CCSprite* bombSprite = CCSprite::createWithSpriteFrameName(name->getCString());
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray*    frames = CCArray::createWithCapacity(numFrames);
    for (int i = 0; i <= numFrames; i++)
    {
        CCString*   name = CCString::createWithFormat("%s_%04d.png", bombName->getCString(), i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
#else
    const char* bombEfectName = "temp_explosion";   // "explosion"
    int numFrames = 4;
    
    CCString*   name = CCString::createWithFormat("%s_01.png", bombEfectName);
    CCSprite* bombSprite = CCSprite::createWithSpriteFrameName(name->getCString());
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray*    frames = CCArray::createWithCapacity(numFrames);
    for (int i = 1; i <= numFrames; i++)
    {
        CCString*   name = CCString::createWithFormat("%s_%02d.png", bombEfectName, i);
        CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(name->getCString());
        if (spriteFrame)
            frames->addObject(spriteFrame);
    }
#endif
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, kDefaultFrameRate);
    CCAnimate* animate = CCAnimate::create(animation);
    CCCallFuncN* removeFunc = CCCallFuncN::create(this, callfuncN_selector(StageScene::removeNode));
    
    bombSprite->setPosition(pos);
    dispLayer->addChild(bombSprite);
    
    bombSprite->runAction(CCSequence::create(animate, removeFunc, NULL));
}

bool StageScene::damagePlayer(EnemyShip* fromEnemy)
{
    bool    overp = false;
    if (_playerShip->hitTheBullet(fromEnemy->getPlayerDamageLevel()))
    {
        doBombEffect(_playerShip->getPosition(), _effectLayer);
        overp = true;
    }
    
    _playerHP = _playerShip->getHP();
    CCString* numHP = CCString::createWithFormat("%d", _playerHP);
    _playerHPItem->setString(numHP->getCString());
    
    return overp;
}

void StageScene::damageEnemy(EnemyShip* enemy)
{
    if (enemy->hitTheBullet(_playerShip->getAttackPoint()))
    {
        doBombEffect(enemy->getPosition(), _effectLayer);
        _score += enemy->getDefeatedPoint();
        CCString* numScore = CCString::createWithFormat("%d", _score);
        _scoreItem->setString(numScore->getCString());
    }
}

float StageScene::getDispWinRatio()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float ratio = size.height / DEFAULT_BASE_HEIGHT;
    return ratio;
}

float StageScene::getDispResolution()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    return (size.height / DEFAULT_BASE_HEIGHT);
}



void StageScene::setInvisible(CCNode * node)
{
    node->setVisible(false);
}

void StageScene::removeNode(cocos2d::CCNode* node)
{
    node->removeFromParentAndCleanup(true);
}


float StageScene::randomValueBetween(float low, float high)
{
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}



