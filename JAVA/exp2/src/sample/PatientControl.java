package sample;

import com.sun.org.apache.xerces.internal.xs.StringList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

import java.awt.*;
import java.util.Date;
import java.text.SimpleDateFormat;
import javax.swing.*;
import java.util.HashMap;
import java.util.Set;

public class PatientControl {
    static String PatientName;
    static String PatientNumber;
    static Double PatientBalance;
    @FXML
    private Button CleanBtn;
    @FXML
    private Button EnsureBtn;
    @FXML
    private Button ExitBtn;
    @FXML
    private ComboBox<String> KSMC;
    @FXML
    private ComboBox<String> YSMC;
    @FXML
    private ComboBox<String> HZLB;
    @FXML
    private TextField HZMC;
    @FXML
    private TextField JKJE;
    @FXML
    private TextField YJJE;
    @FXML
    private TextField SYJE;
    @FXML
    private TextField GHHM;
    @FXML
    private Label UserName;
    @FXML
    private Label UserBalance;

    private HashMap<String, KSXX_Class> AllKS;
    private HashMap<String, YSXX_Class> AllYS;
    private String ShowKSBH, ShowYSBH, ShowHZ;
    private Double ShowCost, ShowYE;

    int HZLB_ZJ;


    @FXML
    void initialize() {
        UserName.setText(PatientName);
        UserBalance.setText(PatientBalance.toString());
        AllKS = DBcontrol.getInstance().GetAllKS();
        AllYS = DBcontrol.getInstance().GetAllYS("all", 2);

        Set set = AllKS.keySet();
        for (Object o : set) {
            KSMC.getItems().addAll(AllKS.get(o).getKSMC() + " " + AllKS.get(o).getPYZS() + " " + (String) o);
        }

        KSMC.setEditable(true);
        YSMC.setEditable(true);
        HZLB.setEditable(true);
        SYJE.setEditable(false);
        HZMC.setEditable(false);
        YJJE.setEditable(false);
        GHHM.setEditable(false);

        new AutoCompleteComboBoxListener<ComboBox>(KSMC);
        new AutoCompleteComboBoxListener<ComboBox>(YSMC);
        new AutoCompleteComboBoxListener<ComboBox>(HZLB);

        if (KSMC.getItems().size() >= 5)
            KSMC.setVisibleRowCount(5);
        else
            KSMC.setVisibleRowCount(KSMC.getItems().size());
    }

    @FXML
    public void ChooseKS() {
        if (!KSMC.getItems().isEmpty() || KSMC.getEditor().getText().trim().split(" ").length == 3)
            ShowKSBH = KSMC.getEditor().getText().trim().split(" ")[2];
        else
            ShowKSBH = "";
        SetYsComboxInfo();
        SetHzComboxInfo();
        SetHzName();
    }

    @FXML
    public void ChooseYS() {
        if (!YSMC.getItems().isEmpty()|| YSMC.getEditor().getText().trim().split(" ").length == 3)
            ShowYSBH = YSMC.getEditor().getText().trim().split(" ")[2];
        else
            ShowYSBH = "";
        SetHzComboxInfo();
        SetHzName();
    }

    @FXML
    public void ChooseHZ() {
        ShowHZ = HZLB.getEditor().getText().trim();
        if (ShowHZ.equals("专家号"))
            HZLB_ZJ = 1;
        else
            HZLB_ZJ = 0;
        SetHzName();
    }

    private void SetYsComboxInfo() {
        if (0 < YSMC.getItems().size())
            YSMC.getItems().subList(0, YSMC.getItems().size()).clear();
        if (KSMC.getItems().isEmpty())
            return;
        if (HZLB.getEditor().getText().trim().isEmpty())
            AllYS = DBcontrol.getInstance().GetAllYS(ShowKSBH, 2);
        else {
            if (ShowHZ.equals("普通号"))
                AllYS = DBcontrol.getInstance().GetAllYS(ShowKSBH, 0);
            else if (ShowHZ.equals("专家号"))
                AllYS = DBcontrol.getInstance().GetAllYS(ShowKSBH, 1);
        }
        Set set = AllYS.keySet();
        for (Object o : set) {
            YSMC.getItems().addAll(AllYS.get(o).getYSMC() + " " + AllYS.get(o).getPYZS() + " " + (String) o);
        }
        YSMC.setEditable(true);
        if (YSMC.getItems().size() >= 5)
            YSMC.setVisibleRowCount(5);
        else
            YSMC.setVisibleRowCount(YSMC.getItems().size());
    }

    private void SetHzComboxInfo() {
        if (0 < HZLB.getItems().size())
            HZLB.getItems().subList(0, HZLB.getItems().size()).clear();

        if (YSMC.getEditor().getText().trim().isEmpty())
            HZLB.getItems().addAll("专家号", "普通号");
        else {
            if (AllYS.get(ShowYSBH).getSFZJ() == 1) {
                HZLB.getItems().addAll("专家号", "普通号");
            } else {
                HZLB.getItems().addAll("普通号");
            }
        }
    }

    @FXML
    private void SetHzName() {
        if (!KSMC.getEditor().getText().trim().isEmpty()) {
            if (!HZLB.getEditor().getText().trim().isEmpty())
                ShowHZ = KSMC.getEditor().getText().trim().split(" ")[0] + ShowHZ;
            else
                ShowHZ = KSMC.getEditor().getText().trim().split(" ")[0];
        } else
            ShowHZ = null;
        HZMC.setText(ShowHZ);
        GetCost();
    }

