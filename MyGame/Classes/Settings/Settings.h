#ifndef __SETINGS_H__
    #define __SETINGS_H__
    
    #include "cocos2d.h"
    #include "LevelJSON.h"
    #include "FileWrite/FWrite.h"
    
    #define SETTINGS
    #define SIZEPNG 69
    #define SIZE_C 8
    
    struct SetapSettings {
    	string font;
    	int bigtext;
    	int smalltext;
    	string png1began;
    	string png1end;
    	string png2began;
    	string png2end;
    	string png3began;
    	string png3end;
    	string Closebegin;
    	string Closeend;
    	string background;
    	string pngback1;
    	string pngback2;    	
    };
    
    class Settings 
    {
        public :
            cocos2d::Vec2 origin;
            cocos2d::Size visibleSize;
            Settings();
            virtual ~Settings(){CCLOG("~Settings");};
            void SetLvl(int);
            int GetQuantityLevel();
            
            void get_settings_for_game();
        protected :
            string level;
            FWrite fWrite;
            JSON * json;
            void FreeJson();
            SetapSettings start_set;
        private :
            unsigned int quantity_level;
            rapidjson::Document document;
    };
    
#endif /*__SETINGS_H__*/
