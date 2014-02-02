//
//  ShibuyaPlayerShip.h
//  cocos2dx-space-game
//
//  Created by c2:shibuya_shun on 14/02/02.
//
//

#ifndef __cocos2dx_space_game__ShibuyaPlayerShip__
#define __cocos2dx_space_game__ShibuyaPlayerShip__

#include <iostream>
#include "cocos2d.h"
#include "PlayerShip.h"

class BulletSprite;


class ShibuyaPlayerShip    : public PlayerShip
{
public:
    ShibuyaPlayerShip();
    virtual ~ShibuyaPlayerShip();
    
    bool initWithFileName(const char* pszFileName);
    bool initWithFrameName(const char* pframeName, int numFrame = 0);
    void initBullets(cocos2d::CCNode* bulletLayer);
    void start();
    void end();
    virtual void update(float dt);
	virtual void shotBullet();
    void setInvisible(cocos2d::CCNode * node);
    void touchBeganProcess(cocos2d::CCPoint& pos);
    cocos2d::CCPoint getBodySize();
    
    void setDamage();
    
public:
    static ShibuyaPlayerShip* createShip(const char* filename);
    static ShibuyaPlayerShip* createShipFrame(const char* filename, int numFrame);
    
public:
    std::vector<BulletSprite*>  bulletList;
	
	void setLife(int life);
	int getLife();
    
protected:
    cocos2d::CCSprite*  _ship;
    cocos2d::CCString*  _imageName;
    bool                _autoShooting;
    bool                _hasShipAnimation;
    double              _shotInterval;
    double              _lastShotTime;
    
    //    cocos2d::CCArray*   _shipLasers;
    int                 _nextShipLaser;
	
	int _lives;
};

#endif /* defined(__cocos2dx_space_game__ShibuyaPlayerShip__) */
