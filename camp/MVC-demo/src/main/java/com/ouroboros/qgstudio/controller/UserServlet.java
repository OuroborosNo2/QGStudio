package com.ouroboros.qgstudio.controller;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.constants.Sex;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.impl.UserServiceImpl;
import com.ouroboros.qgstudio.service.UserService;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

// WebServlet注解表示这是一个Servlet，并映射到地址/:
@WebServlet(urlPatterns = "/")
public class UserServlet extends BaseServlet{

    /**
     * 执行用户登录功能
     * @param req 请求
     * @param resp 响应
     * @throws IOException IO异常
     * */
    public void login(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //获取参数
        UserService service = new UserServiceImpl();
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        try {
            if(!service.contain(username)) {
                System.out.println("用户不存在！");
                resp.sendError(400, "用户不存在！");
            }else {
                User user = service.get(username);
                if(user.getPassword().equals(password)) {
                    service.login(user,req.getSession(true));
                }else {
                    resp.sendError(400, "用户名或密码错误");
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    /**
     * 执行用户注册功能
     * @param req 请求
     * @param resp 响应
     * @throws IOException IO异常
     * */
    public void register(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //获取参数
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        Sex sex = Sex.valueOf(req.getParameter("sex"));
        String email = req.getParameter("email");
        UserService service = new UserServiceImpl();

        try {
            if(service.contain(username)) {
                resp.sendError(400, "用户名已存在");
            }else {
                if(service.register(new User(username, password, sex, email))) {
                    resp.setStatus(200);
                }else {
                    resp.sendError(400);
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void homepage(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        // 设置响应类型:
        resp.setContentType("text/plain");
        //获取session
        HttpSession session = req.getSession();
        // 获取输出流:
        PrintWriter pw = resp.getWriter();
        JSONObject jsonobj = new JSONObject();
        //输出个人资料
        for(HttpSession ss : UserService.userPool.keySet()){
            if(session == ss){//确定是已登录的用户在请求数据
                User user = UserService.userPool.get(ss);
                jsonobj.put("username",user.getUsername());
                jsonobj.put("password",user.getPassword());
                jsonobj.put("sex",user.getSex().ordinal());
                jsonobj.put("email",user.getEmail());
                break;
            }
        }
        //输出所有在线用户
        List<String> usernames = new ArrayList<>();
        for(HttpSession ss : UserService.userPool.keySet()){
                User user = UserService.userPool.get(ss);
                usernames.add(user.getUsername());
        }
        // 写入响应:
        jsonobj.put("usernames",usernames.toArray());
        pw.write(jsonobj.toJSONString());
        // 最后不要忘记flush强制输出:
        pw.flush();
    }
}
