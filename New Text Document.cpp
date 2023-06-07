

#include "wav.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <utility>

#include "FFT/fft.h"
#include "../core/logging.hpp"

namespace lamp
{
    lamp_wav::lamp_wav(std::string path)
        : m_path(path)
    {
        m_audio = std::make_shared<Audio>();
    }

    // Function prototypes
    int getFileSize(FILE *inFile);

    // find the file size
    int getFileSize(FILE *inFile)
    {
        int fileSize = 0;
        fseek(inFile, 0, SEEK_END);

        fileSize = ftell(inFile);

        fseek(inFile, 0, SEEK_SET);
        return fileSize;
    }

    bool lamp_wav::Read()
    {
        int headerSize = sizeof(wav_hdr);

        const char *filePath = "C:/Users/Aidan/Desktop/vulcantesting/resources/CantinaBand3.wav";
        std::string input;

        FILE *wavFile = fopen(filePath, "r");
        if (wavFile == nullptr)
        {
            // TODO just add an assert system
            LOG(lamp::ERROR, "could not load wav file");
            std::cout << filePath << "\n";
        }

        size_t bytesRead = fread(&m_header, 1, headerSize, wavFile); // Reads the header into the struct
        uint16_t bytesPerSample = m_header.bitsPerSample / 8;

        // ! does not load the full song
        uint64_t NumSamples = m_header.ChunkSize / bytesPerSample;

        if (m_header.bitsPerSample == 8)
        {
            LOG(lamp::INFO, "current wav file Uint8 using bytes per sample");
        }
        else if (m_header.bitsPerSample == 16)
        {
            LOG(lamp::INFO, "current wav file Uint16 bytes per sample");
        }

        // ! Channel 2 not initialized right now
        // m_audio->m_channel2 = (short *)malloc(sizeof(short) * NumSamples);

        m_audio->m_ch1 = (int16_t *)malloc(sizeof(int16_t) * NumSamples);
        m_audio->m_ch2 = (int16_t *)malloc(sizeof(int16_t) * NumSamples);

        int16_t *data = (int16_t *)malloc(sizeof(int16_t) * NumSamples);
        fread(data, sizeof(int16_t), NumSamples, wavFile);

        if (m_header.NumOfChan == 2)
        {
            LOG(lamp::INFO, "current wav file using 2 channel");
            for (size_t d = 0; d < NumSamples; d += 2)
            {
                m_audio->m_ch1[d] = data[d];
                m_audio->m_ch2[d] = data[d + 1];
            }
        }
        else if (m_header.NumOfChan == 1)
        {
            LOG(lamp::INFO, "current wav file using 1 channel");
            printf("%lli\n", NumSamples);
            for (size_t d = 0; d < NumSamples; d++)
            {
                m_audio->m_ch1[d] = data[d];
            }
        }

        free(data);
        m_fileLength = getFileSize(wavFile);
        m_audio->m_channelLength = NumSamples / 2;
        fclose(wavFile);

        m_audio->m_header.m_channels = m_header.NumOfChan;
        m_audio->m_header.m_sampleRate = m_header.SamplesPerSec;
        m_audio->m_header.m_bitsPerSample = m_header.bitsPerSample;

        // std::cout << "File is                    :" << filelength << " bytes." << std::endl;
        std::cout << "RIFF header                :" << m_header.RIFF[0] << m_header.RIFF[1] << m_header.RIFF[2] << m_header.RIFF[3] << std::endl;
        std::cout << "WAVE header                :" << m_header.WAVE[0] << m_header.WAVE[1] << m_header.WAVE[2] << m_header.WAVE[3] << std::endl;
        std::cout << "FMT                        :" << m_header.fmt[0] << m_header.fmt[1] << m_header.fmt[2] << m_header.fmt[3] << std::endl;
        std::cout << "Data size                  :" << m_header.ChunkSize << std::endl;

        // Display the sampling Rate from the header
        std::cout << "Sampling Rate              :" << m_header.SamplesPerSec << std::endl;
        std::cout << "Number of bits used        :" << m_header.bitsPerSample << std::endl;
        std::cout << "Number of channels         :" << m_header.NumOfChan << std::endl;
        std::cout << "Number of bytes per second :" << m_header.bytesPerSec << std::endl;
        std::cout << "Data length                :" << m_header.Subchunk2Size << std::endl;
        std::cout << "Audio Format               :" << m_header.AudioFormat << std::endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        std::cout << "Block align                :" << m_header.blockAlign << std::endl;
        std::cout << "Data string                :" << m_header.Subchunk2ID[0] << m_header.Subchunk2ID[1] << m_header.Subchunk2ID[2] << m_header.Subchunk2ID[3] << std::endl;

        printf("runtime %i", (m_header.ChunkSize / m_header.bytesPerSec) / 60);

        return true;
    }

    void lamp_wav::Write()
    {
    }

} // namespace lamp

/*

        std::cout << "File is                    :" << filelength << " bytes." << std::endl;
        std::cout << "RIFF header                :" << m_header.RIFF[0] << m_header.RIFF[1] << m_header.RIFF[2] << m_header.RIFF[3] << std::endl;
        std::cout << "WAVE header                :" << m_header.WAVE[0] << m_header.WAVE[1] << m_header.WAVE[2] << m_header.WAVE[3] << std::endl;
        std::cout << "FMT                        :" << m_header.fmt[0] << m_header.fmt[1] << m_header.fmt[2] << m_header.fmt[3] << std::endl;
        std::cout << "Data size                  :" << m_header.ChunkSize << std::endl;

        // Display the sampling Rate from the header
        std::cout << "Sampling Rate              :" << m_header.SamplesPerSec << std::endl;
        std::cout << "Number of bits used        :" << m_header.bitsPerSample << std::endl;
        std::cout << "Number of channels         :" << m_header.NumOfChan << std::endl;
        std::cout << "Number of bytes per second :" << m_header.bytesPerSec << std::endl;
        std::cout << "Data length                :" << m_header.Subchunk2Size << std::endl;
        std::cout << "Audio Format               :" << m_header.AudioFormat << std::endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        std::cout << "Block align                :" << m_header.blockAlign << std::endl;
        std::cout << "Data string                :" << m_header.Subchunk2ID[0] << m_header.Subchunk2ID[1] << m_header.Subchunk2ID[2] << m_header.Subchunk2ID[3] << std::endl;

*/
