
#pragma once

#include "../core/UUID.hpp"

#include <string>

namespace lamp
{
    class ImGuiWindow;

    class Panel
    {
    public:
        bool m_open;

        // This bool is true when the window first opens and gets set to false after it's first frame
        bool m_fresh;

        uint64_t m_panelID;

        virtual void Render();
        virtual ~Panel() = default;

        friend ImGuiWindow;
    };
} // namespace lamp
