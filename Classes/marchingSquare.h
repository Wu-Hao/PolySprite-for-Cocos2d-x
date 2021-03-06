//
//  marchingSquare.h
//  meshtest
//
//  Created by WuHao on 15/4/14.
//
//

#ifndef __meshtest__marchingSquare__
#define __meshtest__marchingSquare__

#include <string>
#include <vector>
#include "math/Vec2.h"

class MarchingSquare
{
public:
    MarchingSquare(const std::string &filename, const unsigned int threshold = 0);
    //TODO: should return list of vec2s
    void trace();
//    unsigned int getAlphaAt(const unsigned int i);
//    unsigned int getAlphaAt(int x, int y);
    void setThreshold(unsigned int threshold){_threshold = threshold;};
    unsigned int getThreshold(){return _threshold;};
    unsigned int getVecCount(){return points.size();};
    std::vector<cocos2d::Vec2> getPoints(){return points;};
    void printPoints();
    //using Ramer–Douglas–Peucker algorithm
    void optimize(float level = 0);
    
protected:
    unsigned int findFirstNoneTransparentPixel();
    void marchSquare(int startx, int starty);
    unsigned int getSquareValue(int x, int y);
    unsigned char * data;
    std::string _filename;
    unsigned int width;
    unsigned int height;
    unsigned int _threshold;
    unsigned char getAlphaAt(const unsigned int i);
    unsigned char getAlphaAt(const int x, const int y);
    cocos2d::Vec2 start;
    std::vector<cocos2d::Vec2> points;
    int getIndexFromPos(int x, int y){return y*width+x;};
    cocos2d::Vec2 getPosFromIndex(int i){return cocos2d::Vec2(i%width, i/width);};
    
    float epsilon;
    std::vector<cocos2d::Vec2> rdp(std::vector<cocos2d::Vec2> v);
    float perpendicularDistance(cocos2d::Vec2 i, cocos2d::Vec2 start, cocos2d::Vec2 end);
};

#endif /* defined(__meshtest__marchingSquare__) */
