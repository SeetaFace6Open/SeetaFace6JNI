#include "JNIFaceDetector.h"
#include "jni_struct.hpp"
#include "src/seeta/FaceDetector.h"
#include "Common/Struct.h"
#include <vector>
#include <iostream>

#include <orz/mem/need.h>

using namespace seeta::SEETA_FACE_DETECTOR_NAMESPACE_VERSION;
using NativeClass = seeta::SEETA_FACE_DETECTOR_NAMESPACE_VERSION::FaceDetector;


template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}



JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDetector_construct__Lcom_seeta_sdk_SeetaModelSetting_2
  (JNIEnv *env, jobject self, jobject model)
  {
	jclass setting_class = env->GetObjectClass(model);
	jfieldID setting_field_id = env->GetFieldID(setting_class, "id", "I");
        jint jid = env->GetIntField(model, setting_field_id);

        //std::cout << "jid:" << jid << std::endl;
	jfieldID setting_field_device = env->GetFieldID(setting_class, "device", "Lcom/seeta/sdk/SeetaDevice;");
        jobject device_obj = env->GetObjectField(model, setting_field_device);
	jclass device_class = env->FindClass("com/seeta/sdk/SeetaDevice");
        
        jmethodID getVal = env->GetMethodID(device_class, "getValue", "()I");
        jint device_id = env->CallIntMethod(device_obj, getVal);

        //std::cout << "device_id:" << device_id << std::endl;

	jfieldID setting_field_model = env->GetFieldID(setting_class, "model", "[Ljava/lang/String;");
        jobjectArray model_obj = (jobjectArray)env->GetObjectField(model, setting_field_model);
        int len = env->GetArrayLength(model_obj);
       
        std::vector<std::string> modellst; 
        for(int i=0; i<len; i++) {

            jstring str = (jstring)env->GetObjectArrayElement(model_obj, i);
            auto model_path = jni_convert_string(env, str);
            modellst.push_back(model_path);
            //std::cout << "path:" << i << ": " << model_path << std::endl;
        } 

        //std::cout << "modelpath:"  << strmodelpath << std::endl;
         
        ////////////////
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	//auto native_model = jni_convert_string(env, model);
        //std::string native_model = strmodelpath;

	seeta::ModelSetting::Device device = (seeta::ModelSetting::Device)device_id;//seeta::ModelSetting::AUTO;
	//seeta::ModelSetting::Device device = seeta::ModelSetting::AUTO;
	int id = jid; //0;
         
	//seeta::ModelSetting model_setting(native_model, device, id);
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
  
JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDetector_construct__Ljava_lang_String_2Ljava_lang_String_2I
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDetector_dispose
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
 
 
  JNIEXPORT jobjectArray JNICALL Java_com_seeta_sdk_FaceDetector_Detect
  (JNIEnv *env, jobject self, jobject image)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return jni_convert(env, std::vector<SeetaRect>());

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_image = jni_convert_image_data(env, image);
        orz::need  n(delete_array<uint8_t>,native_image.data);

	auto native_infos = native_impl->detect(native_image);
	int faces_size = native_infos.size;
	std::vector<SeetaRect> native_seeta_rects;
	for(int i = 0; i < faces_size; ++i)
	{
		SeetaRect seetaRect = native_infos.data[i].pos;
		native_seeta_rects.push_back(seetaRect);
	}

	auto infos = jni_convert(env, native_seeta_rects);

	//delete[] native_image.data;

	return infos;
  }


  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDetector_set
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
        native_impl->set((FaceDetector::Property)(property_value), value);
  }


  JNIEXPORT jdouble JNICALL Java_com_seeta_sdk_FaceDetector_get
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

        return native_impl->get((FaceDetector::Property)(property_value));
  }

  
