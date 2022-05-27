/* top_process.c
 *
 * This program is meant to show which process is taking the most amount of cpu
 * time at a given moment. This is accomplished by running the 'top' program and
 * parsing its output. For this to work, however, top must be configured in a
 * very specific way. A tailored top configuration file is available in this
 * repository under '.config/procps/customrc', and will be used automatically if
 * placed in the correct folder.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define CMDLEN 256

int main()
{
    float usage;
    char cmd[256];
    char exec[40];
    sprintf(exec, "exec -a custom top -b -d1 -w%d", CMDLEN-1);
    FILE *p = popen(exec, "r");
    while(1)
    {
        for(int i = 0; i < 9; i++)
        {
            fgets(cmd, 256, p);
            if(i == 7)
            {
                for(int i = CMDLEN-5; i < CMDLEN; i++)
                    if(cmd[i] == ','){ cmd[i] = '.'; break; }
                sscanf(&cmd[CMDLEN-6], "%f", &usage);
                for(int i = 0; i < CMDLEN; i++)
                {
                    if(cmd[i] == ' ')
                    {
                        if(cmd[i-7] == 'P' && cmd[i+1] == 'F')
                        {
                            cmd[i] = '_';
                            if(cmd[i+6] == ' ') cmd[i+6] = '_';
                        }
                        else if(cmd[i+1] == '-' || cmd[i+1] == ':' || cmd[i+1] == ' ' || cmd[i+1] == '/')
                        {
                            cmd[i] = 0;
                            break;
                        }
                    }
                }
                if(strlen(cmd) > 15)
                    if(cmd[0] == '/' || cmd[0] == '.' || cmd[1] == ':')
                    {
                        for(int i = 0; i < CMDLEN; i++)
                        {
                            if(cmd[i] == 0)
                            {
                                for(int j = i; j >= 0 ; j--)
                                {
                                    if(cmd[j] == '/' || cmd[j] == '\\')
                                    {
                                        int k;
                                        for(k = 0; cmd[j+k] != 0; k++)
                                            cmd[k] = cmd[j+k+1];
                                        cmd[k-1] = 0;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                char out[25];
                int len = strlen(cmd);
                if(len > 16)
                    cmd[15] = 0;
                strcpy(out, cmd);
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
                fputs(out, stdout);
                fflush(stdout);
            }
        }
    }
}
