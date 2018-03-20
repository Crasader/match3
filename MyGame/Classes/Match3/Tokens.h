#ifndef __TOKEN_H_
    #define __TOKEN_H_
    
    #ifndef SIZEPNG
        #define SIZEPNG 69 
    #endif 
    
    #include "cocos2d.h"
    #include <random>
    using namespace std;
    
    #define TRED             1
    #define TBLUE            2
    #define TGREEN           3
    #define TORANGE          4
    #define TPURPLE          5
    
    #define RANDOM_COLOR    0
    #define NOT_COLOR       -1
    
    
    typedef int Token_color;
    
    class Tokens {
    public :
        cocos2d::Sprite * sprite;
        cocos2d::Vec2 coordinates ;
        Token_color color;
        
        Tokens() : sprite ( NULL )
        {};
        
        ~Tokens(){
            //if ( sprite not NULL ){
               // removeChild()
        }
        
        void set (int _x, int _y){
            coordinates.x = _x;
            coordinates.y = _y;
        };
        
        void init ();
        void set_color ( Token_color _color = RANDOM_COLOR);

    };
    
#endif /*__TOKEN_H_*/