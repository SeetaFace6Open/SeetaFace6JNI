package com.seeta.sdk;

public class AgePredictor {
    static{
        System.loadLibrary("SeetaAgePredictor600_java");
    }

    public enum Property {
        PROPERTY_NUMBER_THREADS(4),
        PROPERTY_ARM_CPU_MODE(5);

        private int value;
        private Property(int value) {
            this.value = value;
        }

        public int getValue(){
            return value;
        }
    }

    public long impl = 0;

    private native void construct(SeetaModelSetting setting);

    public AgePredictor(SeetaModelSetting setting) {
        this.construct(setting);
    }

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    public native int GetCropFaceWidth();
    public native int GetCropFaceHeight();
    public native int GetCropFaceChannels();

    public native boolean CropFace(SeetaImageData image, SeetaPointF[] points, SeetaImageData face);

    public native boolean PredictAge(SeetaImageData face, int[] age);
    public native boolean PredictAgeWithCrop(SeetaImageData image, SeetaPointF[] points, int[] age);

    public native void set(Property property, double value);
    public native double get(Property property);
}
