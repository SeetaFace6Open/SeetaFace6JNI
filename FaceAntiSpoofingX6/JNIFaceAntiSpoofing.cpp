#include "JNIFaceAntiSpoofing.h"
#include "jni_struct.hpp"
#include "seeta/FaceAntiSpoofing.h"
#include "Common/Struct.h"
#include <vector>
#include <iostream>

#include <orz/mem/need.h>

using NativeClass = seeta::FaceAntiSpoofing;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}

JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_construct__Lcom_seeta_sdk_SeetaModelSetting_2
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
	for(int i=0; i<len; i++) 
	{
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_construct__Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *env, jobject self, jstring model, jstring device, jint id)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	std::string native_model = jni_convert_string(env, model);
	std::string native_device = jni_convert_string(env, device);
	
	seeta::ModelSetting_v2 model_setting(native_model, native_device, id);
	  
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
 JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_construct__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *env, jobject self, jstring model1, jstring model2, jstring device, jint id)
  {
	 jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	std::string native_model1 = jni_convert_string(env, model1);
	std::string native_model2 = jni_convert_string(env, model2);
	std::string native_device = jni_convert_string(env, device);
	std::vector<std::string> models = {native_model1, native_model2};
	seeta::ModelSetting_v2 model_setting(models, native_device, id);
	  
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_dispose
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
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_PredictCore
  (JNIEnv *env, jobject self, jobject image, jobject info, jobjectArray landmarks)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_field_impl);

	if(!self_impl)
	{
       jni_throw(env, "impl is null"); 
    }
	  
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_image = jni_convert_image_data(env, image);
	auto native_info = jni_convert_face_info(env, info);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);

	auto result = native_impl->Predict(native_image, native_info, native_point5);

	delete[] native_image.data;
	return result; 
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_PredictVideoCore
  (JNIEnv *env, jobject self, jobject image, jobject info, jobjectArray landmarks)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_field_impl);

	if(!self_impl)
	{
       jni_throw(env, "impl is null"); 
    }
	  
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_image = jni_convert_image_data(env, image);
	auto native_info = jni_convert_face_info(env, info);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);

	auto result = native_impl->PredictVideo(native_image, native_info, native_point5);

	delete[] native_image.data;
	return result; 
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_ResetVideo
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_field_impl);

	if(!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	native_impl->ResetVideo();
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_GetPreFrameScore
  (JNIEnv *env, jobject self, jfloatArray clarity, jfloatArray reality)
  {
	  jclass self_class = env->GetObjectClass(self);
	  jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");
	  
	  jlong self_impl = env->GetLongField(self, self_field_impl);
	  
	  if(!self_impl) return;
	  
	  auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	  
	  float native_clarity;
	  float native_reality;
	  native_impl->GetPreFrameScore(&native_clarity, &native_reality);
	  
	  env->SetFloatArrayRegion(clarity, 0, 1, &native_clarity);
	  env->SetFloatArrayRegion(reality, 0, 1, &native_reality);
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_SetVideoFrameCount
  (JNIEnv *env, jobject self, jint num)
  {
	  jclass self_class = env->GetObjectClass(self);
	  jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");
	  
	  jlong self_impl = env->GetLongField(self, self_field_impl);
	  
	  if(!self_impl) return;
	  
	  auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	  native_impl->SetVideoFrameCount(num);
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_GetVideoFrameCount
  (JNIEnv *env, jobject self)
  {
	  jclass self_class = env->GetObjectClass(self);
	  jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");
	  
	  jlong self_impl = env->GetLongField(self, self_field_impl);
	  
	  if(!self_impl) return 0;
	  auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	  return native_impl->GetVideoFrameCount();
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_SetThreshold
  (JNIEnv *env, jobject self, jfloat thresh1, jfloat thresh2)
  {
	  jclass self_class = env->GetObjectClass(self);
	  jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");
	  
	  jlong self_impl = env->GetLongField(self, self_field_impl);
	  
	  if(!self_impl) return;
	  
	  auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	  
	  native_impl->SetThreshold(thresh1, thresh2);
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceAntiSpoofing_GetThreshold
  (JNIEnv *env, jobject self, jfloatArray clarity, jfloatArray reality)
  {
	  jclass self_class = env->GetObjectClass(self);
	  jfieldID self_field_impl = env->GetFieldID(self_class, "impl", "J");
	  
	  jlong self_impl = env->GetLongField(self, self_field_impl);
	  
	  if(!self_impl) return;
	  
	  auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	  
	  float native_clarity;
	  float native_reality;
	  native_impl->GetThreshold(&native_clarity, &native_reality);
	  
	  env->SetFloatArrayRegion(clarity, 0, 1, &native_clarity);
	  env->SetFloatArrayRegion(reality, 0, 1, &native_reality);
  }
  