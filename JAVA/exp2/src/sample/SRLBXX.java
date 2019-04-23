package sample;

public class SRLBXX {
    private String KSMC;
    private String YSBH;
    private String YSMC;
    private String HZLB;
    private int GHRC;
    private double SRHJ;

    public SRLBXX(String KSMC, String YSBH, String YSMC, String HZLB, int GHRC, double SRHJ) {
        this.KSMC = KSMC;
        this.YSBH = YSBH;
        this.YSMC = YSMC;
        this.HZLB = HZLB;
        this.GHRC = GHRC;
        this.SRHJ = SRHJ;
    }

    public String getKSMC() {
        return KSMC;
    }

    public String getYSBH() {
        return YSBH;
    }

    public String getYSMC() {
        return YSMC;
    }

    public String getHZLB() {
        return HZLB;
    }

    public int getGHRC() {
        return GHRC;
    }

    public double getSRHJ() {
        return SRHJ;
    }

    public void setKSMC(String KSMC) {
        this.KSMC = KSMC;
    }

    public void setYSBH(String YSBH) {
        this.YSBH = YSBH;
    }

    public void setYSMC(String YSMC) {
        this.YSMC = YSMC;
    }

    public void setHZLB(String HZLB) {
        this.HZLB = HZLB;
    }

    public void setGHRC(int GHRC) {
        this.GHRC = GHRC;
    }

    public void setSRHJ(double SRHJ) {
        this.SRHJ = SRHJ;
    }
}
