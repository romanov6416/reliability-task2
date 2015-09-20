//
// Created by andrey on 19.09.15.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum PARSE_CODE {
    SUCCESS = 0,
    MALLOC_FAIL = -1,
    FAIL_PARSE = 1
};

const char * VOID_WORD = "void";
const char * INT_WORD = "int";

const char LEFT_BRACE = '{';
const char RIGHT_BRACE = '}';
const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';
const char SEMICOLON = ';';
const char COMMA = ',';

const char * LEFT_BRACE_STR = "{";
const char * RIGHT_BRACE_STR = "}";
const char * LEFT_BRACKET_STR = "(";
const char * RIGHT_BRACKET_STR = ")";
const char * SEMICOLON_STR = ";";
const char * COMMA_STR = ",";

const char * cur_word = NULL;
FILE * stream = NULL;

int extend_capacity(void * data, size_t * capacity)
{
    const size_t INIT_CAPACITY = 8;
    // extend capacity of word
    if (capacity == 0)
    {
        // init capacity
        data = malloc(INIT_CAPACITY * sizeof(char));
        if (data == NULL)
            return -1;
        *capacity = INIT_CAPACITY;
    } else {
        // extend capacity
        data = realloc(data, 2 * (*capacity));
        if (data == NULL)
            return -1;
    }
}

int isseparator(int c)
{
    return isspace(c) || c == LEFT_BRACE || c == RIGHT_BRACE ||
            c == LEFT_BRACKET || c == RIGHT_BRACKET ||
            c == SEMICOLON || c == COMMA;
}

const char * getword(void)
{
    char * new_word = NULL;
    size_t capacity = 0, new_word_size = 0;
    int c = fgetc(stream);
    do
    {
        if (capacity - 1 <= new_word_size)
            if (extend_capacity(new_word, &capacity) != 0)
                return NULL;
        if (c == EOF)
            break;
        if (!isspace(c))
            new_word[new_word_size++] = (const char) c;
    } while (!isseparator(c = fgetc(stream)));
    new_word[new_word_size++] = '\0';
    return new_word;
}

enum PARSE_CODE init(const char **var_names, const char **var_values)
{
    size_t capacity = 0, var_size = 0;
    if (cur_word != NULL)
        return MALLOC_FAIL;
    if (strcmp(cur_word, INT_WORD) != 0)
        return FAIL_PARSE;
    if (!(cur_word = getword()))
        return MALLOC_FAIL;
    const char * var_name = cur_word;
    const char * var_value = "#";
    if (capacity <= var_size)
    {
        size_t names_capacity = capacity, values_capacity = capacity;
        if (extend_capacity(var_names, &names_capacity) != 0 ||
            extend_capacity(var_values, &values_capacity) != 0)
            return MALLOC_FAIL;
        capacity = names_capacity;
    }
    var_names[var_size] = var_name;
    var_values[var_size++] = var_value;
    while (!(cur_word = getword()) && strcmp(cur_word, COMMA_STR) == 0)
    {
        if (!(cur_word = getword()))
            return MALLOC_FAIL;
        var_name = cur_word;
        var_value = "#";
        if (capacity <= var_size)
        {
            size_t names_capacity = capacity, values_capacity = capacity;
            if (extend_capacity(var_names, &names_capacity) != 0 ||
                extend_capacity(var_values, &values_capacity) != 0)
                return MALLOC_FAIL;
            capacity = names_capacity;
        }
        var_names[var_size] = var_name;
        var_values[var_size++] = var_value;
    }
    if (strcmp(cur_word, SEMICOLON_STR) != 0)
        return FAIL_PARSE;
    cur_word = getword();
    return SUCCESS;
}

enum PARSE_CODE function(const char * func_name)
{
    if (cur_word == NULL)
}

int main(int argc, char **argv)
{
    return 0;
}
