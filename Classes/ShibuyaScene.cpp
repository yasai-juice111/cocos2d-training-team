//
//  ShibuyaScene.cpp
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 14/01/26.
//
//
#include "ShibuyaScene.h"
#include "PlayerShip.h"

using namespace cocos2d;

//// on "init" you need to initialize your instance
//bool ShibuyaScene::init()
//{    
//    return true;
//}

CCScene* ShibuyaScene::scene()
{
    CCLOG("start scene");
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ShibuyaScene *layer = ShibuyaScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShibuyaScene::init()
{
    CCLOG("init start");
    //////////////////////////////
    if ( !CCLayer::init() )
    {
        return false;
    }
    

    return true;
}

// 画面のスケジューラの更新処理
void ShibuyaScene::update(float dt)
{
}

// 画面タッチ開始処理
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

// 画面タッチ移動処理
void ShibuyaScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch *myTouch = (CCTouch*)touches->anyObject();
    CCPoint location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    _moveShipPos = CCPointMake(location.x - _lastTouchPos.x, location.y - _lastTouchPos.y);
    
    _lastTouchPos = location;
}


// 画面タッチ終了処理
void ShibuyaScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _touchFlag = false;
}

