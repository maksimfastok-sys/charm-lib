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
bool aimbot_active = false;
bool wallhack_active = false;

// 1. Инициализация (безопасная)
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontDefault(); // Обязательно, иначе меню будет невидимым
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 100"); // Строго ES 2.0, как в игре
        
        g_Initialized = true;
        LOGI("ImGui initialized (ES2) - Safe Mode");
    }
}

// 2. Отрисовка кадра
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    // Рисуем меню
    if (g_ShowMenu) {
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(320, 200), ImGuiCond_Always);
        
        ImGui::Begin("Charm Menu", &g_ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        
        ImGui::Text("Charm Menu Active");
        ImGui::Separator();
        ImGui::Checkbox("Aimbot", &aimbot_active);
        ImGui::Checkbox("Wallhack", &wallhack_active);
        
        ImGui::End();
    }

    ImGui::Render();
    
    // ВАЖНО: Мы не делаем glViewport и glClear, чтобы не ломать кадр игры.
    // ImGui просто накладывает свои кнопки поверх.
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// 3. Заглушки для касаний (чтобы приложение не падало при нажатии на экран)
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass clazz, jboolean down, jfloat PosX, jfloat PosY) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv *env, jclass clazz, jint width, jint height) {}
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect2(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
