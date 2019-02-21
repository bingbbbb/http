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
        string databody=req.body();
        
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
            char length_env[255];
            

            string Path(req.path().begin()+1,req.path().end());
            Path = webHome + "/" + Path;
            sprintf(meth_env, "REQUEST_METHOD=%s", req.methodString());
            putenv(meth_env);
            if (method == "POST")
            {
                int contentLengthValue=std::stoi(req.getHeader("Content-Length"));
                sprintf(length_env, "CONTENT_LENGTH=%d", contentLengthValue);
                
                putenv(length_env);
                std::cout << length_env << std::endl;
            }
            else
            {
                string Query(req.query().begin()+1,req.query().end());
                sprintf(query_env, "QUERY_STRING=%s", Query.c_str());
                putenv(query_env);
            }

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
            if (method == "POST")
            {
                for(int i=0;i<static_cast<int>(databody.size());++i)
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
            resp->setStatusCode(HttpResponse::k200Ok);
            resp->setStatusMessage("OK");
            resp->setContentType("text/html");
        }
    }
    else
    {
        resp->setStatusCode(HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
    }
    

//*/
}

string ConstructPath(const string &path)
{
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