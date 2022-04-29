package com.ouroboros.qgstudio.service;

import com.alibaba.fastjson.JSONObject;
import com.ouroboros.qgstudio.po.File;
import com.ouroboros.qgstudio.po.User;
import org.apache.commons.fileupload.FileItem;

import javax.servlet.http.HttpServletRequest;
import java.io.BufferedOutputStream;
import java.io.OutputStream;

public interface FileService {
    void processUploadField(FileItem fileItem, User user, String path);
    JSONObject getFileJSON(File file);
    JSONObject getFileListJSON(String path);
    File getFile(String directory, String filename);
    boolean deleteFile(File file);
    int deleteFolder(String path);
    boolean newFolder(String path);
    boolean renameFile(File file, String newname);
    boolean renameFolder(String path, String newname);
    boolean downloadFile(BufferedOutputStream out, File file);
    boolean downloadFolder(OutputStream out);
}
