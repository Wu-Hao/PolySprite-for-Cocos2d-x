//
//  PolySprite.h
//  meshtest
//
//  Created by WuHao on 15/3/6.
//
//

#ifndef __meshtest__PolySprite__
#define __meshtest__PolySprite__

#include <vector>
#include "2d/CCNode.h"
#include "renderer/CCTrianglesCommand.h"
#include "CCDrawNode.h"
#include "PolySpriteCache.h"


//class Mesh;
//class Texture2D;
//class Color4B;
//class MeshData;

class PolySprite : public cocos2d::Node
{
public:
    //create with manually created vertices, color and uv and
    static PolySprite *create(const std::string&, std::vector<cocos2d::V3F_C4B_T2F>&, std::vector<unsigned short>&);
    bool initWithVerts(const std::string&, std::vector<cocos2d::V3F_C4B_T2F>&, std::vector<unsigned short>&);

    //create from list of vertices, with texture rect, and triangle indices, UV is calculated from the texture rect
    static PolySprite *create(const std::string&, std::vector<cocos2d::Vec2>&, std::vector<unsigned short>&, const cocos2d::Rect& rect = cocos2d::Rect::ZERO, bool rotated = false);
    bool initWithRect(const std::string&, std::vector<cocos2d::Vec2>&, std::vector<unsigned short>&, const cocos2d::Rect&, bool);
    
//    //create from ordered list of vertices, with texture rect, and rotated property, Triangles and UV is calculated on the fly
    static PolySprite *create(const std::string&, std::vector<cocos2d::Vec2>&,  const cocos2d::Rect& rect = cocos2d::Rect::ZERO, bool rotated = false);
    bool initWithPoly2tri(const std::string&, std::vector<cocos2d::Vec2>&,  const cocos2d::Rect&, bool);
    
    //create from a texture (rect), and automatically trace and optimize the points.
    //not recommended for production, its better to use the vec2 list for better performance
    static PolySprite *create(const std::string&, const cocos2d::Rect& rect = cocos2d::Rect::ZERO, unsigned short optimization = 1);
    bool initWithMarching(const std::string &file, const cocos2d::Rect &rect, unsigned short optimization);
    bool initWithCache(const std::string &file, const PolySpriteInfo *info);
    
    bool init(cocos2d::Texture2D *texture, const cocos2d::Rect &rect = cocos2d::Rect::ZERO);
    
    virtual void setTexture(const std::string &filename );
    virtual void setTexture(cocos2d::Texture2D *texture);
    
    /** returns the Texture2D object used by the sprite */
    virtual cocos2d::Texture2D* getTexture(){return _texture;};
    const float getArea();
    const unsigned int getTrianglesCount(){return _indices.size()/3;};
protected:
    #if CC_SPRITE_DEBUG_DRAW
        cocos2d::DrawNode *_debugDrawNode;
        void debugDraw();
    #endif //CC_SPRITE_DEBUG_DRAW
    
    bool                                    _triangleDirty; //if triangle is dirty, then it needs to be recalculated from verts and indices
    bool                                    _rectRotated;
    std::vector<cocos2d::V3F_C4B_T2F>       _verts;
    std::vector<unsigned short>             _indices;
    cocos2d::TrianglesCommand               _tcmd;
    cocos2d::BlendFunc                      _blendFunc;
    cocos2d::TrianglesCommand::Triangles    _triangles;
    cocos2d::Texture2D                     *_texture;
    cocos2d::Rect                           _textureRect;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    //======Triangulation
    void triangulate(std::vector<cocos2d::Vec2> & verts);
    cocos2d::Rect setContentSizeFromVecs(std::vector<cocos2d::Vec2>& verts);
    
    
    //TODO: move those to ccUtils

};

#endif /* defined(__meshtest__PolySprite__) */
