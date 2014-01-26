//
//  StageScene.h
//  SpaceGame
//
//  Created by shiramat on H.26/01/15.
//
//

#ifndef __SpaceGame__StageScene__
#define __SpaceGame__StageScene__

#include "cocos2d.h"

class ParallaxLayer;
class PlayerShip;
class EnemyShip;

class StageScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(StageScene);


    virtual void update(float dt);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void setInvisible(cocos2d::CCNode * node);
    float randomValueBetween(float low, float high);
    
private:
    PlayerShip*  _playerShip;
	cocos2d::CCSpriteBatchNode * _batchNode;
    cocos2d::CCNode*    _enemyLayer;
    ParallaxLayer*  _backgroundNode;
    
    std::vector<EnemyShip*>_enemyList;
    
    int             _nextEnemy;
    double          _nextEnemySpawn;

    bool    _touchFlag;
    cocos2d::CCPoint _startTouchPos;
    cocos2d::CCPoint _lastTouchPos;
    cocos2d::CCPoint _moveShipPos;
    

    
};

#endif /* defined(__SpaceGame__StageScene__) */
