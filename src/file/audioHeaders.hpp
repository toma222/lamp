
#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

namespace lamp
{
    namespace utils
    {
        constexpr char riff_id[4] = {'R', 'I', 'F', 'F'};
        constexpr char format[4] = {'W', 'A', 'V', 'E'};
        constexpr char fmt_id[4] = {'f', 'm', 't', ' '};
        constexpr char data_id[4] = {'d', 'a', 't', 'a'};
    } // namespace utils

    struct RIFFHeader
    {
        char chunk_id[4];
        uint32_t chunk_size;
        char format[4];
    };

    struct ChunkInfo
    {
        char chunk_id[4];
        uint32_t chunk_size;
    };

    struct FmtChunk
    {
        uint16_t audio_format;
        uint16_t num_channels;
        uint32_t sample_rate;
        uint32_t byte_rate;
        uint16_t block_align;
        uint16_t bits_per_sample;

        FmtChunk() = default;
    };

} // namespace lamp

/*
template <typename T>
struct DataChunk
// ! We assume 16-bit monochannel samples
{
    T *data;
    int nb_of_samples;
    DataChunk(int s) : nb_of_samples{s}, data{new int16_t[s]} {}
    ~DataChunk() { delete[] data; }
};
*/
