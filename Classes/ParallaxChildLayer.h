//
//  ParallaxChildLayer.h
//  SpaceGame
//
//  Created by shiramat on H.26/01/25.
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

private:
    unsigned int    _z;
    float           _scale;
    cocos2d::CCPoint    _ratio;
    cocos2d::CCPoint    _offset;
    std::vector<cocos2d::CCSprite*> _childList;
};

#endif /* defined(__SpaceGame__ParallaxChildLayer__) */
