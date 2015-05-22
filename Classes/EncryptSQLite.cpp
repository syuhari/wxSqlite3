//
//  EncryptSQLite.cpp
//
//  Created by Akihiro Matsuura on 2015/04/27.
//
//

#include "EncryptSQLite.h"
#include "sqlite3.h"

USING_NS_CC;
using namespace std;

#define DB_FILE_NAME "data.sqlite"
#define DB_RESOURCE_SQL_FILE "data/data.sql"
#define DB_PASSPHRASE "pass_phrase"

static EncryptSQLite* m_instance = nullptr;

EncryptSQLite::EncryptSQLite()
{

}

EncryptSQLite::~EncryptSQLite()
{
    
}

EncryptSQLite* EncryptSQLite::getInstance()
{
    if (!m_instance) {
        m_instance = new EncryptSQLite();
    }
    return m_instance;
}

string EncryptSQLite::getDbPath()
{
    string path = "";
    path += FileUtils::getInstance()->getWritablePath();
    path += DB_FILE_NAME;
    CCLOG("getDbPath: %s", path.c_str());
    return path;
}

void EncryptSQLite::makeEncryptDatabase()
{
    string dbpath = getDbPath();
    
    if(FileUtils::getInstance()->isFileExist(dbpath.c_str())) {
        CCLOG("db file exists");
        return;
    }
    
    sqlite3 *database = NULL;
    if ((sqlite3_open(dbpath.c_str(), &database) != SQLITE_OK)) {
        sqlite3_close(database);
        CCLOG("database open error");
        return;
    }
    sqlite3_key(database, DB_PASSPHRASE, (int)strlen(DB_PASSPHRASE));
    
    std::string path = FileUtils::getInstance()->fullPathForFilename(DB_RESOURCE_SQL_FILE);
    std::string sql = FileUtils::getInstance()->getStringFromFile(path);
    CCLOG("SQL path : %s", path.c_str());
    CCLOG("CREATE SQL: %s", sql.c_str());
    
    if (sqlite3_exec(database, sql.c_str(), 0, 0, NULL)==SQLITE_OK) {
        CCLOG("create tables and insert data done");
    } else {
        CCLOG("error create sql, %s", sqlite3_errmsg(database));
    }
    
    sqlite3_close(database);
}

void EncryptSQLite::selectTest()
{
    std::string path = this->getDbPath();
    
    // select data
    sqlite3 *database = nullptr;
    if ((sqlite3_open(path.c_str(), &database) != SQLITE_OK)) {
        sqlite3_close(database);
    } else {
        sqlite3_key(database, DB_PASSPHRASE, (int)strlen(DB_PASSPHRASE));
        
        sqlite3_stmt *stmt = nullptr;
        
        std::string sql = "SELECT value FROM sample WHERE key='exp'";
        if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                int value = sqlite3_column_int(stmt, 0);
                CCLOG("value = %d", value);
                
                std::string message = StringUtils::format("exp = %d", value);
                MessageBox(message.c_str(), "select test");
            } else {
                CCLOG("error , error=%s", sqlite3_errmsg(database));
            }
        } else {
            CCLOG("error prepared select");
        }
        
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(database);
    }
}
