 ///
 /// @file    test_server.cc
 /// @author  panjiaming(www.wc.com19941214@gmail.com)
 /// @date    2017-10-09 10:25:56
 ///
#include "TcpServer.h"
#include "Threadpool.h"
#include "Config.h"
#include "Pagelib.h"
#include "WordQuery.h"
#include <iostream>

wd::Config config("config/config");
wd::Pagelib _pageLib(config);
WordQuery _Query(_pageLib); 
wd::Threadpool threadpool(4,10);
void onConnection(const wd::TcpConnectionPtr &conn)
{
	printf("\n >%s has connected! \n ",conn->toString().c_str());
//	conn->send("hello , welcome to server \n");
}
void doInTask(const wd::TcpConnectionPtr &conn,const string & msg)
{
string ret=_Query.execute(msg);
cout<<"send:"<<endl<<ret.size()<<endl;
conn->sendInLoop(ret);

}

void excute(wd::TcpConnectionPtr &conn,std::string str)
{
	conn->sendInLoop(str);
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
	
	std::string str(conn->receive());
	printf("%s\n", str.c_str());
//	doInTask(conn,str);
	threadpool.addTask(std::bind(&doInTask,conn,str));
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	printf("\n %s has closed \n",conn->toString().c_str());
}



int main()
{
	cout<<"server strat"<<endl;
	threadpool.start();
	wd::TcpServer server("127.0.0.1",9999);
	server.setConnectionCallback(&onConnection);
	server.setMessageCallback(&onMessage);
	server.setCloseCallback(&onClose);
	server.start();
	return 0;
}
