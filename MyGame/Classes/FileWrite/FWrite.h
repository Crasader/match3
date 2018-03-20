#ifndef __FW_H__
    #define __FW_H__
    
#include <fstream>
#include <string>
#include <ostream>
#include <map>

#define SAVESF "saves.game"
#define KEY 5

	using namespace std;

	struct saves {
		string name;
		string points;
	};

	class FWrite {
		public :
			enum Exceptions{
				clean_list,
				end_list
			};    	

		    FWrite();
		    ~FWrite();

		    string getString();
		    int getpoints(string);
		    void set (string, string,unsigned int);

		private :
			string encrypt( string );
			string decrypt( string );
		
		    ifstream ifile;
		    ofstream ofile;
		    map<string, saves> data_list;
		    map<string, saves>::iterator point;
	};
    
#endif /*__FW_H__*/
