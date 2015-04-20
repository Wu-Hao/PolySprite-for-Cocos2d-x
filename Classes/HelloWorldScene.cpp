#include "HelloWorldScene.h"
#include "PolySprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /*
     ========= 测试看这边 ========
     
     测试只要替换这个图片名字就行了 */
    auto filename = "polytest2.png";
    // 效果图太小，那就放大看看，如果太大装不下，就缩小看看
    // 图片尽量放大，填满整个屏幕
    auto 缩放比例 = 10;
    
    
    
    // ====== 以下就不用动了 ========
    
    
    
    Layer::init();
    Size wsize = Director::getInstance()->getVisibleSize();
    Director::getInstance()->setClearColor(Color4F::WHITE);
    Sprite *s;
    for(int i = 0; i < 50; i++)
    {
        ProfilingBeginTimingBlock("创建50个CCSprite");
        s = Sprite::create(filename);
        ProfilingEndTimingBlock("创建50个CCSprite");
    }
    PolySprite *sp;
    for(int i = 0; i < 50; i++)
    {
        ProfilingBeginTimingBlock("创建50个多边形Sprite");
        sp = PolySprite::create(filename);
        ProfilingEndTimingBlock("创建50个多边形Sprite");
    }
    CCLOG("==== 开始截图：%s ====", filename);
    Profiler::getInstance()->displayTimers();
    sp->setScale(缩放比例);
    sp->getTexture()->setAliasTexParameters();
    
    sp->setPosition(wsize.width/2, wsize.height/2);
    
    auto mouse = EventListenerTouchOneByOne::create();
    mouse->onTouchBegan = [&](Touch* touch, Event* event){
        down = true;
        return 1;
    };
    mouse->onTouchMoved = [=](Touch* touch, Event* event){
        if(down)
        {
            auto pos = touch->getDelta();
            sp->setScale(sp->getScale()+pos.x*0.2);
        }
    };
    mouse->onTouchEnded = [&](Touch* touch, Event* event){
        down = false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse, sp);
    
    addChild(sp);
    float size = sp->getContentSize().width*sp->getContentSize().height;
    CCLOG("pixels: %.2f / %.2f, saved by %.2f%%, with %d triangles", sp->getArea(), size, (1-(sp->getArea()/size))*100.0, sp->getTrianglesCount());
    return true;
}