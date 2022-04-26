package com.ouroboros.qgstudio.dao.Impl;

import com.ouroboros.qgstudio.dao.CRUDUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class UserCRUD implements CRUDUtils {
    @Override
    public int insert(Connection conn, List<Object> params) {
        try(PreparedStatement ps = conn.prepareStatement("INSERT INTO user (username,password,nickname,email,sex,security_question,security_answer,permission,storage,department) VALUES(?,?,?,?,?,?,?,?,?,?);")){
            //写在括号里能自动释放，自己只需释放conn
            for(int i = 0; i < params.size(); i++) {//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i + 1, params.get(i));
            }
            int result = ps.executeUpdate();
            return result;
        }catch(SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    @Override
    public int delete(Connection conn, String range, List<Object> params) {
        try(PreparedStatement ps = conn.prepareStatement("DELETE FROM user WHERE " + range + ";")) {

            for(int i = 0; i < params.size(); i++) {//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i + 1, params.get(i));
            }
            int result = ps.executeUpdate();

            return result;
        }catch(SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    @Override
    public int update(Connection conn, String set, String range, List<Object> params) {
        try (PreparedStatement ps = conn.prepareStatement("UPDATE user SET " + set + " WHERE " + range + ";")){

            for(int i = 0; i < params.size(); i++) {//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i + 1, params.get(i));
            }

            int result = ps.executeUpdate();

            return result;
        }catch(SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    @Override
    public List<Object> query(Connection conn, String range, List<Object> params){
        try (PreparedStatement ps = conn.prepareStatement("SELECT * FROM user WHERE " +range+ ";")){

            for(int i=0;i<params.size();i++){//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i+1,params.get(i));
            }

            try(ResultSet rs = ps.executeQuery();){
                List<Object> str = new ArrayList<>();
                while(rs.next()){
                    //(username,password,email,sex,permission,storage,department)
                    str.add(rs.getString("username"));
                    str.add(rs.getString("password"));
                    str.add(rs.getString("nickname"));
                    str.add(rs.getString("email"));
                    str.add(rs.getInt("sex"));
                    str.add(rs.getInt("security_question"));
                    str.add(rs.getString("security_answer"));
                    str.add(rs.getInt("permission"));
                    str.add(rs.getInt("storage"));
                    str.add(rs.getString("department"));
                }
                return str;
            }
        }catch(SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

}
