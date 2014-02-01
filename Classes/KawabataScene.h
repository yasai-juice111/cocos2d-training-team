//
//  KawabataScene.h
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 2014/01/26.
//
//

#ifndef __cocos2dx_space_game__KawabataScene__
#define __cocos2dx_space_game__KawabataScene__

#include "StageScene.h"
#include "ParallaxLayer.h"
#include "PlayerShip.h"
//#include "EnemyShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "SimpleAudioEngine.h"

#include "KawabataEnemy.h"

// クラス定義必要？
class ParallaxLayer;
class PlayerShip;
//class EnemyShip;
class KawabataEnemy;

class KawabataScene : public StageScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(KawabataScene);
    
    virtual void update(float dt);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void setInvisible(cocos2d::CCNode * node);
    virtual float randomValueBetween(float low, float high);
private:
    PlayerShip* _playerShip;
	cocos2d::CCSpriteBatchNode * _batchNode;
    cocos2d::CCNode*    _enemyLayer;
    ParallaxLayer*  _backgroundNode;
    
    std::vector<KawabataEnemy*>_enemyList;
    
    int             _nextEnemy;
    double          _nextEnemySpawn;
    
    bool    _touchFlag;
    cocos2d::CCPoint _startTouchPos;
    cocos2d::CCPoint _lastTouchPos;
    cocos2d::CCPoint _moveShipPos;
};

#endif /* defined(__cocos2dx_space_game__KawabataScene__) */
