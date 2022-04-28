package com.ouroboros.qgstudio.service.impl;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.dao.FileDao;
import com.ouroboros.qgstudio.dao.Impl.FileDaoImpl;
import com.ouroboros.qgstudio.dao.Impl.UserDaoImpl;
import com.ouroboros.qgstudio.po.User;
import com.ouroboros.qgstudio.service.FileService;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.io.FilenameUtils;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

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
            Timestamp deadline = null;
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
        jsonobj.put("deadline", file.getDeadline());
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
        //这两个操作必须是”原子“的，必须同时成功，且调用顺序不能变。要注意并发造成的问题
        synchronized(file) {//上file锁实际上没有用，并发处理是不是这个项目最难的地方？
            return dao.deleteFileOnDisk(path) && dao.deleteFile(file);
        }
    }

    @Override
    public boolean deleteFolder(String path) {
        return dao.deleteFileOnDisk(path);
    }

    @Override
    public boolean newFolder(String path) {
        return dao.newFolder(path);
    }


}
