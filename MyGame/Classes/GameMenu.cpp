#include "GameMenu.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

GameMenu::~GameMenu(){
    if ( button != nullptr){
        delete [] button;
        button = nullptr;
    }
    CCLOG("~GameMenu");
};

Scene* GameMenu::createScene()
{
    return GameMenu::create();
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto sprite = Sprite::create(start_set.background);  
    sprite->setPosition(Vec2(visibleSize.width/2+ origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    auto closeItem = MenuItemImage::create(start_set.Closebegin,
                                           start_set.Closeend,
                                           CC_CALLBACK_1(GameMenu::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    this->init_Menu();
    
    return true;
}

void GameMenu::init_Menu(){
	CCLOG("GameMenu::init_Menu");
    button = new ui::Button *[QBUTTON];
    
    button[0] = ui::Button::create(start_set.png1began, start_set.png1end);
    button[0]->setTitleText("Играть");
    button[0]->setTitleFontName(start_set.font);
    button[0]->setTitleFontSize(start_set.bigtext);
    button[0]->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height/2));
    button[0]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
       	 	case ui::Widget::TouchEventType::ENDED:
                CCLOG("Start Button");
                for(int i = 0; i < QBUTTON; i++){                        
                    this->removeChild(button[i]);
                }
                delete [] button;
                button = nullptr;
                this->switch_level();
                break;
            default:
                break;
        }
    });
    this->addChild(button[0]);

    button[1] = ui::Button::create(start_set.png2began, start_set.png2end);
    button[1]->setTitleText("Список рекордов");
    button[1]->setTitleFontName(start_set.font);
    button[1]->setTitleFontSize(start_set.smalltext);
    button[1]->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height/2 - button[1]->getContentSize().height));
    button[1]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("Lader Button");
            	for(int i = 0; i < QBUTTON; i++){                        
                    this->removeChild(button[i]);
                }
                delete [] button;
                button = nullptr;
                backbutton();
                LaderList();
                break;
            default:
                break;
        }
    });
    this->addChild(button[1]);
}

void GameMenu::LaderList(){
	CCLOG("GameMenu::LaderList");
	int il = GetQuantityLevel();
	scroll = ui::ScrollView::create();
	scroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	scroll->setContentSize(Size(SIZETEXT*start_set.smalltext,visibleSize.height/2));
	scroll->setInnerContainerSize(Size(SIZETEXT*start_set.smalltext,start_set.smalltext*il));
	//scroll->setContentSize(Size(200,200));
	//scroll->setInnerContainerSize(Size(500,1500));
	scroll->setBounceEnabled( true );
	scroll->setAnchorPoint( Vec2(0.5,0.5));
	scroll->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	for(int i = 0; i < il ; i++){
		try{
			auto label = Label::createWithTTF(fWrite.getString(),start_set.font, start_set.smalltext);
			label->setPosition( Vec2(scroll->getContentSize().width/2,
									 scroll->getContentSize().height - i * 50 - 25));
			scroll->addChild(label);
		}
		catch(FWrite::Exceptions end_list){
			break;
		}
		catch(FWrite::Exceptions clean_list){
			return;
		}
	}
	this->addChild(scroll);
}

void GameMenu::switch_level(){
    qButton = GetQuantityLevel();
    if ( qButton == 0){
        SetLvl(0);
    } else {
    
        button = new ui::Button *[qButton];
        for (int i = 0, _y = 0; i < qButton; i++ ){
            button[i] = ui::Button::create(start_set.png3began, start_set.png3end);
            button[i]->setTitleText(to_string(i+1));
            button[i]->setTitleFontName(start_set.font);
		    button[i]->setTitleFontSize(start_set.smalltext);
            
        	int max_x = (visibleSize.height*0.8 )/ button[i]->getContentSize().height ;
            int y = visibleSize.height/4*3 - button[i]->getContentSize().height  * _y;
            int x = visibleSize.width/4 + button[i]->getContentSize().width  * (i%max_x);
            if (i%max_x == max_x-1) _y++;
            button[i]->setPosition(Vec2(x , y));
            button[i]->setTag(i+1);
            button[i]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
                auto but = (ui::Button*)sender;
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        for (int _i = 0; _i < this->qButton; _i++){
                            this->removeChild(button[_i]);
                        }
                        delete [] button;
                        button = nullptr;
                       	SetLvl(but->getTag());
                        backbutton();
                        this->start();
                        break;
                    default:
                        break;
                }
            });
            this->addChild(button[i]);
        }
    }
}

void GameMenu::backbutton(){
    button = new ui::Button * [1];
    button[0] = ui::Button::create(start_set.pngback1, start_set.pngback2);
    button[0]->setTitleText("Меню");
    button[0]->setTitleFontName(start_set.font);
	button[0]->setTitleFontSize(start_set.smalltext);
    button[0]->setPosition(Vec2( origin.x + button[0]->getContentSize().width * 0.5 ,
                                 visibleSize.height - button[0]->getContentSize().height * 0.5 ));
    button[0]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            	if (scroll != nullptr ){
		            this->removeChild(scroll);
            	}            	
	            this->removeChild(button[0]); 
                delete [] button;
                button = nullptr;
                CCLOG("Back Button");
                StopEdit();
                finish();
                init_Menu();
                break;
            default:
                break;
        }
    });
    
    this->addChild(button[0]);
};

void GameMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
