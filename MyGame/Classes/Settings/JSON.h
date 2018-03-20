#ifndef __JSON_H__
    #define __JSON_H__
    
    #include "../rapidjson/document.h"
    
    typedef int JSON_TYPE;
       
    class JSON 
    {
        public :
            JSON(){};
            JSON(const char *){};
            virtual ~JSON(){};
            virtual void set_json_file ( const char* ) = 0;
            virtual void get(JSON_TYPE) = 0;
        protected:
    };
    
#endif /*__LEVLJSON_H__*/

