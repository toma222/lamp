
#include "wav.hpp"
#include "audioHeaders.hpp"

#include "../core/logging.hpp"

namespace lamp
{
    wavFile::wavFile(std::string filePath, std::shared_ptr<Audio> audio)
        : m_filePath(filePath), m_audio(audio)
    {
    }

    void wavFile::ReadFile()
    {
        LOG(lamp::TRACE, "Reading wav file");

        const char *filePath = m_filePath.c_str();
        std::string input;

        FILE *wavFile = fopen(filePath, "r");
        if (wavFile == nullptr)
        {
            // TODO just add an assert system
            LOG(lamp::ERROR, "could not load wav file");
            std::cout << filePath << "\n";
        }

        LOG(lamp::TRACE, "wav file has been opened");

        RIFFHeader h;
        LOG(lamp::TRACE, "reading RIFFHeader");

        fread(&h, sizeof(h), 1, wavFile);
        if (memcmp(h.chunk_id, utils::riff_id, 4) || memcmp(h.format, utils::format, 4))
        {
            LOG(lamp::WARNING, "riff or format ID's are not formated right on your wav file");
        }

        LOG(lamp::TRACE, "finished reading RIFFHeader");

        // read chunk infos iteratively
        ChunkInfo ch;

        bool fmt_read = false;
        bool data_read = false;
        while (!feof(wavFile))
        {
            fread(&ch, sizeof(ch), 1, wavFile);

            LOG(lamp::TRACE, "searching for the data chunk");

            // if fmt chunk?
            if (memcmp(ch.chunk_id, utils::fmt_id, 4) == 0)
            {
                LOG(lamp::TRACE, "found fmt chunk");
                fread(&m_audio.get()->m_fmt, ch.chunk_size, 1, wavFile);

                LOG(lamp::INFO, "Reading data from fmt");
                std::cout << "bits per sample : " << m_audio->m_fmt.bits_per_sample << "\n";
                std::cout << "sample rate : " << m_audio->m_fmt.sample_rate << "\n";
                std::cout << "Number of channels : " << m_audio->m_fmt.num_channels << "\n";

                fmt_read = true;
            }

            // is data chunk?
            else if (memcmp(ch.chunk_id, utils::data_id, 4) == 0)
            {
                LOG(lamp::TRACE, "found data chunk");
                size_t dataElements = ch.chunk_size / sizeof(int16_t);
                int16_t *data = new int16_t[dataElements];

                fread(data, ch.chunk_size, 1, wavFile);

                if (m_audio->m_fmt.num_channels == 2)
                {
                    LOG(lamp::INFO, "Parsing data chunk into 2 channels");
                    LOG(lamp::INFO, "Allocating memory to channels 1 and 2");
                    m_audio->m_chan_1 = (void *)malloc(sizeof(int16_t) * dataElements);
                    m_audio->m_chan_2 = (void *)malloc(sizeof(int16_t) * dataElements);

                    m_audio->m_freed = true;

                    for (size_t d = 0; d < (dataElements); d += 2)
                    {
                        ((int16_t *)m_audio->m_chan_1)[d] = data[d];
                        ((int16_t *)m_audio->m_chan_2)[d] = data[d + 1];
                    }
                }
                else if (m_audio->m_fmt.num_channels == 1)
                {
                    LOG(lamp::INFO, "Parsing data chunk into 1 channel");
                    LOG(lamp::INFO, "Allocating memory to channel 1");
                    m_audio->m_chan_1 = (void *)malloc(sizeof(int16_t) * dataElements);

                    m_audio->m_freed = true;

                    for (size_t d = 0; d < dataElements; d++)
                    {
                        ((int16_t *)m_audio->m_chan_1)[d] = data[d];
                    }
                }

                m_audio->m_channelLength = dataElements;

                data_read = true;
            }
            else
            {
                LOG(lamp::TRACE, "nothing found, moving to the next chunk");
                fseek(wavFile, ch.chunk_size, SEEK_CUR);
            }
        }

        if (!data_read || !fmt_read)
        {
            LOG(lamp::WARNING, "there was an error reading the data and we could not find the required chunks to read the full file");
        }

        LOG(lamp::TRACE, "done reading the wav file");
    }
} // namespace lamp
