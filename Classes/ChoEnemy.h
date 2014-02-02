//
//  ChoEnemy.h
//  cocos2dx-space-game
//
//  Created by c7:cho_takumi on 2014/02/01.
//
//

#ifndef __cocos2dx_space_game__ChoEnemy__
#define __cocos2dx_space_game__ChoEnemy__

#include "EnemyShip.h"

class ChoEnemy : public EnemyShip
{
public:
	ChoEnemy();
	virtual ~ChoEnemy();
	
	// 更新処理（弾の頻度調整）
	virtual void update(float dt);
	// 弾を打つ(弾の方向調整)
	virtual void shotBullet();
	
public:
    static ChoEnemy* createShip(const char* filename);
    static ChoEnemy* createShipFrame(const char* filename, int numFrame);
	
private:
	void createLaser(BulletSprite *shipLaser, cocos2d::CCSize winSize, int direction);
	int bulletDirection;
	float bulletInterval;
};



#endif /* defined(__cocos2dx_space_game__ChoEnemy__) */
