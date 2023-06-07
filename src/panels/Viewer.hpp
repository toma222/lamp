
#pragma once

#include "Panel.hpp"
#include "../file/audio.hpp"

#include <string>
#include <memory>

namespace lamp
{
    class Viewer : public Panel
    {
    private:
        std::string m_currentFile;
        std::shared_ptr<Audio> m_currentTrack;

        int m_audioDetail;
        double m_playbackPosition;

        std::string m_panelName;

    public:
        Viewer(std::shared_ptr<Audio> a);
        ~Viewer() override = default;

    public:
        void Render() override;
    };
} // namespace lamp
