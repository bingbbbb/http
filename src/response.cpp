#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include "response.h"
extern bool benchmark;
char favicon[555] = {
  '\x89', 'P', 'N', 'G', '\xD', '\xA', '\x1A', '\xA',
  '\x0', '\x0', '\x0', '\xD', 'I', 'H', 'D', 'R',
  '\x0', '\x0', '\x0', '\x10', '\x0', '\x0', '\x0', '\x10',
  '\x8', '\x6', '\x0', '\x0', '\x0', '\x1F', '\xF3', '\xFF',
  'a', '\x0', '\x0', '\x0', '\x19', 't', 'E', 'X',
  't', 'S', 'o', 'f', 't', 'w', 'a', 'r',
  'e', '\x0', 'A', 'd', 'o', 'b', 'e', '\x20',
  'I', 'm', 'a', 'g', 'e', 'R', 'e', 'a',
  'd', 'y', 'q', '\xC9', 'e', '\x3C', '\x0', '\x0',
  '\x1', '\xCD', 'I', 'D', 'A', 'T', 'x', '\xDA',
  '\x94', '\x93', '9', 'H', '\x3', 'A', '\x14', '\x86',
  '\xFF', '\x5D', 'b', '\xA7', '\x4', 'R', '\xC4', 'm',
  '\x22', '\x1E', '\xA0', 'F', '\x24', '\x8', '\x16', '\x16',
  'v', '\xA', '6', '\xBA', 'J', '\x9A', '\x80', '\x8',
  'A', '\xB4', 'q', '\x85', 'X', '\x89', 'G', '\xB0',
  'I', '\xA9', 'Q', '\x24', '\xCD', '\xA6', '\x8', '\xA4',
  'H', 'c', '\x91', 'B', '\xB', '\xAF', 'V', '\xC1',
  'F', '\xB4', '\x15', '\xCF', '\x22', 'X', '\x98', '\xB',
  'T', 'H', '\x8A', 'd', '\x93', '\x8D', '\xFB', 'F',
  'g', '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f', 'v',
  'f', '\xDF', '\x7C', '\xEF', '\xE7', 'g', 'F', '\xA8',
  '\xD5', 'j', 'H', '\x24', '\x12', '\x2A', '\x0', '\x5',
  '\xBF', 'G', '\xD4', '\xEF', '\xF7', '\x2F', '6', '\xEC',
  '\x12', '\x20', '\x1E', '\x8F', '\xD7', '\xAA', '\xD5', '\xEA',
  '\xAF', 'I', '5', 'F', '\xAA', 'T', '\x5F', '\x9F',
  '\x22', 'A', '\x2A', '\x95', '\xA', '\x83', '\xE5', 'r',
  '9', 'd', '\xB3', 'Y', '\x96', '\x99', 'L', '\x6',
  '\xE9', 't', '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',
  '\xA7', '\xC4', 'b', '1', '\xB5', '\x5E', '\x0', '\x3',
  'h', '\x9A', '\xC6', '\x16', '\x82', '\x20', 'X', 'R',
  '\x14', 'E', '6', 'S', '\x94', '\xCB', 'e', 'x',
  '\xBD', '\x5E', '\xAA', 'U', 'T', '\x23', 'L', '\xC0',
  '\xE0', '\xE2', '\xC1', '\x8F', '\x0', '\x9E', '\xBC', '\x9',
  'A', '\x7C', '\x3E', '\x1F', '\x83', 'D', '\x22', '\x11',
  '\xD5', 'T', '\x40', '\x3F', '8', '\x80', 'w', '\xE5',
  '3', '\x7', '\xB8', '\x5C', '\x2E', 'H', '\x92', '\x4',
  '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g', '\x98',
  '\xE9', '6', '\x1A', '\xA6', 'g', '\x15', '\x4', '\xE3',
  '\xD7', '\xC8', '\xBD', '\x15', '\xE1', 'i', '\xB7', 'C',
  '\xAB', '\xEA', 'x', '\x2F', 'j', 'X', '\x92', '\xBB',
  '\x18', '\x20', '\x9F', '\xCF', '3', '\xC3', '\xB8', '\xE9',
  'N', '\xA7', '\xD3', 'l', 'J', '\x0', 'i', '6',
  '\x7C', '\x8E', '\xE1', '\xFE', 'V', '\x84', '\xE7', '\x3C',
  '\x9F', 'r', '\x2B', '\x3A', 'B', '\x7B', '7', 'f',
  'w', '\xAE', '\x8E', '\xE', '\xF3', '\xBD', 'R', '\xA9',
  'd', '\x2', 'B', '\xAF', '\x85', '2', 'f', 'F',
  '\xBA', '\xC', '\xD9', '\x9F', '\x1D', '\x9A', 'l', '\x22',
  '\xE6', '\xC7', '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15',
  '\x90', '\x7', '\x93', '\xA2', '\x28', '\xA0', 'S', 'j',
  '\xB1', '\xB8', '\xDF', '\x29', '5', 'C', '\xE', '\x3F',
  'X', '\xFC', '\x98', '\xDA', 'y', 'j', 'P', '\x40',
  '\x0', '\x87', '\xAE', '\x1B', '\x17', 'B', '\xB4', '\x3A',
  '\x3F', '\xBE', 'y', '\xC7', '\xA', '\x26', '\xB6', '\xEE',
  '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
  '\xA', '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X', '\x0',
  '\x27', '\xEB', 'n', 'V', 'p', '\xBC', '\xD6', '\xCB',
  '\xD6', 'G', '\xAB', '\x3D', 'l', '\x7D', '\xB8', '\xD2',
  '\xDD', '\xA0', '\x60', '\x83', '\xBA', '\xEF', '\x5F', '\xA4',
  '\xEA', '\xCC', '\x2', 'N', '\xAE', '\x5E', 'p', '\x1A',
  '\xEC', '\xB3', '\x40', '9', '\xAC', '\xFE', '\xF2', '\x91',
  '\x89', 'g', '\x91', '\x85', '\x21', '\xA8', '\x87', '\xB7',
  'X', '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N', 'N',
  'b', 't', '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
  '\xEC', '\x86', '\x2', 'H', '\x26', '\x93', '\xD0', 'u',
  '\x1D', '\x7F', '\x9', '2', '\x95', '\xBF', '\x1F', '\xDB',
  '\xD7', 'c', '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF',
  '\x22', 'J', '\xC3', '\x87', '\x0', '\x3', '\x0', 'K',
  '\xBB', '\xF8', '\xD6', '\x2A', 'v', '\x98', 'I', '\x0',
  '\x0', '\x0', '\x0', 'I', 'E', 'N', 'D', '\xAE',
  'B', '\x60', '\x82',
};
void onRequest(const HttpRequest& req, HttpResponse* resp)
{
    bool cgi = false;
    std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
    if (!benchmark)
    {
        const std::map<string, string>& headers = req.headers();
        for (std::map<string, string>::const_iterator it = headers.begin();
            it != headers.end();
            ++it)
        {
        std::cout << it->first << ": " << it->second << std::endl;
        }
    }
///*    
    string method(req.methodString());
    if(method == "POST" || 
	   (method == "GET" && !req.query().empty()) )
	    cgi = true;
    if (!cgi && method == "GET")
    {//not cgi
        string path = ConstructPath(req.path());
        string extent = GetExtent(path);
        string contentType = "";
        GetContentType(extent,contentType);
        string content = GetContent(path);
        if(content.empty())
        {
            resp->setStatusCode(HttpResponse::k404NotFound);
            resp->setStatusMessage("Not Found");
            resp->setCloseConnection(true);
        }
        else
        {
            resp->setBody(content);
            resp->setStatusCode(HttpResponse::k200Ok);
            resp->setStatusMessage("OK");
            resp->setContentType(contentType);
        } 
    }
    ///*
    else if (method == "POST" || method == "GET")
    {//cgi
        int cgi_output[2];
        int cgi_input[2];
        pid_t pid;
        int status;
        char c;
        //POST
        //*
        if(method == "POST")
        {
        
            int contentLengthValue=std::stoi(req.getHeader("Content-Length"));
            string databody=req.body();
            resp->setStatusCode(HttpResponse::k200Ok);
            resp->setStatusMessage("OK");
            if(pipe(cgi_output)<0)
            {
                printf("pipe error\r\n");
                return ;
            }
            if(pipe(cgi_input)<0)
            {
                printf("pipe error\r\n");
                return ;
            }
            if ( (pid = fork()) < 0 )
            {
                printf("fork error\r\n");
                return;
            }
            if(pid==0)
            {
                char meth_env[255];
                char length_env[255];

                string Path(req.path().begin()+1,req.path().end());
                string webHome="/home/bing/CPP/muduoHttp/htdocs";
                Path = webHome + "/" + Path;

                sprintf(meth_env, "REQUEST_METHOD=%s", req.methodString());
                sprintf(length_env, "CONTENT_LENGTH=%d", contentLengthValue);

                putenv(meth_env);
                putenv(length_env);

                dup2(cgi_output[1], 1);
                dup2(cgi_input[0], 0);
                close(cgi_output[0]);
                close(cgi_input[1]);
                
                execl(Path.c_str(), Path.c_str(), NULL);
                exit(0);
            }
            else
            {

                string cgibody;
                close(cgi_output[1]);
                close(cgi_input[0]);

                for(int i=0;i<static_cast<int>(databody.size());++i)
                {
                write(cgi_input[1],&databody[i] ,1 );
                }

                while (read(cgi_output[0], &c, 1) > 0)
                {
                cgibody+=c;
                }


                close(cgi_output[0]);
                close(cgi_input[1]);
                resp->setBody(cgibody);
                waitpid(pid, &status, 0);
                resp->setContentType("text/html");
            }
        }
        else if (method == "GET")
        //*/
        {
            resp->setStatusCode(HttpResponse::k200Ok);
            resp->setStatusMessage("OK");
            if(pipe(cgi_output)<0)
            {
                printf("pipe error\r\n");
                return ;
            }
            if(pipe(cgi_input)<0)
            {
                printf("pipe error\r\n");
                return ;
            }
            if ( (pid = fork()) < 0 )
            {
                printf("fork error\r\n");
                return;
            }

            if(pid==0)
            {
                char meth_env[255];
                char query_env[255];

                string Path(req.path().begin()+1,req.path().end());
                string webHome="/home/bing/CPP/muduoHttp/htdocs";
                Path = webHome + "/" + Path;
                string Query(req.query().begin()+1,req.query().end());
                sprintf(meth_env, "REQUEST_METHOD=%s", req.methodString());
                sprintf(query_env, "QUERY_STRING=%s", Query.c_str());

                std::cout << "meth_env : " << meth_env << std::endl;
                std::cout << "query_env : " << query_env << std::endl;

                dup2(cgi_output[1], 1);
                dup2(cgi_input[0], 0);
                close(cgi_output[0]);
                close(cgi_input[1]);
                putenv(meth_env);
                putenv(query_env);

                execl(Path.c_str(), Path.c_str(), NULL);
                exit(0);
            }
            else
            {
                string cgibody;
                close(cgi_output[1]);
                close(cgi_input[0]);

                while (read(cgi_output[0], &c, 1) > 0)
                {
                    cgibody+=c;
                }
                close(cgi_output[0]);
                close(cgi_input[1]);
                resp->setBody(cgibody);
                waitpid(pid, &status, 0);
                resp->setContentType("text/html");
            }
        }
    }
    //*/
    else
    {
        resp->setStatusCode(HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
    }
    

//*/







/*
    if (req.path() == "/")
    {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("text/html");
        resp->addHeader("Server", "Muduo");
        string now = Timestamp::now().toFormattedString();
        resp->setBody("<html><head><title>This is title</title></head>"
            "<body><h1>Hello</h1>Now is " + now +
            "</body></html>");
    }
    else if (req.path() == "/favicon.ico")
    {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("image/png");
        resp->setBody(string(favicon, sizeof favicon));
    }
    else if (req.path() == "/hello")
    {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("text/plain");
        resp->addHeader("Server", "Muduo");
        resp->setBody("hello, world!\n");
    }
    else
    {
        resp->setStatusCode(HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
    }
*/
}

string ConstructPath(const string &path)
{
    string webHome="/home/bing/CPP/muduoHttp/htdocs";
    if(path=="/")
    {
        return webHome+"/index.html";
    }
    else
    {
        return webHome+path;
    }
}

string GetExtent(const string &path)
{
    int i;
    for(i=static_cast<int>(path.size()-1);;--i)
    {
        if(path[i]=='.')
        break;
    }
    return string(path.begin()+i+1,path.end());
}

void GetContentType(const string &tmpExtension,string &contentType)
{
    if (tmpExtension == "html" || tmpExtension == "htm")
        contentType = "text/html";
    else if (tmpExtension == "png")
        contentType = "image/png";
    else contentType = "text/plain";
}

string GetContent(const string &fileName)
{
    
    std::ifstream fin(fileName);
    if(fin.fail())
    {
        return string("");
    }
    std::ostringstream oss;
    oss << fin.rdbuf();
    return string(oss.str());
}