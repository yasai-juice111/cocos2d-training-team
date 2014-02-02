//
//  PlayerShip.h
//  SpaceGame
//
//  Created by Shinji Hiramatsu on 2014/01/24.
//
//

#ifndef __SpaceGame__PlayerShip__
#define __SpaceGame__PlayerShip__

#include "cocos2d.h"

class BulletSprite;


class PlayerShip    : public cocos2d::CCNode
{
public:
    PlayerShip();
    virtual ~PlayerShip();
    
    bool initWithFileName(const char* pszFileName);
    bool initWithFrameName(const char* pframeName, int numFrame = 0);
    void initBullets(cocos2d::CCNode* bulletLayer);
    void start();
    void end();
    virtual void update(float dt);
	virtual void shotBullet();
    void setInvisible(cocos2d::CCNode * node);
    void removeNode(cocos2d::CCNode* node);
    void touchBeganProcess(cocos2d::CCPoint& pos);
    cocos2d::CCPoint getBodySize();
    cocos2d::CCRect getBoundingBox();
    cocos2d::CCSprite* getBodySprite();
    void stopActions();
    bool hitTheBullet(int damageLevel);
    int getHP() const;
    int getAttackPoint() const;
    virtual void setDamage(cocos2d::CCNode* dispLayer=NULL);
public:
    static PlayerShip* createShip(const char* filename);
    static PlayerShip* createShipFrame(const char* filename, int numFrame);
    
public:
    std::vector<BulletSprite*>  bulletList;
    
protected:
    cocos2d::CCSprite*  _ship;
    cocos2d::CCString*  _imageName;
    bool                _autoShooting;
    bool                _hasShipAnimation;
    bool                _duringBombEffect;
    double              _shotInterval;
    double              _lastShotTime;
    int                 _defaultHP;
    int                 _hp;
    int                 _attackPoint;
    
    //    cocos2d::CCArray*   _shipLasers;
    int                 _nextShipLaser;
};

#endif /* defined(__SpaceGame__PlayerShip__) */
