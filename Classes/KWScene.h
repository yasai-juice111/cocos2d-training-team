//
//  KWScene.h
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 2014/01/26.
//
//

#ifndef __cocos2dx_space_game__KWScene__
#define __cocos2dx_space_game__KWScene__

#include "StageScene.h"
#include "ParallaxLayer.h"
#include "PlayerShip.h"
//#include "EnemyShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "SimpleAudioEngine.h"

#include "KWEnemy.h"
#include "KWPlayer.h"

// クラス定義必要？
class ParallaxLayer;
class PlayerShip;
//class EnemyShip;
class KWEnemy;

class KWScene : public StageScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(KWScene);
    
    virtual void update(float dt);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void setInvisible(cocos2d::CCNode * node);
    virtual float randomValueBetween(float low, float high);
private:
	// Playerの当たり判定を見る
	void judgePlayerHit();
	// Enemyの当たり判定を見る
	void judgeEnemyHit();
	// Plyaer
	KWPlayer* _playerShip;
	// 敵機
    std::vector<KWEnemy*>_enemyList;
};

#endif /* defined(__cocos2dx_space_game__KWScene__) */
