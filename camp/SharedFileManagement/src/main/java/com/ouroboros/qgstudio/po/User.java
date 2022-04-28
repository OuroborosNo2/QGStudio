package com.ouroboros.qgstudio.po;

import com.ouroboros.qgstudio.constants.Permission;
import com.ouroboros.qgstudio.constants.Sex;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Objects;
import java.util.Properties;

public class User {
    private String username;
    private String password;
    private String nickname;
    private String email;
    private Sex sex;
    private int security_question;
    private String security_answer;
    private Permission permission;
    private int storage;
    private String department;

    //三种权限组的默认存储空间
    public static int STORAGE_VISITOR;
    public static int STORAGE_USER;
    public static int STORAGE_ADMINISTRATOR;
    public static int SINGLE_FILE_MAX_SIZE;

    static{
        try(InputStream input = new FileInputStream("../webapps/SFM/WEB-INF/classes/com/ouroboros/qgstudio/config/default_storage.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            STORAGE_VISITOR = Integer.parseInt(prop.getProperty("visitor"));
            STORAGE_USER = Integer.parseInt(prop.getProperty("user"));
            STORAGE_ADMINISTRATOR = Integer.parseInt(prop.getProperty("administrator"));
            SINGLE_FILE_MAX_SIZE = Integer.parseInt(prop.getProperty("singleFileMaxSize"));
        }catch(Exception e){
            e.printStackTrace();
        }
    }


    public User(String username, String password, String nickname, String email, Sex sex, int security_question, String security_answer, Permission permission, int storage, String department){
        this.username = username;
        this.password = password;
        this.nickname = nickname;
        this.email = email;
        this.sex = sex;
        this.security_question = security_question;
        this.security_answer = security_answer;
        this.permission = permission;
        this.storage = storage;
        this.department = department;
    }

    //仅用于注册时
    public User(String username, String password, String email, Sex sex){
        this.username = username;
        this.password = password;
        this.nickname = username;
        this.email = email;
        this.sex = sex;
        this.security_question = 0;
        this.security_answer = null;
        this.permission = Permission.user;
        this.storage = STORAGE_USER;
        this.department = null;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Sex getSex() {
        return sex;
    }

    public void setSex(Sex sex) {
        this.sex = sex;
    }

    public int getSecurity_question() {
        return security_question;
    }

    public void setSecurity_question(int security_question) {
        this.security_question = security_question;
    }

    public String getSecurity_answer() {
        return security_answer;
    }

    public void setSecurity_answer(String security_answer) {
        this.security_answer = security_answer;
    }

    public Permission getPermission() {
        return permission;
    }

    public void setPermission(Permission permission) {
        this.permission = permission;
    }

    public int getStorage() {
        return storage;
    }

    public void setStorage(int storage) {
        this.storage = storage;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return security_question == user.security_question && permission == user.permission && storage == user.storage && username.equals(user.username) && password.equals(user.password) && nickname.equals(user.nickname) && email.equals(user.email) && sex == user.sex && Objects.equals(security_answer, user.security_answer) && department.equals(user.department);
    }

    @Override
    public int hashCode() {
        return Objects.hash(username, password, nickname, email, sex, security_question, security_answer, permission, storage, department);
    }
}