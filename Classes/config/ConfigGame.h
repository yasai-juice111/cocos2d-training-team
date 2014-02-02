//
//  ConfigGame.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigGame__
#define __cocos2dx_space_game__ConfigGame__

#include "cocos2d.h"

class ConfigBackground;
class ConfigPlayer;
class ConfigEnemy;
class ConfigGameState;
class ConfigEnemyPopData;
class ConfigMovePattern;

class ConfigGame
{
public:
    ConfigGame(cocos2d::CCDictionary* dict=NULL);
    virtual ~ConfigGame();
    virtual void setup(cocos2d::CCDictionary* dict);

private:
    void setupBackground(cocos2d::CCDictionary* dict);
    void setupPlayer(cocos2d::CCDictionary* dict);
    void setupEnemy(cocos2d::CCDictionary* dict);
    void setupEnemyPopList(cocos2d::CCDictionary* dict);
    void setupMovePatternList(cocos2d::CCDictionary* dict);
    void setupGameState(cocos2d::CCDictionary* dict);

public:
    ConfigGameState*    gameState;
    ConfigPlayer*       player;
    std::vector<ConfigBackground*>  background;
    std::vector<ConfigEnemy*>       enemy;
    std::vector<ConfigEnemyPopData*>    enemyPopList;
    std::vector<ConfigMovePattern*> movePatterList;
};

#endif /* defined(__cocos2dx_space_game__ConfigGame__) */
