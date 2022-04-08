#include <stdio.h>
#include <unistd.h>

void print(const char *s)
{
    printf(s);
    fflush(stdout);
    usleep(200000);
}

int main()
{
    char out[62];
    for(int i = 0; i < 60; i++)
        out[i] = ' ';
    out[60] = '\n';
    out[61] = 0;
    while(1)
    {
        for(int i = 1; i < 60; i++)
        {
            out[i-1] = ' ';
            out[i] = 'A';
            print(out);
        }
        out[59] = 'B';
        print(out);
        sleep(8);
        out[59] = ' ';
        out[0] = 'A';
        print(out);
    }
}
