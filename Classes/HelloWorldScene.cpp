#include "HelloWorldScene.h"
#include "EncryptSQLite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // make encrypt database
    EncryptSQLite::getInstance()->makeEncryptDatabase();
    
    auto label = Label::createWithTTF("SELECT", "fonts/arial.ttf", 30);
    auto item = MenuItemLabel::create(label, [](Ref* sender){
        // select test
        EncryptSQLite::getInstance()->selectTest();
    });
    auto menu = Menu::create();
    menu->addChild(item);
    this->addChild(menu);
    
    
    return true;
}
