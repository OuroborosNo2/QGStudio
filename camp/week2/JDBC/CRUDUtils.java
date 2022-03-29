import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

//Connection,Statement,ResultSet都是需要关闭的资源！
public class CRUDUtils {
    //连接池
    static MyDataSource ds = new MyDataSource();

    public static void main(String[] args){
        Connection conn = ds.getConnection();
        List<String> params = new ArrayList<>();
        params.add("小红");
        params.add("0");
        params.add("1");
        insert(conn,params);
    }



    /** 不使用连接池，获取并返回一个数据库连接
     * @return 数据库连接
     * */
    public static Connection getConnection(){
        //专门读配置文件
        try(InputStream input = new FileInputStream("camp/week2/JDBC/jdbc.properties")){
            Properties prop = new Properties();
            prop.load(input);
            String user = prop.getProperty("user");
            String password = prop.getProperty("password");
            String url = prop.getProperty("url");
            String driver = prop.getProperty("driver");
            /*另一种方法
            不需要后缀名,而且不同方法路径不一样
            ResourceBundle resource = ResourceBundle.getBundle("jdbc");
            user = resource.getString("user");
            password = resource.getString("password");
            url = resource.getString("url");
            driver = resource.getString("driver");
            */
            //注册驱动
            Class.forName(driver);
            //获取数据库连接对象Connection
            return DriverManager.getConnection(url,user,password);
        }catch(Exception e){
            e.printStackTrace();
            return null;
        }
    }
    /**
     * @param conn   现成的连接
     * @param params 占位符的值
     * @return 插入的结果
     */
    public static int insert(Connection conn, List<String> params) {
        try {
            PreparedStatement ps = conn.prepareStatement("INSERT INTO students (name,gender,grade) VALUES(?,?,?);");
            ps.setObject(1, params.get(0));
            ps.setObject(2, params.get(1));
            ps.setObject(3, params.get(2));
            int result = ps.executeUpdate();
            close(conn,ps,null);

            return result;
        }catch(SQLException e) {
            try {
                conn.close();
            }catch(SQLException ex) {
                ex.printStackTrace();
            }
            return -1;
        }
    }

    /**
     * @param conn   现成的连接
     * @param range  sql语句,删除的范围
     * @param params 占位符的值
     * @return 删除的结果
     */
    public static int delete(Connection conn, String range, List<String> params) {
        try {
            PreparedStatement ps = conn.prepareStatement("DELETE FROM students WHERE " + range + ";");
            for(int i = 0; i < params.size(); i++) {//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i - 1, params.get(i));
            }
            int result = ps.executeUpdate();
            close(conn,ps,null);

            return result;
        }catch(SQLException e) {
            try {
                conn.close();
            }catch(SQLException ex) {
                ex.printStackTrace();
            }
            return -1;
        }
    }

    /**
     * @param conn  现成的连接
     * @param set   sql语句,要修改的字段和值
     * @param range sql语句,修改的范围
     * @return 删除的结果
     */
    public static int update(Connection conn, String set, String range, List<String> params) {
        try {
            PreparedStatement ps = conn.prepareStatement("UPDATE FROM students SET " + set + " WHERE " + range + ";");
            for(int i = 0; i < params.size(); i++) {//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i - 1, params.get(i));
            }

            int result = ps.executeUpdate();
            close(conn,ps,null);

            return result;
        }catch(SQLException e) {
            try {
                conn.close();
            }catch(SQLException ex) {
                ex.printStackTrace();
            }
            return -1;
        }
    }

    /**
     * @param conn  现成的连接
     * @param range sql语句,查询的范围(条件)
     * @return 查询结果集
     */
    public static List<String> query(Connection conn,String range,List<String> params){
        try {
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM students WHERE " +range+ ";");
            for(int i=0;i<params.size();i++){//不确定sql里有几个占位符，错误留给用户
                ps.setObject(i-1,params.get(i));
            }
            ResultSet rs = ps.executeQuery();
            List<String> str = new ArrayList<>();
            while(rs.next()){
                str.add(rs.getString("id"));
                str.add(rs.getString("name"));
                str.add(rs.getString("gender"));
                str.add(rs.getString("grade"));
            }

            close(conn,ps,rs);
            return str;
        }catch(SQLException e) {
            try {
                conn.close();
            }catch(SQLException ex) {
                ex.printStackTrace();
            }
            return null;
        }
    }

    /** 关闭各资源
     * @param conn
     * @param st
     * @param rs
     */
    public static void close(Connection conn,Statement st,ResultSet rs) throws SQLException{
        if(rs!=null) {
            rs.close();
        }
        if(st!=null) {
            st.close();
        }
        conn.close();
    }
}

