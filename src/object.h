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

#ifndef OBJECT_H
#define OBJECT_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#define obj_args_a va_list *args

typedef void obj_t;

typedef struct obj_aspect_s {
  const char *(*_type_)();
  size_t (*_size_)();
  obj_t *(*alloc)(void *unused, ...);
  void (*_dealloc_)(obj_t *self);
  obj_t *(*_copy_)(obj_t *self);
  void (*_show_)(obj_t *self);
  bool (*_equal_)(obj_t *self, obj_t *other);
} obj_aspect_t;

typedef struct obj_header_s {
  obj_aspect_t *_aspect_;
} obj_header_t;

#define obj_header(type) obj_t *obj_##type##_alloc(void *unused, ...);

#define obj_source(type, _alloc_func_, _dealloc_func_, _copy_func_,            \
                   _show_func_, _equal_func_)                                  \
  static const char *_obj_##type##_type_();                                    \
  static size_t _obj_##type##_size_();                                         \
  static void _obj_##type##_dealloc_(obj_t *self);                             \
  static obj_t *_obj_##type##_copy_(obj_t *self);                              \
  static void _obj_##type##_show_(obj_t *self);                                \
  static bool _obj_##type##_equal_(obj_t *self, obj_t *other);                 \
                                                                               \
  static obj_aspect_t _obj_##type##_aspect_ = {                                \
      ._type_ = _obj_##type##_type_,                                           \
      ._size_ = _obj_##type##_size_,                                           \
      .alloc = obj_##type##_alloc,                                             \
      ._dealloc_ = _obj_##type##_dealloc_,                                     \
      ._copy_ = _obj_##type##_copy_,                                           \
      ._show_ = _obj_##type##_show_,                                           \
      ._equal_ = _obj_##type##_equal_};                                        \
                                                                               \
  static const char *_obj_##type##_type_() { return #type; }                   \
                                                                               \
  static size_t _obj_##type##_size_() { return sizeof(type); }                 \
                                                                               \
  obj_t *obj_##type##_alloc(void *unused, ...) {                               \
    obj_header_t *header = calloc(1, sizeof(obj_header_t) + sizeof(type));     \
    header->_aspect_ = (&_obj_##type##_aspect_);                               \
    obj_t *body = ((void *)header) + sizeof(obj_header_t);                     \
    va_list args;                                                              \
    va_start(args, unused);                                                    \
    _alloc_func_((type *)body, &args);                                         \
    va_end(args);                                                              \
    return body;                                                               \
  }                                                                            \
                                                                               \
  static void _obj_##type##_dealloc_(obj_t *self) {                            \
    obj_header_t *header = obj_get_header(self);                               \
    _dealloc_func_((type *)self);                                              \
    free(header);                                                              \
  }                                                                            \
                                                                               \
  static obj_t *_obj_##type##_copy_(obj_t *self) {                             \
    obj_header_t *header = calloc(1, sizeof(obj_header_t) + sizeof(type));     \
    header->_aspect_ = &_obj_##type##_aspect_;                                 \
    obj_t *copy = ((void *)header) + sizeof(obj_header_t);                     \
    _copy_func_((type *)self, (type *)copy);                                   \
    return copy;                                                               \
  }                                                                            \
                                                                               \
  static void _obj_##type##_show_(obj_t *self) { _show_func_((type *)self); }  \
                                                                               \
  static bool _obj_##type##_equal_(obj_t *self, obj_t *other) {                \
    return _equal_func_((type *)self, (type *)other);                          \
  }

#define obj_get_header(self)                                                   \
  ((obj_header_t *)(((obj_t *)self) - sizeof(obj_header_t)))

#define obj_next_arg(type) va_arg(*args, type)

#define obj_alloc(type, ...)                                                   \
  ((type *)obj_##type##_alloc(NULL, ##__VA_ARGS__, NULL))

#define obj_cast(type, self) ((type *)self)

#define obj_typify(type, name, self) type *name = obj_cast(type, self)

#define obj_dealloc(self) obj_get_header(self)->_aspect_->_dealloc_(self)

#define obj_copy(self) obj_get_header(self)->_aspect_->_copy_(self)

#define obj_from(self, ...)                                                    \
  obj_get_header(self)->_aspect_->alloc(NULL, ##__VA_ARGS__, NULL)

#define obj_show(self) obj_get_header(self)->_aspect_->_show_(self)

#define obj_equal(self, other)                                                 \
  obj_get_header(self)->_aspect_->_equal_(self, other)

#define obj_type(self) obj_get_header(self)->_aspect_->_type_()

#define obj_size(self) obj_get_header(self)->_aspect_->_size_()

#endif
