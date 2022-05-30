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

#ifndef MESSAGE_H
#define MESSAGE_H

#include "terminal.h"
#include <stdio.h>
#include <string.h>

#define __FILE_NAME__                                                          \
  (strrchr(__FILE__, '/')                                                      \
       ? strrchr(__FILE__, '/') + 1                                            \
       : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))

#define MSG_TYPE_INFO term(TERM_FONT_GREEN) "info: " term(TERM_RESET)
#define MSG_TYPE_CRASH term(TERM_FONT_RED) "crash: " term(TERM_RESET)
#define MSG_TYPE_ERROR term(TERM_FONT_RED) "error: " term(TERM_RESET)
#define MSG_TYPE_WARNING term(TERM_FONT_YELLOW) "warning: " term(TERM_RESET)

#define msg(format, type, ...)                                                 \
  printf("%s:%d: " type format, __FILE_NAME__, __LINE__, __VA_ARGS__)

#define msg_info(format, ...) msg(format, MSG_TYPE_INFO, ##__VA_ARGS__)
#define msg_crash(format, ...) msg(format, MSG_TYPE_CRASH, ##__VA_ARGS__)
#define msg_error(format, ...) msg(format, MSG_TYPE_ERROR, ##__VA_ARGS__)
#define msg_warning(format, ...) msg(format, MSG_TYPE_WARNING, ##__VA_ARGS__)

#endif
