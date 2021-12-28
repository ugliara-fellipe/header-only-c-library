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

#include <assert.h>

#include "message.h"

int main() {
  msg_info("message 1 %d\n", 10);
  msg_crash("message 2 %d\n", 20);
  msg_error("message 3 %d\n", 30);
  msg_warning("message 4 %d\n", 40);
}