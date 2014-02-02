//
//  EnemyShip.h
//  SpaceGame
//
//  Created by Shinji Hiramatsu on 2014/01/24.
//
//

#ifndef __SpaceGame__EnemyShip__
#define __SpaceGame__EnemyShip__

#include "cocos2d.h"

class BulletSprite;

class EnemyShip    : public cocos2d::CCNode
{
public:
    EnemyShip();
    virtual ~EnemyShip();
    
    bool initWithFileName(const char* pszFileName);
    bool initWithFrameName(const char* pframeName, int numFrame = 0);
    void initBullets(cocos2d::CCNode* bulletLayer);
    void start();
    void end();
    void reset();
    void update(float dt);
    void shotBullet();
    void setInvisible(cocos2d::CCNode * node);
    void touchBeganProcess(cocos2d::CCPoint& pos);
    float getMoveSpeed();
    void setMoveSpeed(float speed);
    void stopActions();
    bool isActive();
    bool hitTheBullet(int damageLevel);
    cocos2d::CCRect getBoundingBox();
    cocos2d::CCSprite* getBodySprite();
    void setAttacked();
    void setDamage();
    int getPlayerDamageLevel() const;
    int getHP() const;
    int getDefeatedPoint() const;
    
public:
    static EnemyShip* createShip(const char* filename);
    static EnemyShip* createShipFrame(const char* filename, int numFrame);
    
public:
    std::vector<BulletSprite*>  bulletList;
    
protected:
    cocos2d::CCSprite*  _ship;
    cocos2d::CCString*  _imageName;
    bool                _autoShooting;
    bool                _attacked;
    double              _shotInterval;
    double              _lastShotTime;
    float               _moveSpeed;
    int                 _defaultHP;
    int                 _hp;
    int                 _playerDamageLevel;
    int                 _defeatedPoint;
    
    int                 _nextShipLaser;
};


#endif /* defined(__SpaceGame__EnemyShip__) */
