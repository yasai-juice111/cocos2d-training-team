//
//  GameTitleScene.cpp
//  SpaceGame
//
//  Created by GCREST on 2014/01/24.
//
//

#include "GameTitleScene.h"
#include "StartMenuScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

CCScene* GameTitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameTitleScene *layer = GameTitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameTitleScene::init()
{
    // レイヤーの初期化　背景を黒に設定
    if (!CCLayerColor::initWithColor(ccc4(0,0,0,0)))
    {
        return false;
    }
    
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // 背景画像を設定
//    CCSprite* backgroundImg = CCSprite::create("top_bg.jpg");
    CCSprite* backgroundImg = CCSprite::create("android_vs_ios.jpeg");
    backgroundImg->setAnchorPoint(ccp(0.5, 0.5));
    backgroundImg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // 背景の画像を縦方向を画面にフィットするようにスケーリング値を取得
    float   baseScale = 1.0;    //backgroundImg->getContentSize().height / visibleSize.height;
    backgroundImg->setScale(baseScale);
    backgroundImg->setOpacity(0);
    backgroundImg->runAction(CCFadeIn::create(0.1));
    this->addChild(backgroundImg);
    
#if 0   //
    // ゲームタイトルを設定
    CCSprite* titleImg = CCSprite::create("top_title.png");
    titleImg->setAnchorPoint(ccp(0.5, 0.5));
    titleImg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));
    titleImg->setScale(baseScale);
    titleImg->setOpacity(0);
    titleImg->runAction(CCFadeIn::create(0.25));
    this->addChild(titleImg);
#endif
    
    this->setTouchEnabled(true);

//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_mainTheme.caf", true);
    
    return true;
}

void GameTitleScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    // スタートメニュー選択が画面に遷移
    CCScene *pScene = StartMenuScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("se_touchSE.mp3", false);
}
