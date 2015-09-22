//
// Created by andrey on 19.09.15.
// 515 аудитория
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int h;
    int f_c, f_a, f_b, f_x, f_y;
    int g_c, g_a, g_b, g_x, g_y;
} State;

typedef struct {
    char h[10];
    char f_c[10], f_x[10], f_y[10];
    char g_c[10], g_x[10], g_y[10];
} PrintState;

enum CONSTANTS {
    // number of achievable strings in function "f"
    F_NUMBER_STRINGS = 11,
    // number of achievable strings in function "g"
    G_NUMBER_STRINGS = 12
};



const int INIT_CAPACITY = 8;
size_t capacity = 0;
size_t arr_size = 0;
// storage of unique state for print
PrintState * array = NULL;

int init_h = 0;
int init_f_x = 0;
int init_f_y = 0;
int init_g_x = 0;
int init_g_y = 0;

State cur_state;

// operator== for State and PrintState
// return 0, if OK
int equal_state(State * st1, PrintState * prst2)
{
    if (st1 == NULL || prst2 == NULL)
        return -1;
    return st1->h == atoi(prst2->h)
            && st1->f_c == atoi(prst2->f_c) && st1->g_c == atoi(prst2->g_c)
            && st1->f_x == atoi(prst2->f_x) && st1->f_y == atoi(prst2->f_y)
            && st1->g_x == atoi(prst2->g_x) && st1->g_y == atoi(prst2->g_y);
}

// operator= for PrintState and State
// return 0, if OK
int assignment(PrintState * prst, State * st) {
    if (prst == NULL || st == NULL)
        return -1;
    if (init_h) {
        if (sprintf(prst->h, "%d", st->h) < 1)
            return -1;
    } else
        prst->h[0] = '#';
    if (init_f_x) {
        if (sprintf(prst->f_x, "%d", st->f_x) < 1)
            return -1;
    } else
        prst->f_x[0] = '#';
    if (init_f_y) {
        if (sprintf(prst->f_y, "%d", st->f_y) < 1)
            return -1;
    } else
        prst->f_y[0] = '#';
    if (init_g_x) {
        if (sprintf(prst->g_x, "%d", st->g_x) < 1)
            return -1;
    } else
        prst->g_x[0] = '#';
    if (init_g_y) {
        if (sprintf(prst->g_y, "%d", st->g_y) < 1)
            return -1;
    } else
        prst->g_y[0] = '#';
    if (sprintf(prst->f_c, "%d", st->f_c) < 1)
        return -1;
    if (sprintf(prst->g_c, "%d", st->g_c) < 1)
        return -1;
    return 0;
}

// print PrintState to stream
// return 0, if OK
int print_to_stream(FILE * stream, PrintState * prst) {
    if (fprintf(stream, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                prst->f_c, prst->g_c, prst->h,
                prst->f_x, prst->f_y, prst->g_x, prst->g_y) < 7)
        return -1;
    return 0;
}

// extend capacity for array
// return 0, if OK
int extend_capacity()
{
    if (capacity == 0)
    {
        capacity = INIT_CAPACITY;
        array = malloc(capacity * sizeof(State));
        if (array == NULL)
            return -1;
        return 0;
    }
    capacity *= 2;
    array = realloc(array, capacity * sizeof(PrintState));
    if (array == NULL)
        return -1;
    return 0;
}

// return 0, if the same state is not existed in array
// return 1, if the same state is existed in array
// return -1, if something is wrong
int find_same(State *p_state)
{
    if (p_state == NULL)
        return -1;
    int i;
    for (i = 0; i < arr_size; ++i)
        if (equal_state(p_state, array +i))
            return 1;
    return 0;
}

// push cur_state
// return 0, if OK
int push(void)
{
    // check the same states
    if (!find_same(&cur_state)) {
        // add unique state
        if (capacity == arr_size)
            if (extend_capacity() != 0)
                return -1;
        if (assignment(array + arr_size++, &cur_state) != 0)
            return -1;
    }
    return 0;
}


// emulator of function f
int execute_f(void)
{
    switch(cur_state.f_c)
    {
        case 0:
            init_f_x = init_f_y = 1;
            cur_state.f_x = cur_state.f_y = 0;
            break;
        case 1:
            init_f_x = 1;
            cur_state.f_x = 8;
            break;
        case 2:
            init_f_y = 1;
            cur_state.f_y = 4;
            break;
        case 3:
            init_h = 1;
            cur_state.h = cur_state.f_y;
            break;
        case 4:
            if (!(cur_state.h > cur_state.f_x + cur_state.f_y))
                ++cur_state.f_c;
            break;
        case 5:
            init_f_x = 1;
            cur_state.f_x = 10;
            break;
        case 6:
            if (!(cur_state.h < cur_state.f_y - cur_state.f_y))
                ++cur_state.f_c;
            break;
        case 7:
            init_h = 1;
            cur_state.h = cur_state.f_y;
            break;
        case 8:
            if (!(cur_state.f_y > 7))
                ++cur_state.f_c;
            break;
        case 9:
            init_h = 1;
            cur_state.h = cur_state.f_y + cur_state.f_y;
            ++cur_state.f_c;
            break;
        case 10:
            init_h = 1;
            cur_state.h = cur_state.f_x;
            break;
        default:
            break;
    }
    return 0;
}

