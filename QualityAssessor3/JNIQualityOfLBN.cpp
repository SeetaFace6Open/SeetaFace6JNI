#include "JNIQualityOfLBN.h"
#include "seeta/QualityOfLBN.h"

#include "jni_struct.hpp"

#include "orz/mem/need.h"


#include <memory>

using NativeClass = seeta::QualityOfLBN;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}

JNIEXPORT void JNICALL Java_com_seeta_sdk_QualityOfLBN_construct__Lcom_seeta_sdk_SeetaModelSetting_2
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_QualityOfLBN_construct__Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *env, jobject self, jstring model, jstring device, jint id)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");
	
	auto native_model = jni_convert_string(env, model);
	auto native_device = jni_convert_string(env, device);
	
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_QualityOfLBN_dispose
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_QualityOfLBN_Detect
  (JNIEnv *env, jobject self, jobject image, 
  jobjectArray landmarks, jintArray light, 
  jintArray blur, jintArray noise)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return ;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_image = jni_convert_image_data(env, image);
	std::vector<SeetaPointF> native_points = jni_convert_landmarks(env, landmarks);
	
	int native_light, native_blur, native_noise;
	native_impl->Detect(native_image, native_points.data(), 
		&native_light, &native_blur, &native_noise);
	
	env->SetIntArrayRegion(light, 0, 1, &native_light);
	env->SetIntArrayRegion(blur, 0, 1, &native_blur);
	env->SetIntArrayRegion(noise, 0, 1, &native_noise);
	
	delete[] native_image.data;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_QualityOfLBN_set
  (JNIEnv *env, jobject self, jobject property, jdouble value)
  {
	jclass enumclass= env->GetObjectClass(property);
	if(enumclass == NULL) {
		return;
	}

	jmethodID getVal = env->GetMethodID(enumclass, "getValue", "()I");
	jint property_value = env->CallIntMethod(property, getVal);

	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	native_impl->set((NativeClass::Property)(property_value), value); 
  }
  
  JNIEXPORT jdouble JNICALL Java_com_seeta_sdk_QualityOfLBN_get
  (JNIEnv *env, jobject self, jobject property)
  {
	jclass enumclass= env->GetObjectClass(property);
	if(enumclass == NULL) {
		return -1;
	}

	jmethodID getVal = env->GetMethodID(enumclass, "getValue", "()I");
	jint property_value = env->CallIntMethod(property, getVal);

	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	return native_impl->get((NativeClass::Property)(property_value)); 
  }