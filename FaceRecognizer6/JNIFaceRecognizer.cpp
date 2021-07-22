#include "JNIFaceRecognizer.h"
#include "jni_struct.hpp"
#include "seeta/FaceRecognizer.h"

#include <orz/mem/need.h>

#include <iostream>

using namespace seeta::SEETA_FACE_RECOGNIZE_NAMESPACE_VERSION;
using NativeClass = seeta::SEETA_FACE_RECOGNIZE_NAMESPACE_VERSION::FaceRecognizer;

//using NativeClass = seeta::FaceRecognizer;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}


JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceRecognizer_construct__Lcom_seeta_sdk_SeetaModelSetting_2
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


        /////////////////////////////////////////
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
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceRecognizer_construct__Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *env, jobject self, jstring model, jstring device, jint id)
  {
	std::string native_model = jni_convert_string(env, model);
	std::string native_device = jni_convert_string(env, device);
	 
	seeta::ModelSetting_v2 model_setting;
	model_setting.device = native_device.c_str();
	model_setting.id = id;
	model_setting.append(native_model);
	
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
	
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");
	
	jlong self_impl = reinterpret_cast<jlong>(native_impl);

	env->SetLongField(self, self_filed_impl, self_impl); 
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceRecognizer_dispose
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
 
  /* 
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceRecognizer_SetLogLevel
  (JNIEnv *env, jclass self, jint level)
  {
	return NativeClass::SetLogLevel(level);
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceRecognizer_SetSingleCalculationThreads
  (JNIEnv *env, jclass self, jint num)
  {
	 NativeClass::SetSingleCalculationThreads(num);
  }
  */
 
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceRecognizer_GetCropFaceWidthV2
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
        	
	return native_impl->GetCropFaceWidthV2();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceRecognizer_GetCropFaceHeightV2
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceHeightV2();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceRecognizer_GetCropFaceChannelsV2
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceChannelsV2();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceRecognizer_GetExtractFeatureSize
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;
	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetExtractFeatureSize();
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceRecognizer_CropFaceV2
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
	auto result = native_impl->CropFaceV2(native_image, native_point5, native_face);

	if (result)
	{
		jni_set_image_data(env, native_face, face);
	}

	//delete[] native_image.data;
	return result;
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceRecognizer_ExtractCroppedFace
  (JNIEnv *env, jobject self, jobject face, jfloatArray feats)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	jsize feats_size = env->GetArrayLength(feats);
	size_t need_feats_size = native_impl->GetExtractFeatureSize();
	if (feats_size < need_feats_size) {
            jni_throw(env, "feats must have enough size");
            return false;
        }

	auto native_face = jni_convert_image_data(env, face);

        orz::need  n(delete_array<uint8_t>,native_face.data);

	std::unique_ptr<float[]> native_feats(new float[need_feats_size]);

	auto result = native_impl->ExtractCroppedFace(native_face, native_feats.get());

	if (result)
	{
		env->SetFloatArrayRegion(feats, 0, need_feats_size, native_feats.get());
	}

	//delete[] native_face.data;

	return result; 
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceRecognizer_Extract
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jfloatArray feats)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	jsize feats_size = env->GetArrayLength(feats);
	size_t need_feats_size = native_impl->GetExtractFeatureSize();
	if (feats_size < need_feats_size) {
            jni_throw(env, "feats must have enough size");
            return false;
        }
	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
	
	auto native_image = jni_convert_image_data(env, image);

        orz::need  n(delete_array<uint8_t>,native_image.data);
	std::unique_ptr<float[]> native_feats(new float[need_feats_size]);

	auto result = native_impl->Extract(native_image, native_point5, native_feats.get());

	if (result)
	{
		env->SetFloatArrayRegion(feats, 0, need_feats_size, native_feats.get());
	}

	//delete[] native_image.data;

	return result; 
  }
  
  JNIEXPORT jfloat JNICALL Java_com_seeta_sdk_FaceRecognizer_CalculateSimilarity
  (JNIEnv *env, jobject self, jfloatArray fc1, jfloatArray fc2)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return 0.0;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	jfloat *fc1_ptr = env->GetFloatArrayElements(fc1, nullptr);
	jfloat *fc2_ptr = env->GetFloatArrayElements(fc2, nullptr);

	float *native_fc1 = fc1_ptr;
	float *native_fc2 = fc2_ptr;

	float similar = native_impl->CalculateSimilarity(native_fc1, native_fc2);

	env->ReleaseFloatArrayElements(fc1, fc1_ptr, 0);
	env->ReleaseFloatArrayElements(fc2, fc2_ptr, 0);

	return similar;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceRecognizer_set
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
        native_impl->set((FaceRecognizer::Property)(property_value), value);
  }


  JNIEXPORT jdouble JNICALL Java_com_seeta_sdk_FaceRecognizer_get
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

        return native_impl->get((FaceRecognizer::Property)(property_value));
  }
