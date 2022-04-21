package com.ouroboros.qgstudio.dao;

import com.ouroboros.qgstudio.po.User;

public interface UserDao{
    MyDataSource ds = new MyDataSource();
    User getUserByName(String username);
    User getUserByEmail(String eamil);
    boolean insertUser(User user);
    boolean deleteUser(String user);
    boolean updateUser(User user);

}