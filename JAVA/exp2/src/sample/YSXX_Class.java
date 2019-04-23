package sample;

public class YSXX_Class {
    public String KSBH;
    public String YSMC;
    public String PYZS;
    public Integer SFZJ;

    YSXX_Class(String KSBH, String YSMC, String PYZS, int SFZJ) {
        this.KSBH = KSBH;
        this.PYZS = PYZS;
        this.SFZJ = SFZJ;
        this.YSMC = YSMC;
    }

    String getKSBH() {
        return this.KSBH;
    }

    String getYSMC() {
        return this.YSMC;
    }

    String getPYZS() {
        return this.PYZS;
    }

    Integer getSFZJ() {
        return this.SFZJ;
    }
}
