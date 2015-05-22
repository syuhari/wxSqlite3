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
    
    // select test
    EncryptSQLite::getInstance()->selectTest();
    
    return true;
}
