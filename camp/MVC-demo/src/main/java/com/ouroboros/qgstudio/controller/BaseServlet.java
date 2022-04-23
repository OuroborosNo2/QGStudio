package com.ouroboros.qgstudio.controller;

import com.ouroboros.qgstudio.constants.Sex;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.UserService;
import com.ouroboros.qgstudio.service.impl.UserServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


public class BaseServlet extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        String methodName = req.getParameter("method");
        UserServlet s = new UserServlet();
        switch(methodName){
            case "homepage":
                s.homepage(req,resp);
                break;
        }
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        // 设置响应类型:
        resp.setContentType("text/html");
        String methodName = req.getParameter("method");
        System.out.println(methodName);
        //通过反射自动获取并调用目标方法，整合了servlet，易于维护，不易出错
        try {
            Class<? extends BaseServlet> actionClass = this.getClass();
            Method method = actionClass.getMethod(methodName,HttpServletRequest.class,HttpServletResponse.class);
            method.invoke(this,req,resp);
        }catch(NoSuchMethodException | InvocationTargetException | IllegalAccessException e) {
            resp.sendError(400,"请求了错误方法");
            e.printStackTrace();
        }
        /*UserServlet s = new UserServlet();
        switch(methodName){
            case "login":
                s.login(req,resp);
                break;
            case "register":
                s.register(req,resp);
                break;
        }*/
    }
}
