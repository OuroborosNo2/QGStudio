package com.ouroboros.qgstudio.service.impl;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.dao.Impl.UserDaoImpl;
import com.ouroboros.qgstudio.dao.UserDao;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.UserService;

import javax.servlet.http.HttpSession;
import java.io.File;

public class UserServiceImpl implements UserService {

    UserDao dao = new UserDaoImpl();

    @Override
    public boolean login(User user) {
        if(!contain(user.getUsername())){//不存在此用户则拒绝登陆
            return false;
        }else{
            return true;
        }
    }

    @Override
    public boolean sendMessage(User user, String message) {
        return false;
    }//TODO

    @Override
    public boolean contain(String username) {
        return dao.getUserByName(username)==null ? false : true;
    }

    @Override
    public User getUser(String username) {
        return dao.getUserByName(username);
    }

    @Override
    public boolean register(User user) {
        boolean result = dao.insertUser(user);
        if(result){
            File f = new File("../webapps/files/"+user.getUsername());
            f.mkdirs();
        }
        return result;
    }

    @Override
    public boolean delete(User user) {
        return dao.deleteUser(user.getUsername());
    }

    @Override
    public boolean setHeadimg() {
        return false;
    }

    @Override
    public boolean updateUser(User user) {
        return dao.updateUser(user);
    }

    @Override
    public JSONObject getUserJSON(User user) {
        JSONObject jsonobj = new JSONObject();
        jsonobj.put("username", user.getUsername());
        jsonobj.put("password", user.getPassword());
        jsonobj.put("nickname", user.getNickname());
        jsonobj.put("email", user.getEmail());
        jsonobj.put("sex", user.getSex().ordinal());
        if(user.getSecurity_question() == 0) {//未设置
            jsonobj.put("security_question", null);
            jsonobj.put("security_answer", null);
        }else {
            jsonobj.put("security_question", new UserDaoImpl().readSecurityQuestions().get(user.getSecurity_question() - 1));
            jsonobj.put("security_answer", user.getSecurity_answer());
        }
        jsonobj.put("permission", user.getPermission());
        jsonobj.put("storage", user.getStorage());
        jsonobj.put("department", user.getDepartment());
        return jsonobj;
    }
}
