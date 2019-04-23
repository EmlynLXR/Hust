package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.Set;

import java.time.*;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.scene.control.cell.PropertyValueFactory;

public class DoctorControl {
    static String DoctorName;
    static String DoctorNumber;
    static String DoctorKs;
    static int DoctorZj;
    private ObservableList<BRLBXX> BRdata = FXCollections.observableArrayList();
    private ObservableList<SRLBXX> SRdata = FXCollections.observableArrayList();
    @FXML
    private TableView<BRLBXX> BRview;
    @FXML
    private TableView<SRLBXX> SRview;
    @FXML
    private TableColumn<BRLBXX, String> BRview_GHBH, BRview_BRMC, BRview_GHRQ, BRview_HZLB;
    @FXML
    private TableColumn<SRLBXX, String> SRview_KSMC, SRview_YSBH, SRview_YSMC, SRview_HZLB, SRview_GHRC, SRview_SRHJ;
    @FXML
    private Label UserName;
    @FXML
    private DatePicker DatePickerStart;
    @FXML
    private DatePicker DatePickerEnd;
    @FXML
    private ComboBox<String> StartHour, StartMinute, EndHour, EndMinute;

    @FXML
    void initialize() {
        UserName.setText(DoctorName);
        DatePickerStart.setValue(LocalDate.now());
        DatePickerEnd.setValue(DatePickerStart.getValue().plusDays(1));

        for (int i = 0; i < 24; i++) {
            StartHour.getItems().add(i + "时");
            EndHour.getItems().add(i + "时");
        }
        for (int i = 0; i < 60; i++) {
            StartMinute.getItems().add(i + "分");
            EndMinute.getItems().add(i + "分");
        }
        StartHour.getSelectionModel().select(0);
        StartMinute.getSelectionModel().select(0);
        EndHour.getSelectionModel().select(0);
        EndMinute.getSelectionModel().select(0);
        int S_1 = Integer.parseInt(StartHour.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int S_2 = Integer.parseInt(StartMinute.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int E_1 = Integer.parseInt(EndHour.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int E_2 = Integer.parseInt(EndMinute.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        String startTime = DatePickerStart.getValue().toString() + " " + String.format("%02d", S_1) + ":" + String.format("%02d", S_2) + ":00";
        String endTime = DatePickerEnd.getValue().toString() + " " + String.format("%02d", E_1) + ":" + String.format("%02d", E_2) + ":00";

        SetBRLB(startTime, endTime);
        SetSRLB(startTime, endTime);
    }

    @FXML
    public void ExitEvent(ActionEvent event) {
        System.exit(0);
    }

    private void SetBRLB(String startTime, String endTime) {
        BRview_GHBH.setCellValueFactory(new PropertyValueFactory<>("GHBH"));
        BRview_BRMC.setCellValueFactory(new PropertyValueFactory<>("BRMC"));
        BRview_GHRQ.setCellValueFactory(new PropertyValueFactory<>("GHRQ"));
        BRview_HZLB.setCellValueFactory(new PropertyValueFactory<>("HZLB"));

        BRdata = DBcontrol.getInstance().GetBRLB(DoctorNumber, startTime, endTime);
        BRview.setItems(BRdata);
    }

    private void SetSRLB(String startTime, String endTime) {
        SRview_KSMC.setCellValueFactory(new PropertyValueFactory<>("KSMC"));
        SRview_YSBH.setCellValueFactory(new PropertyValueFactory<>("YSBH"));
        SRview_YSMC.setCellValueFactory(new PropertyValueFactory<>("YSMC"));
        SRview_HZLB.setCellValueFactory(new PropertyValueFactory<>("HZLB"));
        SRview_GHRC.setCellValueFactory(new PropertyValueFactory<>("GHRC"));
        SRview_SRHJ.setCellValueFactory(new PropertyValueFactory<>("SRHJ"));

        SRdata = DBcontrol.getInstance().GetSRLB(startTime, endTime);
        SRview.setItems(SRdata);
    }

    @FXML
    public void SearchEvent(ActionEvent event) {
        int S_1 = Integer.parseInt(StartHour.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int S_2 = Integer.parseInt(StartMinute.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int E_1 = Integer.parseInt(EndHour.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        int E_2 = Integer.parseInt(EndMinute.getSelectionModel().getSelectedItem().replace("时", "").replace("分", "").trim());
        String startTime = DatePickerStart.getValue().toString() + " " + String.format("%02d", S_1) + ":" + String.format("%02d", S_2) + ":00";
        String endTime = DatePickerEnd.getValue().toString() + " " + String.format("%02d", E_1) + ":" + String.format("%02d", E_2) + ":00";

//        System.out.println("开始时间：" + startTime + "\t结束时间：" + endTime);
//        SetBRLB(startTime,endTime);
//        SetSRLB(startTime,endTime);

        BRdata = DBcontrol.getInstance().GetBRLB(DoctorNumber, startTime, endTime);
        BRview.setItems(BRdata);
        SRdata = DBcontrol.getInstance().GetSRLB(startTime, endTime);
        SRview.setItems(SRdata);
    }
}
