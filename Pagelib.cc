 ///
 /// @file    Pagelib.cc
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-10-12 09:46:34
 ///
#include "Pagelib.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;
namespace wd
{
	Pagelib::Pagelib(Config  config)
		:_config(config)
	{
		readPagelib();
		buildInvertedMap();
	}
	Pagelib::~Pagelib()
	{
		cout<<"~Pagelib()"<<endl;
	}


    void Pagelib::readPagelib()//通过offsetlib.bat 读取Pagelib.bat 由WebPage分析保存至内存中
	{
		cout<<"readPagelib()"<<endl;
		auto _configMap=_config.getMap();
		cout<<endl<<"pagelib:"<<_configMap["pagelib"].c_str()<<endl;
		cout<<"offsetlib:"<<_configMap["offsetlib"].c_str()<<endl;
		ifstream ifstreamPagelib(_configMap["pagelib"].c_str());
		ifstream ifstreamoffsetlib(_configMap["offsetlib"].c_str());
		if(!(ifstreamoffsetlib.good())||!(ifstreamPagelib.good()))
		{
			cout<<"read Config fail"<<endl;
			exit(-1);

		}
		string s;
		string offsetInfo;
		int id,offset,length;
		while(getline(ifstreamoffsetlib,offsetInfo))
		{
			istringstream info(offsetInfo);
			info>>id>>offset>>length;
			string doc;
			doc.resize(length,' ');
			ifstreamPagelib.seekg(offset,ifstreamPagelib.beg);
			ifstreamPagelib.read(&*doc.begin(),length);
		//	cout<<doc<<endl;
			WebPage webpage(doc,_config,_cppjieba);
			auto & wordMap=webpage.getWordsMap();
			pair<int,WebPage> tmppair(webpage.getDocId(),webpage);
			_PageMap.insert(tmppair);
			_wordMap.insert(wordMap.begin(),wordMap.end());
			for(auto & item:wordMap)
			_docWordMap[item.first].insert(webpage.getDocId());

			_PageVec.push_back(webpage);
		}
	}

	void Pagelib::debugPageVec()
	{
#if 0
		for(const auto & idx:_PageVec)
		{
			cout<<idx.getTitle()<<endl;
		}
#endif 
		for(const auto & idx:_wordMap)
		{
			cout<<idx.first<<" : "<<idx.second<<endl;
		}
	}

	void Pagelib::buildInvertedMap()
	{
		double tf=0;
		double df=0;
		double idf=0;
		double N=_PageVec.size();
		double sqart_;
		for(auto & PageIdx: _PageVec)
		{
			sqart_=0;
			auto & wordsIdx = PageIdx.getWordsMap();
			for(auto & wordIdx:wordsIdx)
			{
				string __word=wordIdx.first;
				tf=(double)wordIdx.second;
				df=_docWordMap[__word].size();
				idf=log(N/df);
				double weight=tf*idf;
				sqart_=weight*weight+sqart_;
			}
			for(auto & wordIdx:wordsIdx)
			{
				string __word=wordIdx.first;
				tf=(double)wordIdx.second;
				df=_docWordMap[__word].size();
				idf=log(N/df);
				double weight=tf*idf;
				pair<int,double> tmpair(PageIdx.getDocId(),weight/sqrt(sqart_));
				_invertedMap[__word].insert(tmpair);
			}


		}
		for(auto & invertedMapIdx:_invertedMap)
		{
			cout<<invertedMapIdx.first<<":"<<endl;
			for(auto & setIdx:invertedMapIdx.second)
			{
				cout<<"DocID:"<<setIdx.first<<"   Weight"<<setIdx.second<<endl;
			}
		}
	}
	unordered_map<string,set<pair<int,double>>> & Pagelib::getInvertedMap()
	{
		
		return _invertedMap;
	}
	map<string,int> & Pagelib::getWordMap()
	{
		return _wordMap;
	}
	map<string,set<int>> &  Pagelib::getdocWordMap()
	{
		return _docWordMap;
	}
	int Pagelib::getPageNum()
	{
		return _PageVec.size();
	}
	map<int,WebPage> & Pagelib::getPageMap()
	{
		return _PageMap;
	}

}
