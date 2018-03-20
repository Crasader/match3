#include "Tokens.h"

void Tokens :: init(){
    switch (color){
        case TRED :
            sprite = cocos2d::Sprite::create("res/3.png",cocos2d::Rect(SIZEPNG * 0 ,
                                                    0,
                                                    SIZEPNG,
                                                    SIZEPNG));
            break;
        case TBLUE:
            sprite = cocos2d::Sprite::create("res/3.png",cocos2d::Rect(SIZEPNG * 1 ,
                                                    0,
                                                    SIZEPNG,
                                                    SIZEPNG));
            break;
        case TGREEN:
            sprite = cocos2d::Sprite::create("res/3.png",cocos2d::Rect(SIZEPNG * 2 ,
                                                    0,
                                                    SIZEPNG,
                                                    SIZEPNG));
            break;
        case TORANGE:
            sprite = cocos2d::Sprite::create("res/3.png",cocos2d::Rect(SIZEPNG * 3,
                                                    0,
                                                    SIZEPNG,
                                                    SIZEPNG));
            break;
        case TPURPLE :
            sprite = cocos2d::Sprite::create("res/3.png",cocos2d::Rect(SIZEPNG * 4,
                                                    0,
                                                    SIZEPNG,
                                                    SIZEPNG));
            break;
        case RANDOM_COLOR :
            break;
        default :
            break;
    };
}

void Tokens :: set_color ( Token_color _color ){
    if ( _color == RANDOM_COLOR ){
        random_device rd;
        mt19937 gen(rd());
        _color = gen()%5 + 1;
    };
    color = _color;
}