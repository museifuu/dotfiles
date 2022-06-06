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
    char cmd[CMDLEN*2];
    char exec[40];
    sprintf(exec, "exec -a custom top -b -d1 -w%d", CMDLEN-1);
    FILE *p = popen(exec, "r");
    while(1)
    {
        for(int line = 0; line < 9; line++)
        {
            fgets(cmd, CMDLEN*2, p);
            if(line == 7)
            {
                int len = strlen(cmd);

                for(int i = len-5; i < len; i++)
                    if(cmd[i] == ','){ cmd[i] = '.'; break; }

                sscanf(&cmd[len-6], "%f", &usage);

                for(int i = 0; i < len; i++)
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

                len = strlen(cmd);
                if(len > 15)
                    if(cmd[0] == '/' || cmd[0] == '\\' || cmd[0] == '.' || cmd[1] == ':')
                    {
                        for(int i = 0;; i++)
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
                int max_cmd_len_bytes, max_cmd_len_chars;
                max_cmd_len_bytes = max_cmd_len_chars = usage < 10 ? 16 : 15;

                len = 0;
                char *s = cmd;
                while(*s)
                {
                    int char_len = 1;
                    if      ((*s & 0xE0) == 0xC0) char_len = 2;
                    else if ((*s & 0xF0) == 0xE0) char_len = 3;
                    else if ((*s & 0xF8) == 0xF0) char_len = 4;
                    s += char_len;
                    max_cmd_len_bytes += char_len - 1;
                    len++;
                }

                if(len > max_cmd_len_chars)
                {
                    cmd[max_cmd_len_bytes-1] = '+';
                    cmd[max_cmd_len_bytes] = 0;
                    len = max_cmd_len_chars;
                }

                printf("%s", cmd);

                for(int i = len; i < max_cmd_len_chars; i++)
                    printf(" ");

                printf(" %.1f%%\n", usage);

                fflush(stdout);
            }
        }
    }
}
