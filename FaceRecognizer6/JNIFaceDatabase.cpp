#include "JNIFaceDatabase.h"
#include "jni_struct.hpp"
#include "seeta/FaceDatabase.h"

#include <orz/mem/need.h>

using NativeClass = seeta::FaceDatabase;

template<typename T>
static void delete_array(T * ptr) {
    delete [] ptr;
}

template<typename T>
static void delete_obj(T * ptr) {
    delete ptr;
}

JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_construct__Lcom_seeta_sdk_SeetaModelSetting_2
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

	seeta::ModelSetting::Device device = (seeta::ModelSetting::Device)device_id;
	int id = jid;//0;

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
  
 JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_construct__Lcom_seeta_sdk_SeetaModelSetting_2II
  (JNIEnv *env, jobject self, jobject model, jint extraction_core_number, jint comparation_core_number)
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

	seeta::ModelSetting::Device device = (seeta::ModelSetting::Device)device_id;
	int id = jid;//0;

	seeta::ModelSetting model_setting(modellst, device, id);
	NativeClass *native_impl = nullptr;
	try
	{
		native_impl = new NativeClass(model_setting, extraction_core_number, comparation_core_number);
	}
	catch (const std::exception &e)
	{
		jni_throw(env, e.what());
		return;
	}

	jlong self_impl = reinterpret_cast<jlong>(native_impl);

	env->SetLongField(self, self_filed_impl, self_impl); 
  }

 JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_dispose
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
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceDatabase_SetLogLevel
  (JNIEnv *env, jclass self, jint level)
  {	
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->SetLogLevel(level);
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceDatabase_GetCropFaceWidthV2
  (JNIEnv *env, jclass self)
  {	
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceWidthV2();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceDatabase_GetCropFaceHeightV2
  (JNIEnv *env, jclass self)
  {	
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceHeightV2();
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceDatabase_GetCropFaceChannelsV2
  (JNIEnv *env, jclass self)
  {	
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->GetCropFaceChannelsV2();
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceDatabase_CropFaceV2
  (JNIEnv *env, jclass self, jobject image, jobjectArray landmarks, jobject face)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);

	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
		
	SeetaImageData native_face;
	native_face.width = native_impl->GetCropFaceWidthV2();
	native_face.height = native_impl->GetCropFaceHeightV2();
	native_face.channels = native_impl->GetCropFaceChannelsV2();
	
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
  
  JNIEXPORT jfloat JNICALL Java_com_seeta_sdk_FaceDatabase_Compare
  (JNIEnv *env, jobject self, jobject image1, jobjectArray landmarks1, jobject image2, jobjectArray landmarks2)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return 0.0;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image1 = jni_convert_image_data(env, image1);
	auto native_image2 = jni_convert_image_data(env, image2);
	
	SeetaPointF native_points1[5];
	SeetaPointF native_points2[5];
	jni_convert_point5(env, landmarks1, native_points1);
	jni_convert_point5(env, landmarks2, native_points2);
	
	float sim = native_impl->Compare(native_image1, native_points1, native_image2, native_points2);
	
	delete[] native_image1.data;
	delete[] native_image2.data;
	
	return sim;
  }
  
  JNIEXPORT jfloat JNICALL Java_com_seeta_sdk_FaceDatabase_CompareByCroppedFace
  (JNIEnv *env, jobject self, jobject face1, jobject face2)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return 0.0;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face1 = jni_convert_image_data(env, face1);
	auto native_face2 = jni_convert_image_data(env, face2);
	
	float sim = native_impl->CompareByCroppedFace(native_face1, native_face2);
	
	delete[] native_face1.data;
	delete[] native_face2.data;
	
	return sim;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_Register
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	
	SeetaPointF native_point5[5];
	jni_convert_point5(env, landmarks, native_point5);
	
	jlong face_index = native_impl->Register(native_image, native_point5);
	
	delete[] native_image.data;
	
	return face_index;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_RegisterByCroppedFace
  (JNIEnv *env, jobject self, jobject face)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	jlong face_index = native_impl->RegisterByCroppedFace(native_face);
	
	delete[] native_face.data;
	
	return face_index;
  }
  
  JNIEXPORT jint JNICALL Java_com_seeta_sdk_FaceDatabase_Delete
  (JNIEnv *env, jobject self, jlong index)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->Delete(index);
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_Clear
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	native_impl->Clear();
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_Count
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	return native_impl->Count();
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_Query__Lcom_seeta_sdk_SeetaImageData_2_3Lcom_seeta_sdk_SeetaPointF_2
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	SeetaPointF native_points[5];
	jni_convert_point5(env, landmarks, native_points);
	
	jlong index = native_impl->Query(native_image, native_points);
	
	delete[] native_image.data;
	
	return index;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_Query__Lcom_seeta_sdk_SeetaImageData_2_3Lcom_seeta_sdk_SeetaPointF_2_3F
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jfloatArray similarity)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	SeetaPointF native_points[5];
	jni_convert_point5(env, landmarks, native_points);
	
	float top_similarity;
	jlong index = native_impl->Query(native_image, native_points, &top_similarity);
	
	env->SetFloatArrayRegion(similarity, 0, 1, &top_similarity);
	
	delete[] native_image.data;
	
	return index;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryByCroppedFace__Lcom_seeta_sdk_SeetaImageData_2
  (JNIEnv *env, jobject self, jobject face)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	jlong index = native_impl->QueryByCroppedFace(native_face);
	
	delete[] native_face.data;
	
	return index;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryByCroppedFace__Lcom_seeta_sdk_SeetaImageData_2_3F
  (JNIEnv *env, jobject self, jobject face, jfloatArray similarity)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	float top_similarity;
	jlong index = native_impl->QueryByCroppedFace(native_face, &top_similarity);
	
	env->SetFloatArrayRegion(similarity, 0, 1, &top_similarity);
	
	delete[] native_face.data;
	
	return index;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryTop
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jlong N, jlongArray indexes, jfloatArray similarities)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	
	SeetaPointF native_points[5];
	jni_convert_point5(env, landmarks, native_points);
	
	int64_t* native_indexes = new int64_t[N];
	float* native_similarities = new float[N];
	
	jlong num = native_impl->QueryTop(native_image, native_points, N, native_indexes, native_similarities);
	
	env->SetLongArrayRegion(indexes, 0, N, native_indexes);
	env->SetFloatArrayRegion(similarities, 0, N, native_similarities);
	
	delete[] native_image.data;
	delete[] native_indexes;
	delete[] native_similarities;
	
	return num;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryTopByCroppedFace
  (JNIEnv *env, jobject self, jobject face, jlong N, jlongArray indexes, jfloatArray similarities)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	int64_t* native_indexes = new int64_t[N];
	float* native_similarities = new float[N];
	
	jlong num = native_impl->QueryTopByCroppedFace(native_face, N, native_indexes, native_similarities);
	
	env->SetLongArrayRegion(indexes, 0, N, native_indexes);
	env->SetFloatArrayRegion(similarities, 0, N, native_similarities);
	
	delete[] native_face.data;
	delete[] native_indexes;
	delete[] native_similarities;
	
	return num;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryAbove
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jfloat thresh, jlong N, jlongArray indexes, jfloatArray similarities)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	SeetaPointF native_points[5];
	jni_convert_point5(env, landmarks, native_points);
	
	int64_t* native_indexes = new int64_t[N];
	float* native_similarities = new float[N];
	
	jlong num = native_impl->QueryAbove(native_image, native_points, thresh, N, native_indexes, native_similarities);
	
	env->SetLongArrayRegion(indexes, 0, N, native_indexes);
	env->SetFloatArrayRegion(similarities, 0, N, native_similarities);
	
	delete[] native_image.data;
	delete[] native_indexes;
	delete[] native_similarities;
	
	return num;
  }
  
  JNIEXPORT jlong JNICALL Java_com_seeta_sdk_FaceDatabase_QueryAboveByCroppedFace
  (JNIEnv *env, jobject self, jobject face, jfloat thresh, jlong N, jlongArray indexes, jfloatArray similarities)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return -1;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	int64_t* native_indexes = new int64_t[N];
	float* native_similarities = new float[N];
	
	jlong num = native_impl->QueryAboveByCroppedFace(native_face, thresh, N, native_indexes, native_similarities);
	
	env->SetLongArrayRegion(indexes, 0, N, native_indexes);
	env->SetFloatArrayRegion(similarities, 0, N, native_similarities);
	
	delete[] native_face.data;
	delete[] native_indexes;
	delete[] native_similarities;
	
	return num;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_RegisterParallel
  (JNIEnv *env, jobject self, jobject image, jobjectArray landmarks, jlongArray face_index)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_image = jni_convert_image_data(env, image);
	SeetaPointF native_points[5];
	jni_convert_point5(env, landmarks, native_points);
	
	int64_t native_face_index;
	native_impl->RegisterParallel(native_image, native_points, &native_face_index);
	
	env->SetLongArrayRegion(face_index, 0, 1, &native_face_index);
	
	delete[] native_image.data;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_RegisterByCroppedFaceParallel
  (JNIEnv *env, jobject self, jobject face, jlongArray face_index)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_face = jni_convert_image_data(env, face);
	
	int64_t native_face_index;
	native_impl->RegisterByCroppedFaceParallel(native_face, &native_face_index);
	
	env->SetLongArrayRegion(face_index, 0, 1, &native_face_index);
	
	delete[] native_face.data;
  }
  
  JNIEXPORT void JNICALL Java_com_seeta_sdk_FaceDatabase_Join
  (JNIEnv *env, jobject self)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	native_impl->Join();
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceDatabase_Save
  (JNIEnv *env, jobject self, jstring path)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_path = jni_convert_string(env, path);
	
	jboolean result = native_impl->Save(native_path.c_str());
	
	return result;
  }
  
  JNIEXPORT jboolean JNICALL Java_com_seeta_sdk_FaceDatabase_Load
  (JNIEnv *env, jobject self, jstring path)
  {
	jclass self_class = env->GetObjectClass(self);
	jfieldID self_filed_impl = env->GetFieldID(self_class, "impl", "J");

	jlong self_impl = env->GetLongField(self, self_filed_impl);

	if (!self_impl) return false;

	auto native_impl = reinterpret_cast<NativeClass *>(self_impl);
	
	auto native_path = jni_convert_string(env, path);
	
	jboolean result = native_impl->Load(native_path.c_str());
	
	return result;
  }