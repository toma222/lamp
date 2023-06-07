
#pragma once

namespace lamp
{
    class ImGuiWindow;

    class Toolbar
    {
    public:
        // touch this pointer and you die
        ImGuiWindow *m_window;

        void DrawToolBar();

    public:
        Toolbar(ImGuiWindow *window)
            : m_window(window) {};
            
        ~Toolbar() = default;
    };
} // namespace lamp
