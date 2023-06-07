
#include "Toolbar.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "../core/logging.hpp"

#include "Window.hpp"

namespace lamp
{
    void DrawFileMenu()
    {
        if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
        {
            LOG(lamp::WARNING, "open project not available yet");
        }

        ImGui::Separator();

        if (ImGui::MenuItem("New Scene", "Ctrl+N"))
        {
            LOG(lamp::WARNING, "new projects not available yet");
        }

        if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
        {
            LOG(lamp::WARNING, "saving not available yet");
        }

        if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
            LOG(lamp::WARNING, "saving not available yet");

        ImGui::Separator();

        if (ImGui::MenuItem("Exit"))
            LOG(lamp::WARNING, "Exit not available");

        ImGui::EndMenu();
    }

    void DrawPanelMenu()
    {
        ImGui::Text("Open Panel");
        ImGui::Separator();

        if (ImGui::MenuItem("Viewer"))
            LOG(lamp::WARNING, "can't open the viewer panel");

        ImGui::EndMenu();
    }

    void Toolbar::DrawToolBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                DrawFileMenu();
            }

            if (ImGui::BeginMenu("Panel"))
            {
                DrawPanelMenu();
            }

            ImGui::EndMenuBar();
        }
    }
} // namespace lamp
