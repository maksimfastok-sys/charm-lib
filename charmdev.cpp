#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>

#define LOG_TAG "Charm"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

bool g_Initialized = false;

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    LOGI("Native Init Called");
    g_Initialized = true;
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;
    // Очищаем экран (чтобы не было артефактов)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
