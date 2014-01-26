#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d;
using namespace CocosDenshion;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }

    _touchFlag = false;
    _moveShipPos = ccp(0, 0);

    _batchNode = CCSpriteBatchNode::create("Sprites.pvr.ccz");
    this->addChild(_batchNode);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");

    _ship = CCSprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ship->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    _batchNode->addChild(_ship, 1);
    
    // enemy
	_enemy = CCSprite::create("Android_Robot_100.png");
	_enemy->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.4));
	this->addChild(_enemy, 1);
	_enemyVelocityX = winSize.width * (-0.01);
	_enemyVelocityY = winSize.height * (-0.01);
    
    // enemyChild
#define KNUMENEMYCHILDS 2
    _enemyChilds = new CCArray();
    for(int i = 0; i < KNUMENEMYCHILDS; ++i) {
        CCSprite *enemyChild = CCSprite::create("Android_Robot_100.png");
        enemyChild->setScale(0.5);
        enemyChild->setVisible(false);
        this->addChild(enemyChild);
        _enemyChilds->addObject(enemyChild);
    }

    
    // 1) Create the CCParallaxNode
    _backgroundNode = CCParallaxNodeExtras::node();
    this->addChild(_backgroundNode,-1) ;
    
    // 2) Create the sprites will be added to the CCParallaxNode
    _spacedust1 = CCSprite::create("bg_front_spacedust.png");
    _spacedust2 = CCSprite::create("bg_front_spacedust.png");
    _planetsunrise = CCSprite::create("bg_planetsunrise.png");
    _galaxy = CCSprite::create("bg_galaxy.png");
    _spacialanomaly = CCSprite::create("bg_spacialanomaly.png");
    _spacialanomaly2 = CCSprite::create("bg_spacialanomaly2.png");
    
    // 3) Determine relative movement speeds for space dust and background
    CCPoint dustSpeed = ccp(0.1, 0.1);
    CCPoint bgSpeed = ccp(0.05, 0.05);
    
    // 4) Add children to CCParallaxNode
    _backgroundNode->addChild(_spacedust1, 0, dustSpeed , ccp(0,winSize.height/2) ); // 2
    _backgroundNode->addChild(_spacedust2, 0, dustSpeed , ccp(_spacedust1->getContentSize().width,winSize.height/2));
    _backgroundNode->addChild(_galaxy,-1, bgSpeed, ccp(0,winSize.height * 0.7));
    _backgroundNode->addChild(_planetsunrise, -1 , bgSpeed, ccp(600, winSize.height * 0));
    _backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, ccp(900, winSize.height * 0.3));
    _backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed, ccp(1500, winSize.height * 0.9));
        
    this->scheduleUpdate();

    HelloWorld::addChild(CCParticleSystemQuad::create("Stars1.plist"));
    HelloWorld::addChild(CCParticleSystemQuad::create("Stars2.plist"));
    HelloWorld::addChild(CCParticleSystemQuad::create("Stars3.plist"));
    
    this->setAccelerometerEnabled(false);
    
    #define KNUMASTEROIDS 15
    _asteroids = new CCArray();
    for(int i = 0; i < KNUMASTEROIDS; ++i) {
        CCSprite *asteroid = CCSprite::createWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false);
        _batchNode->addChild(asteroid);
        _asteroids->addObject(asteroid);
    }
    
    #define KNUMLASERS 15
    _shipLasers = new CCArray();
    for(int i = 0; i < KNUMLASERS; ++i) {
        CCSprite *shipLaser = CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
        shipLaser->setVisible(false);
        _batchNode->addChild(shipLaser);
        _shipLasers->addObject(shipLaser);
    }
    _enemyLasers = new CCArray();
	for(int i = 0; i < KNUMLASERS; ++i) {
		CCSprite *enemyLaser = CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
		enemyLaser->setVisible(false);
		_batchNode->addChild(enemyLaser);
		_enemyLasers->addObject(enemyLaser);
	}
    _enemyChildLasers = new CCArray();
	for(int i = 0; i < KNUMLASERS; ++i) {
		CCSprite *enemyChildLaser = CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
		enemyChildLaser->setVisible(false);
		_batchNode->addChild(enemyChildLaser);
		_enemyChildLasers->addObject(enemyChildLaser);
	}

    this->setTouchEnabled(true);
    
    _lives = 3;
    this->showLifeLabel();
    double curTime = getTimeTick();
    _gameOverTime = curTime + 30000;
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceGame.wav",true);
    SimpleAudioEngine::sharedEngine()->preloadEffect("explosion_large.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("laser_ship.wav");
    
    return true;

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float dt) {
    CCPoint backgroundScrollVert = ccp(-1000,0);
    _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
    
    CCArray *spaceDusts = CCArray::createWithCapacity(2);
    spaceDusts->addObject(_spacedust1);
    spaceDusts->addObject(_spacedust2);
    for ( int ii = 0; ii <spaceDusts->count(); ii++ ) {
        CCSprite * spaceDust = (CCSprite *)(spaceDusts->objectAtIndex(ii));
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x ;
        float size = spaceDust->getContentSize().width;
        if ( xPosition < -size/2 ) {
            _backgroundNode->incrementOffset(ccp(spaceDust->getContentSize().width*2,0),spaceDust);
        }
    }
    
    CCArray *backGrounds = CCArray::createWithCapacity(4);
    backGrounds->addObject(_galaxy);
    backGrounds->addObject(_planetsunrise);
    backGrounds->addObject(_spacialanomaly);
    backGrounds->addObject(_spacialanomaly2);
    for ( int ii = 0; ii <backGrounds->count(); ii++ ) {
        CCSprite * background = (CCSprite *)(backGrounds->objectAtIndex(ii));
        float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
        float size = background->getContentSize().width;
        if ( xPosition < -size ) {
            _backgroundNode->incrementOffset(ccp(2000,0),background); 
        }
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float maxX = winSize.width - _ship->getContentSize().width/2;
    float maxY = winSize.height - _ship->getContentSize().height/2;
    float minX = _ship->getContentSize().width/2;
    float minY = _ship->getContentSize().height/2;
    
    //    float diff = (_shipPointsPerSecY * dt);
    float newX = _ship->getPosition().x + _moveShipPos.x;
    float newY = _ship->getPosition().y + _moveShipPos.y;
    newX = MIN(MAX(newX, minX), maxX);
    newY = MIN(MAX(newY, minY), maxY);
    _ship->setPosition(ccp(newX, newY));
    _moveShipPos = ccp(0, 0);
    
    // enemy position
	float newEnemyX = _enemy->getPosition().x + _enemyVelocityX;
	if (newEnemyX < winSize.width * 0.3 || winSize.width * 0.9 < newEnemyX) {
		_enemyVelocityX *= -1;
		newEnemyX += _enemyVelocityX * 10;
	}
	float newEnemyY = _enemy->getPosition().y + _enemyVelocityY;
	if (newEnemyY < winSize.height * 0.1 || winSize.height * 0.9 < newEnemyY) {
		_enemyVelocityY *= -1;
		newEnemyY += _enemyVelocityY * 10;
	}
	_enemy->setPosition(ccp(newEnemyX, newEnemyY));
    
    // enemyChild position
    CCObject* enemyChild;
    for (int i = 0; i < _enemyChilds->count(); i++) {
        //        CCARRAY_FOREACH(_enemyChilds, enemyChild){
        enemyChild = _enemyChilds->objectAtIndex(i);
        if (((CCSprite *) enemyChild)->isVisible()) {
            ((CCSprite *) enemyChild)->setPosition(ccp(newEnemyX, newEnemyY - winSize.height * 0.15 + winSize.height * 0.3 * i));
        }
    }
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > _nextAsteroidSpawn) {
        
        float randMillisecs = randomValueBetween(0.20,1.0) * 1000;
        _nextAsteroidSpawn = randMillisecs + curTimeMillis;
        
        CCSprite *enemyLaser = (CCSprite *)_enemyLasers->objectAtIndex(_nextEnemyLaser++);
		if ( _nextEnemyLaser >= _enemyLasers->count() )
			_nextEnemyLaser = 0;
		enemyLaser->setPosition( ccpAdd( _enemy->getPosition(), ccp(enemyLaser->getContentSize().width/2, 0)));
		enemyLaser->setVisible(true);
		enemyLaser->stopAllActions();
		enemyLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(-winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL));  // DO NOT FORGET TO TERMINATE WITH NULL
        
        CCARRAY_FOREACH(_enemyChilds, enemyChild){
            if (((CCSprite *) enemyChild)->isVisible() == true) {
                CCSprite *enemyChildLaser = (CCSprite *)_enemyChildLasers->objectAtIndex(_nextEnemyChildLaser++);
                if ( _nextEnemyChildLaser >= _enemyChildLasers->count() )
                    _nextEnemyChildLaser = 0;
                enemyChildLaser->setPosition( ccpAdd(((CCSprite *) enemyChild)->getPosition(), ccp(enemyChildLaser->getContentSize().width/2, 0)));
                enemyChildLaser->setVisible(true);
                enemyChildLaser->stopAllActions();
                enemyChildLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(-winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL));  // DO NOT FORGET TO TERMINATE WITH NULL
            }
        }
    }
    
    // Asteroids
    CCObject* shipLaser;
    CCObject* enemyLaser;
    // 敵機レーザー
    CCARRAY_FOREACH(_enemyLasers, enemyLaser){
        if (!((CCSprite *) enemyLaser)->isVisible() )
            continue;
        // 自機と敵機レーザー
        if (_ship->boundingBox().intersectsRect(((CCSprite *)enemyLaser)->boundingBox()) ) {
            ((CCSprite *)enemyLaser)->setVisible(false);
            _ship->runAction( CCBlink::create(1.0, 9));
            _lives--;
            this->showLifeLabel();
        }
    }
    // 敵機子機レーザー
    CCARRAY_FOREACH(_enemyChildLasers, enemyLaser){
        if (!((CCSprite *) enemyLaser)->isVisible() )
            continue;
        // 自機と敵機レーザー
        if (_ship->boundingBox().intersectsRect(((CCSprite *)enemyLaser)->boundingBox()) ) {
            ((CCSprite *)enemyLaser)->setVisible(false);
            _ship->runAction( CCBlink::create(1.0, 9));
            _lives--;
            this->showLifeLabel();
        }
    }
    // 自機レーザー
    CCARRAY_FOREACH(_shipLasers, shipLaser){
        if (!((CCSprite *) shipLaser)->isVisible() )
            continue;

        // 自機レーザーと敵機
        if (_enemy->boundingBox().intersectsRect(((CCSprite *)shipLaser)->boundingBox()) ) {
            ((CCSprite *)shipLaser)->setVisible(false);
            _enemy->runAction( CCBlink::create(1.0, 9));
            CCObject* enemyChild;
            CCARRAY_FOREACH(_enemyChilds, enemyChild){
                if (((CCSprite *) enemyChild)->isVisible() == false) {
                    ((CCSprite *) enemyChild)->setVisible(true);
                }
            }
        }
    }
    if (_lives <= 0) {
        _ship->stopAllActions();
        _ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    } else if (curTimeMillis >= _gameOverTime) {
        this->endScene(KENDREASONWIN);
    } else {
        this->showRemainingTimeLabel(curTimeMillis);
    }
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue) {
    #define KFILTERINGFACTOR 0.1
    #define KRESTACCELX -0.6
    #define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
    #define KMAXDIFFX 0.2
    
    double rollingX;
    
    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAccelerationValue->x = pAccelerationValue->y;
    rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAccelerationValue->x - rollingX;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

float HelloWorld::randomValueBetween(float low, float high) {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

float HelloWorld::getTimeTick() {
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}

void HelloWorld::setInvisible(CCNode * node) {
    node->setVisible(false);
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = true;
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _startTouchPos = location;
    
    SimpleAudioEngine::sharedEngine()->playEffect("laser_ship.wav");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    // レーザー射出
    CCSprite *shipLaser = (CCSprite *)_shipLasers->objectAtIndex(_nextShipLaser++);
    if ( _nextShipLaser >= _shipLasers->count() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( _ship->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL  // DO NOT FORGET TO TERMINATE WITH NULL
    ));
    
    _lastTouchPos = location;
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    _moveShipPos = CCPointMake(location.x - _lastTouchPos.x, location.y - _lastTouchPos.y);

    // レーザー射出
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *shipLaser = (CCSprite *)_shipLasers->objectAtIndex(_nextShipLaser++);
    if ( _nextShipLaser >= _shipLasers->count() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( _ship->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL  // DO NOT FORGET TO TERMINATE WITH NULL
                                            ));
    
    _lastTouchPos = location;
}


void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = false;
}


void HelloWorld::restartTapped() {
    CCDirector::sharedDirector()->replaceScene
    (CCTransitionZoomFlipX::create(0.5, this->scene()));
    // reschedule
    this->scheduleUpdate();
}

void HelloWorld::showLifeLabel() {
    const int tagLife = 200;
    CCString* lifeString = CCString::createWithFormat("%d", _lives);
    
    CCLabelTTF* lifeLabel = (CCLabelTTF*)this->getChildByTag(tagLife);
    if (lifeLabel) {
        lifeLabel->setString(lifeString->getCString());
    } else {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        lifeLabel = CCLabelTTF::create(lifeString->getCString(), "Arial", 24.0);
        lifeLabel->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.9));
        lifeLabel->setTag(tagLife);
        this->addChild(lifeLabel);
    }
}

