 ///
 /// @file    Config.h
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-09-28 16:49:27
 ///
 
#ifndef __WD_CONFIG_H__
#define	__WD_CONFIG_H__
#include <map>
#include <string>
#include <set>
using std::set;
using std::map;
using std::string;
namespace wd
{
class Config
{
	public:
	Config(const char *);
	string getPath();
	void getSeverIpAddr();
	short getSeverPort();
	map<string,string> &  getMap();
	set<string> & getStopWordList();
	private:
	set<string> _stopWordList;	
	map<string,string> _configMap;
	string _path;
	string _severIpAddr;
	string _severPort;
};
}//end of wd

#endif
