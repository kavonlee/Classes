#include "TestArmature.h"

//#include <spine/spine-cocos2dx.h>
//#include "spine/spine.h"
//using namespace spine;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    //加载骨骼动画的文件
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/robot.png", "armature/robot.plist", "armature/robot.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml");
    
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/Cowboy0.png", "armature/Cowboy0.plist", "armature/Cowboy.ExportJson");

    Menu * menu=Menu::create();
    for (int i=0; i<3; i++) {
        auto item=MenuItemFont::create("item", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        item->setTag(i);
        menu->addChild(item);
    }
    menu->alignItemsHorizontally();
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(Point(300,200));
    this->addChild(menu);
   
       return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    MenuItemFont* font=(MenuItemFont*)pSender;
    int a=font->getTag();
    switch (a) {
        case 0:
        {
            Armature *armature = Armature::create("Cowboy");
            armature->getAnimation()->play("Fire");
            armature->setScale(0.3);
            armature->getAnimation()->setSpeedScale(0.5);
            armature->setPosition(Point(200,300));
            addChild(armature);
            /*
             * Set armature's movement event callback function
             * To disconnect this event, just setMovementEventCallFunc(nullptr, nullptr);
             */
            armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(HelloWorld::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            
            
            Vec2 p = armature->getBone("Layer126")->getDisplayRenderNode()->convertToWorldSpaceAR(Vec2(0, 0));
            
            auto bullet=Sprite::create("CloseNormal.png");
            bullet->setPosition(p.x + 60, p.y);
            
            bullet->stopAllActions();
            bullet->runAction(CCMoveBy::create(1.5f, Vec2(350, 0)));
            this->addChild(bullet);

        }
            break;
        case 1:
        {
          auto  armature = Armature::create("Dragon");
            armature->getAnimation()->playWithIndex(1);
            armature->setPosition(Point(400,400));
            armature->setScale(0.6f);
            addChild(armature);
            //添加显示
            Skin* skin = Skin::createWithSpriteFrameName("parts-tail.png");
            Skin* skin2 = Skin::createWithSpriteFrameName("parts-head.png");
            auto dic=armature->getBoneDic();
            auto mapKeyVec = dic.keys();
            for(auto key : mapKeyVec)
            {
                log("%s",key.c_str());
            }
            int index = armature->getBone("armR")->getDisplayManager()->getCurrentDisplayIndex();
            log("index=%d",index);
            //tianjia显示
            armature->getBone("armR")->addDisplay(skin, 1);
            armature->getBone("armR")->addDisplay(skin2, 2);

            armature->getBone("armR")->changeDisplayWithIndex(2, true);
            int index2 = armature->getBone("armR")->getDisplayManager()->getCurrentDisplayIndex();
            log("index=%d",index2);
           
        }
            break;
        case 2:
        {
           auto armature = Armature::create("Cowboy");
            armature->getAnimation()->playWithIndex(1);
            armature->setPosition(Point(500,400));
            armature->getAnimation()->setSpeedScale(2);
            armature->setScaleX(-1);
            addChild(armature);
        }
            break;
        default:
            break;
    }
   
}
void HelloWorld::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == LOOP_COMPLETE)
    {
        if (movementID == "Fire")
        {
            ActionInterval *actionToRight = MoveTo::create(2, Vec2(900- 50, 600));
            armature->stopAllActions();
            armature->runAction(Sequence::create(actionToRight, CallFuncN::create( CC_CALLBACK_1(HelloWorld::callback1, this)), nullptr));
            armature->getAnimation()->play("Walk");
        }
        else if (movementID == "FireMax")
        {
            ActionInterval *actionToLeft = MoveTo::create(2, Vec2(  50, 600));
            armature->stopAllActions();
            armature->runAction(Sequence::create(actionToLeft,  CallFuncN::create( CC_CALLBACK_1(HelloWorld::callback2, this)), nullptr));
            armature->getAnimation()->play("Walk");
        }
    }
}

void HelloWorld::callback1(Node* sender)
{
    auto armature=(Armature*)sender;
   armature->runAction(ScaleTo::create(0.3f, 0.24f, 0.24f));
   armature->getAnimation()->play("FireMax", 10);
}
void HelloWorld::callback2(Node* sender)
{
   auto armature=(Armature*)sender;
   armature->runAction(ScaleTo::create(0.3f, -0.24f, 0.24f));
   armature->getAnimation()->play("Fire", 10);
}
 void HelloWorld::onExit()
{
    //释放资源
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/Cowboy.ExportJson");
    ArmatureDataManager::destroyInstance();
    Layer::onExit();
}








