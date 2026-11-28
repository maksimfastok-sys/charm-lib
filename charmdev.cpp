#include <jni.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"

#define LOG_TAG "Charm"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

bool g_Initialized = false;
bool g_ShowMenu = true;

// Поток для проверки загрузки
void* CheckLoad(void* arg) {
    sleep(3);
    FILE* f = fopen("/data/data/com.verba.online/files/CharmLoaded.txt", "w");
    if (f) {
        fprintf(f, "Library loaded successfully!");
        fclose(f);
    }
    return NULL;
}

// Эта функция вызывается, когда игра загружает библиотеку
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("CHARM LIBRARY LOADED!");
    pthread_t thread;
    pthread_create(&thread, NULL, CheckLoad, NULL);
    return JNI_VERSION_1_6;
}

// Инициализация ImGui
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontDefault();
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 300 es");
        
        g_Initialized = true;
    }
}

// Отрисовка
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;
    if (ImGui::GetCurrentContext() == NULL) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    if (g_ShowMenu) {
        ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
        
        ImGui::Begin("Charm Menu", &g_ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::Text("Verba Online Cheats");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Заглушки для остальных методов
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv *env, jclass clazz, jint width, jint height) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass clazz, jboolean down, jfloat PosX, jfloat PosY) {}
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect2(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
