#ifndef __SETTJSON_H__
    #define __SETTJSON_H__
    
    #include <string>
    #include "JSON.h"
    #include "cocos2d.h"
    #include "Settings.h"
    
    #define ALL 0
    #define TEXTSMALL 1
    #define TEXTBIG 2
    #define TEXTFONT 3
        
    using namespace std;
    
    USING_NS_CC;
  
    
    class SettingsJSON : virtual public JSON
    {
        public :
            SettingsJSON();
            SettingsJSON(const char*);
            virtual ~SettingsJSON(){};
            void set_json_file (const char*);
            void get(JSON_TYPE js_type);
        private :
            rapidjson::Document document;
    };

#endif /*__SETTJSON_H__*/
