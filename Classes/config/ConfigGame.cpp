//
//  ConfigGame.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "ConfigGame.h"
#include "ConfigPlayer.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigGame::ConfigGame(CCDictionary *dict)
{
    if (dict)
    {
        setup(dict);
    }
}

ConfigGame::~ConfigGame()
{
    
}

void ConfigGame::setup(CCDictionary* dict)
{
    setupGameState(dict);
    setupPlayer(dict);
    setupEnemy(dict);
    setupBackground(dict);
}

void ConfigGame::setupBackground(CCDictionary* dict)
{
    
}

void ConfigGame::setupPlayer(CCDictionary* dict)
{
    CCDictionary *srcDict = (CCDictionary*)dict->objectForKey("player");
    if (srcDict)
    {
        player = new ConfigPlayer(srcDict);
    }
}

void ConfigGame::setupEnemy(CCDictionary* dict)
{
    
}

void ConfigGame::setupGameState(CCDictionary* dict)
{
    
}

void ConfigGame::setupEnemyPopList(cocos2d::CCDictionary* dict)
{
    
}

void ConfigGame::setupMovePatternList(cocos2d::CCDictionary* dict)
{
    
}



