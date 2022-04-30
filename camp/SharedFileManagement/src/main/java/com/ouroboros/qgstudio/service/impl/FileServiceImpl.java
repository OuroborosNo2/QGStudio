package com.ouroboros.qgstudio.service.impl;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.dao.FileDao;
import com.ouroboros.qgstudio.dao.Impl.FileDaoImpl;
import com.ouroboros.qgstudio.dao.Impl.UserDaoImpl;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.FileService;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.io.FilenameUtils;

import java.io.*;
import java.sql.Date;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Random;

public class FileServiceImpl implements FileService {

    FileDao dao = new FileDaoImpl();

    @Override
    public void processUploadField(FileItem fileItem, User user, String path) {
        try {
            // 得到文件输入流
            InputStream in = fileItem.getInputStream();
            // 创建一个文件存盘的目录
            File storeDirectory = new File("../webapps/files/" + path);// 即代表文件又代表目录
            if (!storeDirectory.exists()) {
                storeDirectory.mkdirs();// 创建一个指定的目录
            }
            // 得到上传的名字
            String fileName = fileItem.getName();
            // 处理文件名
            if (fileName != null) {
                /*
                将文件名的父目录去掉
                fileName = filename.substring(fileName.lastIndexOf(File.separator)+1);
                substring:获取字符串从某个位置开始的子字符串
                File.separator: 文件分隔符 如“/”
                indexOf:包含 xx 的第一个位置
                lastIndexOf:倒着开始数的 indexOf
                */
                fileName = FilenameUtils.getName(fileName);// 效果同上
                // 解决文件同名的问题
                int i=1;
                while(new File(storeDirectory +File.separator+ fileName).exists()){
                    //TODO 如果上传的文件本身就带（）或者. 就会有错，稍后用正则
                    //. 、 $、 | 和 * 等转义字符，必须得加 \\
                    String[] s1 = fileName.split("\\.");
                    String[] s2 = s1[0].split("\\(");
                    fileName = s2[0] + "(" + i + ")." + s1[1];
                    i++;
                }
            }
            // 通过文件输出流将上传的文件保存到磁盘
            FileOutputStream out = new FileOutputStream(storeDirectory.getPath() + File.separator +fileName);
            //保存文件
            int size = dao.saveFile(in,out);
            //录入相应的文件信息
            Date deadline = null;
            //deadLine = Timestamp.valueOf("9999-12-31 00:00:00");//null可以存入数据库，不需要额外定特殊值
            dao.insertFile(new com.ouroboros.qgstudio.po.File(0,fileName,path,-1,deadline,null,size));
            //更新用户个人空间
            user.setStorage(user.getStorage()-size);
            new UserDaoImpl().updateUser(user);
            //删除缓存文件
            fileItem.delete();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public JSONObject getFileJSON(com.ouroboros.qgstudio.po.File file) {
        if(file == null){
            return null;
        }
        JSONObject jsonobj = new JSONObject();
        jsonobj.put("filename", file.getFilename());
        jsonobj.put("directory", file.getDirectory());
        jsonobj.put("times", file.getTimes());
        jsonobj.put("deadline", file.getDeadline() == null ? null : file.getDeadline().toString());
        jsonobj.put("get_code", file.getGet_code());
        jsonobj.put("size", file.getSize());
        return jsonobj;
    }

    @Override
    public JSONObject getFileListJSON(String path){
        String totalPath = "../webapps/files/" + path;
        File f = new File(totalPath);

        File[] listFiles = f.listFiles();
        if(listFiles == null){//找不到目录或无文件
            return null;
        }

        //List<File> files = new ArrayList<>();//装文件
        List<String> folders = new ArrayList<>();//装目录
        JSONObject jsonobj = new JSONObject();//最外层
        List<JSONObject> fjson = new ArrayList<>();//文件json数组,不需要目录json数组，直接放目录名字数组

        //将文件和文件夹分离
        for(File file : listFiles){
            if(file.isDirectory()){
                //目录
                folders.add(file.getName());
            }else{
                //文件
                //files.add(file);
                fjson.add(this.getFileJSON(dao.getFile(path, file.getName())));
            }
        }
        jsonobj.put("files",fjson.toArray());
        jsonobj.put("folders",folders.toArray());

        return jsonobj;
    }

    @Override
    public com.ouroboros.qgstudio.po.File getFile(String directory, String filename){
        return dao.getFile(directory, filename);
    }

    @Override
    public boolean deleteFile(com.ouroboros.qgstudio.po.File file) {
        String path = "../webapps/files/" + file.getDirectory() + "/" + file.getFilename();
        //TODO 这两个操作必须是”原子“的，必须同时成功，且调用顺序不能变。要注意并发造成的问题
        return dao.deleteFileOnDisk(path)!=-1  && dao.deleteFile(file);
    }

    @Override
    public int deleteFolder(String path) {
        return dao.deleteChildrenFile("../webapps/files/" + path);
    }

    @Override
    public boolean newFolder(String path) {
        return dao.newFolder(path);
    }

    @Override
    public boolean renameFile(com.ouroboros.qgstudio.po.File file, String newname) {
        String path = "../webapps/files/" + file.getDirectory() + "/" + file.getFilename();
        file.setFilename(newname);
        synchronized(file) {
            return dao.renameFileOnDisk(path,newname) && dao.updateFile(file);
        }
    }

    @Override
    public boolean renameFolder(String path, String newname) {
        return dao.renameChildrenFileDirectory(path,path,newname) && dao.renameFileOnDisk("../webapps/files/" + path,newname);
    }

    @Override
    public boolean downloadFile(BufferedOutputStream out, com.ouroboros.qgstudio.po.File file) {
        return dao.downloadFile(out,"../webapps/files/" + file.getDirectory() + "/" + file.getFilename());
    }

    @Override
    public boolean downloadFolder(OutputStream out) {
        //TODO
        return false;
    }

    @Override
    public String createGet_code(com.ouroboros.qgstudio.po.File file, int times, int deadlineLength) {
        //生成随机字符串
        String str="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        Random random=new Random();
        StringBuffer sb;
        do {//生成随机字符串
            sb = new StringBuffer();
            for(int i = 0; i < 5; i++) {
                int number = random.nextInt(36);
                sb.append(str.charAt(number));
            }
        }while(dao.getFileByGet_code(sb.toString()) != null);//直到无重复取件码

        file.setGet_code(sb.toString());
        file.setTimes(times);

        Timestamp tt = new Timestamp(System.currentTimeMillis());
        Calendar cc = Calendar.getInstance();
        cc.setTime(tt);
        cc.add(Calendar.DAY_OF_MONTH, deadlineLength);//加n天
        file.setDeadline(new java.sql.Date(cc.getTime().getTime()));

        dao.updateFile(file);
        return sb.toString();
    }

    @Override
    public com.ouroboros.qgstudio.po.File getFileByGet_code(String get_code) {
        return dao.getFileByGet_code(get_code);
    }

    public boolean updateFile(com.ouroboros.qgstudio.po.File file){
        return dao.updateFile(file);
    }

    @Override
    public boolean cancelShare(com.ouroboros.qgstudio.po.File file) {
        file.setGet_code(null);
        file.setDeadline(null);
        file.setTimes(-1);
        return dao.updateFile(file);
    }
}
