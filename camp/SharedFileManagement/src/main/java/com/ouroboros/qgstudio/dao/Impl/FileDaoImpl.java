package com.ouroboros.qgstudio.dao.Impl;

import com.ouroboros.qgstudio.dao.CRUDUtils;
import com.ouroboros.qgstudio.dao.FileDao;
import com.ouroboros.qgstudio.po.File;
import org.apache.commons.fileupload.FileItem;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.Date;
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
            return new File((String)list.get(0), (String)list.get(1), (int)list.get(2), (Date) list.get(3), (String)list.get(4), (int)list.get(5));
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
    public boolean deleteFile(String directory, String filename) {
        this.conn = ds.getConnection();

        List<Object> list = new ArrayList<>();
        list.add(directory);
        list.add(filename);
        CRUDUtils crud = new FileCRUD();
        int result = crud.delete(this.conn,"directory = ? AND filename = ?",list);

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
        list.add(file.getDirectory());
        list.add(file.getFilename());
        CRUDUtils crud = new FileCRUD();
        int result = crud.update(this.conn,"filename = ?, directory = ?, times = ?, deadline = ?, get_code = ?, size = ?","directory = ? AND filename = ?",list);

        ds.releaseConnection(this.conn);
        return result != -1;//result==-1 ? false : true的简化
    }

    @Override
    public void saveFile(InputStream in, FileOutputStream out) {
        try {
            // 通过文件输出流将上传的文件保存到磁盘
            int len = 0;
            byte[] b = new byte[1024];
            while((len = in.read(b)) != -1) {
                out.write(b, 0, len);
            }
            out.close();
            in.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
