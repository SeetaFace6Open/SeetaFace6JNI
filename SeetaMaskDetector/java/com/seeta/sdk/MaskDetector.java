package com.seeta.sdk;

public class MaskDetector {
    static {
        System.loadLibrary("SeetaMaksDetector200_java");
    }

    public long impl = 0;

    private native void construct(SeetaModelSetting setting) throws Exception;
    public MaskDetector(SeetaModelSetting setting) throws Exception {
        this.construct(setting);
    }

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    public native boolean detect(SeetaImageData imageData, SeetaRect face, float[] score);
}
