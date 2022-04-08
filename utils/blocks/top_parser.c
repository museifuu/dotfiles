#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    float usage;
    const int width = 150;
    char name[width];
    while(1)
    {
        START:
        usleep(2000000);
        FILE *tp = fopen("/tmp/top_grepped", "r");
        if(fgets(name, width, tp) == NULL)
        {
            fclose(tp);
            goto START;
        }
        freopen("/tmp/top_grepped", "w", tp);
        fclose(tp);
        for(int i = width-5; i < width; i++)
            if(name[i] == ','){ name[i] = '.'; break; }
        sscanf(&name[width-6], "%f", &usage);
        for(int i = 0; i < width; i++)
        {
            if(name[i] == ' ')
            {
                if(name[i-7] == 'P' && name[i+1] == 'F')
                {
                    name[i] = '_';
                    if(name[i+6] == ' ') name[i+6] = '_';
                }
                else if(name[i+1] == '-' || name[i+1] == ':' || name[i+1] == ' ' || name[i+1] == '/')
                {
                    name[i] = 0;
                    break;
                }
            }
        }
        if(strlen(name) > 15)
            if(name[0] == '/' || name[0] == '.' || name[1] == ':')
            {
                for(int i = 0; i < width; i++)
                {
                    if(name[i] == 0)
                    {
                        for(int j = i; j >= 0 ; j--)
                        {
                            if(name[j] == '/' || name[j] == '\\')
                            {
                                int k;
                                for(k = 0; name[j+k] != 0; k++)
                                    name[k] = name[j+k+1];
                                name[k-1] = 0;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        char out[25];
        int len = strlen(name);
        if(len > 16)
            name[15] = 0;
        strcpy(out, name);
        for(int i = 0; i < 16-len; i++)
        out[i+len] = ' ';
        int x = 15;
        if(len > 15)
            out[14] = '+';
        if(usage < 10)
            x++;
        sprintf(&out[x], " %.1f%%", usage);
        for(int i = 0; i < 21; i++)
            if(out[i] == 0) out[i] = ' ';
        out[21] = '\n';
        out[22] = 0;
        FILE *of = fopen("/tmp/top_process", "w+");
        fputs(out, of);
        fclose(of);
    }
}
