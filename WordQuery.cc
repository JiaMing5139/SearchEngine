 ///
 /// @file    WordQuery.cc
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-10-16 12:38:02
 ///
#include <algorithm>
#include <json/json.h>
#include "WordQuery.h"
struct candidate
{
	int _id;
	double _cos;
	candidate(int id,double cos):_id(id),_cos(cos){};
	bool operator > (const   candidate & lhs) const { return _cos>lhs._cos;}
	bool operator < (const   candidate & lhs) const { return _cos<lhs._cos;}
};
WordQuery::~WordQuery()
{
	cout<<"~WordQuery"<<endl;

}

WordQuery::WordQuery(wd::Pagelib & pagelib)
	:_PageLib(pagelib)
	 
{
	cout<<"WordQuery init: queryword: "<<endl;
}
#if 0
void WordQuery::deBug()
{
	_conn->sendInLoop(_QueryWord);

}
#endif
vector<double> WordQuery::getQueryWordWeight(vector<string> &  queryword)
{
		vector<double> ret;
		map<string,int> queryWordMap;
		for(auto item:queryword)
		{
			++queryWordMap[item];
		}
	    auto   PagewordMap=_PageLib.getdocWordMap();
		double tf=0;
		double df=0;
		double idf=0;
		double N=_PageLib.getPageNum();
		double sqart_;
			sqart_=0;
			auto & wordsIdx = queryWordMap;
			for(auto & wordIdx:wordsIdx)
			{
				string __word=wordIdx.first;
				cout<<__word<<":"<<endl;
				tf=(double)wordIdx.second;
				df=PagewordMap[wordIdx.first].size();
				idf=log(N/df);
				double weight=tf*idf;
				cout<<"tf:"<<tf<<endl
					<<"idf"<<idf<<endl
					<<"weight"<<weight<<endl;
				sqart_=weight*weight+sqart_;
			}
			for(auto & wordIdx:wordsIdx)
			{
				string __word=wordIdx.first;
				tf=(double)wordIdx.second;
				df=PagewordMap[wordIdx.first].size();
				idf=log(N/df);
				double weight=tf*idf;
				ret.push_back(weight/sqrt(sqart_));
			
			}


	#if 1
		for(auto & invertedMapIdx:ret)
		{
			
			cout<<endl<<invertedMapIdx<<endl;
		}
	#endif
	return ret;
}
string  WordQuery::execute(string _QueryWord)
{
	vector<string>   _wordlist=_jieba(_QueryWord.c_str());

	cout<<"查询词分词："<<endl;
	for(auto i:_wordlist)
	{
		cout<<i<<endl;
	}
	auto &  invertedMap=_PageLib.getInvertedMap();
#if 1
	for(const string & word:_wordlist)   //过滤不存在的关键???
	{
		auto j=invertedMap.find(word);
		if(j==invertedMap.end())
		{
			for(auto k=_wordlist.begin();k!=_wordlist.end();++k)
			{
				if(*k==word)
				_wordlist.erase(k);
			}
		}
	}
#endif	
	if(_wordlist.size()==0) 
	{
		cout<<"not found"<<endl;
		return 0;
	}

	vector<double> queryWordvec=getQueryWordWeight(_wordlist);//获取标准向量

	map<int,vector<double>>  resultMap;
	for(auto & item:_wordlist)   //初始化resultM
	{
		for(auto & setIdx:invertedMap[item])
		{
			resultMap[setIdx.first].push_back(setIdx.second);
		}
	}
	map<int,double> cosMap;
	priority_queue<candidate> _candQueue;
	for(auto & idx: resultMap)  
	{
		if(idx.second.size()!=_wordlist.size())
		continue;
		double tmp=cosCaculate(queryWordvec,idx.second);
		candidate candidatePage(idx.first,tmp);
		_candQueue.push(candidatePage);
		
		//cout<<"id:"<<idx.first<<"  cos"<<tmp<<endl;
	}
string result;
vector<int> docVec;
	while(_candQueue.size()!=0)
	{
		//auto &  webPageMap=_PageLib.getPageMap();
		//cout<<webPageMap[_candQueue.top()._id].getTitle()<<endl;
		//result=result+webPageMap[_candQueue.top()._id].getTitle();
		docVec.push_back(_candQueue.top()._id);	
		_candQueue.pop();
	}
	return createJson(docVec,_wordlist);
									//PC------------------------------------------------>
}
double WordQuery::cosCaculate(const vector<double>  & r,const vector<double> &  l)
{
	double ret;
	double denominator=0;
	double element=0;
	double lSquare=0;
	double rSquare=0;

	for(size_t i=0;i<r.size();i++)
	{
		element=r[i]*l[i]+element;
	}
	for(const auto & idx:r)
	{
		rSquare=rSquare+idx*idx;
	}
	for(const auto & idx:l)
	{
		lSquare=lSquare+idx*idx;
	}
	denominator=sqrt(rSquare*rSquare);
	ret=element/denominator;
	return ret;
}

string WordQuery::createJson(vector<int> & docIdVec, const vector<string> & queryWords)
{
	Json::Value root;
	Json::Value arr;
	auto & _pageLib=_PageLib.getPageMap();

	int cnt = 0;
	for(auto id : docIdVec)
	{
		string summary = _pageLib[id].summary(queryWords);
		string title = _pageLib[id].getTitle();
		string url = _pageLib[id].getUrl();

		Json::Value elem;
		elem["title"] = title;
		elem["summary"] = summary;
		elem["url"] = url;
		arr.append(elem);
		if(++cnt == 100)// 最多记???00???
			break;
	}

	root["files"] = arr;
	Json::StyledWriter writer;
	return writer.write(root);
}
   

