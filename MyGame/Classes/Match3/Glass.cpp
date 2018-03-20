
#include "Glass.h"
#include "base/CCEventKeyboard.h"
#include "FileWrite/FWrite.h"
#ifndef SETTINGS
        #define SIZEPNG 69
#endif

USING_NS_CC;

void Glass::onMouseDown(cocos2d::Event *event)
{
    EventMouse* eventM = (EventMouse*)event;
    Vec2 position;
    position.x = eventM->getCursorX();
    #ifndef SETTINGS
        position.y = eventM->getCursorY() + Director::getInstance()->getVisibleSize().height;
    #else
         position.y = eventM->getCursorY() + visibleSize.height;
    #endif
    
    int i = -1, j = -1;
    for (int _j = 0; _j < SIZE_C; _j++){
        if (position.x < container[0][_j].coordinates.x + SIZEPNG / 2 and
            position.x > container[0][_j].coordinates.x - SIZEPNG / 2)
        {
            j = _j;
            break;
        };    
    }
    for (int _i = 0; _i < SIZE_C; _i++){
        if (position.y < container[_i][0].coordinates.y + SIZEPNG / 2 and
            position.y > container[_i][0].coordinates.y - SIZEPNG / 2)
        {
            i = _i;
            break;
        };    
    }
    
    
    if (i != -1 and j != -1){
        if ( container[i][j].color == NOT_COLOR){
            delete Clic.FirstClic;
            Clic.FirstClic = NULL;
            return;
        }
        if ( Clic.FirstClic != NULL )
        {
            if( (Clic.FirstClic->x == j - 1 and Clic.FirstClic->y == i) or
                (Clic.FirstClic->x == j + 1 and Clic.FirstClic->y == i) or
                (Clic.FirstClic->x == j and Clic.FirstClic->y == i + 1) or
                (Clic.FirstClic->x == j and Clic.FirstClic->y == i - 1) )
            {
                CCLOG("C2 i%d j%d",i,j);
                Clic.SecondClic = new Vec2(j,i);
                this->swap();
                delete Clic.SecondClic;
                Clic.SecondClic = NULL;
                delete Clic.FirstClic;
                Clic.FirstClic = NULL;
            } else {
                delete Clic.FirstClic;
                Clic.FirstClic = NULL;
                Clic.FirstClic = new Vec2(j,i);
                CCLOG("C1 i%d j%d",i,j);

            }
        } else {
            Clic.FirstClic = new Vec2(j,i);
            CCLOG("C1 i%d j%d",i,j);
        }
    }
}

void Glass :: swap(bool first){
    CCLOG("swap");
    auto buf_color = container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].color;
    container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].color = container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].color;
    container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].color = buf_color;

    auto movf = MoveBy::create(0.25, Vec2(
        container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].coordinates.x - container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].coordinates.x,
        container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].coordinates.y - container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].coordinates.y));
    auto movs = MoveBy::create(0.25, Vec2(
        container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].coordinates.x - container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].coordinates.x,
        container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].coordinates.y - container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].coordinates.y));
    auto delay = DelayTime::create(0.25);
    auto ms = Sequence::create(movs->clone(), delay, nullptr);
    auto mf = Sequence::create(movf->clone(), delay, nullptr);
    container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].sprite->runAction(ms);
    container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].sprite->runAction(mf);
    
    if (checking_container(true) == 0){
        buf_color = container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].color;
        container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].color = container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].color;
        container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].color = buf_color;
    
        container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].sprite->runAction(ms->reverse());
        container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].sprite->runAction(mf->reverse());
        
        return;
    }
    auto buf_sprite = container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].sprite;
    container[(int)Clic.SecondClic->y][(int)Clic.SecondClic->x].sprite = container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].sprite;
    container[(int)Clic.FirstClic->y][(int)Clic.FirstClic->x].sprite = buf_sprite;
    
    Points.acts++;
}

