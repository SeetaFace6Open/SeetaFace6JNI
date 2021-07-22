#include "JNIPoseEstimator.h"
#include "jni_struct.hpp"
#include "seeta/PoseEstimator.h"

using NativeClass = seeta::PoseEstimator;

JNIEXPORT void JNICALL Java_com_seeta_sdk_PoseEstimator_construct__Ljava_lang_String_2
  (JNIEnv *env, jobject self, jstring model)
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_PoseEstimator_construct__Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *env, jobject self, jstring model, jstring device, jint id)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	auto native_model = jni_convert_string(env, model);
	auto native_device = jni_convert_string(env, device);
	
	seeta::ModelSetting_v2 model_setting(native_model.c_str(), native_device.c_str(), id);
	
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_PoseEstimator_dispose
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_PoseEstimator_Estimate
  (JNIEnv *env, jobject self, jobject image, jobject info, jfloatArray yaw, jfloatArray pitch, jfloatArray roll)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_image = jni_convert_image_data(env, image);
	auto native_info = jni_convert_face_info(env, info);
	
	float native_yaw, native_pitch,native_roll;
	native_impl->Estimate(native_image, native_info, &native_yaw, &native_pitch, &native_roll);
	
	env->SetFloatArrayRegion(yaw, 0, 1, &native_yaw);
	env->SetFloatArrayRegion(pitch, 0, 1, &native_pitch);
	env->SetFloatArrayRegion(roll, 0, 1, &native_roll);
	
	delete[] native_image.data;
  }