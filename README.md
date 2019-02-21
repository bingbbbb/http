增加POST请求及cgi功能  
使用muduo-tutorial提供的Makefile编译会有 undefined reference to `muduo::net::HttpServer::start() 的报错, 
使用nm命令查看 build/release-install/lib 文件夹, 会发现 HttpServer 类被包含在 libmuduo_http.a 中，所以需要在
Makefile中加入-lmuduo_http  
修改了muduo/net/http/HttpRequest.h、muduo/net/http/HttpContext.cc  
muduo默认使用的string是__gnu_cxx::__sso_string（muduo/base/Types.h),建议使用std::string，标准库函数只支持std::string  