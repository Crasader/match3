#include "SettingsJSON.h"
#include "rapidjson/error/en.h"
#include "Settings.h"

USING_NS_CC;

SettingsJSON :: SettingsJSON(){
	set_json_file("json/settings.json");
}

SettingsJSON :: SettingsJSON(const char* json_dok){
    set_json_file(json_dok);
}

void SettingsJSON :: set_json_file ( const char* json_dok){
    string stringData = FileUtils::getInstance()->getStringFromFile(json_dok);
    if (document.Parse(stringData.c_str()).HasParseError()) {
        CCLOG("Json error!!! %s", rapidjson::GetParseError_En(document.GetParseError()));
        
    }
}

void SettingsJSON :: get(JSON_TYPE js_type){
	switch(js_type){
		case ALL :
			{
				//assert(document["text"].IsObject());
				SetapSettings buf;
				buf.smalltext = document["text"]["smalltext"].GetInt();
				buf.bigtext = document["text"]["bigtext"].GetInt();
				buf.font = document["text"]["font"].GetString();
				
				buf.png1began = document["button"]["png1began"].GetString();
				buf.png1end = document["button"]["png1end"].GetString();
				buf.png2began = document["button"]["png2began"].GetString();
				buf.png2end = document["button"]["png2end"].GetString();
				
				buf.png3began = document["button"]["png3began"].GetString();
				buf.png3end = document["button"]["png3began"].GetString();
				
				buf.pngback1 = document["button"]["pngback2"].GetString();
				buf.pngback2 = document["button"]["pngback2"].GetString();
				buf.Closebegin = document["button"]["Closebegin"].GetString();
				buf.Closeend = document["button"]["Closeend"].GetString();
				buf.background = document["background"].GetString();
				
				throw buf;
			}
		case TEXTSMALL :
			{
				rapidjson::Value& a = document["text"];
				assert(a.IsObject());
				throw a["smalltext"].GetInt();
			}
		case TEXTBIG :
			{
				rapidjson::Value& a = document["text"];
				assert(a.IsObject());
				throw a["bigtext"].GetInt();
			}
		case TEXTFONT :
			{
				rapidjson::Value& a = document["text"];
				assert(a.IsObject());
				throw a["font"].GetString();
			}
	}
}
