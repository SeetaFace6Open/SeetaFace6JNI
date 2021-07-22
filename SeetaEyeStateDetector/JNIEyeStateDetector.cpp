#include "JNIEyeStateDetector.h"
#include "jni_struct.hpp"
#include "seeta/EyeStateDetector.h"

#include <orz/mem/need.h>

using NativeClass  = seeta::EyeStateDetector;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}

JNIEXPORT void JNICALL Java_com_seeta_sdk_EyeStateDetector_construct
  (JNIEnv *env, jobject self, jobject model)
  {
	jclass setting_class = env->GetObjectClass(model);
	jfieldID setting_field_id = env->GetFieldID(setting_class, "id", "I");
	jint jid = env->GetIntField(model, setting_field_id);

	jfieldID setting_field_device = env->GetFieldID(setting_class, "device", "Lcom/seeta/sdk/SeetaDevice;");
	jobject device_obj = env->GetObjectField(model, setting_field_device);
	jclass device_class = env->FindClass("com/seeta/sdk/SeetaDevice");

	jmethodID getVal = env->GetMethodID(device_class, "getValue", "()I");
	jint device_id = env->CallIntMethod(device_obj, getVal);


	jfieldID setting_field_model = env->GetFieldID(setting_class, "model", "[Ljava/lang/String;");
	jobjectArray model_obj = (jobjectArray)env->GetObjectField(model, setting_field_model);
	int len = env->GetArrayLength(model_obj);

	std::vector<std::string> modellst; 
	for(int i=0; i<len; i++) {

		jstring str = (jstring)env->GetObjectArrayElement(model_obj, i);
		auto model_path = jni_convert_string(env, str);
		modellst.push_back(model_path);
	} 

	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	seeta::ModelSetting::Device device = (seeta::ModelSetting::Device)device_id;//seeta::ModelSetting::AUTO;
	int id = jid; //0;
	 
	seeta::ModelSetting model_setting(modellst, device, id);

	NativeClass *native_impl = nullptr;
	try
	{
		native_impl = new NativeClass(model_setting);
	}
	catch (const std::exception &e)
	{
		jni_throw(env, e.what());
			return;
	}

	jlong self_impl = reinterpret_cast<jlong>(native_impl);

	env->SetLongField(self, self_filed_impl, self_impl); 
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_EyeStateDetector_dispose
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	delete native_impl;

	env->SetLongField(self, self_filed_impl, 0);
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_EyeStateDetector_DetectCore
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jintArray eye_indexes)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
	
	auto native_image = jni_convert_image_data(env, image);

    orz::need  n(delete_array<uint8_t>,native_image.data);
	
	seeta::v6::EyeStateDetector::EYE_STATE left_state,right_state;
	native_impl->Detect(native_image, native_point5, left_state, right_state);
	
	int native_indexs[2];
	native_indexs[0] = (int)left_state;
	native_indexs[1] = (int)right_state;
	
	env->SetIntArrayRegion(eye_indexes, 0, 2, native_indexs);
  }