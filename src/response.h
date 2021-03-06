#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>

using namespace muduo;
using namespace muduo::net;
const string webHome="/home/bing/CPP/http/htdocs";
void onRequest(const HttpRequest& req, HttpResponse* resp);
string ConstructPath(const string &path);
string GetExtent(const string &path);
void GetContentType(const string&,string&);
string GetContent(const string &);