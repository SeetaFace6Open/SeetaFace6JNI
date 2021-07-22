package com.seeta.sdk;

import com.seeta.sdk.SeetaModelSetting;

public class FaceDetector
{
    static {
        System.loadLibrary("SeetaFaceDetector600_java");
    }
 
    public enum Property {
                PROPERTY_MIN_FACE_SIZE(0),
                PROPERTY_THRESHOLD(1),
                PROPERTY_MAX_IMAGE_WIDTH(2),
                PROPERTY_MAX_IMAGE_HEIGHT(3),
                PROPERTY_NUMBER_THREADS(4),
				PROPERTY_ARM_CPU_MODE(0x101);

    private int value;
    private Property(int value) {
        this.value = value;
    }

    public int getValue(){
        return value;
    }
    }

    public long impl = 0;

    private native void construct(SeetaModelSetting setting) throws Exception;
    public FaceDetector(SeetaModelSetting setting) throws Exception {
        this.construct(setting);
    }

    public native void dispose();
    protected void finalize()throws java.lang.Throwable{
        super.finalize();
        this.dispose();
    }

    public native SeetaRect[] Detect(SeetaImageData image);
  
    public native void set(Property property, double value);
    public native double get(Property property);
 
    /*     
    public native void SetComputingThreads(int num);
    public native int GetComputingThreads();


    public native void SetMinFaceSize(int size);
    public native int GetMinFaceSize();

    public native void SetThresh(float thresh);
    public native float GetThresh();

    public native void SetMaxImageWidth(int width);
    public native int GetMaxImageWidth();

    public native void SetMaxImageHeight(int height);
    public native int GetMaxImageHeight();
    */
}
