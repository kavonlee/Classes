#include "HelloWorldScene.h"

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
   
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //
    auto bg=Sprite::create("armature/bg.jpg");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    bg->setScale(visibleSize.width/bg->getContentSize().width,visibleSize.height/bg->getContentSize().height);
    this->addChild(bg,0);

    //加载骨骼动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/knight.png","armature/knight.plist","armature/knight.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/weapon.png","armature/weapon.plist","armature/weapon.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/robot.png","armature/robot.plist","armature/robot.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/cyborg.png","armature/cyborg.plist","armature/cyborg.xml");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/Dragon.png","armature/Dragon.plist","armature/Dragon.xml");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/Cowboy0.png","armature/Cowboy0.plist","armature/Cowboy.ExportJson");
    

    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //创建动画
    auto armature = Armature::create("Dragon");
    armature -> getAnimation() ->playWithIndex(1);
    armature -> setPosition(Vec2(200, 300));
    armature -> getAnimation() -> setSpeedScale(1.0);
    armature -> setScale(1.0);
    this -> addChild(armature);
    
//    
    //得到骨骼的字典
    auto dic = armature -> getBoneDic();
    auto mapkeyvec = dic.keys();
    for (auto key:mapkeyvec) {
        log("%s",key.c_str());
    }
    
    //得到眼睛的index
    int index = armature -> getBone("eyeR") -> getDisplayManager() -> getCurrentDisplayIndex();
    log("index = %d",index);
    Skin *skin = Skin::createWithSpriteFrameName("parts-tail.png");
    Skin *skin2 = Skin::createWithSpriteFrameName("parts-head.png");
    
    //添加皮肤 下标依次增长
    armature->getBone("armL")->addDisplay(skin,1);
    armature->getBone("armL")->addDisplay(skin2,2);
    
    //armature -> getBone("armR") -> changeDisplayWithIndex(1, true);
    armature -> getBone("armL") -> changeDisplayWithIndex(2, true);
    
//    int index2 = armature -> getBone("armR") -> getDisplayManager() -> getCurrentDisplayIndex();
    
    
    
}








