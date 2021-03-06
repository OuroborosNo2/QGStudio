package com.ouroboros.qgstudio.dao;

import com.ouroboros.qgstudio.po.File;

import java.io.*;

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

    int deleteFileOnDisk(String path);

    int deleteChildrenFile(String path);

    boolean renameFileOnDisk(String path, String newname);

    boolean renameChildrenFileDirectory(String path, String oldname, String newname);

    boolean newFolder(String path);

    boolean downloadFile(BufferedOutputStream out, String path);

    File getFileByGet_code(String get_code);
}
