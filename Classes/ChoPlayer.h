//
//  ChoPlayer.h
//  cocos2dx-space-game
//
//  Created by c7:cho_takumi on 2014/02/01.
//
//

#ifndef __cocos2dx_space_game__ChoPlayer__
#define __cocos2dx_space_game__ChoPlayer__

#include "PlayerShip.h"
#include "BulletSprite.h"

// 弾の出方のバリエーション
enum bulletVariation {
	ONE,
	FOCUS,
	THREE
};

class ChoPlayer : public PlayerShip
{
public:
	ChoPlayer();
	virtual ~ChoPlayer();
	
	virtual void update(float dt);
	virtual void shotBullet();
public:
    static ChoPlayer* createShip(const char* filename);
    static ChoPlayer* createShipFrame(const char* filename, int numFrame);
private:
	void createLaser(BulletSprite *shipLaser, cocos2d::CCSize winSize, float direction, float speed);
	
	// 弾のスピード
	float _bulletSpeed;
	// 弾の出方のバリエーション
	int _bulletVariation;
	// 弾のインターバル
	float bulletInterval;
};

#endif /* defined(__cocos2dx_space_game__ChoPlayer__) */
