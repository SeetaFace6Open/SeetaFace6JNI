#include "JNIGenderPredictor.h"
#include "jni_struct.hpp"
#include "seeta/GenderPredictor.h"

#include <orz/mem/need.h>

#include <iostream>

using NativeClass = seeta::GenderPredictor;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}

JNIEXPORT void JNICALL Java_com_seeta_sdk_GenderPredictor_construct
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
	}


	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	//auto native_model = jni_convert_string(env, model);

	//seeta::ModelSetting::Device device = seeta::ModelSetting::AUTO;
        seeta::ModelSetting::Device device = (seeta::ModelSetting::Device)device_id;
	int id = jid;//0;
	//seeta::ModelSetting model_setting(native_model.c_str(), device, id);
	
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_GenderPredictor_dispose
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
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_GenderPredictor_GetCropFaceWidth
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
        	
	return native_impl->GetCropFaceWidth();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_GenderPredictor_GetCropFaceHeight
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceHeight(); 
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_GenderPredictor_GetCropFaceChannels
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceChannels(); 
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_GenderPredictor_CropFace
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jobject face)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
		
	SeetaImageData native_face;
	native_face.width = native_impl->GetCropFaceWidth();
	native_face.height = native_impl->GetCropFaceHeight();
	native_face.channels = native_impl->GetCropFaceChannels();
	
	std::unique_ptr<uint8_t[]> native_face_data(new uint8_t[native_face.width * native_face.height * native_face.channels]);
	native_face.data = native_face_data.get();
	auto native_image = jni_convert_image_data(env, image);

        orz::need  n(delete_array<uint8_t>,native_image.data);
	auto result = native_impl->CropFace(native_image, native_point5, native_face);

	if (result)
	{
		jni_set_image_data(env, native_face, face);
	}

	return result; 
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_GenderPredictor_PredictGenderCore
  (JNIEnv *env, jobject self, jobject face, jintArray gender_index)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	auto native_face = jni_convert_image_data(env, face);

    orz::need  n(delete_array<uint8_t>,native_face.data);
	
	seeta::GenderPredictor::GENDER native_gender;

	auto result = native_impl->PredictGender(native_face, native_gender);
	int native_gender_index = (int)native_gender;
	
	if (result)
	{
		env->SetIntArrayRegion(gender_index, 0, 1, &native_gender_index);
	}

	return result;  
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_GenderPredictor_PredictGenderWithCropCore
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jintArray gender_index)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
	
	auto native_image = jni_convert_image_data(env, image);

    orz::need  n(delete_array<uint8_t>,native_image.data);
	
	seeta::GenderPredictor::GENDER native_gender;
	auto result = native_impl->PredictGenderWithCrop(native_image, native_point5, native_gender);
	int native_gender_index = (int)native_gender;

	if (result)
	{
		env->SetIntArrayRegion(gender_index, 0, 1, &native_gender_index);
	}

	return result; 
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_GenderPredictor_set
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
  
  JNIEXPORT jdouble JNICALL Java_com_seeta_sdk_GenderPredictor_get
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