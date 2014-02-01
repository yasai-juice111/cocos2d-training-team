//
//  KWPlayer.cpp
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//

#include "KWPlayer.h"

USING_NS_CC;

KWPlayer::KWPlayer()
{
    
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