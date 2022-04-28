package com.ouroboros.qgstudio.controller;

import com.ouroboros.qgstudio.po.User;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebFilter(urlPatterns = "/*")
public class UserValidatingFilter implements Filter {
    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain)
            throws ServletException, IOException {
        //System.out.println("UserValidatingFilter:doFilter");
        String uri = ((HttpServletRequest) req).getRequestURI();//这个uri还tm只能获取一次？？？
        if(uri.equals("/SFM/upload")) {
            chain.doFilter(req, resp);
            return;
        }

        String methodName = req.getParameter("method");
        if(methodName.equals("login") || methodName.equals("register") || methodName.equals("getHeadImg")) {//访问登陆和注册
            //不验证会话和身份
        }else {
            //验证会话和身份
            HttpSession session = ((HttpServletRequest) req).getSession();
            User user = (User) session.getAttribute("user");
            //会话是否有效
            if(user == null) {
                ((HttpServletResponse) resp).sendError(401, "会话失效，请重新登录");
                return;
            }
        }
        chain.doFilter(req, resp);
    }
}