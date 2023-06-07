
#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <memory>

#include "audio.hpp"

namespace lamp
{
    // only does one channel for now
    struct wavFile
    {
    public:
        std::string m_filePath;
        std::shared_ptr<Audio> m_audio;

    public:
        wavFile(std::string filePath, std::shared_ptr<Audio> audio);

        // Reads the file in m_filePath
        void ReadFile();

        // Returns the data as a void pointer so you can destroy the known universe
        // doing things you SHOULD NOT BE DOING IN CPP
        void *GetChannel1() { return m_audio->m_chan_1; };
        void *GetChannel2() { return m_audio->m_chan_2; };

    public:
        uint16_t GetAudioFormat() { return m_audio->m_fmt.audio_format; };
        uint16_t GetNumChannels() { return m_audio->m_fmt.num_channels; };
        uint32_t GetSampleRate() { return m_audio->m_fmt.sample_rate; };
        uint32_t GetByteRate() { return m_audio->m_fmt.byte_rate; };
        uint16_t GetBlockAlign() { return m_audio->m_fmt.block_align; };
        uint16_t GetBitsPerSample() { return m_audio->m_fmt.bits_per_sample; };
    };
} // namespace lamp
