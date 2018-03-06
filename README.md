# SearchEngine
安装 jsconspp和cppjieba库

将网页XML库存放在data目录下，offsetlib.dat存放每个网页在pagelibdata中的文章序号/t起始/t偏移  pagelib.dat存放xml形式的网页

编译 +g++ *.c -std=c++11 -lpthread -ljson

运行后将在本地的5080端口监听

向5080端口使用socket发送queryword，返回在网页库中最相似的文章xml网页内容及摘要
