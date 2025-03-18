#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define ERROR_QUIT(format, ...) { fprintf(stderr, format "\n" __VA_OPT__(,) __VA_ARGS__); exit(1); }
#define ERROR_EXPL_QUIT(format, ...) { fprintf(stderr, format ": %s" "\n", __VA_ARGS__ __VA_OPT__(,) strerror(errno)); exit(1); }
#define FREE_AND_NULLIFY(var, free_f) if (var) { free_f(var); (var) = nullptr; }

// Must be null-terminated strings
void trim_left(char** p_str, size_t* p_size, typeof(int(int)) *predicate) __attribute__((nonnull));
void trim_right(char** p_str, size_t* p_size, typeof(int(int)) *predicate) __attribute__((nonnull));
void trim(char** p_str, size_t* p_size, typeof(int(int)) *predicate) __attribute__((nonnull));

// Input
typedef struct {
  char* str;
  size_t size;
} input_t;

typedef struct {
  FILE* file;
  char* input;
} _input_allocs_t;

input_t get_input(const char* filename);
