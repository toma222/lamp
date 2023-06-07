
#include "Viewer.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "imgui/implot.h"

#include "../core/UUID.hpp"

namespace lamp
{
    Viewer::Viewer(std::shared_ptr<Audio> a)
    {
        m_currentTrack = a;
        m_open = true;
        m_fresh = true;

        m_audioDetail = 300;
        m_playbackPosition = 0;
        m_panelID = (uint64_t)UUID();

        m_panelName = "Viewer";
        m_panelName.append("###");
        m_panelName.append(std::to_string(m_panelID));
        printf("%s\n", m_panelName.c_str());
    }

    void Viewer::Render()
    {
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);

        ImGui::Begin(m_panelName.c_str());

        ImGui::SliderInt("Graph Optimization Level", &m_audioDetail, 10, 1000);

        if (ImGui::Button("Fit Graph"))
        {
            ImPlot::SetNextAxesToFit();
        }

        ImGui::Text("Sample Rate %i", m_currentTrack->GetSampleRate());
        ImGui::Text("Channels %i", m_currentTrack->GetNumChannels());
        ImGui::Text("Bits Per Sample %i", m_currentTrack->GetBitsPerSample());
        ImGui::Text("Byte Rate %i", m_currentTrack->GetByteRate());
        ImGui::Text("Block Align %i", m_currentTrack->GetBlockAlign());
        ImGui::Text("Audio Format %i", m_currentTrack->GetAudioFormat());
        ImGui::Text("UUID %llu", (uint64_t)m_currentTrack->c_registryUUID);

        static ImPlotDragToolFlags flags = ImPlotDragToolFlags_None;

        if (ImPlot::BeginPlot("My Plot"))
        {
            ImPlot::SetupAxes("X", "Y",
                              0, ImPlotAxisFlags_AutoFit);

            if (m_currentTrack->GetNumChannels() == 2)
            {
                // ImGui::PushID("node");
                ImPlot::PlotBars("Channel 1", (int16_t *)m_currentTrack->m_chan_1, m_currentTrack->m_channelLength / m_audioDetail, 2, 0, 0, 0, sizeof(int16_t) * m_audioDetail);

                // ImGui::PushID("node");
                ImPlot::PlotBars("Channel 2", (int16_t *)m_currentTrack->m_chan_2, m_currentTrack->m_channelLength / m_audioDetail, 2, 0, 0, 0, sizeof(int16_t) * m_audioDetail);
            }
            else
            {
                //* Assumes 1 channel
                ImPlot::PlotBars("Channel 1", (int16_t *)m_currentTrack->m_chan_1, m_currentTrack->m_channelLength / m_audioDetail, 2, 0, 0, 0, sizeof(int16_t) * m_audioDetail);
            }

            static double drag_tag = 0.25;
            ImPlot::DragLineX(0, &drag_tag, ImVec4(0, 1, 0, 1), 1, ImPlotDragToolFlags_NoFit);
            ImPlot::TagX(drag_tag, ImVec4(0, 1, 0, 1), " ");

            ImPlot::EndPlot();
        }

        m_playbackPosition += 1;

        ImGui::End();
    }
} // namespace lamp
