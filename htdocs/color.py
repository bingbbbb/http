#!/usr/bin/python
# -*- coding: UTF-8 -*-

# filename：color.py

# CGI处理模块
import cgi, cgitb 

# 创建 FieldStorage 的实例化
form = cgi.FieldStorage() 

# 获取数据
color = form.getvalue('color')

print "Content-type:text/html"
print
print "<html>"
print "<head>"
print "<meta charset=\"utf-8\">"
print "<title>%s</title>" % (color)
print "</head>"
print '<body bgcolor="%s">' % (color)
print "<h1>This is %s</h1>" % (color)
print "</body>"
print "</html>"
