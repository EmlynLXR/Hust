package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.event.ActionEvent;
import javafx.collections.*;

import javax.swing.*;

import java.awt.*;
import java.io.IOException;
import java.sql.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import javafx.scene.Scene;
import javafx.fxml.FXMLLoader;
import com.sun.javafx.robot.impl.FXRobotHelper;

public class Login {
    @FXML
    private Button login_btn;
    @FXML
    private ComboBox<String> UserType;
    @FXML
    private TextField UserName;
    @FXML
    private TextField UserPwd;

    @FXML
    public void LoginIn(ActionEvent event) {
        int type = UserType.getSelectionModel().getSelectedIndex();
        UserLoginIn(UserName.getText(), UserPwd.getText(), type);
    }


    @FXML
    void initialize() {
        UserType.getItems().addAll(
                "patient",
                "doctor"
        );
        UserType.getSelectionModel().select(0);
    }

    @FXML
    private void UserLoginIn(String account, String pwd, int type) {
        if (account.isEmpty() || pwd.isEmpty()) {
            JOptionPane.showMessageDialog(null, "用户名或密码为空！", "提示", JOptionPane.ERROR_MESSAGE);
        } else if (type == 0) {
            //病人登陆
            ResultSet re = DBcontrol.getInstance().GetPatientInfo(UserName.getText().trim());
            if (re == null) {
                JOptionPane.showMessageDialog(null, "读取数据库错误！", "提示", JOptionPane.ERROR_MESSAGE);
            }

            try {
                if (!re.next()) {
                    JOptionPane.showMessageDialog(null, "用户不存在！", "提示", JOptionPane.ERROR_MESSAGE);
                } else if (!re.getString("DLKL").equals(UserPwd.getText())) {
                    JOptionPane.showMessageDialog(null, "密码错误！", "提示", JOptionPane.ERROR_MESSAGE);
                } else {
                    //打开病人登陆后界面
                    PatientControl.PatientName = re.getString("BRMC");
                    PatientControl.PatientNumber = re.getString("BRBH");
                    PatientControl.PatientBalance = re.getDouble("YCJE");

                    DBcontrol.getInstance().UpdatePatientLoginTime(PatientControl.PatientNumber,
                            LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));

                    try {
                        Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Patient.fxml")));
                        scene.getStylesheets().add(getClass().getResource("Login.css").toExternalForm());
                        FXRobotHelper.getStages().get(0).setScene(scene);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                }
            } catch (SQLException | NullPointerException e) {
                e.printStackTrace();
            }

        } else if (type == 1) {
            //医生登陆
            ResultSet re = DBcontrol.getInstance().GetDoctorInfo(UserName.getText().trim());
            if (re == null) {
                JOptionPane.showMessageDialog(null, "读取数据库错误！", "提示", JOptionPane.ERROR_MESSAGE);
            }

            try {
                if (!re.next()) {
                    JOptionPane.showMessageDialog(null, "用户不存在！", "提示", JOptionPane.ERROR_MESSAGE);
                } else if (!re.getString("DLKL").equals(UserPwd.getText())) {
                    JOptionPane.showMessageDialog(null, "密码错误！", "提示", JOptionPane.ERROR_MESSAGE);
                } else {
                    //打开病人登陆后界面
                    DoctorControl.DoctorName = re.getString("YSMC");
                    DoctorControl.DoctorNumber = re.getString("YSBH");
                    DoctorControl.DoctorKs = re.getString("KSBH");
                    DoctorControl.DoctorZj = re.getInt("SFZJ");

                    DBcontrol.getInstance().UpdateDoctorLoginTime(DoctorControl.DoctorNumber,
                            LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));

                    try {
                        Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Doctor.fxml")));
                        scene.getStylesheets().add(getClass().getResource("Login.css").toExternalForm());
                        FXRobotHelper.getStages().get(0).setScene(scene);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            } catch (NullPointerException | SQLException e) {
                e.printStackTrace();
            }
        } else {
            JOptionPane.showMessageDialog(null, "登陆失败！", "提示", JOptionPane.ERROR_MESSAGE);
        }
    }
}
