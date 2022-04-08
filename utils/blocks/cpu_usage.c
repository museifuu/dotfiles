/* cpu_usage.c
 *
 * This program is meant to show the general cpu time usage and individual
 * thread usage on the statusbar. General cpu usage is shown in percentage,
 * while individual thread usage is shown in vertical gauges that change in
 * color, going from blue on 0% to red on 100%. This is accomplished by writing a
 * parseable output to /tmp/cpu, containing instructions to draw each individual
 * gauge.
 *
 * If DWM_STATUS is set, the output is formatted to be parsed by dwm with the
 * 'status2d' patch, which allows the rendering of rectangles:
 * https://dwm.suckless.org/patches/status2d/
 *
 * If WAYBAR_STATUS is set, the output is formatted with Pango Markup to draw
 * block characters that represent the gauges.
 *
 */

//#define DWM_STATUS
#define WAYBAR_STATUS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uchar.h>

// time in seconds between updates, can also be set through the command line argument
float update = 1.f;

#if defined(DWM_STATUS)
// height of the statusbar, take a screenshot and measure to be sure
const int bar_height = 18;
// width of the gauge, decrease if your system has many cores
const int gauge_width = 10;
// space between gauges, same as before
const int gauge_spacement = 5;
#endif

int get_thread_count()
{
    FILE *f = popen("nproc", "r");
    char ts[3];
    fgets(ts, 3, f);
    pclose(f);
    int t;
    sscanf(ts, "%d", &t);
    return t;
}

int main(int argc, char **argv)
{
    if(argc > 1)
        update = atof(argv[1]);

    unsigned long long int total, idle, *lastTotal, *lastIdle;
    int thread_count = get_thread_count();

    /* arrays for storing the measurements for each thread plus general*/
    lastTotal = malloc(sizeof(long long int)*(thread_count+1));
    lastIdle  = malloc(sizeof(long long int)*(thread_count+1));

    for(int i = 0; i <= thread_count; i++)
        lastTotal[i] = lastIdle[i] = 1;

    char *line = malloc(100);
    size_t size;
    while(1)
    {
        FILE *stat = fopen("/proc/stat", "r");

        if(stat == NULL)
            printf("Could not open /proc/stat");

        FILE *out = fopen("/tmp/cpu", "w+");
        for(int i = 0; i <= thread_count; i++)
        {
            getline(&line, &size, stat);
            char *token = strtok(line, " ");
            total = 0;
            idle = 0;
            /* states:
             * 1: user, 2: nice, 3: system, 4: idle, 5: iowait, 6: irq,
             * 7: softirq, 8: steal, 9: guest, 10: guest_nice
             */
            for(int state = 0; state < 10; state++)
            {
                token = strtok(NULL, " ");
                total += atoi(token);

                if(state == 3 /* idle */ || state == 4 /* iowait */)
                    idle += atoi(token);
            }
            // subtracting the normalized idle time from 1 gives us the normalized usage
            float usage = (1.0f - (float)(idle - lastIdle[i])/(total - lastTotal[i]));
            if(i == 0) // general usage
            {
                char padding[3] = "\0\0";
                if(usage < 1.f)
                    padding[0] = ' ';
                if(usage < 0.1f)
                    padding[1] = ' ';
                fprintf(out, "%s%d%% ", padding, (int)(usage*100));
            }
            else // thread usage
            {
#if defined(DWM_STATUS)
                int gauge_height = (usage*bar_height);
#endif

                // color calculations
                int r = 40, g = 0, b = 255;
                r += 215.f * usage;
                b -= 215.f * usage;
                g = (r+b)/5;

                // turns the color into a hexadecimal string
                char hex_color[7];
                char *hexer = "0123456789abcdef";
                hex_color[0] = hexer[r/16];
                hex_color[1] = hexer[r%16];
                hex_color[2] = hexer[g/16];
                hex_color[3] = hexer[g%16];
                hex_color[4] = hexer[b/16];
                hex_color[5] = hexer[b%16];
                hex_color[6] = 0;
#if defined(DWM_STATUS)
                fprintf(out, "^c#%s^^r0,%d,%d,%d^^f%d^", hex_color, bar_height - gauge_height, gauge_width, bar_height, gauge_width + gauge_spacement);
#elif defined(WAYBAR_STATUS)
                char *gauges[8] = { "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█" };
                fprintf(out, " <span color=\"#%s\">%s</span>", hex_color, gauges[(int)(usage*7)]);
#endif
            }
            lastTotal[i] = total;
            lastIdle[i] = idle;
        }
#if defined(DWM_STATUS)
        fprintf(out, "^d^");
#elif defined(WAYBAR_STATUS)
        fprintf(out, "\n");
#endif
        fclose(stat);
        fclose(out);
        usleep(update * 1000000);
    }
}
