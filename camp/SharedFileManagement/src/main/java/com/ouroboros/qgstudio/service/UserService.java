package com.ouroboros.qgstudio.service;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.po.User;

public interface UserService{

    /**
     * 某user登陆
     * @param user User对象
     * @return true(succeed) or false(fail)
     * */
    boolean login(User user);
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
    User getUser(String username);
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
     * 设置头像
     * */
    boolean setHeadimg();

    JSONObject getUserJSON(User user);
}