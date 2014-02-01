//
//  ShibuyaBossShip.h
//  cocos2dx-space-game
//
//  Created by Shun SHIBUYA on 14/02/01.
//
//

#ifndef __cocos2dx_space_game__ShibuyaBossShip__
#define __cocos2dx_space_game__ShibuyaBossShip__

#include <iostream>
#include "cocos2d.h"
#include "PlayerShip.h"

class BulletSprite;


class ShibuyaBossShip    : public PlayerShip
{
public:
    ShibuyaBossShip();
    virtual ~ShibuyaBossShip();
    
    bool initWithFileName(const char* pszFileName);
    bool initWithFrameName(const char* pframeName, int numFrame = 0);
    void initBullets(cocos2d::CCNode* bulletLayer);
    void start();
    void end();
    void update(float dt);
    void shotBullet();
    void setInvisible(cocos2d::CCNode * node);
    void touchBeganProcess(cocos2d::CCPoint& pos);
    cocos2d::CCPoint getBodySize();
    
    void setDamage();
	
	float getPositionDx();
	float getPositionDy();
	void turnPositionDx();
	void turnPositionDy();
	
public:
    static ShibuyaBossShip* createShip(const char* filename);
    static ShibuyaBossShip* createShipFrame(const char* filename, int numFrame);
    
public:
    std::vector<BulletSprite*>  bulletList;
	
	void setLife(int life);
	int getLife();
    
private:
    cocos2d::CCSprite*  _ship;
    cocos2d::CCString*  _imageName;
    bool                _autoShooting;
    bool                _hasShipAnimation;
    double              _shotInterval;
    double              _lastShotTime;
	
	float positionDx;
	float positionDy;
	
	int _lives;
    
	//    cocos2d::CCArray*   _shipLasers;
    int                 _nextShipLaser;
};

#endif /* defined(__cocos2dx_space_game__ShibuyaBossShip__) */
