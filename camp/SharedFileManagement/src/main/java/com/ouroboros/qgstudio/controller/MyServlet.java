package com.ouroboros.qgstudio.controller;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.constants.Sex;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.FileService;
import com.ouroboros.qgstudio.service.UserService;
import com.ouroboros.qgstudio.service.impl.FileServiceImpl;
import com.ouroboros.qgstudio.service.impl.UserServiceImpl;

import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.*;
import java.sql.Date;
import java.util.Locale;

@WebServlet(urlPatterns = "/*")
public class MyServlet extends BaseServlet{

    public void login(HttpServletRequest req, HttpServletResponse resp) {
        //获取参数
        UserService service = new UserServiceImpl();
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        try {
            if(!service.contain(username)) {
                resp.sendError(400, "用户不存在！");
            }else {
                User user = service.getUser(username);
                if(user.getPassword().equals(password)) {
                    service.login(user);
                    req.getSession().setAttribute("user",user);//绑定session会话
                }else {
                    resp.sendError(400, "用户名或密码错误");
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void register(HttpServletRequest req, HttpServletResponse resp) {
        //获取参数
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String email = req.getParameter("email");
        Sex sex = Sex.valueOf(req.getParameter("sex"));
        UserService service = new UserServiceImpl();

        try {
            if(service.contain(username)) {
                resp.sendError(400, "用户名已存在");
            }else {
                if(service.register(new User(username, password, email, sex))) {
                    resp.setStatus(200);
                }else {
                    resp.sendError(400);
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void logout(HttpServletRequest req, HttpServletResponse resp){
        //销毁会话
        req.getSession().invalidate();
    }

    public void getUserJSON(HttpServletRequest req, HttpServletResponse resp){
        try {
            //设置响应类型:
            resp.setContentType("application/json");
            HttpSession session = req.getSession();
            User user = (User) session.getAttribute("user");

            PrintWriter pw = resp.getWriter();
            // 写入响应:
            pw.write(new UserServiceImpl().getUserJSON(user).toJSONString());
            // 最后不要忘记flush强制输出:
            pw.flush();

        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void isFileExist(HttpServletRequest req, HttpServletResponse resp){
        resp.setContentType("text/plain");//纯文本
        try(PrintWriter pw = resp.getWriter()){
            String name = req.getParameter("file");
            File f = new File(name);
            if(f.exists()) {
                pw.write("true");
            }else {
                pw.write("false");
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void getHeadImg(HttpServletRequest req, HttpServletResponse resp){
        try{
            resp.setContentType("image/png");
            User user = new UserServiceImpl().getUser(req.getParameter("username"));
            if(user == null){
                user = (User)req.getSession().getAttribute("user");
                if(user == null){
                    resp.sendError(401, "会话失效，请重新登录");
                }
            }
            OutputStream out = resp.getOutputStream();
            File f = new File("../webapps/headImgs/"+user.getUsername()+"/headImg.png");
            if(!f.exists()) {//换成默认头像
                f = new File("../webapps/headImgs/defaultHeadImg2.png");
            }

            InputStream in = new FileInputStream(f);
            int size =in.available(); //得到文件大小
            byte[] data =new byte[size];
            in.read(data);  //读数据
            out.write(data);
            out.flush();
            in.close();
            out.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void getFileInf(HttpServletRequest req, HttpServletResponse resp){
        resp.setContentType("application/json");
        resp.setCharacterEncoding("utf-8");
        String path = req.getParameter("path");
        String filename = req.getParameter("filename");
        FileService service = new FileServiceImpl();
        try(PrintWriter pw = resp.getWriter()) {
            pw.write(service.getFileJSON(service.getFile(path, filename)).toJSONString());
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void getFileList(HttpServletRequest req, HttpServletResponse resp){
        resp.setContentType("application/json");
        resp.setCharacterEncoding("utf-8");

        //TODO 有安全问题，普通用户可以获取他人文件
        String path = req.getParameter("path");
        JSONObject jsonobj = new FileServiceImpl().getFileListJSON(path);
        try(PrintWriter pw = resp.getWriter()){
            if(jsonobj == null){
                resp.sendError(500, "未找到目录或无文件");
                return;
            }
            pw.write(jsonobj.toJSONString());
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void deleteFile(HttpServletRequest req, HttpServletResponse resp){
        String path = req.getParameter("path");
        String filename = req.getParameter("filename");
        String fileType = req.getParameter("fileType");
        FileService service = new FileServiceImpl();

        if(fileType.equals("file")){//文件
            com.ouroboros.qgstudio.po.File file = service.getFile(path,filename);
            if(file == null){
                try {
                    resp.sendError(404, "文件不存在");
                }catch(IOException e){
                    e.printStackTrace();
                }
            }else{
                if(service.deleteFile(file)) {
                    //改个人容量
                    User user = (User) req.getSession().getAttribute("user");
                    user.setStorage(user.getStorage() + file.getSize());
                    new UserServiceImpl().updateUser(user);
                }else{
                    try {
                        resp.sendError(500,"删除失败");
                    }catch(IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }else{//文件夹
            int size = service.deleteFolder(path + "/" + filename);
            //改个人容量
            User user = (User) req.getSession().getAttribute("user");
            user.setStorage(user.getStorage() + size);
            new UserServiceImpl().updateUser(user);
        }

    }

    public void newFolder(HttpServletRequest req, HttpServletResponse resp){
        String path = "../webapps/files/" + req.getParameter("path");
        if(!new FileServiceImpl().newFolder(path)){
            try {
                resp.sendError(500, "创建失败或文件夹已存在");
            }catch(IOException e){
                e.printStackTrace();
            }
        }
    }

    public void renameFile(HttpServletRequest req, HttpServletResponse resp){
        try {
            String path = req.getParameter("path");
            String filename = req.getParameter("filename");
            String newname = req.getParameter("newname");
            String fileType = req.getParameter("fileType");
            FileService service = new FileServiceImpl();

            if(fileType.equals("file")) {
                com.ouroboros.qgstudio.po.File file = service.getFile(path, filename);
                if(file == null) {
                    try {
                        resp.sendError(404, "文件不存在");
                    }catch(IOException e) {
                        e.printStackTrace();
                    }
                }else {
                    if(!service.renameFile(file, newname)){
                        resp.sendError(500,"重命名失败");
                    }
                }
            }else {
                if(!service.renameFolder(path + "/" + filename, newname)){
                    resp.sendError(500,"重命名失败");
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void getDefaultStorage(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        resp.setContentType("application/json");
        resp.setCharacterEncoding("utf-8");
        JSONObject jsonobj = new JSONObject();
        jsonobj.put("STORAGE_VISITOR",User.STORAGE_VISITOR);
        jsonobj.put("STORAGE_USER",User.STORAGE_USER);
        jsonobj.put("STORAGE_ADMINISTRATOR",User.STORAGE_ADMINISTRATOR);
        jsonobj.put("SINGLE_FILE_MAX_SIZE",User.SINGLE_FILE_MAX_SIZE);
        try(PrintWriter pw = resp.getWriter()){
            pw.write(jsonobj.toJSONString());
        }catch(IOException e){
            e.printStackTrace();
            resp.sendError(500,"未知错误");
        }
    }

    public void downloadFile(HttpServletRequest req, HttpServletResponse resp) throws IOException {
         resp.setContentType("application/octet-stream");
         String path = req.getParameter("path");
         String filename = req.getParameter("filename");
         String fileType = req.getParameter("fileType");
         FileService service = new FileServiceImpl();

         resp.setHeader("Content-Disposition","attachment;filename=\"" + filename +"\"");

         try(BufferedOutputStream out = new BufferedOutputStream(resp.getOutputStream())){
             boolean result;
            if(fileType.equals("file")){//下载文件
                com.ouroboros.qgstudio.po.File file = service.getFile(path,filename);
                if(file == null){
                    resp.sendError(404,"要下载的文件不存在");
                }
                result = service.downloadFile(out,file);
            }else{//下载文件夹
                result = service.downloadFolder(out);
            }
            if(!result){
                resp.sendError(500,"下载失败");
            }
         }catch(IOException e){
             e.printStackTrace();
             resp.sendError(500,"下载失败");
         }
    }

    public void createGet_code(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        resp.setContentType("text/plain");
        String path = req.getParameter("path");
        String filename = req.getParameter("filename");
        int times = Integer.parseInt(req.getParameter("times"));
        int deadlineLength = Integer.parseInt(req.getParameter("deadlineLength"));
        FileService service = new FileServiceImpl();

        try(PrintWriter pw = resp.getWriter()){
            String code = service.createGet_code(service.getFile(path,filename),times,deadlineLength);
            pw.write(code);
        }catch(IOException e) {
            e.printStackTrace();
            resp.sendError(500,"生成取件码失败");
        }
    }

    public void cancelShare(HttpServletRequest req, HttpServletResponse resp){
        String path = req.getParameter("path");
        String filename = req.getParameter("filename");
        FileService service = new FileServiceImpl();

        service.cancelShare(service.getFile(path,filename));
    }

    public void pickupFile(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        resp.setContentType("application/json");
        String get_code = req.getParameter("get_code").toUpperCase();
        FileService service = new FileServiceImpl();

        com.ouroboros.qgstudio.po.File file = service.getFileByGet_code(get_code);
        if(file == null){
            resp.sendError(404,"无效取件码");
            return;
        }

        if(file.getTimes()<=0 || file.getDeadline().before(new Date(System.currentTimeMillis()))){//取件码次数用尽或到期
            service.cancelShare(file);
            resp.sendError(404,"无效取件码");
            return;
        }

        try(PrintWriter pw = resp.getWriter()) {
            pw.write(service.getFileJSON(service.getFile(file.getDirectory(), file.getFilename())).toJSONString());
            file.setTimes(file.getTimes()-1);
            service.updateFile(file);
        }catch(IOException e){
            e.printStackTrace();
        }
        /*resp.setCharacterEncoding("UTF-8");
        resp.setHeader("Content-Disposition","attachment;filename=\"" + file.getFilename() +"\"");
        try(BufferedOutputStream out = new BufferedOutputStream(resp.getOutputStream())){
            boolean result;
            result = service.downloadFile(out,file);

            if(result){
                file.setTimes(file.getTimes()-1);
                service.updateFile(file);
            }else{
                resp.sendError(500,"下载失败");
            }
        }catch(IOException e){
            e.printStackTrace();
            resp.sendError(500,"下载失败");
        }*/
    }
}
