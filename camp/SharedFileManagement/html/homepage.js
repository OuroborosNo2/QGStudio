"use strict";
//全局变量 很容易弄混，调用的时候最好加window.
var user;
var path;
var defaultStorage;
//选择一律获取id
var navigation_select;
var file_select;
$(document).ready(function () {
    getDefaultStorage();
    getUser();
    $("#navigation button").click(function () {
        window.navigation_select = this.getAttribute("id");//获取导航选择
        alert(window.navigation_select);
    });
});

function getUser() {
    $.ajax({//给user赋值
        url: '../SFM?method=getUserJSON',
        type: 'get',
        async: true,
        dataType: "json",
        success: function (result) {
            window.user = result;
            window.path = window.user.username;

            $("#nickname").text(window.user.nickname);
            window.navigation_select = "personalSpace";
            personalSpace();
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        },
        timeout: 3000
    });
}
function getDefaultStorage(){
    $.ajax({
        url: '../SFM?method=getDefaultStorage',
        type: 'get',
        async: false,
        dataType: "json",
        success: function (result) {
            window.defaultStorage = result;
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        },
        timeout: 3000
    });
}
function personalSpace(){
    $("#content").empty();
    showType();
    showManu();
    showDirectory(window.path);
    showFileList(window.path);
}
function departmentSpace(){}
function group(){}
function friend(){}
function profile(){}
function logout(){
    $.get('../SFM?method=logout');
    window.open('login.html','_self');
}

