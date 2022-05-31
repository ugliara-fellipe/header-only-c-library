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

#include "exception.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enable_exceptions;

int main() {
  int i = 11;

  try(
    raise(i - 10); 
  ) catch (exception < 5,
    i++;
    retry;
  ) catch (exception,
    assert(exception == 5); 
  ) finally();

  i = 15;
  try( 
    retry; 
  ) catch (exception == RETRY_EXCEPTION,
    if (i < 16) {
      assert(i == 15);
      i = 16;
      retry;
    }
    assert(i == 16);
  ) finally();

  raise(1);

  return EXIT_SUCCESS;
}
