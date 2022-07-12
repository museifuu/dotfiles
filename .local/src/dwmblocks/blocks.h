//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/                 	            	/*Update Interval*/	/*Update Signal*/
    {""                     , "cat /tmp/network",                       1,                  0},
    {""                     , "~/.local/bin/signal",               20,	            	0},
    {"^c#FF00FF^CPU:^d^ "   , "cat /tmp/cpu",                           1,                  0},
    {""                     , "cat /tmp/top_process",                   2,                  0},
    {""                     , "~/.local/bin/cpu_temp",               1,              	0},
    {""                     , "~/.local/bin/memory",		            1,	            	0},
    {""                     , "date '+%a %d %h %Y %T'",	            1,	            	0},
};

//sets delimeter between status commands. empty string ("") means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;

