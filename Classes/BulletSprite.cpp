//
//  BulletSprite.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on 2014/01/24.
//
//

#include "BulletSprite.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;


BulletSprite::BulletSprite()
{
    
}

BulletSprite::~BulletSprite()
{
    
}

bool BulletSprite::initWithFileName(const char* pszFileName)
{
    if (!CCSprite::init())
        return false;
    
    _flag = false;
    
    this->initWithFile(pszFileName);
    
    return true;
    
}

BulletSprite* BulletSprite::createBullet(const char* pszFileName)
{
    BulletSprite *pobSprite = new BulletSprite();
    if (pobSprite && pobSprite->initWithFileName(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

BulletSprite* BulletSprite::createWithSpriteFrameName(const char *pszSpriteFrameName, int numFrames)
{
    CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
    BulletSprite *pobSprite = new BulletSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}


