#ifndef __STAKAN_H__
    #define __STAKAN_H__
    
    #include "../Stack/stack.h"
    #include "cocos2d.h"
    #include "Tokens.h"
    #include "../Settings/Settings.h"
    #include "../FileWrite/FWrite.h"
    #include "ui/CocosGUI.h"
    
    USING_NS_CC;
    
    
    class Glass :  public cocos2d::Scene, protected Settings
    {
        public :
            Glass();
            virtual ~Glass();
            //проверка на 3 в ряд и на безвыходность 
            void start();
        protected:
            void finish();
            void StopEdit();
        private :
            void GameOver();
            void get();
            
            Tokens ** container;
            EventListenerMouse * mouseListener;
            
            
            void EditText();
            void textFieldEvent(Ref *, ui::TextField::EventType );
            struct {
                string name;
                ui::TextField * textField;
                ui::Button * button;
            } Name;
            
            struct{
                int acts;
                int max_points;
                int point_i;
                Label * point_l;
            }Points;
            
            struct {
                Vec2 * FirstClic;
                Vec2 * SecondClic;
            } Clic;
            
            void add();
            void remove();
            void swap(bool first = true);
            
            void onMouseDown(Event *);
            void update(float fb = 0);
        
            void fall_tokens();
            int checking_container (bool);
            bool scan_for_combo();
            
            inline void delete_Vertical_line(buf_stack<Vec2,int> *);
            inline void delete_Horizontal_line(buf_stack<Vec2,int> *);
            
            inline int findfind_horizontal_line(int ,int );
            inline int find_vertical_line(int ,int);
    };

#endif /*__STAKAN_H__*/
