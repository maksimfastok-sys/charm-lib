#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"

#define LOG_TAG "Charm"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

bool g_Initialized = false;
bool g_ShowMenu = true;
bool aimbot_active = false;
bool wallhack_active = false;
float aim_smooth = 5.0f;

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        
        // Добавляем дефолтный шрифт, иначе текст не отрисуется
        io.Fonts->AddFontDefault();
        
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 8.0f;
        style.FrameRounding = 4.0f;
        style.WindowBorderSize = 1.0f;
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.95f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.60f, 1.00f, 1.00f);
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 100"); // OpenGL ES 2.0
        
        g_Initialized = true;
        LOGI("ImGui initialized (ES2)");
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv *env, jclass clazz) {
    if (!g_Initialized) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    if (g_ShowMenu) {
        // Принудительно ставим меню в левый верхний угол
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(350, 250), ImGuiCond_FirstUseEver);
        
        ImGui::Begin("Charm Menu", &g_ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        
        ImGui::TextColored(ImVec4(0.20f, 0.50f, 0.90f, 1.00f), "Free Fire Cheats");
        ImGui::Separator();
        
        ImGui::Checkbox("Aimbot", &aimbot_active);
        if (aimbot_active) {
            ImGui::SliderFloat("Smooth", &aim_smooth, 1.0f, 10.0f);
        }
        
        ImGui::Checkbox("Wallhack", &wallhack_active);
        
        ImGui::Spacing();
        if (ImGui::Button("Close Menu", ImVec2(100, 30))) {
            g_ShowMenu = false;
        }
        
        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Заглушки для остальных методов, чтобы Java не падала
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv *env, jclass clazz, jint width, jint height) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass clazz, jboolean down, jfloat PosX, jfloat PosY) {}
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
extern "C" JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect2(JNIEnv *env, jclass clazz) { return env->NewStringUTF("0,0,0,0"); }
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_setWallhack(JNIEnv *env, jclass clazz, jboolean on) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_setAimBot(JNIEnv *env, jclass clazz, jboolean on, jfloat fov, jfloat smooth, jint bone) {}
extern "C" JNIEXPORT void JNICALL Java_com_mycompany_application_MainActivity_drawMenu(JNIEnv *env, jclass clazz, jint w, jint h) {}
extern "C" JNIEXPORT jboolean JNICALL Java_com_mycompany_application_MainActivity_menuTouched(JNIEnv *env, jclass clazz, jfloat x, jfloat y, jint action) { return JNI_FALSE; }
