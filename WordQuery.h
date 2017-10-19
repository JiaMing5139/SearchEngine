 ///
 /// @file    WordQuery.h
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-10-16 12:38:13
 ///
 
#ifndef __WD_WORDQUERY_H__
#define	__WD_WORDQUERY_H__
#include "Pagelib.h"
#include "WordSegmentation.hpp"
#include "TcpConnection.h"
#include <string>
#include <queue>
//struct candicate
//{
//	int _id;
//	double _cos;
//	bool operator > (const  candicate & lhs){ return _cos>lhs._cos;}
//	bool operator < (const  candicate & lhs){ return _cos<lhs._cos;}
//	candicate(int id,double cos):_id(id),_cos(cos){};
//};


using namespace std;
class WordQuery
{
	

	public:
		~WordQuery();
		WordQuery()=default;
		WordQuery(wd::Pagelib &);
		string execute(string);
		void debugExecute();
		void deBug();
	private:
		string createJson(vector<int> & docIdVec, const vector<string> & queryWords);	
		vector<double> getQueryWordWeight(vector<string> &);
		double cosCaculate(const vector<double> &,const vector<double> &);
	private:
		wd::Pagelib & _PageLib;
		//string _QueryWord;
		//wd::TcpConnectionPtr _conn;
		wd::WordSegmentation _jieba;
		//priority_queue<candicate> _candQueue;

};

#endif
