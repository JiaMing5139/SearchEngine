 ///
 /// @file    Pagelib.h
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-10-11 21:00:22
 ///
 
#ifndef __WD_PAGELIB_H__
#define	__WD_PAGELIB_H__
#include "Config.h"
#include "WebPage.hpp"
#include "WordSegmentation.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;
namespace wd
{
	class WebPage;
	class Pagelib
	{
		public:
		~Pagelib();
		void debugPageVec() ;
		Pagelib(Config);
	    void Execute(string queryword);
		void readPagelib();
		unordered_map<string,set<pair<int,double>>> & getInvertedMap();
		map<string,int> & getWordMap();
		map<string,set<int>> &  getdocWordMap();
		int getPageNum();
		map<int,WebPage> & getPageMap();
		private:
		void buildInvertedMap();
		private:
		Config                       _config;
		vector<WebPage>             _PageVec;
		map<string,int>   _wordMap;
		unordered_map<string,set<pair<int,double>>> _invertedMap;
		map<string,set<int>> _docWordMap;
		map<int,WebPage>			_PageMap;
		WordSegmentation           _cppjieba;

	};
}



#endif
