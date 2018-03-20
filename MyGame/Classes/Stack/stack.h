#ifndef BUF_STAK
    #define BUF_STAK
    
    
    #ifndef NULL
        #define NULL 0x0000
    #endif

template <typename Type1, typename Type2>
class stack_element{
    public :
        stack_element(Type1 _element1, Type2 _element2, stack_element * _next) :
                element1(_element1),
                element2(_element2),
                next(_next)
        {};
        ~stack_element(){};
        
        stack_element * get_next(){
            return next;
        };
        
        Type1 get1() { return element1; };
        Type2 get2() { return element2; };
        
    private:
        stack_element * next;
        Type1 element1;
        Type2 element2;
};

template <typename Type1, typename Type2>
class buf_stack{
    public:
        buf_stack() : start(NULL) {};
        ~buf_stack(){
            while (dell());
        };
        
        void push(Type1 type1, Type2 type2){
            start = new stack_element<Type1, Type2> (type1,type2,start);
        };
        
        bool take_out(Type1 &ell1, Type2 &ell2){
            if (start == NULL){
                return false;
            }
            ell1 = start->get1();
            ell2 = start->get2();
            return true;
        }
        
        bool dell(){
            if (start == NULL){
                return false;
            }
            stack_element<Type1, Type2> * buf = start->get_next();
            delete start;
            start = buf;
            return true;
        }
        
    private:
        stack_element<Type1, Type2> * start;
};
    
#endif /*BUF_STAK*/
