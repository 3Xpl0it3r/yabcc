#include <linux/bpf.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <argp.h>
#include <time.h>

/*
 */
#include "event.h"
#include "cachestat.hpp"


static volatile int exiting = 0;
static void sig_handler(int sig) { exiting = 1; }


const char *argp_program_bug_address = "shouc.wang@hotmail.com";
const char *argp_program_version = "v0.0.1";

static struct argp_option options[] = 
{
    {0 ,0 ,0 ,0 , "Network Tracing", 1},
    {"dhost", 1111, "String", 0, "destination host"},
    {"shost", 1112, "String", 0, "source host"},
    {"potocol", 'p', "String",0, "protocol eg icmp tcp udp ..."},
    {"sport", 1113, "Intenger",0, "source port"},
    {"dport", 1114, "Intenger",0, "destination port"},
    {0,0,0,0, "iotop", 2},
    {"interval", 2221, "Intenger", OPTION_ARG_OPTIONAL, "output interval, in seconds"},
    {"count", 2222, "Intenger", OPTION_ARG_OPTIONAL, "number of outputs"},
    {0}
};



static char *tool_kind;
static inline error_t parser_parse_tool_kind(int key, char *arg, struct argp_state *state)
{
    switch (key) {
        case ARGP_KEY_NO_ARGS:
            argp_usage(state);
            break;
        case ARGP_KEY_ARG:
            {
                if (state->arg_num >= 1) {
                    argp_usage(state);
                }
                *(char **)state->input = arg;
                break;
            }
    }
    return 0;
}
static struct argp argp_tool_kind = {options, parser_parse_tool_kind,0, 0};


static inline error_t parser_parse_options(int key, char *arg, struct argp_state *state)
{
    return 0;
}



int main(int argc, char*argv[])
{
    CacheState *cs = new(CacheState);
    cs->Run();
    return 0;
}

