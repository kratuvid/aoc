#include "utils.h"

/* Strings */

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

typedef struct {
  char** strs;
  void* next;
} _si_alloc_node_t;

static struct {
  _si_alloc_node_t *head, *tail;
} _si_alloc_list = {};

static bool _si_exit_cb_registered = false;
static void _split_inplace_exit_cb() {
  _si_alloc_node_t* current = _si_alloc_list.head;
  while (current) {
    _si_alloc_node_t* save_next = current->next;
    FREE_AND_NULLIFY(current->strs, free);
    FREE_AND_NULLIFY(current, free);
    current = save_next;
  }
}

split_t split_inplace(char* str, typeof(int(int))* predicate, bool discard_empty) {
  if (!_si_exit_cb_registered
      && (_si_exit_cb_registered = true)
      && atexit(_split_inplace_exit_cb) != 0)
    ERROR_QUIT("split_inplace: atexit registration failed");

  size_t length = 0;
  char *begin = str, *at = str - 1;

  _si_alloc_node_t* node;
  if (!(node = malloc(sizeof(_si_alloc_node_t))))
    ERROR_EXPL_QUIT("split_inplace: couldn't allocate a new node");
  memset(node, 0, sizeof(_si_alloc_node_t));

  if (_si_alloc_list.tail) _si_alloc_list.tail->next = node;
  _si_alloc_list.tail = node;
  if (!_si_alloc_list.head) _si_alloc_list.head = node;

  do {
    at++;
    const char at_c = *at;

    if (predicate(at_c) || at_c == '\0') {
      if (!(at == begin && discard_empty)) {
	length++;

	const size_t new_size = sizeof(void*) * length;
	if (!(node->strs = realloc(node->strs, new_size)))
	  ERROR_EXPL_QUIT("split_inplace: couldn't reallocate %zu bytes", new_size);

	node->strs[length-1] = begin;
      }

      *at = '\0';
      begin = at + 1;
    }

    if (at_c == '\0') break;
  } while (true);

  const size_t new_size = sizeof(void*) * (length + 1);
  if (!(node->strs = realloc(node->strs, new_size)))
    ERROR_EXPL_QUIT("split_inplace: couldn't reallocate %zu bytes for the null terminator", new_size);
  node->strs[length] = nullptr;

  split_t product = {
    .strs = node->strs,
    .length = length
  };
  return product;
}

static char _general_predicate_ref = '\0';
static int _general_predicate(int ch) {
  return ch == (int)_general_predicate_ref;
}

split_t split_inplace_c(char* str, char ch, bool discard_empty) {
  _general_predicate_ref = ch;
  return split_inplace(str, _general_predicate, discard_empty);
}


/* Files */

typedef struct {
  FILE* file;
  char* input;
} _input_alloc_t;

static _input_alloc_t _gi_alloc = {};
static void _get_input_exit_cb() {
  FREE_AND_NULLIFY(_gi_alloc.input, free);
  FREE_AND_NULLIFY(_gi_alloc.file, fclose);
}

static bool _get_input_is_used = false;
input_t get_input(const char* filename) {
  if (_get_input_is_used)
    ERROR_QUIT("get_input: you can't use this function twice");
  _get_input_is_used = true;
  
  if (atexit(_get_input_exit_cb) != 0)
    ERROR_QUIT("get_input: atexit registration failed");

  if (!(_gi_alloc.file = fopen(filename, "rb")))
    ERROR_EXPL_QUIT("get_input: couldn't open input file %s", filename);

  const int fd = fileno(_gi_alloc.file);
  if (fd == -1)
    ERROR_EXPL_QUIT("get_input: couldn't get the file descriptor associated with %s", filename);

  struct stat stat = {};
  if (fstat(fd, &stat) == -1)
    ERROR_EXPL_QUIT("get_input: couldn't stat %s", filename);

  if (!(_gi_alloc.input = malloc(stat.st_size + 1)))
    ERROR_EXPL_QUIT("get_input: couldn't allocate a buffer of size %ld when processing %s", stat.st_size + 1, filename);
  _gi_alloc.input[stat.st_size] = '\0';

  size_t fread_size = 0;
  if ((fread_size = fread(_gi_alloc.input, 1, stat.st_size, _gi_alloc.file)) != (size_t)stat.st_size)
    ERROR_EXPL_QUIT("get_input: could only read %zu/%ld bytes when processing %s", fread_size, stat.st_size, filename);
  FREE_AND_NULLIFY(_gi_alloc.file, fclose);

  input_t product = {
    .str = _gi_alloc.input,
    .size = stat.st_size
  };
  return product;
}
