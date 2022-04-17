package com.ouroboros.qgstudio.service.impl;

import com.ouroboros.qgstudio.dao.Impl.UserDaoImpl;
import com.ouroboros.qgstudio.dao.UserDao;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.UserService;

import javax.servlet.http.HttpSession;

public class UserServiceImpl implements UserService {

    UserDao dao = new UserDaoImpl();

    @Override
    public boolean login(User user, HttpSession session) {
        if(isOnline(user) || !contain(user.getUsername())){//已在线或不存在此用户都拒绝登陆
            return false;
        }else{
            UserService.userPool.put(session,user);
            session.setAttribute("user",user);
            return true;
        }
    }

    @Override
    public boolean isOnline(User user) {
        for(User u : UserService.userPool.values()){
            if(u.getUsername().equals(user.getUsername())){//在用户池找到匹配用户
                return true;
            }
        }
        return false;//找不到
    }

    @Override
    public boolean forceOffline(User user) {
        return false;
    }//TODO

    @Override
    public boolean sendMessage(User user, String message) {
        return false;
    }//TODO

    @Override
    public boolean contain(String username) {
        return dao.getUserByName(username)==null ? false : true;
    }

    @Override
    public User get(String username) {
        return dao.getUserByName(username);
    }

    @Override
    public boolean register(User user) {
        return dao.insertUser(user);
    }

    @Override
    public boolean delete(User user) {
        if(isOnline(user)){
            ban(user,3600000);
            forceOffline(user);
        }
        return dao.deleteUser(user.getUsername());
    }

    @Override
    public boolean ban(User user, int time) {
        return false;
    }//TODO

    @Override
    public boolean unban(User user) {
        return false;
    }//TODO
}
