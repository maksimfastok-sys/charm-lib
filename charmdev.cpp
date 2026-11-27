#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"

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
        
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 8.0f;
        style.FrameRounding = 4.0f;
        style.WindowBorderSize = 1.0f;
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.95f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.60f, 1.00f, 1.00f);
        
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 100"); // ES 2.0
        
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
