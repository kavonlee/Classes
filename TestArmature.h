#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
    virtual void onExit();
    void animationEvent(Armature *armature,MovementEventType movementType, const std::string& movementID);
    void callback1(Node* sender);
    void callback2(Node* sender);
};
#endif // __HELLOWORLD_SCENE_H__
