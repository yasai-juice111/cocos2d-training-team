//
//  ParallaxChildLayer.h
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __SpaceGame__ParallaxChildLayer__
#define __SpaceGame__ParallaxChildLayer__

#include "cocos2d.h"


class ParallaxChildLayer     : public cocos2d::CCNode
{
public:
    ParallaxChildLayer();
    virtual ~ParallaxChildLayer();
    
    void initWithData(const char* pzFileName, unsigned int z, float scale,
                      const cocos2d::CCPoint& ratio, const cocos2d::CCPoint& offset,
                      cocos2d::CCNode* container);
    
    void update(cocos2d::CCPoint& movePt);

protected:
    unsigned int    _z;
    float           _scale;
    cocos2d::CCPoint    _ratio;
    cocos2d::CCPoint    _offset;
    std::vector<cocos2d::CCSprite*> _childList;
};

#endif /* defined(__SpaceGame__ParallaxChildLayer__) */
