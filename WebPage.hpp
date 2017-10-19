 ///
 /// @file    WebPage.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-01-18 16:38:20
 ///

#ifndef _WD_WEB_PAGE_H_
#define _WD_WEB_PAGE_H_

#include "Config.h"
#include "WordSegmentation.hpp"

#include <string>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::vector;
using std::set;

namespace wd
{


class WebPage
{
	friend bool operator == (const WebPage & lhs, const WebPage & rhs); 
	friend bool operator < (const WebPage & lhs, const WebPage & rhs);
public:
	const static int TOPK_NUMBER = 20;
	WebPage()=default;

	WebPage(string & doc, Config & config, WordSegmentation & jieba);

	string getTitle() const 
	{
		return _docTitle;
	}
	int getDocId()
	{	return _docId;	}

	map<string, int> & getWordsMap()
	{	return _wordsMap;	}

	string getDoc()
	{	return _doc;	}
	string getUrl()
	{return _docUrl;}
	string summary(const vector<string> & queryWords);

private:
	void processDoc(const string & doc, Config & config, WordSegmentation & jieba);
         
	void calcTopK(vector<string> & wordsVec, int k, set<string> & stopWordList);

private:
	int _docId;
	string _doc;
	string _docTitle;     //文档标题
	string _docUrl;		  //文档URL
	string _docContent;	  //文档内容
	string _docSummary;   //文档摘要，需要自动生成，不是确定�?

	vector<string>   _topWords;
	map<string, int> _wordsMap; // 存储文档的所有词(去停用词之后)和该项词的词�?
};

}// end of namespace wd

#endif
