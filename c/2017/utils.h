#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define ERROR_QUIT(format, ...) { fprintf(stderr, format "\n" __VA_OPT__(,) __VA_ARGS__); exit(1); }
#define ERROR_EXPL_QUIT(format, ...) { fprintf(stderr, format ": %s" "\n", __VA_ARGS__ __VA_OPT__(,) strerror(errno)); exit(1); }
#define FREE_AND_NULLIFY(var, free_f) if (var) { free_f(var); (var) = nullptr; }

/* Strings */
typedef struct {
  char** strs;
  size_t length;
} split_t;

// Must be null-terminated strings
void trim_left(char** p_str, size_t* p_size, typeof(int(int))* predicate);
void trim_right(char** p_str, size_t* p_size, typeof(int(int))* predicate);
void trim(char** p_str, size_t* p_size, typeof(int(int))* predicate);

split_t split_inplace(char* str, typeof(int(int))* predicate, bool discard_empty);
split_t split_inplace_c(char* str, char ch, bool discard_empty);

/* Files */
typedef struct {
  char* str;
  size_t size;
} input_t;

input_t get_input(const char* filename);
