package com.ouroboros.qgstudio.dao;

import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.Properties;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/*
实际上连接池要管理三种资源，一个connection对应一个statement是极浪费资源的，通常用户申请时是提供statement
*/


public class MyDataSource{

    private LinkedList<Connection> pool = new LinkedList<>();

    private static int maximumPoolSize = 10;//默认为10

    private static String user = "";
    private static String password = "";
    private static String url = "";
    private static String driver = "";


    //与wait()和notify()类似
    //成对使用，而且不用写synchronized，只用一个condition对象能操作多个线程。
    private Lock lock = new ReentrantLock();
    private Condition condition = lock.newCondition();

    static {
        //读取配置文件
        try(InputStream input = new FileInputStream("../webapps/demo/WEB-INF/classes/com/ouroboros/qgstudio/config/jdbc.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            user = prop.getProperty("user");
            password = prop.getProperty("password");
            url = prop.getProperty("url");
            driver = prop.getProperty("driver");
        }catch(Exception e){
            e.printStackTrace();
        }
        // 注册驱动
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    // 通过构造方法初始化连接
    public MyDataSource() {
        for (int i = 0; i < maximumPoolSize; i++) {
            try {
                Connection conn = DriverManager.getConnection(url, user, password);
                pool.addLast(conn);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static void setMaximumPoolSize(int size){
        MyDataSource.maximumPoolSize = size;
    }
    // 获取数据库连接
    public Connection getConnection() {
        Connection conn = null;
        lock.lock();
        try {
            while (pool.size() < 0) {
                try {
                    condition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            if (!pool.isEmpty()) {
                conn = pool.removeFirst();//获取连接即将连接移出连接池
            }
            return conn;
        } finally {
            lock.unlock();
        }
    }

    // 释放数据库连接
    public void releaseConnection(Connection conn) {
        if (conn != null) {
            lock.lock();
            try {
                // 释放连接过程就是把连接放回连接池过程
                pool.addLast(conn);
                condition.signal();
            } finally {
                lock.unlock();
            }
        }
    }
}
