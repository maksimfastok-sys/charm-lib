#include <jni.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"

#define LOG_TAG "Charm"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

bool g_Initialized = false;

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) {
        LOGI("Init called");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontDefault();
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 300 es"); // Возвращаем ES 3.0
        
        g_Initialized = true;
        LOGI("ImGui initialized");
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;
    
    // Ничего не рисуем, просто вызываем NewFrame, чтобы проверить стабильность
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    ImGui::Render();
}
