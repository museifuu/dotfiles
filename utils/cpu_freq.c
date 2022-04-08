#include <unistd.h>
#include <stdio.h>

typedef unsigned int Uint32;

const char *filename[4] =
{
    "/sys/devices/system/cpu/cpufreq/policy0/scaling_cur_freq",
    "/sys/devices/system/cpu/cpufreq/policy1/scaling_cur_freq",
    "/sys/devices/system/cpu/cpufreq/policy2/scaling_cur_freq",
    "/sys/devices/system/cpu/cpufreq/policy3/scaling_cur_freq"
};

int main(int argc, char **argv)
{
    FILE *cpu_file[4];
    char cpu_str[8];
    Uint32 cpu, cpu_total_i;
    float cpu_total_f;

    cpu_total_i = 0;
    for(int i = 0; i < 4; i++)
    {
        cpu_file[i] = fopen(filename[i], "r");
        fgets(cpu_str, 8, cpu_file[i]);
        sscanf(cpu_str, "%d", &cpu);
        cpu_total_i += cpu;
    }

    cpu_total_f = ((float)cpu_total_i)/4000;
    printf("%.3f MHz\n", cpu_total_f);
}
