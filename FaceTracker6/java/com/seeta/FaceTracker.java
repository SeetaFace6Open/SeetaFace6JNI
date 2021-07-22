package com.seeta.sdk;

public class FaceTracker {
    static{
        System.loadLibrary("FaceTracker600_java");
    }

    public long impl = 0;
    private native void construct(String seetaModel, int videoWidth, int videoHeight);
    public FaceTracker(String seetaModel, int videoWidth, int videoHeight) {
        this.construct(seetaModel, videoWidth, videoHeight);
    }

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    public native void SetSingleCalculationThreads(int num);

    public native SeetaTrackingFaceInfo[] Track(SeetaImageData image);
    public native SeetaTrackingFaceInfo[] Track(SeetaImageData image, int frame_no);

    public native void SetMinFaceSize(int size);
    public native int GetMinFaceSize();

    public native void SetVideoStable(boolean stable);
    public native boolean GetVideoStable();
}
