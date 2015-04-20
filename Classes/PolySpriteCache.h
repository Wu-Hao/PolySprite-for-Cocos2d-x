//
//  PolySprite.h
//  meshtest
//
//  Created by WuHao on 15/3/6.
//
//

#ifndef __meshtest__PolySpriteCache__
#define __meshtest__PolySpriteCache__

#include <vector>
#include "2d/CCNode.h"
#include "renderer/CCTrianglesCommand.h"
#include "CCDrawNode.h"


struct PolySpriteInfo
{
    cocos2d::Rect _rect;
    cocos2d::TrianglesCommand::Triangles _triangles;
    cocos2d::Rect _textureRect;
};

typedef std::vector<PolySpriteInfo*> VecPolySpriteInfo;
typedef std::unordered_map<std::string, VecPolySpriteInfo> MapPolySpriteInfo;

class CC_DLL PolySpriteCache: public cocos2d::Ref
{
public:
    virtual ~PolySpriteCache();
    static PolySpriteCache* getInstance();
    static void destroyInstance();
    void   addPolySpriteCache(const std::string& filePath, const PolySpriteInfo& polySpriteInfo);
    PolySpriteInfo* getPolySpriteCache(const std::string& filePath, const cocos2d::Rect& rect);
    void   removePolySpriteCache(const std::string& filePath, const cocos2d::Rect* rect = nullptr);
    void   removeAllPolySpriteCache();
    bool   isPolySpriteCachExist(const std::string& filePath, const cocos2d::Rect& rect);
protected:
    PolySpriteCache();
private:
    void init();
private:
    static PolySpriteCache* _polySpriteCache;
    MapPolySpriteInfo _polySpriteCacheMap;
    
};
#endif /* defined(__meshtest__PolySprite__) */