void HelloWorld::showRemainingTimeLabel(float time) {
    const int tagLife = 201;
    float remainingTime = (_gameOverTime - time) / 1000;
    CCString* lifeString = CCString::createWithFormat("%8.1f", remainingTime);
    
    CCLabelTTF* lifeLabel = (CCLabelTTF*)this->getChildByTag(tagLife);
    if (lifeLabel) {
        lifeLabel->setString(lifeString->getCString());
    } else {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        lifeLabel = CCLabelTTF::create(lifeString->getCString(), "Arial", 24.0);
        lifeLabel->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.9));
        lifeLabel->setTag(tagLife);
        this->addChild(lifeLabel);
    }
}

/**
 * 終了処理
 */
void HelloWorld::endScene( EndReason endReason ) {
    if (_gameOver)
        return;
    _gameOver = true;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    char message[10] = "You Win";
    if ( endReason == KENDREASONLOSE)
        strcpy(message,"You Lose");
    CCLabelBMFont * label ;
    label = CCLabelBMFont::create(message, "Arial.fnt");
    label->setScale(0.1);
    label->setPosition(ccp(winSize.width/2 , winSize.height*0.6));
    this->addChild(label);
    
    CCLabelBMFont * restartLabel;
    strcpy(message,"Restart");
    restartLabel = CCLabelBMFont::create(message, "Arial.fnt");
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(HelloWorld::restartTapped) );
    restartItem->setScale(0.1);
    restartItem->setPosition( ccp(winSize.width/2, winSize.height*0.4));
    
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    // clear label and menu
    restartItem->runAction(CCScaleTo::create(0.5, 1.0));
    label ->runAction(CCScaleTo::create(0.5, 1.0));
    // Terminate update callback
    this->unscheduleUpdate();
}
