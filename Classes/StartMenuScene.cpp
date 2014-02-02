//
//  StartMenuScene.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/01/15.
//
//

#include "StartMenuScene.h"
#include "StageScene.h"
#include "HiramatsuScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

CCScene* StartMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartMenuScene *layer = StartMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartMenuScene::init()
{
    // レイヤーの初期化　背景を黒に設定
    if (!CCLayerColor::initWithColor(ccc4(0,0,0,0)))
    {
        return false;
    }
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // ゲームタイトルを設定
    CCMenuItemLabel *titleImg = CCMenuItemLabel::create(CCLabelTTF::create("ステージ選択", "", 48),
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel1));
//    CCSprite* titleImg = CCSprite::create("title_selectdifficulty.png");
    titleImg->setAnchorPoint(ccp(0.5, 0.5));
    titleImg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/4*3 + origin.y));
    this->addChild(titleImg);

    // ゲームレベル選択メニューの設定
#if 1
    // Game Level1
    CCMenuItemLabel *pGameLevel1 = CCMenuItemLabel::create(CCLabelTTF::create("Epsode 1", "", 48),
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel1));
	pGameLevel1->setPosition(ccp(origin.x + visibleSize.width/2 - pGameLevel1->getContentSize().width,
                                 origin.y + visibleSize.height/2 + pGameLevel1->getContentSize().height/2));
    CCMenu* pLevel1Menu = CCMenu::create(pGameLevel1, NULL);
    pLevel1Menu->setPosition(CCPointZero);
    this->addChild(pLevel1Menu, 1);
    
    // Game Level2
    CCMenuItemLabel *pGameLevel2 = CCMenuItemLabel::create(CCLabelTTF::create("Epsode 2", "", 48),
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel2));
	pGameLevel2->setPosition(ccp(origin.x + visibleSize.width/2 + pGameLevel2->getContentSize().width ,
                                 origin.y + visibleSize.height/2 + pGameLevel2->getContentSize().height/2));
    CCMenu* pLevel2Menu = CCMenu::create(pGameLevel2, NULL);
    pLevel2Menu->setPosition(CCPointZero);
    this->addChild(pLevel2Menu, 1);
    
    // Game Level3
    CCMenuItemLabel *pGameLevel3 = CCMenuItemLabel::create(CCLabelTTF::create("Epsode 3", "", 48),
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel3));
	pGameLevel3->setPosition(ccp(origin.x + visibleSize.width/2 - pGameLevel3->getContentSize().width,
                                 origin.y + visibleSize.height/2 - pGameLevel3->getContentSize().height));
    CCMenu* pLevel3Menu = CCMenu::create(pGameLevel3, NULL);
    pLevel3Menu->setPosition(CCPointZero);
    this->addChild(pLevel3Menu, 1);
    
    // Game Level4
    CCMenuItemLabel *pGameLevel4 = CCMenuItemLabel::create(CCLabelTTF::create("Epsode 4", "", 48),
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel4));
	pGameLevel4->setPosition(ccp(origin.x + visibleSize.width/2 + pGameLevel4->getContentSize().width,
                                 origin.y + visibleSize.height/2 - pGameLevel4->getContentSize().height));
    CCMenu* pLevel4Menu = CCMenu::create(pGameLevel4, NULL);
    pLevel4Menu->setPosition(CCPointZero);
    this->addChild(pLevel4Menu, 1);
#else
    // Game Level1
    CCMenuItemImage *pGameLevel1 = CCMenuItemImage::create("button_diff_easy.png", "button_diff_easy.png",
                                                          this, menu_selector(StartMenuScene::menuSelectGameLevel1));
	pGameLevel1->setPosition(ccp(origin.x + visibleSize.width/2 - pGameLevel1->getContentSize().width/2,
                                origin.y + visibleSize.height/2 + pGameLevel1->getContentSize().height/2));
    CCMenu* pLevel1Menu = CCMenu::create(pGameLevel1, NULL);
    pLevel1Menu->setPosition(CCPointZero);
    this->addChild(pLevel1Menu, 1);
    
    // Game Level2
    CCMenuItemImage *pGameLevel2 = CCMenuItemImage::create("button_diff_normal.png", "button_diff_normal.png",
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel2));
	pGameLevel2->setPosition(ccp(origin.x + visibleSize.width/2 + pGameLevel2->getContentSize().width/2 ,
                                 origin.y + visibleSize.height/2 + pGameLevel2->getContentSize().height/2));
    CCMenu* pLevel2Menu = CCMenu::create(pGameLevel2, NULL);
    pLevel2Menu->setPosition(CCPointZero);
    this->addChild(pLevel2Menu, 1);
    
    // Game Level3
    CCMenuItemImage *pGameLevel3 = CCMenuItemImage::create("button_diff_hard.png", "button_diff_hard.png",
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel3));
	pGameLevel3->setPosition(ccp(origin.x + visibleSize.width/2 - pGameLevel3->getContentSize().width/2,
                                 origin.y + visibleSize.height/2 - pGameLevel3->getContentSize().height));
    CCMenu* pLevel3Menu = CCMenu::create(pGameLevel3, NULL);
    pLevel3Menu->setPosition(CCPointZero);
    this->addChild(pLevel3Menu, 1);

    // Game Level4
    CCMenuItemImage *pGameLevel4 = CCMenuItemImage::create("button_diff_vhard.png", "button_diff_vhard.png",
                                                           this, menu_selector(StartMenuScene::menuSelectGameLevel4));
	pGameLevel4->setPosition(ccp(origin.x + visibleSize.width/2 + pGameLevel4->getContentSize().width/2 ,
                                 origin.y + visibleSize.height/2 - pGameLevel4->getContentSize().height));
    CCMenu* pLevel4Menu = CCMenu::create(pGameLevel4, NULL);
    pLevel4Menu->setPosition(CCPointZero);
    this->addChild(pLevel4Menu, 1);
#endif
    
    return true;
}

#define kTouchSEName "se_touchSE.mp3"   // TODO ボタンをタッチした時のエフェクトファイル　まだ未実装

void StartMenuScene::menuSelectGameLevel1(CCObject* pSender)
{
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(kTouchSEName, false);

    // スタートメニュー選択が画面に遷移
    CCScene *pScene = StageScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void StartMenuScene::menuSelectGameLevel2(CCObject* pSender)
{
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(kTouchSEName, false);

    // スタートメニュー選択が画面に遷移
    CCScene *pScene = StageScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void StartMenuScene::menuSelectGameLevel3(CCObject* pSender)
{
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(kTouchSEName, false);

    // スタートメニュー選択が画面に遷移
    CCScene *pScene = StageScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void StartMenuScene::menuSelectGameLevel4(CCObject* pSender)
{
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(kTouchSEName, false);

    // スタートメニュー選択が画面に遷移
    CCScene *pScene = HiramatsuScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

