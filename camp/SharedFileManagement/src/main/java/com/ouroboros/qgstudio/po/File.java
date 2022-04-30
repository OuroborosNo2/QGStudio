package com.ouroboros.qgstudio.po;

import java.sql.Date;

public class File {
    private int id;
    private String filename;
    private String directory;
    private int times;//不限：-1
    private Date deadline;//不限：null
    private String get_code;//不限：null
    private int size;//int 最大为2g左右，够用了，不需要long，但要限制单个文件最大值

    public File(int id, String filename, String directory, int times, Date deadline, String get_code, int size) {
        this.id = id;
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

    public Date getDeadline() {
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

    public void setDeadline(Date deadline) {
        this.deadline = deadline;
    }

    public void setGet_code(String get_code) {
        this.get_code = get_code;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
