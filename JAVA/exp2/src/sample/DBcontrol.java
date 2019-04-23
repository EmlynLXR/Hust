package sample;

import java.sql.*;
import java.util.HashMap;

import com.sun.org.apache.bcel.internal.generic.RETURN;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class DBcontrol {
    private static DBcontrol instance = null;
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/java_exp?useUnicode=true&characterEncoding=utf-8&useSSL=false&serverTimezone=GMT";

    private static final String USER = "root";
    private static final String PASS = "89667431";

    private Connection connection;

    private DBcontrol() throws Exception {
        try {
            System.out.println("加载驱动程序...");
            Class.forName(JDBC_DRIVER);
            System.out.println("连接数据库...");
            connection = (Connection) DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    static DBcontrol getInstance() {
        try {
            if (instance == null)
                instance = new DBcontrol();
        } catch (ClassNotFoundException e) {
            System.err.print("cannot load sql driver.");
            System.exit(1);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return instance;
    }

    public void disconnectDataBase() throws SQLException {
        connection.close();
    }

    ResultSet GetPatientInfo(String number) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_BRXX where BRBH = " + number;
            return statement.executeQuery(sql);
        } catch (SQLException e) {
            return null;
        }
    }

    ResultSet GetDoctorInfo(String number) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_KSYS where YSBH = " + number;
            return statement.executeQuery(sql);
        } catch (SQLException e) {
            return null;
        }
    }

    void UpdatePatientLoginTime(String number, String time) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "update T_BRXX set DLRQ = \"" + time + "\" where BRBH = " + number;
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    void UpdateDoctorLoginTime(String number, String time) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "update T_KSYS set DLRQ = \"" + time + "\" where YSBH = " + number;
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    void UpdatePatientYLJE(String BRBH, double YCJE) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "update T_BRXX set YCJE = \"" + YCJE + "\" where BRBH = " + BRBH;
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    void InsertGHXX(String GHBH, String HZBH, String YSBH, String BRBH, int GHRC, double GHFY, String RQSJ) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "insert into T_GHXX (GHBH,HZBH,YSBH,BRBH,GHRC,THBZ,GHFY,RQSJ) VALUES(\'" + GHBH + "\',\'" + HZBH + "\',\'" + YSBH + "\',\'"
                    + BRBH + "\'," + GHRC + "," + 0 + "," + GHFY + ",\'" + RQSJ + "\')";
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    int GetCount(String Table) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select count(*) as dd from " + Table;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt("dd");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    int GetHZRC(String HZBH) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select max(GHRC) as dd from T_GHXX where HZBH = " + HZBH;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt("dd");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    String GetHZBH(String KSBH, int ZJ) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_HZXX where KSBH = " + KSBH + " and SFZJ = " + ZJ;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getString("HZBH");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "";
    }

    int GetHZRS(String HZBH) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_HZXX where HZBH = " + HZBH;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt("GHRS");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    double GetGuaHaoFY(String KSBH, int ZJ) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_HZXX where HZBH = " + KSBH + " or KSBH = " + KSBH;
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                if (re.getInt("SFZJ") == ZJ)
                    return re.getInt("GHFY");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    HashMap<String, KSXX_Class> GetAllKS() {
        HashMap<String, KSXX_Class> KSinfo = new HashMap<>();
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "SELECT * FROM T_KSXX";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                String KSMC = "", PYZS = "";
                if (!re.getString("PYZS").isEmpty()) {
                    PYZS = re.getString("PYZS");
                }
                if (!re.getString("KSMC").isEmpty()) {
                    KSMC = re.getString("KSMC");
                }
                KSinfo.put(re.getString("KSBH"), new KSXX_Class(KSMC, PYZS));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return KSinfo;
    }

    HashMap<String, YSXX_Class> GetAllYS(String KSBH, int ZJ) {
        HashMap<String, YSXX_Class> YSinfo = new HashMap<>();
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql;
            if (KSBH.equals("all"))
                sql = "SELECT * FROM T_KSYS";
            else
                sql = "SELECT * FROM T_KSYS where KSBH = " + KSBH;
            ResultSet re = statement.executeQuery(sql);
            String YSMC = "", PYZS = "", curKSBH = "";
            int SFZJ;
            if (ZJ != 0 && ZJ != 1) {
                while (re.next()) {
                    if (!re.getString("PYZS").isEmpty()) {
                        PYZS = re.getString("PYZS");
                    }
                    if (!re.getString("YSMC").isEmpty()) {
                        YSMC = re.getString("YSMC");
                    }
                    SFZJ = re.getInt("SFZJ");
                    curKSBH = re.getString("KSBH");
                    YSinfo.put(re.getString("YSBH"), new YSXX_Class(curKSBH, YSMC, PYZS, SFZJ));
                }
            } else {
                while (re.next()) {
                    if (re.getInt("SFZJ") == ZJ) {
                        if (!re.getString("PYZS").isEmpty()) {
                            PYZS = re.getString("PYZS");
                        }
                        if (!re.getString("YSMC").isEmpty()) {
                            YSMC = re.getString("YSMC");
                        }
                        SFZJ = ZJ;
                        curKSBH = re.getString("KSBH");
                        YSinfo.put(re.getString("YSBH"), new YSXX_Class(curKSBH, YSMC, PYZS, SFZJ));
                    }
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return YSinfo;
    }

    ObservableList<SRLBXX> GetSRLB(String ST, String ET) {
        ObservableList<SRLBXX> date = FXCollections.observableArrayList();
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select a.ghbh,a.hzbh,a.ysbh,a.brbh,a.ghfy,a.rqsj,b.ysbh,b.ksbh,b.ysmc,sum(GHFY),count(*) " +
                    "from T_GHXX a,T_KSYS b where a.thbz = 0 and a.ysbh=b.ysbh and RQSJ between '" + ST + "' and '" + ET +
                    "' group by a.ysbh,a.hzbh";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                String HZBH = re.getString("HZBH");
                double SRHJ = Double.valueOf(re.getString("sum(GHFY)"));
                String KSBH = re.getString("KSBH");
                String KSMC = DBcontrol.getInstance().GetKSMC(KSBH);
                String YSBH = re.getString("YSBH");
                String YSMC = re.getString("YSMC");
                String HZLB = DBcontrol.getInstance().GetHZLB(HZBH);
                int GHRC = re.getInt("count(*)");

                date.addAll(new SRLBXX(KSMC, YSBH, YSMC, HZLB, GHRC, SRHJ));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return date;
    }

    ObservableList<BRLBXX> GetBRLB(String YSBH, String ST, String ET) {
        ObservableList<BRLBXX> date = FXCollections.observableArrayList();
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_GHXX where YSBH = " + YSBH + " and RQSJ between '" + ST + "' and '" + ET + "'";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                String HZBH = re.getString("HZBH");
                String BRBH = re.getString("BRBH");
                String GHBH = re.getString("GHBH");
                String GHRQ = re.getString("RQSJ");

                String BRMC = DBcontrol.getInstance().GetBRMC(BRBH);
                String HZLB = DBcontrol.getInstance().GetHZLB(HZBH);
                date.addAll(new BRLBXX(GHBH, BRMC, GHRQ, HZLB));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return date;
    }

    private String GetKSMC(String KSBH) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_KSXX where KSBH = " + KSBH;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getString("KSMC");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "";
    }

    private String GetBRMC(String BRBH) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_BRXX where BRBH = " + BRBH;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getString("BRMC");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "";
    }

    private String GetHZLB(String HZBH) {
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from T_HZXX where HZBH = " + HZBH;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                if (re.getInt("SFZJ") == 1)
                    return "专家号";
                else
                    return "普通号";
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "";
    }
}