// emulator of function g
int execute_g(void)
{
    switch(cur_state.g_c)
    {
        case 0:
            init_g_x = init_g_y = 1;
            cur_state.g_x = cur_state.g_y = 0;
            break;
        case 1:
            init_g_x = 1;
            cur_state.g_x = 6;
            break;
        case 2:
            init_g_y = 1;
            cur_state.g_y = 3;
            break;
        case 3:
            init_h = 1;
            cur_state.h = 1;
            break;
        case 4:
            init_g_x = 1;
            cur_state.g_x = 9;
            break;
        case 5:
            if (!(cur_state.h > cur_state.g_x + cur_state.g_y))
                ++cur_state.g_c;
            break;
        case 6:
            init_h = 1;
            cur_state.h = 4;
            break;
        case 7:
            if (!(cur_state.h > 5))
                ++cur_state.g_c;
            break;
        case 8:
            init_h = 1;
            cur_state.h = 3;
            break;
        case 9:
            init_g_y = 1;
            cur_state.g_y = 0;
            break;
        default:
            break;
    }
    return 0;
}

int check_correct_seq(const int sequence) {
    int seq = sequence, n_0 = 0, n_1 = 0;
    int i;
    for (i = 11 + 12; i > 0; seq >>= 2, --i)
        seq % 2 == 1 ? ++n_1 : ++n_0;
    return n_0 == 11 && n_1 == 12;
}

// compute and save all achievable states in array
// return 0, if OK
int compute_states(const int f_a, const int f_b,
                   const int g_a, const int g_b) {
    int first_situation = 0;    //  000 0000 0000 1111 1111 1111
    int last_situation = 0;  //  111 1111 1111 1000 0000 0000
    int i = 0;
    for (; i < G_NUMBER_STRINGS; ++i)
        first_situation |= (1 << i);
    last_situation |= (first_situation << F_NUMBER_STRINGS);
    // first_situation  ==  000 0000 0000 1111 1111 1111
    // last_situation   ==  111 1111 1111 1000 0000 0000

    // generate all situations
    for (i = first_situation; i <= last_situation; ++i)
    {
//        printf("%o\n", i);
        if (!check_correct_seq(i))
            // incorrect sequence (wrong number of "1" or "0")
            continue;
        // init starting state, when program is starting
        int command_seq = i;
        cur_state.f_c = cur_state.g_c = 0;
        cur_state.f_a = f_a;
        cur_state.f_b = f_b;
        cur_state.g_a = g_a;
        cur_state.g_b = g_b;
        // execute program according to chosen sequence of operator
        int j;
        for (j = F_NUMBER_STRINGS + G_NUMBER_STRINGS;
             j > 0; command_seq >>= 1, --j)
        {
            if (push() != 0)
                return -1;
            int operator = command_seq % 2;
            // execute operator in chosen function
            // according to command_seq
            switch (operator)
            {
                case 0:
                    if (execute_f() != 0)
                        return 1;
                    ++cur_state.f_c;
                    break;
                case 1:
                    if (execute_g() != 0)
                        return 2;
                    ++cur_state.g_c;
                    break;
                default:
                    return 3;
            }
        }
    }
    return 0;
}

// print help for user
// return 0, if OK
int help_user(void)
{
    if (!printf("Hello! This program compute set of state program \"task.txt\"\n"))
        return -1;
    if (!printf("Using: <name_program> <f_a> <f_b> <g_a> <g_b> [-count] [-file <filename]\n"))
        return -1;
    if (!printf("Author: Romanov Andrey, 421 group.\n"))
        return -1;
    if (!printf("2015 year.\n"))
        return -1;
    return 0;
}

int main(int argc, char *argv[]) {
    int f_a, f_b, g_a, g_b;
    FILE * out_stream = stdout;
    const char * filename = "";
    int print_count = 0;

    // parse basic incoming parameters
    if (argc < 5)
        return help_user();
    if (!sscanf(argv[1], "%d", &f_a))
        return 1;
    if (!sscanf(argv[2], "%d", &f_b))
        return 2;
    if (!sscanf(argv[3], "%d", &g_a))
        return 3;
    if (!sscanf(argv[4], "%d", &g_b))
        return 4;

    int i;
    // parse extra incoming parameters
    for (i = 5; i < argc; ++i) {
        if (strcmp(argv[i], "-count") == 0)
            print_count = 1;
        else if (strcmp(argv[i], "-file") == 0) {
            if (++i >= argc)
                return help_user();
            filename = argv[i];
        } else
            return help_user();
    }
    // open file if parameter "-file" was appeared
    if (strcmp(filename, "") != 0) {
        out_stream = fopen(filename, "w");
        if (out_stream == NULL)
            return 5;
    }

    // compute all states
    if (compute_states(f_a, f_b, g_a, g_b) == 0) {
        // print names of variables
        if (fprintf(out_stream, "c_f\tc_g\th\tf.x\tf.y\tg.x\tg.y\n") < 7)
            return 6;
        // print all states to stream
        for (i = 0; i < arr_size; ++i) {
            if (print_to_stream(out_stream, array +i) != 0)
                return 3;
        }
        // print count of states
        if (print_count)
            printf("%lu\n", arr_size);
    }
    // clear memory
    if (array != NULL)
        free(array);
    // close file, if file was opened
    if (strcmp(filename, "") != 0)
        if (fclose(out_stream) != 0)
            return 7;
    return 0;
}
