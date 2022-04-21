package com.ouroboros.qgstudio.dao.Impl;

import com.ouroboros.qgstudio.constants.Sex;
import com.ouroboros.qgstudio.dao.CRUDUtils;
import com.ouroboros.qgstudio.dao.UserDao;
import com.ouroboros.qgstudio.po.User;

import java.sql.Connection;
import java.util.ArrayList;
import java.util.List;

public class UserDaoImpl implements UserDao {

    private Connection conn;

    @Override
    public User getUserByName(String username) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(username);
        CRUDUtils crud = new UserCRUD();
        List<Object> rs = crud.query(this.conn,"username = ?",list);
        ds.releaseConnection(this.conn);
        return getUser(rs);
    }

    @Override
    public User getUserByEmail(String email) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(email);
        CRUDUtils crud = new UserCRUD();
        list = crud.query(this.conn,"email = ?",list);//不多定义一个变量了，直接覆盖

        ds.releaseConnection(this.conn);
        return getUser(list);
    }

    private User getUser(List<Object> list) {
        if(!list.isEmpty()){
            //注册时控制好不会有同名用户，故此时不必考虑
            Sex sex = Sex.values()[(int)list.get(4)];//int转枚举
            User user = new User((String)list.get(0), (String)list.get(1), (String)list.get(2), (String)list.get(3),sex, (int)list.get(5), (String)list.get(6), (int)list.get(7), (int)list.get(8), (String)list.get(9));
            return user;
        }else{
            return null;
        }
    }

    @Override
    public boolean insertUser(User user) {
        this.conn = ds.getConnection();
        List<Object> list = new ArrayList<>();
        list.add(user.getUsername());
        list.add(user.getPassword());
        list.add(user.getNickname());
        list.add(user.getEmail());
        list.add(user.getSex().ordinal());
        list.add(user.getSecurity_question());
        list.add(user.getSecurity_answer());
        list.add(user.getPermission());
        list.add(user.getStorage());
        list.add(user.getDepartment());
        CRUDUtils crud = new UserCRUD();
        int result = crud.insert(this.conn,list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public boolean deleteUser(String username) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(username);
        CRUDUtils crud = new UserCRUD();
        int result = crud.delete(this.conn,"username = ?",list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public boolean updateUser(User user) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        //set里的占位符
        list.add(user.getUsername());
        list.add(user.getPassword());
        list.add(user.getNickname());
        list.add(user.getEmail());
        list.add(user.getSex().ordinal());
        list.add(user.getSecurity_question());
        list.add(user.getSecurity_answer());
        list.add(user.getPermission());
        list.add(user.getStorage());
        list.add(user.getDepartment());
        //range里的占位符
        list.add(user.getUsername());
        CRUDUtils crud = new UserCRUD();
        int result = crud.update(this.conn,"username = ?, password = ?, nickname = ?, email = ?, sex = ?, security_question = ?, security_answer = ?, permission = ?, storage = ?, department = ?","username = ?",list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }
}