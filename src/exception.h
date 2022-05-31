/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <limits.h>
#include <setjmp.h>
#include <stdlib.h>

extern jmp_buf *_raise_env_;
extern jmp_buf *_retry_env_;

#define enable_exceptions                                                      \
  jmp_buf *_raise_env_ = NULL;                                                 \
  jmp_buf *_retry_env_ = NULL;

#define RETRY_EXCEPTION (INT_MAX - 1)

#define raise(exception)                                                       \
  do {                                                                         \
    if (_raise_env_)                                                           \
      longjmp(*_raise_env_, exception);                                        \
    else                                                                       \
      exit(exception);                                                         \
  } while (0)

#define retry                                                                  \
  do {                                                                         \
    if (_retry_env_)                                                           \
      longjmp(*_retry_env_, 1);                                                \
    else                                                                       \
      raise(RETRY_EXCEPTION);                                                  \
  } while (0)

#define try(block)                                                             \
  do {                                                                         \
    jmp_buf * _old_raise_env_ = _raise_env_;                                   \
    jmp_buf * _old_retry_env_ = _retry_env_;                                   \
    jmp_buf _catch_raise_env_;                                                 \
    const int _reraise_ = setjmp(_catch_raise_env_);                           \
                                                                               \
    if (!_reraise_) {                                                          \
      jmp_buf _try_raise_env_;                                                 \
      const int _exception_ = setjmp(_try_raise_env_);                         \
      jmp_buf _try_retry_env_;                                                 \
      const int _retry_ = setjmp(_try_retry_env_);                             \
                                                                               \
      _raise_env_ = &_try_raise_env_;                                          \
      _retry_env_ = _old_retry_env_;                                           \
      if (!_exception_ || _retry_) {                                           \
        block                                                                  \
      } else {                                                                 \
        const int exception = _exception_;                                     \
                                                                               \
        _raise_env_ = &_catch_raise_env_;                                      \
        _retry_env_ = &_try_retry_env_;

#define catch(condition, block)                                                \
        if (condition) {                                                       \
          block                                                                \
        } else

#define finally(block)                                                         \
        { raise(exception); }                                                  \
      }                                                                        \
    }                                                                          \
    _retry_env_ = _old_retry_env_;                                             \
    _raise_env_ = _old_raise_env_;                                             \
    block                                                                      \
    if (_reraise_) { raise(_reraise_); }                                       \
  } while (0)

#endif
