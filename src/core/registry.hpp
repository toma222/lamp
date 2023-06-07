
#pragma once

#include <map>
#include <unordered_map>
#include <memory>

#include "UUID.hpp"

#include "../algorithms/table.hpp"
#include "../file/audio.hpp"

namespace lamp
{
    class AudioRegistry
    {
    private:
        Table<UUID, std::shared_ptr<Audio>> m_registry;
        static AudioRegistry s_audioRegistry;

    private:
        AudioRegistry();

    public:
        AudioRegistry(const AudioRegistry &) = delete;
        ~AudioRegistry() = default;

        static AudioRegistry &Get() { return s_audioRegistry; }

        // Creates Audio and adds it to the registry
        std::shared_ptr<Audio> CreateAudio();
        std::shared_ptr<Audio> CreateAudioFromUUID(UUID id);

        std::shared_ptr<Audio> GetAudio(UUID id);

        // Copy audio

        // Remove audio
    };
} // namespace lamp