Glass :: Glass ()
{
    CCLOG("Glass");
    container = nullptr;
    
    Points.max_points = 0;
    Points.point_i = 0;
    Points.point_l = nullptr;
    
    Clic.FirstClic = nullptr;
    Clic.SecondClic = nullptr;
}

Glass :: ~ Glass () {
    finish();
    CCLOG("~Glass");
}

void Glass :: GameOver(){
    CCLOG("Glass :: GameOver");
    finish();
    Points.point_l = Label::createWithTTF(
                                          "Ваш результат : " + to_string(Points.acts) + " ходов",
                                          start_set.font, start_set.bigtext);
    Points.point_l->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + visibleSize.height/4));
    this->addChild( Points.point_l,0);
    if (fWrite.getpoints(level) > Points.acts or
        fWrite.getpoints(level) == 0)
    {
        EditText();    
    }
}

void Glass :: EditText(){
    Name.textField = ui::TextField::create("введите своё имя:",start_set.font,start_set.smalltext);
    Name.textField->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height/2));
    Name.textField->setMaxLength(10);
    Name.textField->setMaxLengthEnabled(true);
    Name.textField->setFontSize(30);
    Name.textField->addEventListener(CC_CALLBACK_2(Glass::textFieldEvent, this));
    this->addChild(Name.textField,1);
    
    Name.name = "anonymous";
    
    Name.button = ui::Button::create(start_set.png1began, start_set.png1end);
    Name.button->setTitleText("Готово");
    Name.button->setTitleFontName(start_set.font);
    Name.button->setTitleFontSize(start_set.smalltext);
    Name.button->setPosition(Vec2(visibleSize.width/2,
                             visibleSize.height/4 - Name.button->getContentSize().height ));
    Name.button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
                case ui::Widget::TouchEventType::BEGAN:
                        break;
                case ui::Widget::TouchEventType::ENDED:
                        CCLOG("Inputtext Button");
                        log("final text %s",Name.name.c_str());
                        fWrite.set(level,Name.name,Points.acts);
                        this->removeChild(Name.textField);
                        this->removeChild(Name.button);
                        Name.button = nullptr;
                        Name.textField = nullptr;
                        break;
                default:
                        break;
        }
    });
    this->addChild(Name.button);
}

void Glass :: StopEdit(){
    if(Name.textField != nullptr){
        fWrite.set(level,Name.name,Points.acts);
        this->removeChild(Name.textField);
        this->removeChild(Name.button);
        Name.textField = nullptr;
        Name.button = nullptr;
    }
}

void Glass :: textFieldEvent(Ref *sender, ui::TextField::EventType type)
{
    auto textField = (ui::TextField *)sender;
    switch (type)
    {
        case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
            CCLOG("Appear");
            break;

        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("Disappear");
            break;
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("Insert");
            log ("text %s",textField->getString().c_str());
            Name.name = textField->getString();
            break;
        default:
            break;
    }
}


void Glass :: finish(){
    CCLOG("Glass ::  finish");
    _eventDispatcher->removeEventListener(mouseListener);
    unschedule( schedule_selector(Glass::update));
    remove();
    if (container != nullptr){
        for (int i = 0 ; i < SIZE_C ; i++){
            delete [] container[i];
        }
        delete [] container;
        container = nullptr;
    }
    if (Clic.FirstClic != nullptr){
        delete Clic.FirstClic;
        Clic.FirstClic = nullptr;
    }
    if (Clic.SecondClic != nullptr){
        delete Clic.SecondClic;
        Clic.SecondClic = nullptr;
    }
    if (Points.point_l != nullptr){
        this->removeChild(Points.point_l);
        Points.point_l = nullptr;
    }
}

