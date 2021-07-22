package com.seeta.sdk;

public class PoseEstimator {
    static{
        System.loadLibrary("PoseEstimation600_java");
    }

    public long impl = 0;
    private native void construct(String seetaModel);
    private native void construct(String model, String device, int id);

    public PoseEstimator(String seetaModel){
        this.construct(seetaModel);
    }
    public PoseEstimator(String model, String device ,int id){this.construct(model, device, id);}

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    public native void Estimate(SeetaImageData image, SeetaRect face, float[] yaw, float[] pitch, float[] roll);
}
