//
//  HiramatsuScene.h
//  cocos2dx-space-game
//
//  Created by CyberAgent on H.26/01/31.
//
//

#ifndef __cocos2dx_space_game__HiramatsuScene__
#define __cocos2dx_space_game__HiramatsuScene__

#include "StageScene.h"
#include "cocos2d.h"

class ParallaxLayer;
class PlayerShip;
class EnemyShip;
//class ConfigGame;

class HiramatsuScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HiramatsuScene);
    
    
    virtual void update(float dt);
    virtual void checkPopupEnemy();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    virtual void createUIItems();
    virtual void doBombEffect(cocos2d::CCPoint pos, cocos2d::CCNode* dispLayer);
    virtual bool damagePlayer(EnemyShip* fromEnemy);
    virtual void damageEnemy(EnemyShip* enemy);
    
    float getDispWinRatio();
    float getDispResolution();
    void setInvisible(cocos2d::CCNode * node);
    void removeNode(cocos2d::CCNode* node);
    float randomValueBetween(float low, float high);
    
private:
    PlayerShip*  _playerShip;
	cocos2d::CCSpriteBatchNode * _batchNode;
    cocos2d::CCNode*    _enemyLayer;
    cocos2d::CCNode*    _effectLayer;
    cocos2d::CCNode*    _uiLayer;
    ParallaxLayer*  _backgroundNode;
        
    std::vector<EnemyShip*>_enemyList;
    
    // UI View Items
    cocos2d::CCLabelTTF*     _scoreItem;
    cocos2d::CCLabelTTF*     _playerHPItem;
    cocos2d::CCLabelTTF*     _bossHPItem;
    
    // Configuration, data model
//    ConfigGame*     _config;
    int             _score;
    int             _playerHP;
    int             _bossHP;
    
    // Work Variable
    int             _nextEnemy;
    double          _nextEnemySpawn;
    bool            _duringPlayerBombEffect;
    
    bool    _touchFlag;
    cocos2d::CCPoint _startTouchPos;
    cocos2d::CCPoint _lastTouchPos;
    cocos2d::CCPoint _moveShipPos;
};

#endif /* defined(__cocos2dx_space_game__HiramatsuScene__) */
