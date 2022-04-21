package com.ouroboros.qgstudio.po;

import com.ouroboros.qgstudio.constants.Sex;

import java.util.Objects;

public class User {
    private String username;
    private String password;
    private String nickname;
    private String email;
    private Sex sex;
    private int security_question;
    private String security_answer;
    private int permission;
    private int storage;
    private String department;

    public User(String username, String password, String nickname, String email, Sex sex, int security_question, String security_answer, int permission, int storage, String department) {
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

    public int getPermission() {
        return permission;
    }

    public void setPermission(int permission) {
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