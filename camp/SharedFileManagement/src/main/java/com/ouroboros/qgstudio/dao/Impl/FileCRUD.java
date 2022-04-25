package com.ouroboros.qgstudio.dao.Impl;

import com.ouroboros.qgstudio.dao.CRUDUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class FileCRUD implements CRUDUtils {
    @Override
    public int insert(Connection conn, List<Object> params) {
        try(PreparedStatement ps = conn.prepareStatement("INSERT INTO file (filename,directory,times,deadline,get_code,size) VALUES(?,?,?,?,?,?,?);")){
            //写在括号里能自动释放，自己只需释放conn
            for(int i = 0; i < 7; i++) {
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
        try(PreparedStatement ps = conn.prepareStatement("DELETE FROM file WHERE " + range + ";")) {

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
        try (PreparedStatement ps = conn.prepareStatement("UPDATE file SET " + set + " WHERE " + range + ";")){

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
        try (PreparedStatement ps = conn.prepareStatement("SELECT * FROM file WHERE " +range+ ";")){

            for(int i=0;i<params.size();i++){//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i+1,params.get(i));
            }

            try(ResultSet rs = ps.executeQuery();){
                List<Object> str = new ArrayList<>();
                while(rs.next()){
                    //(filename,directory,times,deadline,get_code,size)
                    str.add(rs.getString("filename"));
                    str.add(rs.getString("directory"));
                    str.add(rs.getInt("times"));
                    str.add(rs.getDate("deadline"));
                    str.add(rs.getInt("get_Code"));
                    str.add(rs.getInt("size"));
                }
                return str;
            }


        }catch(SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

}