    @FXML
    private void GetCost() {
        if (KSMC.getEditor().getText().trim().isEmpty() || YSMC.getEditor().getText().trim().isEmpty()
                || HZLB.getEditor().getText().trim().isEmpty())
            return;

        ShowCost = DBcontrol.getInstance().GetGuaHaoFY(ShowKSBH, HZLB_ZJ);
        YJJE.setText(String.valueOf(ShowCost));
        GetLastCost();
    }

    @FXML
    private void GetLastCost() {
        if (JKJE.getText().isEmpty() || !isNumeric(JKJE.getText())) {
            ShowYE = PatientBalance - ShowCost;
            if (ShowYE < 0) {
                SYJE.setText("余额不足，请充值！");
                JKJE.setText(null);
            } else {
                JKJE.setText("余额充足，无需充值！");
                SYJE.setText(String.valueOf(ShowYE));
            }
        } else {
            ShowYE = Double.valueOf(JKJE.getText()) + PatientBalance - ShowCost;
            if (ShowYE < 0)
                SYJE.setText("充值金额不足！");
            else
                SYJE.setText(String.valueOf(ShowYE));
        }
    }

    @FXML
    public void EnsureEvent(ActionEvent event) {
        if (KSMC.getEditor().getText().isEmpty()) {
            JOptionPane.showMessageDialog(null, "科室名称不能为空！", "提示", JOptionPane.ERROR_MESSAGE);
        } else if (YSMC.getEditor().getText().isEmpty()) {
            JOptionPane.showMessageDialog(null, "医生姓名不能为空！", "提示", JOptionPane.ERROR_MESSAGE);
        } else if (HZLB.getEditor().getText().isEmpty()) {
            JOptionPane.showMessageDialog(null, "号种类别不能为空！", "提示", JOptionPane.ERROR_MESSAGE);
        } else if (HZMC.getText().isEmpty()) {
            JOptionPane.showMessageDialog(null, "号种名称不能为空！", "提示", JOptionPane.ERROR_MESSAGE);
        } else {
            if (ShowYE < 0) {
                if (JKJE.getText().isEmpty())
                    JOptionPane.showMessageDialog(null, "余额不足，请充值！", "提示", JOptionPane.WARNING_MESSAGE);
                else
                    JOptionPane.showMessageDialog(null, "充值金额不足！", "提示", JOptionPane.WARNING_MESSAGE);
            } else {
                int re = JOptionPane.showConfirmDialog(null,
                        KSMC.getEditor().getText() + " " + YSMC.getEditor().getText() + " "
                                + HZLB.getEditor().getText() + "\n是否确认挂号？", "提示", JOptionPane.YES_NO_OPTION);
                if (re == 0) {
                    //确认挂号
                    if (GetGuaHao(ShowKSBH, ShowYSBH, HZLB_ZJ)) {
                        JOptionPane.showMessageDialog(null, "挂号成功！挂号号码为" + GHHM.getText() + "!", "提示", JOptionPane.INFORMATION_MESSAGE);
                        CleanAll();
                    } else {
                        JOptionPane.showMessageDialog(null, "挂号失败，当前号种已挂满！", "提示", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        }
    }

    private boolean GetGuaHao(String KSBH, String YSBH, int ZJ) {
        String HZBH = DBcontrol.getInstance().GetHZBH(KSBH, ZJ);
        int HZRS = DBcontrol.getInstance().GetHZRS(HZBH);

        int HZRC = DBcontrol.getInstance().GetHZRC(HZBH);

        if (HZRC >= HZRS)
            return false;

        HZRC++;


        //获得表挂号总数量生成挂号编号
        int count = DBcontrol.getInstance().GetCount("T_GHXX") + 1;
        String GHBH = String.valueOf(count);
        while (GHBH.length() < 6) {
            GHBH = "0" + GHBH;
        }
        GHHM.setText(GHBH);//设置挂号号码
        String Date = GetNowDate();
        System.out.println(GHBH + HZBH + " " + " " + YSBH + "" + PatientNumber + "" + HZRC + "" + YJJE.getText() + "" + Date);
        //添加挂号信息
        DBcontrol.getInstance().InsertGHXX(GHBH, HZBH, YSBH, PatientNumber, HZRC, Double.valueOf(YJJE.getText()), Date);

        //修改用户信息余额
        DBcontrol.getInstance().UpdatePatientYLJE(PatientNumber, Double.valueOf(SYJE.getText()));
        PatientBalance = ShowYE;
        UserBalance.setText(String.valueOf(PatientBalance));
        return true;
    }

    private String GetNowDate() {
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return df.format(new Date());
    }

    @FXML
    private void CleanAll() {
        if (0 < KSMC.getItems().size())
            KSMC.getItems().subList(0, KSMC.getItems().size()).clear();
        if (0 < YSMC.getItems().size())
            YSMC.getItems().subList(0, YSMC.getItems().size()).clear();
        if (0 < HZLB.getItems().size())
            HZLB.getItems().subList(0, HZLB.getItems().size()).clear();
        HZMC.setText("");
        JKJE.setText("");
        YJJE.setText("");
        SYJE.setText("");
        GHHM.setText("");
        initialize();
    }

    @FXML
    public void CleanEvent(ActionEvent event) {
        CleanAll();
    }

    @FXML
    public void ExitEvent(ActionEvent event) {
        System.exit(0);
    }

    private static boolean isNumeric(String str) {
        if (str == "")
            return true;
        for (int i = str.length(); --i >= 0; ) {
            if (!Character.isDigit(str.charAt(i))) {
                return false;
            }
        }
        return true;
    }

}
