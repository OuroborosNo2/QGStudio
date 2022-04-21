package com.ouroboros.qgstudio.po;

import java.util.Date;

public class File {
    private String filename;
    private String directory;
    private int times;
    private Date deadline;
    private String get_code;
    private int size;

    public File(String filename, String directory, int times, Date deadline, String get_code, int size) {
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


}
