#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Match3/Glass.h"
#include "ui/CocosGUI.h"

#define QBUTTON 2
#define SIZETEXT (5+2+1+10+1+4)
class GameMenu : public Glass
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    GameMenu() : qButton(0),
    			 button(nullptr),
    			 scroll(nullptr)
    {CCLOG("Gamemenu");};
    virtual ~GameMenu();
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);
private :
	ui::ScrollView * scroll;
    ui::Button ** button;
	int qButton;
	
    void init_Menu();

    void LaderList();
    void switch_level();

    void backbutton();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
