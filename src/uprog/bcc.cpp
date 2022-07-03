#include <argp.h>
#include <bits/types/error_t.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

/*
 */
#include "event.h"
#include "cachestat.hpp"
#include "iotop.hpp"
#include "u_option.hpp"

using namespace std;

static volatile int exiting = 0;
static void sig_handler(int sig) { exiting = 1; }


const char *argp_program_bug_address = "shouc.wang@hotmail.com";
const char *argp_program_version = "v0.0.1";
static char args_doc[] = "[iotop|cachestat]";

static struct argp_option options[] = 
{
    {0 ,0 ,0 ,0 , "common", 1},
    {"interval", 'i', "Int", 0, "interval"},
    {0,0,0,0, "CacheState", 2},
    {"timestamp", 'T', 0, 0, "print the timestamp"},
    {0,0,0,0, "iotop", 3},
    {"sort", 3330, "Str", 0, "sort by [io|byte|cost]"},
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
static struct argp argp_for_kind = {options, parser_parse_tool_kind,args_doc, 0};


static inline error_t parser_parse_options(int key, char *arg, struct argp_state *state)
{
    Options *opt = (Options*)state->input;
    switch (key) {
        case 'i':
            {
                int interval = 1;
                if (arg != NULL)  interval = atoi(arg); 
                opt->m_opt_interval = interval;
            }
            break;
        case 'T':
            if (opt->Kind() == CACHESTAT) opt->m_opt_options.cachestat.show_time = true; 
            break;
        case 3330:
            if (opt->Kind() != IOTOP) break;
            opt->m_opt_options.iotop.sort_field = arg;
    }
    return 0;
}

static struct argp argp_for_opt = {options, parser_parse_options, 0, 0};

int main(int argc, char*argv[])
{
    error_t err = argp_parse(&argp_for_kind, argc, argv, 0, 0, &tool_kind);
    if (err) {
        cout << "parse argument failed" << endl;
    }
    Options *opt = new Options(tool_kind);
    if (opt->Kind() == UNKNOWN) {
        cout << "unkonow tool" << tool_kind << endl;
        exit(-1);
    }
    err = argp_parse(&argp_for_opt, argc, argv, 0, 0, opt);
    if (err) {
        cout << "parse argument failed" << endl;
    }
    Controller *ctrl = opt->NewForController();
    ctrl->Run();

    return 0;
}

