/*
no-way-c is a library that improves C17 standard library
Copyright (C) 2021  Fellipe Augusto Ugliara

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>

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

static void test_obj_show(test_obj_t *self) { printf("%d\n", self->i); }

static bool test_obj_equal(test_obj_t *self, test_obj_t *other) {}

obj_source(test_obj_t, test_obj_alloc, test_obj_dealloc, test_obj_copy,
           test_obj_show, test_obj_equal);

void test_obj_print(test_obj_t *self) { printf("%d\n", self->i); }

int main() {
  test_obj_t *obj = obj_alloc(test_obj_t, 34);
  obj_show(obj);
  test_obj_print(obj);
  printf("%ld\n", obj_size(obj));
  obj_dealloc(obj);
  return EXIT_SUCCESS;
}
