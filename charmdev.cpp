#include <jni.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <string>
#include <sstream>

#define LOG_TAG "CharmDev"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// --- Заглушки для MainActivity ---
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_setWallhack(JNIEnv *env, jclass clazz, jboolean on) {
    LOGI("setWallhack called");
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_setAimBot(JNIEnv *env, jclass clazz, jboolean on, jfloat fov, jfloat smooth, jint bone) {
    LOGI("setAimBot called");
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_drawMenu(JNIEnv *env, jclass clazz, jint w, jint h) {
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_mycompany_application_MainActivity_menuTouched(JNIEnv *env, jclass clazz, jfloat x, jfloat y, jint action) {
    return JNI_FALSE;
}

// --- Заглушки для GLES3JNIView ---
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    LOGI("GL Init");
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv *env, jclass clazz, jint width, jint height) {
    glViewport(0, 0, width, height);
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass clazz, jboolean down, jfloat PosX, jfloat PosY) {
}

extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("0,0,0,0");
}

extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect2(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("0,0,0,0");
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("CharmDev library loaded successfully");
    return JNI_VERSION_1_6;
}
