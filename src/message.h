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
