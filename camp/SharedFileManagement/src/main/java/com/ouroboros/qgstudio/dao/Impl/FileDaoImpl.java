package com.ouroboros.qgstudio.dao.Impl;

import com.ouroboros.qgstudio.dao.CRUDUtils;
import com.ouroboros.qgstudio.dao.FileDao;
import com.ouroboros.qgstudio.po.File;
import org.apache.commons.fileupload.FileItem;

import java.io.*;
import java.sql.Connection;
import java.sql.Date;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

public class FileDaoImpl implements FileDao {

    private Connection conn;

    @Override
    public File getFile(String directory, String filename) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(directory);
        list.add(filename);
        CRUDUtils crud = new FileCRUD();
        List<Object> rs = crud.query(this.conn,"directory = ? AND filename = ?",list);
        ds.releaseConnection(this.conn);
        if(!rs.isEmpty()){
            return new File((int)rs.get(0),(String)rs.get(1), (String)rs.get(2), (int)rs.get(3), (Timestamp) rs.get(4), (String)rs.get(5), (int)rs.get(6));
        }else{
            return null;
        }
    }

    @Override
    public boolean insertFile(File file) {
        this.conn = ds.getConnection();
        List<Object> list = new ArrayList<>();
        list.add(file.getFilename());
        list.add(file.getDirectory());
        list.add(file.getTimes());
        list.add(file.getDeadline());
        list.add(file.getGet_code());
        list.add(file.getSize());

        CRUDUtils crud = new FileCRUD();
        int result = crud.insert(this.conn,list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public boolean deleteFile(File file) {
        if(file == null){
            return false;
        }
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(file.getId());
        CRUDUtils crud = new FileCRUD();
        int result = crud.delete(this.conn,"id = ?",list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public boolean updateFile(File file) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        //set里的占位符
        list.add(file.getFilename());
        list.add(file.getDirectory());
        list.add(file.getTimes());
        list.add(file.getDeadline());
        list.add(file.getGet_code());
        list.add(file.getSize());
        //range里的占位符
        list.add(file.getId());
        CRUDUtils crud = new FileCRUD();
        int result = crud.update(this.conn,"filename = ?, directory = ?, times = ?, deadline = ?, get_code = ?, size = ?","id = ?",list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public int saveFile(InputStream in, FileOutputStream out) {
        int size = 0;
        try {
            // 通过文件输出流将上传的文件保存到磁盘
            int len = 0;
            byte[] b = new byte[1024];
            while((len = in.read(b)) != -1) {
                out.write(b, 0, len);
                size += len;
            }
            out.flush();
            out.close();
            in.close();
        }catch(IOException e){
            e.printStackTrace();
        }
        return size;
    }

    @Override
    public int deleteFileOnDisk(String path) {
        java.io.File f = new java.io.File(path);
        int size = (int)f.length();
        if(f.exists()){//存在文件，执行删除
            return f.delete() ? size : -1;
        }else{//磁盘上不存在此文件
            return -1;
        }
    }

    @Override
    public int deleteChildrenFile(String path) {
        int totalSize = 0;
        try {
            java.io.File f = new java.io.File(path);
            java.io.File[] listFiles = f.listFiles();
            if(listFiles != null) {//目录下有东西,把目录下所有文件也删了
                //将文件和文件夹分离
                for(java.io.File file : listFiles) {
                    if(file.isDirectory()) {
                        //目录
                        totalSize += this.deleteChildrenFile(path + "/" + file.getName());
                    }else {
                        //文件
                        String[] str = path.split("../webapps/files/");
                        com.ouroboros.qgstudio.po.File toDelete = this.getFile(str.length==0 ? "" : str[1], file.getName());
                        this.deleteFile(toDelete);
                        totalSize += this.deleteFileOnDisk(path + "/" + file.getName());
                    }
                }
            }
            f.delete();
        }catch(Exception e){
            e.printStackTrace();
        }
        return totalSize;
    }

    @Override
    public boolean renameChildrenFileDirectory(String path, String oldpath, String newname) {
        try {
            java.io.File f = new java.io.File("../webapps/files/" + path);
            java.io.File[] listFiles = f.listFiles();
            if(listFiles != null) {//目录下有东西,要把他们的父路径也改了
                //将文件和文件夹分离
                for(java.io.File file : listFiles) {
                    if(file.isDirectory()) {
                        //目录
                        this.renameChildrenFileDirectory(path + "/" + file.getName(), oldpath, newname);
                    }else {
                        //文件
                        com.ouroboros.qgstudio.po.File toUpdate = this.getFile(path, file.getName());
                        String[] str = path.split(oldpath);
                        toUpdate.setDirectory(oldpath.substring(0, oldpath.lastIndexOf("/") + 1) + newname + (str.length==0 ? "" : str[1]));
                        this.updateFile(toUpdate);
                    }
                }
            }
        }catch(Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    @Override
    public boolean renameFileOnDisk(String path, String newname) {

        java.io.File f1 = new java.io.File(path);
        java.io.File f2 = new java.io.File(path.substring(0,path.lastIndexOf("/")+1)+newname);
        if(f1.exists()){//存在文件，执行重命名
            return f1.renameTo(f2);
        }else{//磁盘上不存在此文件
            return false;
        }
    }

    @Override
    public boolean newFolder(String path) {
        java.io.File f = new java.io.File(path);
        if(f.exists()){
            return false;
        }else{
            return f.mkdir();//要求上级文件夹存在
        }
    }

    @Override
    public boolean downloadFile(BufferedOutputStream out, String path) {
        java.io.File f = new java.io.File(path);
        if(f.exists()) {
            try(BufferedInputStream in = new BufferedInputStream(new FileInputStream(f))){
                int len;
                byte[] b = new byte[1024];
                while((len = in.read(b)) != -1){
                    out.write(b,0,len);
                }
                out.flush();
            }catch(IOException e){
                e.printStackTrace();
                return false;
            }
            return true;
        }else{
            return false;
        }
    }
}