function uploadFile() {
    const maxSize = window.defaultStorage.SINGLE_FILE_MAX_SIZE;
    let totalSize = 0;
    const formData = new FormData();
    const f = document.getElementById("file");
    formData.append("path",window.path);
    for (let i = 0; i < f.files.length; i++) {
        if (f.files[i].size > maxSize) {
            alert("单个文件最大不能超过"+maxSize/1024/1024+"MB("+maxSize+")！\n" + f.files[i].name + "大小为" + f.files[i].size);
            return;
        }
        totalSize += f.files[i].size;
        if(totalSize > window.user.storage){
            alert("剩余空间不足");
            break;
        }
        let strname = "file" + i;
        //将参数以键值对的形式添加到formDate构造函数
        formData.append(strname, f.files[i]);
    }
    $.ajax({
        url: "../SFM/upload",
        type: 'POST',
        data: formData,
        async: true,
        cache: false,
        contentType: false,
        processData: false,
        success: function (data) {
            alert("上传成功");
            getUser();
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        }
    });
    const parent = f.parentElement;//.upload
    parent.removeChild(f);
    const d = document.createElement('input');
    d.setAttribute('type', 'file');
    d.setAttribute('class', 'change');
    d.setAttribute('id', 'file');
    d.setAttribute('multiple', 'multiple');
    d.setAttribute('onchange', 'uploadFile()');
    parent.insertBefore(d, parent.children[0]);
}
function downloadFile(){
    let selected = getSelected();
    if(selected === undefined){
        return;
    }else if(selected.fileType === "folder"){
        alert("暂不处理下载整个文件夹");
        return;
    }
    $.ajax({
        url: "../SFM/?method=downloadFile",
        type: 'POST',
        data:{
          path: window.path,
          filename: selected.filename,
          fileType: selected.fileType
        },
        async: true,
        responseType: 'blob',
        success: function (data) {
            //上面responseType blob不起作用
            const blob = new Blob([data], {type: 'blob'});
            const url = URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.style.display = 'none';
            a.href = url;
            a.download = selected.filename;
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        }
    });
}
function deleteFile(){
    let selected = getSelected();
    if(selected === undefined){
        return;
    }
    $.ajax({
        url: '../SFM/?method=deleteFile',
        type: 'get',
        async: true,
        data:{
            path:window.path,
            filename:selected.filename,
            fileType:selected.fileType
        },
        success: function (result) {
            alert("删除成功");
            window.file_select = undefined;
            getUser();
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        },
        timeout: 3000
    });
}
function renameFile(){
    let selected = getSelected();
    if(selected === undefined){
        return;
    }

    const selectingFile = $(document.getElementById(window.file_select));

    selectingFile.replaceWith("<div id='div_renamingFile'>" +
        "<input type='text' id='div_renamingFile_name' size='20'>" +
        "<button type='button' id='div_renamingFile_confirm'>确定</button>" +
        "<button type='button' id='div_renamingFile_cancel'>取消</button>" +
        "</div>");

    $("#div_renamingFile_name").val(selectingFile.text());
    $("#div_renamingFile_name").focus();

    //如果点击的不是确定，那就相当于取消
    document.addEventListener("mousedown", func, false);
    function func(e){
        if(e.target.id === "div_renamingFile_confirm"){
            const newname = $("#div_renamingFile_name").val();
            $.ajax({
                url: '../SFM/?method=renameFile',
                type: 'get',
                async: true,
                data:{
                    path:window.path,
                    filename:selected.filename,
                    newname:newname,
                    fileType:selected.fileType
                },
                success: function () {
                    showFileList();//异步
                },
                error: function (XMLHttpRequest) {
                    alertError(XMLHttpRequest);
                    showFileList();
                },
                timeout: 3000
            });
        }else if(e.target.id === "div_renamingFile_name"){
            return;//无反应
        }
        document.removeEventListener("mousedown",func);
        showFileList();
    }
}
function newFolder() {
    $("<div id='div_creatingFolder'>" +
        "<i class='icon_folder'></i>" +
        "<input type='text' id='div_creatingFolder_name' size='20'>" +
        "<button type='button' id='div_creatingFolder_confirm'>确定</button>" +
        "<button type='button' id='div_creatingFolder_cancel'>取消</button>" +
        "</div>")
        .prependTo($("#div_list"));
    $("#div_creatingFolder_name").focus();

    //如果点击的不是确定，那就相当于取消
    document.addEventListener("mousedown", func, false);
    function func(e){//e是触发事件的对象
        if(e.target.id === "div_creatingFolder_confirm"){
            const name = $("#div_creatingFolder_name").val();
            if(name.match(/[\\\/:*?"<>|]/)){
                alert("文件名不能包含下列字符\n \\ / : * ? \" < > |");
                return;
            }
            $.ajax({
                url: '../SFM?method=newFolder',
                type: 'get',
                async: true,
                data:{
                    path:window.path + "/" + name
                },
                error: function (XMLHttpRequest) {
                    alertError(XMLHttpRequest);
                },
                timeout: 3000
            });
        }else if(e.target.id === "div_creatingFolder_name"){
            return;//无反应，保持不变
        }
        document.removeEventListener("mousedown",func);
        showFileList();
    }
}
function showType(){
    $('<div id="type" class="content">' +
        ' <button type="button" id="all">全部</button>' +
        ' <button type="button" id="picture">图片</button>' +
        ' <button type="button" id="document">文档</button>' +
        ' <button type="button" id="video">视频</button>' +
        ' <button type="button" id="audio">音频</button>' +
        '<p id="remainingStorage"></p> ' +
        '</div>')
        .appendTo($("#content"));
    $("#remainingStorage").text("剩余空间："+ (window.user.storage/1024/1024).toFixed(2) + "MB/"
        + ((window.defaultStorage.STORAGE_USER)/1024/1024).toFixed(2) + "MB");
}
function showManu(){
    $('<div id="right" class="content"></div>').appendTo($("#content"));

    $('<div id="manu">' +
        ' <button type="button" id="sort">按xxx排序</button>' +
        ' <button type="button" id="share">分享</button>' +
        ' <button type="button" id="delete" onClick="deleteFile()">删除</button>' +
        '<button type="button" id="rename" onClick="renameFile()">重命名</button>' +
        ' <button type="button" id="download" onClick="downloadFile()">下载</button>' +
        ' <a type="button" class="upload">' +
            ' <input type="file" id="file" multiple="multiple" onChange="uploadFile()"/>' +
            ' <button type="button">上传</button>' +
        ' </a>' +
        ' <img src="img/icon_newFolder.png" alt="新建文件夹" id="newFolder" onClick="newFolder()">' +
        ' <button type="button" id="multi">多选</button> ' +
        ' <button type="button" id="view">视图</button>' +
        ' </div>')
        .appendTo($("#right"))
}
function showDirectory(){
    let div_directory = $('<div id="div_directory"></div>');
    //没有就appendTo   有就replaceWith
    if(typeof($("#div_directory").html()) === "undefined"){
        div_directory.appendTo($("#right"));
    }else{
        $("#div_directory").replaceWith(div_directory);
    }


    //返回上一级
    $("<button type='button' id='div_directory_back'>返回上一级</button>")
        .click(function(){
            //截去最后一个/后的内容
            if(window.path.indexOf("/") === -1){//最顶层了
                if(window.navigation_select !== "departmentSpace"){//非部门空间，结束函数，不显示别的用户的文件
                    return;
                }
            }
            window.path = window.path.substring(0,window.path.lastIndexOf("/"));
            showDirectory();
            showFileList();

        })
        .appendTo(div_directory);

    //目录
    let directories = window.path.split("/");
    directories.forEach(function(value,index){
        $("<span></span>")
            .attr("id","directory_"+value)
            .text(value+" > ")
            .attr("title",value)
            .appendTo(div_directory);
    });
    $("#div_directory span").click(function(){
        let iterator = $(this);
        window.path = iterator.attr("title");
        while(1){
            iterator = iterator.prev();
            if(iterator.attr("id") === "div_directory_back"){
                break;
            }
            window.path = iterator.attr("title") + "/" + window.path;
        }
        showDirectory();
        showFileList();
    });
}
function showFileList(){
    let div_list = $('<div id="div_list"></div>');
    //没有就appendTo   有就replaceWith
    if(typeof($("#div_list").html()) === "undefined"){
        div_list.appendTo($("#right"));
    }else{
        $("#div_list").replaceWith(div_list);
    }

    $.ajax({
        url: '../SFM?method=getFileList',
        type: 'get',
        async: true,
        data:{
            path:window.path
        },
        dataType: "json",
        success: function (result) {
            //列出文件夹
            result.folders.forEach(function(value,index){
                if(value !== null) {
                    let folder = $("<div class='list_folder'></div>");
                    folder.append("<i class='icon_folder'></i>");
                    folder.append("<a></a>");
                    folder.children("a").attr("title", value);
                    folder.children("a").attr("id", "folder_" + value);//防止id重复
                    folder.children("a").text(value);
                    div_list.append(folder);
                }
            });
            //绑定双击文件夹事件
            div_list.on('dblclick','div.list_folder a',function (){
                window.file_select = undefined;//重置文件选择
                window.path = window.path === "" ? event.srcElement.innerText : window.path + "/" + event.srcElement.innerText;
                showDirectory();
                showFileList();

            });
            //列出文件
            result.files.forEach(function(value,index){
                if(value !== null){
                    let file = $("<div class='list_file'></div>");
                    file.append("<i class='icon_file'></i>");
                    file.append("<a></a>");
                    file.children("a").attr("title",value.filename);
                    file.children("a").attr("id","file_"+value.filename);
                    file.children("a").text(value.filename);
                    div_list.append(file);
                }
            });
            //绑定点击文件/文件夹事件
            div_list.on('click','div.list_file a , div.list_folder a',function (){
                //获取文件选择
                window.file_select = event.srcElement.getAttribute("id");
                //重置文件背景色
                $(".list_file , .list_folder").css("background-color","#FFFFFF");
                //设置选中文件背景色
                event.srcElement.parentElement.style.setProperty("background-color","#A9CBE8");

            });
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        },
        timeout: 10000
    });
}

function alertError(XMLHttpRequest) {
    let msg = XMLHttpRequest.responseText;
    msg = msg.substring(msg.indexOf("消息"));
    msg = msg.substring(msg.indexOf(" ") + 1, msg.indexOf("</p>"));
    alert(msg);
    if (msg === "会话失效，请重新登录") {
        window.open("login.html", "_self");
    }
}
function getSelected(){
    if(window.file_select === undefined){//未选择文件
        alert("请选择文件");
        return undefined;
    }//判断是文件夹还是文件
    let filename;
    let fileType;
    if(window.file_select.substring(0,4) === "file"){
        filename = window.file_select.substring(5);//file_value ,从_后开始截取value
        fileType = "file";
    }else{
        filename = window.file_select.substring(7);//folder_value ,从_后开始截取value
        fileType = "folder";
    }
    return {"filename":filename,"fileType":fileType};
}
