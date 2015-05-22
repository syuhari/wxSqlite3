//
//  EncryptSQLite.h
//
//  Created by Akihiro Matsuura on 2015/04/27.
//
//

#ifndef __Syuhari__EncryptSQLite__
#define __Syuhari__EncryptSQLite__

#include "cocos2d.h"

class EncryptSQLite
{
public:
    EncryptSQLite();
    ~EncryptSQLite();
    static EncryptSQLite* getInstance();
    void makeEncryptDatabase();
    
    void selectTest();
protected:

private:
    std::string getDbPath();
};

#endif /* defined(__Syuhari__EncryptSQLite__) */
