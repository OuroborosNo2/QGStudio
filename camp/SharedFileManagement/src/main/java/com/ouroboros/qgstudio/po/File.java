package com.ouroboros.qgstudio.po;

import java.sql.Timestamp;

public class File {
    private String filename;
    private String directory;
    private int times;//不限：-1
    private Timestamp deadline;//不限：9999-12-31 00:00:00
    private String get_code;//不限：null
    private int size;//int 最大为2g左右，够用了，不需要long，但要限制单个文件最大值

    public File(String filename, String directory, int times, Timestamp deadline, String get_code, int size) {
        this.filename = filename;
        this.directory = directory;
        this.times = times;
        this.deadline = deadline;
        this.get_code = get_code;
        this.size = size;
    }

    public String getFilename() {
        return filename;
    }

    public String getDirectory() {
        return directory;
    }

    public int getTimes() {
        return times;
    }

    public Timestamp getDeadline() {
        return deadline;
    }

    public String getGet_code() {
        return get_code;
    }

    public int getSize() {
        return size;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public void setDirectory(String directory) {
        this.directory = directory;
    }

    public void setTimes(int times) {
        this.times = times;
    }

    public void setDeadline(Timestamp deadline) {
        this.deadline = deadline;
    }

    public void setGet_code(String get_code) {
        this.get_code = get_code;
    }

    public void setSize(int size) {
        this.size = size;
    }


}
