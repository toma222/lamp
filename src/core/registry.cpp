#include "registry.hpp"

namespace lamp
{
    AudioRegistry AudioRegistry::s_audioRegistry;

    AudioRegistry::AudioRegistry()
    {
    }

    std::shared_ptr<Audio> AudioRegistry::CreateAudio()
    {
        return CreateAudioFromUUID(UUID());
    }

    std::shared_ptr<Audio> AudioRegistry::CreateAudioFromUUID(UUID id)
    {
        std::shared_ptr<Audio> audio = std::make_shared<Audio>(id);
        m_registry.Add(id, audio);

        return audio;
    }
}
