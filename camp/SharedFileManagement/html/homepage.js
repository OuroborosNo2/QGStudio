"use strict";
//全局变量 很容易弄混，调用的时候最好加window.
var user;
var path;
//选择一律获取id
var navigation_select;
var file_select;
$(document).ready(function () {
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
            personalSpace()
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

    const maxSize = 1024 * 1024 * 500;
    const formData = new FormData();
    const f = document.getElementById("file");
    formData.append("path",window.path);
    for (let i = 0; i < f.files.length; i++) {
        if (f.files[i].size > maxSize) {
            alert("单个文件最大不能超过500m(524288000)！\n" + f.files[i].name + "大小为" + f.files[i].size);
            continue;
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
            showFileList(window.path);
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
function deleteFile(){
    if(window.file_select === undefined){//未选择文件
        alert("请选择文件");
        return;
    }
    //判断是文件夹还是文件
    let filename;
    let fileType;
    if(window.file_select.substring(0,3) === "file"){
        filename = window.file_select.substring(5);//file_value ,从_后开始截取value
        fileType = "file";
    }else{
        filename = window.file_select.substring(7);//folder_value ,从_后开始截取value
        fileType = "folder";
    }
    $.ajax({
        url: '../SFM/?method=deleteFile',
        type: 'get',
        async: true,
        data:{
            path:window.path,
            filename:filename,
            fileType:fileType
        },
        success: function (result) {
            alert("删除成功");
            window.file_select = undefined;
            showFileList(window.path);
        },
        error: function (XMLHttpRequest) {
            alertError(XMLHttpRequest);
        },
        timeout: 3000
    });
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
    function func(e){
        if(e.target.id === "div_creatingFolder_confirm"){
            const name = $("#div_creatingFolder_name").val();
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
            return;//无反应
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
        ' <button type="button" id="audio">音频</button> ' +
        '</div>')
        .appendTo($("#content"));
}
function showManu(){
    $('<div id="right" class="content"></div>').appendTo($("#content"));

    $('<div id="manu">' +
        ' <button type="button" id="sort">按xxx排序</button>' +
        ' <button type="button" id="share">分享</button>' +
        ' <button type="button" id="delete" onClick="deleteFile()">删除</button>' +
        ' <button type="button" id="download">下载</button>' +
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
            .appendTo(div_directory);
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
                let folder = $("<div class='list_folder'></div>");
                folder.append("<i class='icon_folder'></i>");
                folder.append("<a></a>");
                folder.children("a").attr("title",value);
                folder.children("a").attr("id","folder_"+value);//防止id重复
                folder.children("a").text(value);
                div_list.append(folder);
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
                let file = $("<div class='list_file'></div>");
                file.append("<i class='icon_file'></i>");
                file.append("<a></a>");
                file.children("a").attr("title",value.filename);
                file.children("a").attr("id","file_"+value.filename);
                file.children("a").text(value.filename);
                div_list.append(file);
            });
            //绑定点击文件/文件夹事件
            div_list.on('click','div.list_file a , div.list_folder',function (){
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