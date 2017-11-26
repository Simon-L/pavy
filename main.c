/***
  This file is part of PulseAudio.
  PulseAudio is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation; either version 2.1 of the License,
  or (at your option) any later version.
  PulseAudio is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License
  along with PulseAudio; if not, see <http://www.gnu.org/licenses/>.
***/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 256

#include "heavy/Heavy_theme_groundfloor.h"

float peak = 0.7;

int main(int argc, char*argv[]) {
    double sampleRate = 44100.0;

    HeavyContextInterface *context = hv_theme_groundfloor_new(sampleRate);

    int numOutputChannels = hv_getNumOutputChannels(context);
    printf("Audio channels: %d\n", numOutputChannels);

    float *outBuffers = (float *) hv_malloc(numOutputChannels * BUFSIZE * sizeof(float));

    /* The Sample format to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_FLOAT32LE,
        .rate = 44100,
        .channels = 2
    };

    pa_simple *s = NULL;
    int ret = 1;
    int error;

    /* replace STDIN with the specified file if needed */
    if (argc > 1) {
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, __FILE__": open() failed: %s\n", strerror(errno));
            goto finish;
        }
        if (dup2(fd, STDIN_FILENO) < 0) {
            fprintf(stderr, __FILE__": dup2() failed: %s\n", strerror(errno));
            goto finish;
        }
        close(fd);
    }
    /* Create a new playback stream */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    for (;;) {
        uint8_t buf[BUFSIZE];
        ssize_t r;
#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        fprintf(stderr, "%0.0f usec    \r", (float)latency);
#endif
        /* Read some data ... */
        // if ((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0) {
        //     if (r == 0) /* EOF */
        //         break;
        //     fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
        //     goto finish;
        // }
        /* ... and play it */
        hv_processInlineInterleaved(context, NULL, outBuffers, BUFSIZE);
        for (size_t g = 0; g < BUFSIZE * 2; g++) {
          // outBuffers[g] = outBuffers[g] * 0.1;
          // fprintf(stderr, "%d - %f\n", g, outBuffers[g]);
          if (outBuffers[g] > peak) {
            peak = outBuffers[g];
            printf("Peak value: %f\n", peak);
          }
        }
        // printf("----");
        if (pa_simple_write(s, outBuffers, numOutputChannels * BUFSIZE * sizeof(float), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            goto finish;
        }
    }
    /* Make sure that every single sample was played */
    if (pa_simple_drain(s, &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    ret = 0;
finish:
    hv_delete(context);
    if (s)
        pa_simple_free(s);
    return ret;
}
