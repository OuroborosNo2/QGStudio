package com.ouroboros.qgstudio.dao;

import com.ouroboros.qgstudio.po.User;

public interface UserDao{
    MyDataSource ds = new MyDataSource();
    User getUserByName(String username);
    User getUserByEmail(String email);
    boolean insertUser(User user);
    boolean deleteUser(String username);
    boolean updateUser(User user);

}