
#include "wav.hpp"
#include "audioHeaders.hpp"

#include "../core/logging.hpp"

namespace lamp
{
    Audio::Audio(UUID id)
        : c_registryUUID(id)
    {
        m_freed = false;
    }
} // namespace lamp
