#include "JNIFaceTracker.h"
#include "jni_struct.hpp"
#include "seeta/FaceTracker.h"

using NativeClass = seeta::FaceTracker;

JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_construct__Ljava_lang_String_2II
  (JNIEnv *env, jobject self, jstring model, jint video_width, jint video_height)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	auto native_model = jni_convert_string(env, model);

	seeta::ModelSetting::Device device = seeta::ModelSetting::AUTO;
	int id = 0;
	seeta::ModelSetting model_setting(native_model.c_str(), device, id);
	
	NativeClass *native_impl = nullptr;
	try
	{
		native_impl = new NativeClass(model_setting, video_width, video_height);
	}
	catch (const std::exception &e)
	{
		jni_throw(env, e.what());
		return;
	}
	
	jlong self_impl = reinterpret_cast<jlong>(native_impl);

	env->SetLongField(self, self_filed_impl, self_impl); 
  }
  
 JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_construct__Ljava_lang_String_2Ljava_lang_String_2III
  (JNIEnv *env, jobject self, jstring model, jstring device, jint id, jint video_width, jint video_height)
  {
	 jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	auto native_model = jni_convert_string(env, model);
	auto native_device = jni_convert_string(env, device);
	
	seeta::ModelSetting_v2 model_setting(native_model, native_device, id);
	
	NativeClass *native_impl = nullptr;
	try
	{
		native_impl = new NativeClass(model_setting, video_width, video_height);
	}
	catch (const std::exception &e)
	{
		jni_throw(env, e.what());
		return;
	}
	
	jlong self_impl = reinterpret_cast<jlong>(native_impl);

	env->SetLongField(self, self_filed_impl, self_impl);  
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_dispose
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_SetSingleCalculationThreads
  (JNIEnv *env, jobject self, jint num)
  {	
	// NativeClass::SetSingleCalculationThreads(num);
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	native_impl->SetSingleCalculationThreads(num);
  }
  
  JNIEXPORT jobjectArray JNICALL Java_com_seeta_sdk_FaceTracker_Track__Lcom_seeta_sdk_SeetaImageData_2
  (JNIEnv *env, jobject self, jobject image)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return nullptr;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	
	auto native_tracking_info_array = native_impl->Track(native_image);
	
	auto tracking_info_array = jni_convert_tracking_face_info(env, native_tracking_info_array);
	
	delete[] native_image.data;
	
	return tracking_info_array;
  }
  
  JNIEXPORT jobjectArray JNICALL Java_com_seeta_sdk_FaceTracker_Track__Lcom_seeta_sdk_SeetaImageData_2I
  (JNIEnv *env, jobject self, jobject image, jint frame_no)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return nullptr;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	
	auto native_tracking_info_array = native_impl->Track(native_image, frame_no);
	
	auto tracking_info_array = jni_convert_tracking_face_info(env, native_tracking_info_array);
	
	delete[] native_image.data;
	
	return tracking_info_array;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_SetMinFaceSize
  (JNIEnv *env, jobject self, jint size)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	native_impl->SetMinFaceSize(size);
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceTracker_GetMinFaceSize
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetMinFaceSize();
  }
  
JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceTracker_SetVideoStable
  (JNIEnv *env, jobject self, jboolean is_stable)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	native_impl->SetVideoStable(is_stable);
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceTracker_GetVideoStable
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	jboolean result = native_impl->GetVideoStable();
	
	return result;
  }