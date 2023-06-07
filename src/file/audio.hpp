
#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <memory>

#include "audioHeaders.hpp"
#include "../core/UUID.hpp"

namespace lamp
{
    struct wavFile;

    struct Audio
    {
    public:
        void *m_chan_1;
        void *m_chan_2;
        size_t m_channelLength;

        // This boolean is true when there is allocated MEMORY inside any of the 2 channels
        // This boolean is false when there is no allocated memory and asking for values in any of the 2 channels will crash your program
        // (AHHHEEEMMM DO ERROR CHECK PLEAZZZZZ)
        bool m_freed;

        FmtChunk m_fmt;

        const UUID c_registryUUID;

    public:
        uint16_t GetAudioFormat() { return m_fmt.audio_format; };
        uint16_t GetNumChannels() { return m_fmt.num_channels; };
        uint32_t GetSampleRate() { return m_fmt.sample_rate; };
        uint32_t GetByteRate() { return m_fmt.byte_rate; };
        uint16_t GetBlockAlign() { return m_fmt.block_align; };
        uint16_t GetBitsPerSample() { return m_fmt.bits_per_sample; };

        Audio(const UUID id);
        ~Audio() = default;

        friend wavFile;
    };

} // namespace lamp
