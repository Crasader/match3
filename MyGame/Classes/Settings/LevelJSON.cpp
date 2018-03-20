#include "LevelJSON.h"
#include "rapidjson/error/en.h"
#include "Settings.h"

USING_NS_CC;

LevelJSON :: LevelJSON(const char* json_dok) :
    iterator(0)
{
    set_json_file(json_dok);
};

void LevelJSON :: set_json_file ( const char* json_dok){
    string stringData = FileUtils::getInstance()->getStringFromFile(json_dok);
    if (document.Parse(stringData.c_str()).HasParseError()) {
        CCLOG("Json error!!! %s", rapidjson::GetParseError_En(document.GetParseError()));
        //throw "json";//json_file;
    }
}

void LevelJSON :: get(JSON_TYPE js_type){
    switch(js_type){
		case MAP :
			{
		    	rapidjson::Value& a = document["mass"];
		    	assert(a.IsArray());
			    if (iterator == SIZE_C * SIZE_C){
			        iterator = 0;
			    }
			    throw  a[iterator++].GetBool();
			}
		case TIMEVALL :
		    throw  document["timevall"].GetInt();
		case POINT :
		    throw  document["points"].GetInt();
		case ACT :
		    throw  document["act"].GetInt();
		default :
			return ;
	}
}
