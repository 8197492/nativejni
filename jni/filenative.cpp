#include <jni.h>  
#include <sys/types.h>  
#include <stdlib.h>  
#include <android/asset_manager_jni.h>  
#include <android/asset_manager.h>  
#include <android/log.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <dlfcn.h>  
#include <stdio.h>  
#include <fcntl.h>  

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"UnityNative",__VA_ARGS__) // 定义LOGD类型  
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"UnityNative",__VA_ARGS__) 

extern "C" 
{
	int addInt(int a, int b)
	{
		return a + b;
	}

	static AAssetManager* mgr = NULL;

	void  Java_com_example_filenative_InitreadFromAssets(JNIEnv* env, jclass tis, jobject assetManager)
	{
		LOGW("init_DSActivity_initreadFromAssets");
		mgr = AAssetManager_fromJava(env, assetManager);
		if (mgr == NULL)
		{
			LOGW(" %s", "AAssetManager==NULL");
			return;
		}
	}

	void getNativeStreamFromOffsetAssets(char* fileName, char* data, int offset, int length, int dataoffset)
	{
		if (mgr == NULL)
		{
			LOGW("mgr is null ");
			return;
		}

		AAsset* asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
		if (asset == NULL)
		{
			LOGW("asset is null ");
			return;
		}
		AAsset_seek(asset, offset, SEEK_SET);
		data = data + dataoffset;
		AAsset_read(asset, data, length);
		AAsset_close(asset);

	}

	void getNativeStreamFromAssets(char* fileName, char* data, int offset, int length)
	{
		if (mgr == NULL)
		{
			LOGW("mgr is null ");
			return;
		}

		AAsset* asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
		if (asset == NULL)
		{
			LOGW("asset is null ");
			return;
		}
		AAsset_seek(asset, offset, SEEK_SET);
		AAsset_read(asset, data, length);
		AAsset_close(asset);

	}

	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
	{
		LOGW("JNI_OnLoad");

		JNIEnv* env = NULL;

#ifdef __cplusplus  
		if (jvm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
#else  
		if ((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_4) != JNI_OK)
#endif  
		{
			return -1;
		}

#ifdef __cplusplus  
		jclass DSActivity = env->FindClass("com/example/filenative");
#else  
		jclass DSActivity = (*env)->FindClass(env, "com/example/filenative");
#endif  
		if (DSActivity != NULL)
		{
#ifdef __cplusplus  
			jmethodID getSDPath = env->GetStaticMethodID(DSActivity, "getSDPath", "()Ljava/lang/String;");
#else  
			jmethodID getSDPath = (*env)->GetStaticMethodID(env, DSActivity, "getSDPath", "()Ljava/lang/String;");
#endif  
			jstring jstr = NULL;
#ifdef __cplusplus  
			jstr = (jstring)env->CallStaticObjectMethod(DSActivity, getSDPath);
#else  
			jstr = (jstring)(*env)->CallStaticObjectMethod(env, DSActivity, getSDPath);
#endif  
			const char* cstr = NULL;
#ifdef __cplusplus  
			cstr = env->GetStringUTFChars(jstr, 0);
#else  
			cstr = (*env)->GetStringUTFChars(env, jstr, 0);
#endif  
			if (cstr == NULL)
			{
				LOGW("11getSDPath=NULL");
			}
			else
			{
				LOGW("11getSDPath OK");
			}

#ifdef __cplusplus  
			env->ReleaseStringUTFChars(jstr, cstr);
#else  
			(*env)->ReleaseStringUTFChars(env, jstr, cstr);
#endif
		}


		return JNI_VERSION_1_4;
	}

	JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *jvm, void *reserved)
	{
		LOGW("JNI_OnUnload");
		return;
	}
}

