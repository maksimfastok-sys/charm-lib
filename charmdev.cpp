#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"

#define LOG_TAG "Charm"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

bool g_Initialized = false;
bool g_ShowMenu = true;

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        
        // Загружаем системный шрифт Android, чтобы избежать проблем с памятью
        io.Fonts->AddFontFromFileTTF("/system/fonts/Roboto-Regular.ttf", 18.0f);
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 100");
        
        g_Initialized = true;
        LOGI("ImGui initialized with system font");
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;
    
    // Защита от вызова до полной инициализации контекста
    if (ImGui::GetCurrentContext() == NULL) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    if (g_ShowMenu) {
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
        
        ImGui::Begin("Charm Menu", &g_ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::Text("Charm Menu Active");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Заглушки для методов, чтобы Java-код не падал
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass clazz, jboolean down, jfloat PosX, jfloat PosY) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv *env, jclass clazz, jint width, jint height) {}
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect2(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
