/*
MIT License

Copyright (c) 2021 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <assert.h>

#include "object.h"

typedef struct test_obj_s {
  int i;
} test_obj_t;

obj_header(test_obj_t);

static void test_obj_alloc(test_obj_t *self, obj_args_a) {
  self->i = obj_next_arg(int);
}

static void test_obj_dealloc(test_obj_t *self) {}

static void test_obj_copy(test_obj_t *self, test_obj_t *copy) {}

static void test_obj_show(test_obj_t *self) {}

static bool test_obj_equal(test_obj_t *self, test_obj_t *other) {}

obj_source(test_obj_t, test_obj_alloc, test_obj_dealloc, test_obj_copy,
           test_obj_show, test_obj_equal);

void test_obj_print(test_obj_t *self) {}

int main() {
  test_obj_t *obj = obj_alloc(test_obj_t, 34);
  obj_show(obj);
  test_obj_print(obj);
  obj_dealloc(obj);
  return EXIT_SUCCESS;
}
