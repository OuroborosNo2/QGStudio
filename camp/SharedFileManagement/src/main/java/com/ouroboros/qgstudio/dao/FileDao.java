package com.ouroboros.qgstudio.dao;

import com.ouroboros.qgstudio.po.File;
import org.apache.commons.fileupload.FileItem;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.List;

public interface FileDao {
    MyDataSource ds = new MyDataSource();
    /** 获取指定文件
     * @param directory 文件父目录
     * @param filename 文件名
     * */
    File getFile(String directory, String filename);
    boolean insertFile(File file);
    boolean deleteFile(String directory, String filename);
    boolean updateFile(File file);
    void saveFile(InputStream in, FileOutputStream out);
}
