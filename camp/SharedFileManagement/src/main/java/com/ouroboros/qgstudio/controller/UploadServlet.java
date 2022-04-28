package com.ouroboros.qgstudio.controller;

import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.FileService;
import com.ouroboros.qgstudio.service.impl.FileServiceImpl;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.util.List;

@WebServlet(urlPatterns = "/upload")
public class UploadServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        User user = (User) req.getSession().getAttribute("user");
        if(user == null){
            resp.sendError(401,"会话失效，请重新登录");
            return;
        }
        //使用fileupload组件：
        //1. 创建工厂类DiskFileItemFactory对象：创建一个DiskFileItemFactory工厂类
        DiskFileItemFactory factory = new DiskFileItemFactory();
        factory.setRepository(new File("../webapps/temp"));//指定临时文件的存储目录
        //2. 使用工厂创建解析器对象：创建一个ServletFileUpload核心对象
        ServletFileUpload fileUpload = new ServletFileUpload(factory);
        fileUpload.setHeaderEncoding("UTF-8");
        try {
            fileUpload.setSizeMax(user.getStorage());//多文件总大小不能超过用户剩余的存储空间
        }catch(Exception e){
            resp.sendError(403,"空间不足");
            e.printStackTrace();
        }
        //3. 使用解析器来解析request对象：
        List<FileItem> list = null;
        try {
            list = fileUpload.parseRequest(req);
        }catch(FileUploadException e) {
            resp.sendError(400,"formData解析失败");
            e.printStackTrace();
        }
        FileService service = new FileServiceImpl();
        String path = "";
        for (FileItem fileItem : list) {
            if (fileItem.isFormField()) {
                // 普通表单项
                String name = fileItem.getFieldName();
                //获取值
                if(name.equals("path")) {
                    path = fileItem.getString("utf-8");
                }
            } else {
                // 上传表单项
                service.processUploadField(fileItem,user,path);
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        doGet(req,resp);
    }
}
