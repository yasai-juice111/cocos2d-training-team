//
//  ChoScene.h
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 14/02/02.
//
//

#ifndef __cocos2dx_space_game__ChoScene__
#define __cocos2dx_space_game__ChoScene__

#include "StageScene.h"
#include "ParallaxLayer.h"
#include "PlayerShip.h"
#include "BulletSprite.h"
#include "TimeUtils.h"
#include "SimpleAudioEngine.h"

#include "ChoEnemy.h"
#include "ChoPlayer.h"

// クラス定義必要？
class ParallaxLayer;
class PlayerShip;
class ChoEnemy;

class ChoScene : public StageScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(ChoScene);
    
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
	ChoPlayer* _playerShip;
	// 敵機
    std::vector<ChoEnemy*>_enemyList;
};


#endif /* defined(__cocos2dx_space_game__ChoScene__) */
