//
//  StageScene.h
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __SpaceGame__StageScene__
#define __SpaceGame__StageScene__

#include "cocos2d.h"

class ParallaxLayer;
class PlayerShip;
class EnemyShip;
class ConfigGame;

class StageScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(StageScene);
    
    
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
    
protected:
	cocos2d::CCSpriteBatchNode * _batchNode;
    cocos2d::CCNode*    _enemyLayer;
    cocos2d::CCNode*    _effectLayer;
    cocos2d::CCNode*    _uiLayer;
    ParallaxLayer*  _backgroundNode;
    
    
    // UI View Items
    cocos2d::CCLabelTTF*     _scoreItem;
    cocos2d::CCLabelTTF*     _playerHPItem;
    cocos2d::CCLabelTTF*     _bossHPItem;
    
    // Configuration, data model
    ConfigGame*     _config;
    int             _score;
    int             _playerHP;
    int             _bossHP;
    
    // Work Variable
    int             _nextEnemy;
    double          _nextEnemySpawn;
    
    bool    _touchFlag;
    cocos2d::CCPoint _startTouchPos;
    cocos2d::CCPoint _lastTouchPos;
    cocos2d::CCPoint _moveShipPos;
    
private:
    PlayerShip*  _playerShip;
    std::vector<EnemyShip*>_enemyList;
};

#endif /* defined(__SpaceGame__StageScene__) */
