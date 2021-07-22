package com.seeta.sdk;

public class EyeStateDetector {
    static{
        System.loadLibrary("SeetaEyeStateDetector200_java");
    }

    public long impl = 0;
    public enum  EYE_STATE{
        EYE_CLOSE,
        EYE_OPEN,
        EYE_RANDOM,
        EYE_UNKNOWN
    }

    private native void construct(SeetaModelSetting setting) throws Exception;
    public EyeStateDetector(SeetaModelSetting setting) throws Exception {
        this.construct(setting);
    }

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    public void Detect(SeetaImageData imageData, SeetaPointF[] points, EYE_STATE[] eyeStatus)
    {
        if(eyeStatus.length < 2) return;

        int[] eyeStateIndexs = new int[2];
        DetectCore(imageData, points, eyeStateIndexs);

        eyeStatus[0] = EYE_STATE.values()[eyeStateIndexs[0]];
        eyeStatus[1] = EYE_STATE.values()[eyeStateIndexs[1]];

        eyeStateIndexs = null;
    }

    private native void DetectCore(SeetaImageData imageData, SeetaPointF[] points, int[] eyeStateIndexs);
}
