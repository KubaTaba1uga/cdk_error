#include <my_error.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static my_error_t failing_func(int i);

int main(void) {
  char buf[1024] = {0};
  int i = 0;

  while (true) {
    my_errno = failing_func(i);
    i++;
    sleep(1);
    my_error_dumps(my_errno, sizeof(buf), buf);    
    puts(buf);
  }

  return 0;
}

static my_error_t nested_failing_func(int i) {
  my_errno = my_errnof(i, "Error number %d", i);

  return my_errno;
}

static my_error_t failing_func(int i) {
  my_errno = nested_failing_func(i);
  MY_TRY(my_errno);

  return 0;

error_out:
  return my_errno;
}
