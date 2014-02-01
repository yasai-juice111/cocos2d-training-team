//
//  KawabataEnemy.h
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//

#ifndef __cocos2dx_space_game__KawabataEnemy__
#define __cocos2dx_space_game__KawabataEnemy__

#include "EnemyShip.h"

class KawabataEnemy : public EnemyShip
{
public:
	KawabataEnemy();
	virtual ~KawabataEnemy();
	
	// 更新処理（弾の頻度調整）
	virtual void update(float dt);
	// 弾を打つ(弾の方向調整)
	virtual void shotBullet();
	
public:
    static KawabataEnemy* createShip(const char* filename);
    static KawabataEnemy* createShipFrame(const char* filename, int numFrame);
	
private:
	void createLaser(BulletSprite *shipLaser, cocos2d::CCSize winSize, int direction);
	int bulletDirection;
	float bulletInterval;
};



#endif /* defined(__cocos2dx_space_game__KawabataEnemy__) */
