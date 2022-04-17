package com.ouroboros.qgstudio;

import com.ouroboros.qgstudio.constants.Sex;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.UserService;
import com.ouroboros.qgstudio.service.impl.UserServiceImpl;

public class Main {
    public static void main(String[] args){
        UserService service = new UserServiceImpl();
        String username = "test";
        String password = "root";
        Sex sex = Sex.male;
        String email = "764904497@qq.com";
        //service.register(new User(username,password,sex,email));
        System.out.println(service.contain(username));
    }
}
