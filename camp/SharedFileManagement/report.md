# 项目报告

## 待完成
* 前端中输入的正则
* 导出建表文件
* user添加phone
* 上传文件时，实现用户自己的多层目录

## 存在问题

## 遇到的问题和解决过程
* 问题：整合servlet时理解错误，以为BaseServlet是中转站，映射了BaseServlet，导致反射获取方法时找不到方法。
  * 解决方法：改为映射UserServlet，BaseServlet仅仅是用来继承的
* 问题：上传文件时后台报错 request 问题
  * 原因：无论是表单请求还是ajax请求上传文件时只能放一个formData，不能放别的参数
  * 解决方法：没找到放参数还能解析request的办法，只能另外开一个servlet映射来处理文件上传了。
* 问题：有时候上传一次文件后，再上传一次同文件没反应
  * 原因：同样的文件没触发onchange()
  * 解决方法：上传完一次后重置\<input>,然而出于安全考虑，浏览器只允许用户点击\<input type="file">来选择本地文件，
  用JavaScript对\<input type="file">的value赋值是没有任何效果的。
  所以先删再加回去。

## 依赖
* fastjson
* jdbc-mysql
* commons-fileupload
* commons-io


## 想请教的问题
* 产生的数据文件是放在webapps里好，还是限制在项目里好。
如果限制在项目里，tomcat更新war包时容易丢失数据呀。
* 好友列表和群组列表这种东西好像不适合放在数据库，所以我放外面了。
