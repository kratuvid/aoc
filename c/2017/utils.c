#include "utils.h"

void trim_left(char** p_str, size_t* p_size, typeof(int(int)) *predicate) {
  char* str = *p_str;                        // inclusive
  const char* const end = *p_str + *p_size;  // exclusive

  while (str < end && predicate(*str)) {
    str++;
  }

  *p_str = str;
  *p_size = end - str;
}

void trim_right(char** p_str, size_t* p_size, typeof(int(int)) *predicate) {
  char* end = *p_str + *p_size - 1;  // inclusive
  const char* const str = *p_str;    // inclusive

  while (end >= str && predicate(*end)) {
    end--;
  }

  end++; // now exclusive
  *end = '\0';
  *p_size = end - str;
}

void trim(char** p_str, size_t* p_size, typeof(int(int)) *predicate) {
  trim_left(p_str, p_size, predicate);
  trim_right(p_str, p_size, predicate);
}

static _input_allocs_t _get_input_allocs = {};
static void _get_input_exit_callback() {
  FREE_AND_NULLIFY(_get_input_allocs.input, free);
  FREE_AND_NULLIFY(_get_input_allocs.file, fclose);
}

static bool _get_input_is_used = false;
input_t get_input(const char* filename) {
  if (_get_input_is_used)
    ERROR_QUIT("get_input: you can't use this function twice");
  _get_input_is_used = true;
  
  if (atexit(_get_input_exit_callback) != 0)
    ERROR_QUIT("get_input: atexit registration failed");

  if (!(_get_input_allocs.file = fopen(filename, "rb")))
    ERROR_EXPL_QUIT("get_input: couldn't open input file %s", filename);

  const int fd = fileno(_get_input_allocs.file);
  if (fd == -1)
    ERROR_EXPL_QUIT("get_input: couldn't get the file descriptor associated with %s", filename);

  struct stat stat = {};
  if (fstat(fd, &stat) == -1)
    ERROR_EXPL_QUIT("get_input: couldn't stat %s", filename);

  if (!(_get_input_allocs.input = malloc(stat.st_size + 1)))
    ERROR_EXPL_QUIT("get_input: couldn't allocate a buffer of size %ld when processing %s", stat.st_size + 1, filename);
  _get_input_allocs.input[stat.st_size] = '\0';

  size_t fread_size = 0;
  if ((fread_size = fread(_get_input_allocs.input, 1, stat.st_size, _get_input_allocs.file)) != (size_t)stat.st_size)
    ERROR_EXPL_QUIT("get_input: could only read %zu/%ld bytes when processing %s", fread_size, stat.st_size, filename);
  FREE_AND_NULLIFY(_get_input_allocs.file, fclose);

  input_t product = {
    .str = _get_input_allocs.input,
    .size = stat.st_size
  };
  return product;
}
