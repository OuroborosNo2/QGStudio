package com.ouroboros.qgstudio.controller;

import com.ouroboros.qgstudio.dao.FileDao;
import com.ouroboros.qgstudio.dao.UserDao;
import com.ouroboros.qgstudio.service.impl.UserServiceImpl;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class AppListener implements ServletContextListener {
    // 在此初始化WebApp
    public void contextInitialized(ServletContextEvent sce) {
        System.out.println("WebApp initialized.");
    }

    // 在此清理WebApp
    public void contextDestroyed(ServletContextEvent sce) {
        UserDao.ds.destroyDataSource();
        FileDao.ds.destroyDataSource();
        System.out.println("WebApp destroyed.");
    }
}