void Glass :: start(){
    CCLOG("Glass :: start");
    int x = visibleSize.width / 2 - SIZEPNG * SIZE_C /2 + SIZEPNG / 2 ;
    int y = visibleSize.height / 2 + SIZEPNG * SIZE_C /2 - SIZEPNG / 2;
    
    Name.button = nullptr;
    Name.textField = nullptr;
    
    try {
        json->get(POINT);
    }
    catch(int max_points){
        Points.max_points = max_points;
    }
    Points.point_i = 0;
    Points.point_l = Label::createWithTTF(  to_string(Points.max_points) + '/' +
                                            to_string(Points.point_i),
                                            start_set.font, start_set.smalltext);
    Points.point_l->setPosition(Vec2(visibleSize.width - Points.point_l->getContentSize().width * 2,
                                     visibleSize.height- Points.point_l->getContentSize().height * 2));
    Points.acts = 0;
    
    this->addChild(Points.point_l,0);
    container = new Tokens * [SIZE_C];
    for ( int j = 0 ; j < SIZE_C ; j++ ){
        container[j] = new Tokens [SIZE_C];
    };
    
    for (int i = 0; i < SIZE_C; i++){
        for (int j = 0; j < SIZE_C; j++){
            container[i][j].set(x + SIZEPNG * j ,
                                y - SIZEPNG * i  );
        }
    }
    
    this->get();
    
    
    mouseListener            = EventListenerMouse::create();
    //mouseListener->setSwallowTouches(true);
    mouseListener->onMouseDown    = CC_CALLBACK_1(Glass::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    this->schedule( schedule_selector(Glass::update), 1.25);
}

void Glass :: get(){
    CCLOG("Glass :: get");
    for (int i = 0; i < SIZE_C; i++){
        for (int j = 0; j < SIZE_C; j++){
            try {
                json->get(MAP);
            }
            catch(bool init_token){
                if (init_token){
                    container[i][j].set_color();
                } else {
                    container[i][j].set_color(NOT_COLOR);
                }
            }
            catch( ... ){
                container[i][j].set_color();
            }
        }
    }
    FreeJson();
    
    checking_container (false);
    fall_tokens();
    if (not scan_for_combo() ){
        this->remove();
        this->get();
    }
    this->add();
};

void Glass :: remove(){
    CCLOG("Glass :: remove");
    if (container != nullptr){
        for (int i = 0; i < SIZE_C; i++){
            for (int j = 0; j < SIZE_C; j++){
                if (container[i][j].sprite != nullptr){
                    this->removeChild(container[i][j].sprite);
                    container[i][j].sprite = nullptr;
                }
            }
        }
    }
}

void Glass :: add(){
    CCLOG("Glass :: add");
    for (int i = 0; i < SIZE_C; i++){
        for (int j = 0; j < SIZE_C; j++){
            container[i][j].init();
            
            if (container[i][j].sprite != nullptr){
                container[i][j].sprite->setPosition(container[i][j].coordinates.x,
                                                    container[i][j].coordinates.y + visibleSize.width / 2 + SIZEPNG * (SIZE_C - i));
                auto move = MoveTo::create(0.15 * (SIZE_C - i), Vec2(container[i][j].coordinates.x,
                                                                     container[i][j].coordinates.y));
                this->addChild(container[i][j].sprite, 0);
                container[i][j].sprite->runAction(move->clone());
            }
        }
    }
}


void Glass :: update(float fd){
    CCLOG("update");
    Points.point_i += checking_container (false);
    if (Points.point_l != nullptr){
        Points.point_l->setString(to_string(Points.max_points) + '/' + to_string(Points.point_i));
        Points.point_l->updateContent();
    }
    fall_tokens();
    if (not scan_for_combo() ){
        this->remove();
        get();
    }
    if (Points.point_i > Points.max_points){
        GameOver();
    }
}

void Glass :: fall_tokens(){
    CCLOG("FALL");
    bool fall = false;
    int i_up ;
    for (int j = 0; j < SIZE_C; j++ ){
        for(i_up = 0;container[i_up][j].color == NOT_COLOR; i_up++ );
        for (int i = SIZE_C - 1; i > -1; i-- ){
            while(container[i][j].color == RANDOM_COLOR){
                this->removeChild(container[i][j].sprite);
                 
                for( int buf_i_in = i; buf_i_in > 0; buf_i_in--){
                    if(container[buf_i_in][j].color == NOT_COLOR){
                        continue;
                    }
                    fall  = true;
                    int buf_i_ot = buf_i_in - 1;
                    while (buf_i_ot > 0 and container[buf_i_ot][j].color == NOT_COLOR)
                    {
                        buf_i_ot--;
                    };
                    if (container[buf_i_ot][j].color != NOT_COLOR){
                        container[buf_i_in][j].color = container[buf_i_ot][j].color;
                        if (container[buf_i_ot][j].sprite != nullptr){
                            auto fall_t = MoveBy::create(0.25 * (buf_i_in - buf_i_ot),
                                                         Vec2(0,container[buf_i_in][j].coordinates.y-container[buf_i_ot][j].coordinates.y));

                            container[buf_i_ot][j].sprite->runAction(fall_t->clone());
                        };
                        container[buf_i_in][j].sprite = container[buf_i_ot][j].sprite;
                    }
                }
                 
                container[i_up][j].set_color();
                if (container[i_up][j].sprite != nullptr){
                    container[i_up][j].init();
                    container[i_up][j].sprite->setPosition(container[i_up][j].coordinates.x,
                                                           visibleSize.width + SIZEPNG );
                    auto move = MoveTo::create(1 , Vec2(container[i_up][j].coordinates.x,
                                                           container[i_up][j].coordinates.y));
                    this->addChild(container[i_up][j].sprite,0);
                    container[i_up][j].sprite->runAction(move->clone());
                };
            }
        }
    }
    if(fall){
        if (Points.point_i == 0){
            checking_container (false);
            fall_tokens();
            if (not scan_for_combo() ){
                this->remove();
                this->get();
            }
        }
    }
}

int Glass :: checking_container (bool check_for_line){
    CCLOG("chec");
    int _points = 0;
    buf_stack<Vec2,int> DeleteHorizontalList;
    buf_stack<Vec2,int> DeleteVerticalList;
    int i = 0 ,j = 0,buf = 0;

    for (i = 0; i < SIZE_C; i++){
        for ( j = 0; j < SIZE_C - 2; ){
            buf = findfind_horizontal_line(i,j);
            if (buf > 2 ){
                _points += buf * buf * 0.75;
                Vec2 buf_ij;
                buf_ij.y = i;
                buf_ij.x = j;
                CCLOG("h:i:%d:j:%d:b:%d",i,j,buf);
                DeleteHorizontalList.push(buf_ij,buf);
            };
            j += buf;
            buf = 0;
        }
    }
    for (j = 0; j < SIZE_C; j++){
        for ( i = 0; i < SIZE_C - 2; ){
            buf = find_vertical_line(i,j);
            if (buf > 2 ){
                _points += buf * buf * 0.75;
                Vec2 buf_ij;
                buf_ij.y = i;
                buf_ij.x = j;
                CCLOG("v:i:%d:j:%d:b:%d",i,j,buf);
                DeleteVerticalList.push(buf_ij,buf);
            }
            i += buf;
            buf = 0;
        }
    }
    if (not check_for_line){
        delete_Vertical_line(&DeleteVerticalList);
        delete_Horizontal_line(&DeleteHorizontalList);    
    }
    return _points;
}

void Glass :: delete_Vertical_line(buf_stack<Vec2,int> *list){
    Vec2 buf;
    int len;
    while ( list->take_out(buf,len) ){
        while (len --> 0){
            container[(int)buf.y + len ][(int)buf.x].color = RANDOM_COLOR;
        }
        list->dell();
    }
}

void Glass :: delete_Horizontal_line(buf_stack<Vec2,int> *list){
    Vec2 buf;
    int len;
    while ( list->take_out(buf,len) ){
        while (len --> 0){
            container[(int)buf.y][(int)buf.x + len ].color = RANDOM_COLOR;
        }
        list->dell();
    }
}

int Glass :: findfind_horizontal_line(int i,int j){
    int Lengh = 1;
    while (j+Lengh < SIZE_C and
           container[i][j].color == container[i][j+Lengh].color and
           container[i][j].color != NOT_COLOR)
    {
        Lengh++;
    }
    return Lengh;
}

int Glass :: find_vertical_line(int i,int j){
    int Lengh = 1;
    while (i+Lengh < SIZE_C and
           container[i][j].color == container[i+Lengh][j].color and
           container[i][j].color != NOT_COLOR)
    {
        Lengh++;
    }
    return Lengh;
}

bool Glass :: scan_for_combo(){
    CCLOG("scan");
    for (int i = 0; i < SIZE_C; i++){
        for (int j = 0; j < SIZE_C; j++){
            if(container[i][j].color == NOT_COLOR){
                continue;
            }
            if (i + 1 < SIZE_C and container[i][j].color == container[i+1][j].color){
                if (i - 1 >= 0 and container[i-1][j].color != NOT_COLOR){
                    if (j - 1 >= 0){
                        if (container[i][j].color == container[i-1][j-1].color){
                            return true;
                        }
                    }
                    if(j + 1 < SIZE_C){
                        if (container[i][j].color == container[i-1][j+1].color){
                            return true;
                        }
                    }
                    if (i - 2 >= 0){
                        if (container[i][j].color == container[i-2][j].color){
                            return true;
                        }
                    }
                }
                if (i + 3 < SIZE_C and container[i+2][j].color != NOT_COLOR){
                    if (j - 1 >= 0){
                        if (container[i][j].color == container[i+2][j-1].color){
                            return true;
                        }
                    }
                    if(j + 1 < SIZE_C){
                        if (container[i][j].color == container[i+2][j+1].color){
                            return true;
                        }
                    }
                    if (j + 3 < SIZE_C){
                        if (container[i][j].color == container[i+3][j].color){
                            return true;
                        }
                    }
                }
            }
            if (j + 1 < SIZE_C and container[i][j].color == container[i][j+1].color){
                if (j - 1 >= 0 and container[i][j-1].color != NOT_COLOR){
                    if (i - 1 >= 0){
                        if (container[i][j].color == container[i-1][j-1].color){
                            return true;
                        }
                    }
                    if(i + 1 < SIZE_C){
                        if (container[i][j].color == container[i+1][j-1].color){
                            return true;
                        }
                    }
                    if (j - 2 >= 0){
                        if (container[i][j].color == container[i][j-2].color){
                            return true;
                        }
                    }
                }
                if (j + 2 < SIZE_C and container[i][j+2].color != NOT_COLOR){
                    if (i - 1 >= 0){
                        if (container[i][j].color == container[i-1][j+2].color){
                            return true;
                        }
                    }
                    if(i + 1 < SIZE_C){
                        if (container[i][j].color == container[i+1][j+2].color){
                            return true;
                        }
                    }
                    if (j + 3 < SIZE_C){
                        if (container[i][j].color == container[i][j+3].color){
                            return true;
                        }
                    }
                }
            }
            if(i - 1 >= 0){
                if (j - 1 >= 0 ){
                    if(j + 1 < SIZE_C ){
                        if (container[i][j].color == container[i-1][j-1].color and
                            container[i][j].color == container[i-1][j+1].color and
                            container[i-1][j].color != NOT_COLOR)
                        {
                            return true;
                        }
                    }
                    if (i + 1 < SIZE_C){
                        if (container[i][j].color == container[i-1][j-1].color and
                            container[i][j].color == container[i+1][j-1].color and
                            container[i][j-1].color != NOT_COLOR)
                        {
                            return true;
                        }
                    }
                }
            }
            if(i + 1< SIZE_C){
                if (j + 1 < SIZE_C){
                    if (j - 1 >= 0 ){
                        if (container[i][j].color == container[i+1][j-1].color and
                            container[i][j].color == container[i+1][j+1].color and
                            container[i+1][j].color != NOT_COLOR)
                        {
                            return true;
                        }
                    }
                    if (i - 1 >= 0 ){
                        if (container[i][j].color == container[i-1][j+1].color and
                            container[i][j].color == container[i+1][j+1].color and
                            container[i][j+1].color != NOT_COLOR)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
};

