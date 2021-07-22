package com.seeta.sdk;

public class QualityOfPoseEx {
    static {
        System.loadLibrary("QualityAssessor300_java");
    }

    public enum QualityLevel
    {
        LOW ,//Quality level is low
        MEDIUM,//Quality level is medium
        HIGH,//Quality level is high
    }

    public enum Property {
        YAW_LOW_THRESHOLD(0),
        YAW_HIGH_THRESHOLD(1),
        PITCH_LOW_THRESHOLD (2),
        PITCH_HIGH_THRESHOLD (3),
        ROLL_LOW_THRESHOLD (4),
        ROLL_HIGH_THRESHOLD(5);

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

    public QualityOfPoseEx(SeetaModelSetting setting) throws Exception {
        this.construct(setting);
    }

    public native void dispose();
    protected void finalize()throws Throwable{
        super.finalize();
        this.dispose();
    }

    /**
     *
     * @param imageData [input]image data
     * @param face [input] face location
     * @param landmarks [input] face landmarks
     * @param score [output] quality score
     * @return QualityLevel quality level sorted into "LOW" , "Medium" , "HIGH"
     */
    private native int checkCore(SeetaImageData imageData, SeetaRect face, SeetaPointF[] landmarks, float[] score);
    public QualityLevel check(SeetaImageData imageData, SeetaRect face, SeetaPointF[] landmarks, float[] score){
        int index = this.checkCore(imageData, face, landmarks, score);

        QualityLevel level = QualityLevel.values()[index];
        return level;
    }

    /**
     *
     * @param imageData [input]image data
     * @param face [input] face location
     * @param landmarks [input] face landmarks
     * @param yaw [output] face location in yaw
     * @param pitch [output] face location in pitch
     * @param roll [oputput] face location in roll
     * @return
     */
    private native void checkCore(SeetaImageData imageData, SeetaRect face, SeetaPointF[] landmarks, float[] yaw, float[] pitch, float[] roll);
    public void check(SeetaImageData imageData, SeetaRect face, SeetaPointF[] landmarks, float[] yaw, float[] pitch, float[] roll){
        this.checkCore(imageData, face, landmarks, yaw, pitch, roll);
    }

    public native void set(Property property, double value);
    public native double get(Property property);
}
