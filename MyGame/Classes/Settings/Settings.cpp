#include "Settings.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "SettingsJSON.h"
#include "LevelJSON.h"

#include "cocos2d.h"
#include <string>

using namespace std;

USING_NS_CC;

Settings :: Settings() {
    CCLOG("Settings");
    
    string stringData = FileUtils::getInstance()->getStringFromFile("json/level.json");
    if (document.Parse(stringData.c_str()).HasParseError()) {
        CCLOG("Json error");
        throw "json";//json_file;
    }
    rapidjson::Value& a = document["Level"];
    quantity_level = a.Size();
    
    CCLOG(" quantity_level %d", quantity_level);
    
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    json = new SettingsJSON();
    try{
    	json->get(ALL);
    }
    catch(SetapSettings json_throw){
    	start_set = json_throw;
    }
    FreeJson();
};

int Settings :: GetQuantityLevel(){
    return quantity_level;
}

void Settings :: SetLvl(int N){
    CCLOG("level %d",N);
    level = "level" + to_string(N);
    if (N != 0){
        N--;
        rapidjson::Value& a = document["Level"];
        assert(a.IsArray());
        json = new LevelJSON (a[N].GetString());
    } else {
        throw ;
    }
}

void Settings :: FreeJson(){
	delete json;
}

