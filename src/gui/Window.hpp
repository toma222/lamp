
#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <string>

#include "../panels/Panel.hpp"
#include "Toolbar.hpp"

namespace lamp
{
    class ImGuiWindow
    {
    private:
        int width;
        int height;
        std::string name;

        GLFWwindow *m_window;
        Toolbar m_toolbar;

        std::vector<std::shared_ptr<Panel>> m_panels;

    public:
        ImGuiWindow();
        ~ImGuiWindow();

        template <typename T, typename... Args>
        std::shared_ptr<T> AddPanel(Args &&...args)
        {
            std::shared_ptr<T> t = std::make_shared<T>(std::forward<Args>(args)...);
            std::shared_ptr<Panel> p = std::static_pointer_cast<Panel>(t);
            m_panels.push_back(p);
            return t;
        }

        void Update();
        bool CheckClose();
    };
} // namespace lamp
