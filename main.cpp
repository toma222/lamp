
/*
#include <soundio/soundio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "src/gui/Window.hpp"
#include "src/panels/Viewer.hpp"
#include "src/file/wav.hpp"
#include "src/core/logging.hpp"

lamp::lamp_wav de("path");
int place = 0;

static int prioritized_sample_rates[] = {
    48000,
    44100,
    44100,
    96000,
    24000,
    0,
};

__attribute__((cold))
__attribute__((noreturn))
__attribute__((format(printf, 1, 2))) static void
panic(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    abort();
}

static int min_int(int a, int b)
{
    return (a < b) ? a : b;
}

static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;

int16_t *read_ptr;

static void write_callback(struct SoundIoOutStream *outstream,
                           int frame_count_min, int frame_count_max)
{
    struct SoundIoChannelArea *areas;
    int frames_left;
    int frame_count;
    int err;

    int fill_bytes = de.m_fileLength;
    int fill_count = fill_bytes / outstream->bytes_per_frame;

    if (fill_bytes < 0)
    {
        // Ring buffer does not have enough data, fill with zeroes.
        LOG(lamp::ERROR, "you are out of data :(");
        frames_left = frame_count_min;
        for (;;)
        {
            frame_count = frames_left;
            if (frame_count <= 0)
                return;
            if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count)))
                panic("begin write error: %s", soundio_strerror(err));
            if (frame_count <= 0)
                return;
            for (int frame = 0; frame < frame_count; frame += 1)
            {
                for (int ch = 0; ch < outstream->layout.channel_count; ch += 1)
                {
                    memset(areas[ch].ptr, 0, outstream->bytes_per_sample);
                    areas[ch].ptr += areas[ch].step;
                }
            }

            if ((err = soundio_outstream_end_write(outstream)))
                panic("end write error: %s", soundio_strerror(err));
            frames_left -= frame_count;
        }
    }

    int read_count = min_int(frame_count_max, fill_count);
    frames_left = read_count;

    while (frames_left > 0)
    {
        int frame_count = frames_left;

        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count)))
            panic("begin write error: %s", soundio_strerror(err));

        if (frame_count <= 0)
            break;

        for (int frame = 0; frame < frame_count; frame += 1)
        {
            for (int ch = 0; ch < outstream->layout.channel_count; ch += 1)
            {
                memcpy(areas[ch].ptr, read_ptr, outstream->bytes_per_sample);
                areas[ch].ptr += areas[ch].step;
            }

            read_ptr += outstream->bytes_per_sample; // ! SOMETHING IS WRONG WITH THIS, I DONT KNOW WHAT BUT SOMETHING IS WRONG WITH THIS LINE OF CODE
        }

        if ((err = soundio_outstream_end_write(outstream)))
            panic("end write error: %s", soundio_strerror(err));

        frames_left -= frame_count;
    }
}

int main(int argc, char **argv)
{
    de.Read();
    read_ptr = de.m_audio->m_ch1;

    int err;
    struct SoundIo *soundio = soundio_create();
    if (!soundio)
    {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    if ((err = soundio_connect(soundio)))
    {
        fprintf(stderr, "error connecting: %s\n", soundio_strerror(err));
        return 1;
    }

    soundio_flush_events(soundio);

    int default_out_device_index = soundio_default_output_device_index(soundio);
    if (default_out_device_index < 0)
    {
        fprintf(stderr, "no output device found\n");
        return 1;
    }

    struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
    if (!device)
    {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    fprintf(stderr, "Output device: %s\n", device->name);

    struct SoundIoOutStream *outstream = soundio_outstream_create(device);
    if (!outstream)
    {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    if (!soundio_device_supports_sample_rate(device, de.m_audio->m_header.m_sampleRate))
    {
        LOG(lamp::WARNING, "device does not like that sample rate");
        printf("%i\n", de.m_audio->m_header.m_sampleRate);
    }

    outstream->format = SoundIoFormatS16LE;
    outstream->sample_rate = de.m_audio->m_header.m_sampleRate;
    outstream->write_callback = write_callback;

    if ((err = soundio_outstream_open(outstream)))
    {
        fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
        return 1;
    }

    if (outstream->layout_error)
        fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

    if ((err = soundio_outstream_start(outstream)))
    {
        fprintf(stderr, "unable to start device: %s\n", soundio_strerror(err));
        return 1;
    }

    for (;;)
        soundio_wait_events(soundio);

    soundio_outstream_destroy(outstream);
    soundio_device_unref(device);
    soundio_destroy(soundio);
    return 0;
}
*/

#include <GLFW/glfw3.h>
#include <soundio/soundio.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>

#include "implot.h"

#include "src/gui/Window.hpp"

#include "src/panels/Viewer.hpp"

#include "src/file/audio.hpp"
#include "src/file/wav.hpp"

#include "src/core/registry.hpp"

int main(int argc, char const *argv[])
{
    glfwInit();

    lamp::ImGuiWindow window;

    lamp::wavFile file("C:/Users/Aidan/Desktop/vulcantesting/resources/StarWars3.wav", lamp::AudioRegistry::Get().CreateAudio());
    file.ReadFile();

    lamp::wavFile clair("C:/Users/Aidan/Desktop/vulcantesting/resources/Clair_de_Lune__Debussy.wav", lamp::AudioRegistry::Get().CreateAudio());
    clair.ReadFile();

    // -------------------------------------------- //

    // -------------------------------------------- //

    window.AddPanel<lamp::Viewer>(file.m_audio);
    window.AddPanel<lamp::Viewer>(clair.m_audio);

    while (!window.CheckClose())
    {
        window.Update();
    }

    return 0;
}
