package com.ouroboros.qgstudio.dao;

import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.*;
import java.util.List;
import java.util.Properties;

public interface CRUDUtils {
    /**
     * 不使用连接池，获取并返回一个数据库连接
     * @return 数据库连接
     */
    static Connection getConnection(){
        //专门读配置文件
        try(InputStream input = new FileInputStream("../webapps/SFM/WEB-INF/classes/com/ouroboros/qgstudio/config/jdbc.properties")){
            Properties prop = new Properties();
            prop.load(input);
            String user = prop.getProperty("user");
            String password = prop.getProperty("password");
            String url = prop.getProperty("url");
            String driver = prop.getProperty("driver");
            /*另一种方法
            不需要后缀名,而且不同方法路径不一样
            ResourceBundle resource = ResourceBundle.getBundle("jdbc");
            user = resource.getString("user");
            password = resource.getString("password");
            url = resource.getString("url");
            driver = resource.getString("driver");
            */
            //注册驱动
            Class.forName(driver);
            //获取数据库连接对象Connection
            return DriverManager.getConnection(url,user,password);
        }catch(Exception e){
            e.printStackTrace();
            return null;
        }
    }

    /**
     * @param conn   现成的连接
     * @param params 占位符的值
     * @return 插入的结果
     */
    int insert(Connection conn, List<Object> params);

    /**
     * @param conn   现成的连接
     * @param range  sql语句,删除的范围
     * @param params 占位符的值
     * @return 删除的结果
     */
    int delete(Connection conn, String range, List<Object> params);

    /**
     * @param conn  现成的连接
     * @param set   sql语句,要修改的字段和值
     * @param range sql语句,修改的范围
     * @return 删除的结果
     */
    int update(Connection conn, String set, String range, List<Object> params);

    /**
     * @param conn  现成的连接
     * @param range sql语句,查询的范围(条件)
     * @return 查询结果集，没有则返回null
     */
    List<Object> query(Connection conn, String range, List<Object> params);

    /** 关闭各资源（连接池则用连接池的方法）
     */
    static void close(Connection conn, Statement st, ResultSet rs) throws SQLException {
        if(rs!=null) {
            rs.close();
        }
        if(st!=null) {
            st.close();
        }
        conn.close();
    }
}
