package com.ouroboros.qgstudio.po;

import com.ouroboros.qgstudio.constants.Sex;

import java.util.Objects;

public class User{
    private String username;
    private String password;
    private Sex sex;
    private String email;

    public User(String username,String password,Sex sex,String email){
        this.username = username;
        this.password = password;
        this.sex = sex;
        this.email = email;
    }

    public void setUsername(String username){
        this.username = username;
    }

    public void setPassword(String password){
        this.password = password;
    }

    public void setSex(Sex sex) {
        this.sex = sex;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public Sex getSex() {
        return sex;
    }

    public String getEmail() {
        return email;
    }


    @Override
    public boolean equals(Object o) {
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return username.equals(user.username) && password.equals(user.password) && email.equals(user.email) && sex == user.sex;
    }

    @Override
    public int hashCode() {
        return Objects.hash(username, password, email, sex);
    }
}