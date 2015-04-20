//
//  PolySpriteCache.cpp
//  meshtest
//
//  Created by WuHao on 15/3/6.
//
//

#include "PolySpriteCache.h"
#include "3d/CCMesh.h"
#include "3d/CCMeshVertexIndexData.h"

#include "marchingSquare.h"

#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include <vector>

#include "poly2tri/poly2tri.h"
#include "platform/CCFileUtils.h"
using namespace std;

USING_NS_CC;

PolySpriteCache* PolySpriteCache::_polySpriteCache = nullptr;

PolySpriteCache::PolySpriteCache()
{
    
}

PolySpriteCache::~PolySpriteCache()
{
}

PolySpriteCache* PolySpriteCache::getInstance()
{
    if (NULL == _polySpriteCache)
    {
        _polySpriteCache = new (std::nothrow) PolySpriteCache();
        _polySpriteCache->init();
    }
    return _polySpriteCache;
}

void PolySpriteCache::destroyInstance()
{
    CC_SAFE_DELETE(_polySpriteCache);
}

void PolySpriteCache::init()
{
    
}

void PolySpriteCache::addPolySpriteCache(const std::string& filePath, const PolySpriteInfo& polySpriteInfo)
{
    auto fullpath = filePath;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() != it)
    {
        VecPolySpriteInfo vecInfo = it->second;
        
        auto infoIt = vecInfo.begin();
        for (; infoIt != vecInfo.end(); infoIt++)
        {
            if ((*infoIt)->_rect.equals(polySpriteInfo._rect))
            {
                (*infoIt)->_triangles = polySpriteInfo._triangles;
                (*infoIt)->_textureRect = polySpriteInfo._textureRect;
                return;
            }
        }
    }
    
    VecPolySpriteInfo vecInfo;
    vecInfo.clear();
    PolySpriteInfo* info = new (std::nothrow)PolySpriteInfo;
    if (nullptr != info)
    {
        info->_rect = polySpriteInfo._rect;
        
        info->_triangles.verts = new V3F_C4B_T2F[polySpriteInfo._triangles.vertCount];
        info->_triangles.indices = new unsigned short[polySpriteInfo._triangles.indexCount];
        info->_triangles.vertCount = polySpriteInfo._triangles.vertCount;
        info->_triangles.indexCount =polySpriteInfo._triangles.indexCount;
        
        memcpy(info->_triangles.verts, polySpriteInfo._triangles.verts, polySpriteInfo._triangles.vertCount*sizeof(V3F_C4B_T2F));
        memcpy(info->_triangles.indices, polySpriteInfo._triangles.indices, polySpriteInfo._triangles.indexCount*sizeof(unsigned short));
        info->_textureRect = polySpriteInfo._textureRect;
        
        vecInfo.push_back(info);
        _polySpriteCacheMap[filePath] = vecInfo;
    }
}

PolySpriteInfo* PolySpriteCache::getPolySpriteCache(const std::string& filePath, const cocos2d::Rect& rect)
{
    auto fullpath = filePath;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return nullptr;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return *infoIter;
    }
    
    return nullptr;
}

void   PolySpriteCache::removePolySpriteCache(const std::string& filePath, const cocos2d::Rect* rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return;
    
    if (nullptr == rect)
    {
        
    }
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        
    }
    
    return;
}

void   PolySpriteCache::removeAllPolySpriteCache()
{
    
}

bool PolySpriteCache::isPolySpriteCachExist(const std::string& filePath, const cocos2d::Rect& rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return false;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return false;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return true;
    }
    
    return false;
}

USING_NS_CC;
