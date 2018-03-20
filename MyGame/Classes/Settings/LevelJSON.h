#ifndef __LEVLJSON_H__
    #define __LEVLJSON_H__
    
    #include <string>
    #include "JSON.h"
    #include "cocos2d.h"
    
    #define MAP 0
    #define TIMEVALL 1
    #define POINT 2
    #define ACT 3
    
    using namespace std;
    
    USING_NS_CC;
    
    class LevelJSON : virtual public JSON
    {
        public :
            LevelJSON() :
                iterator(0)
            {};
            LevelJSON(const char*);
            virtual ~LevelJSON(){};
            void set_json_file (const char*);
            void get(JSON_TYPE);
        private :
            rapidjson::Document document;
            int iterator;
    };

#endif /*__LEVLJSON_H__*/
