#include "FWrite.h"
#include "cocos2d.h"
//#include <cstdlib>

FWrite :: FWrite() : ifile("Resources/Saves/game.saves") , point(data_list.end())
{
    if( not ifile.is_open()){
    	CCLOG("FW :: not open");
        return ;
    } else {
    	CCLOG("FW :: open");
        while((not ifile.eof()) and (not ifile.fail())){
        	int s = ifile.rdstate();
            if ( s & ios::badbit ){
                ifile.close();
                break;
            }
        	string _point;
		    string _level;
		    string _name;
		    string buf;
            ifile >> _level;
            _level = decrypt( _level );
            if ( getline(ifile,buf) == 0){
            	break;
            }
            int i;
            for(i = buf.size() - 1; buf[i] != ' '; i-- );
			for (unsigned int ii = i+1; ii < buf.size(); ii++){
				_point += buf[ii];
			}
			_point = decrypt( _point );
			for( int ii = 1; ii < i; ii++){
				_name += buf[ii];
			}
			_name = decrypt( _name );
            saves sv;
            sv.name = _name;
            sv.points = _point;
            data_list.insert(pair<string,saves>(_level,sv));
        }
        point = data_list.begin();
    }
    ifile.close();
}

FWrite :: ~  FWrite()
{
	if (data_list.begin() == data_list.end()) return;
    ofile.open("Resources/Saves/game.saves",ios::trunc);
    
    auto it = data_list.begin();
    while(it != data_list.end()){
	    ofile<<encrypt((*it).first)<<' '
	    	 <<encrypt((*it).second.name)<<' '
	    	 <<encrypt((*it).second.points)<<endl;
		it++;
    }
    ofile.close();
    data_list.clear();
}

string FWrite :: getString(){
	CCLOG("FWrite :: getString");
	if (point == data_list.end()){
		CCLOG("!!!");
		point = data_list.begin();
		if (point == data_list.end()) throw Exceptions::clean_list;
		else throw Exceptions::end_list;
	}
	string buf;
	buf = (*point).first;
	
	if (buf.size() < 7){
		buf += ' ';
	}
	buf += ' ';
	for(int i =	10 - (*point).second.name.size(); i != 0; i--){
		buf += ' ';
	}
	buf += (*point).second.name;
	buf += ' ';
	for(int i =	4 - (*point).second.points.size(); i != 0; i--){
		buf += ' ';
	}
	buf += (*point).second.points;
	point ++;
	
	CCLOG("%s",buf.c_str());
	return buf;
}

int FWrite :: getpoints(string level){
    auto buf = data_list.find(level);
    if (buf == data_list.end()){
       return 0;
    } else {
        return stoi((*buf).second.points);
    }
}

void FWrite :: set (string level, string name,unsigned int points){
	CCLOG("FWrite :: set");
    saves sv;
    sv.name = name;
    sv.points = to_string( points );
    auto buf = data_list.find(level);
    if (buf == data_list.end()){
       data_list.insert(pair<string,saves>(level,sv));
       point = data_list.begin();
    } else {
        (*buf).second = sv;
        point = data_list.begin();
    }
}

string FWrite :: encrypt( string buf){
	string res;
	for (unsigned int i = 0; i < buf.size(); i++){
		char b = (char)buf[i] ;
		switch(b){
			case 33 ... 126-KEY : 
				b += KEY;
				break ;
			case 127-KEY ... 126 :
				b -= 126 - 33 - KEY;
				break;
			default :
				;
		}
		res += b;
	}
	return res;
}

string FWrite :: decrypt( string buf){
	string res;
	for (unsigned int i = 0; i < buf.size(); i++){
		char b = (char)buf[i] ;
		switch(b){
			case 33 ... 33+KEY : 
				b += 126 - 33 - KEY;
				break ;
			case 34+KEY ... 126 :
				b -= KEY;
				break;
			default :
				;
		}
		res += b;
	}
	return res;
}

