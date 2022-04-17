package com.ouroboros.qgstudio.service;

import com.ouroboros.qgstudio.po.User;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.Map;

public interface UserService{
    //在线user的维护
    Map<HttpSession,User> userPool = new HashMap<>();

    /**
     * 某user登陆
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean login(User user,HttpSession session);
    /**
     * 查询某user是否在线
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean isOnline(User user);
    /**
     * 强制某user下线
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean forceOffline(User user);
    /**
     * 给某user发系统信息
     * @param user User对象
     * @param message 发送的信息
     * @return true(succeed) or false(fail)
     * */
    boolean sendMessage(User user, String message);
    /**
     * 是否存在某User
     * @param username 用户名
     * @return true(yes) or false(no)
     * */
    boolean contain(String username);
    /**
     * 获取指定User
     * @param username 要获取的User的名字
     * @return 所需User对象
     * */
    User get(String username);
    /**
     * 添加一个User
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean register(User user);
    /**
     * 删除指定User
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean delete(User user);
    /**
     * 封禁指定User一段时间
     * @param user User对象
     * @param time 要封禁的时间，以毫秒为单位
     * @return true(succeed) or false(fail)
     * */
    boolean ban(User user,int time);
    /**
     * 解封指定User
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean unban(User user);
}