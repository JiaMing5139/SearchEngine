 ///
 /// @file    Config.cpp
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-09-28 16:57:20
 ///
 //
#include "Config.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
using std::ifstream;
using std::cout;
using std::endl;
namespace wd
{
	Config::Config(const char * s)
	{
		ifstream is(s);
		if(!is)
		{
			cout<<"fail to open the file"<<endl;
			exit(-1);
		}
		string text;
		cout<<"start to read configtext"<<endl;
		while(getline(is,text))
		{
			//cout<<"text:"<<text<<endl;
			char first[32],second[32];
			char  src[128];
			memset(first,0,sizeof(first));
			memset(second,0,sizeof(second));
			memset(src,0,sizeof(src));
			strcpy(src,text.c_str());
			//printf("src : %s \n",src);
			int ret=sscanf(src,"%s %s",first,second);
			//printf("first:%s  ,  second:%s\n",first,second);
			if(ret!=-1)
			{
				_configMap[first]=second;
			}
			else
			{
				perror("ssprintf");
			}
		}
		_path=_configMap["path"];
		cout<<"read config  successfully"<<endl;
	}
	string Config::getPath()
	{
		return this->_path;
	}
	map<string,string> & Config::getMap()
	{	
		return _configMap;
	}
	set<string> & Config::getStopWordList()
	{
		if(_stopWordList.size()>0)
			return _stopWordList;
		string stopWordFilePath =_configMap["stopword"];
		ifstream ifs(stopWordFilePath.c_str());
		if(!ifs)
		{
			cout<<"StopWordList open failed"<<endl;
			exit(-1);
		}
		string word;
		while(getline(ifs,word))
		{
			_stopWordList.insert(word);
		}
		return _stopWordList;
		
	}
	
}
 
