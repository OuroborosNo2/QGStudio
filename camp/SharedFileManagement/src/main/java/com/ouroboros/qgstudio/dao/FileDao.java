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
    boolean deleteFile(File file);
    boolean updateFile(File file);

    //以下是io操作

    /** 从一处读文件并写到另一处
     * @param in 读数据
     * @param out 写数据
     * @return 写入的文件大小
     * */
    int saveFile(InputStream in, FileOutputStream out);
    /** 在磁盘上删除file对应的文件
     * @param file 是po的File 不是io的
     * */
    boolean deleteFileOnDisk(File file);
}
