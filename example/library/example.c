#include <cdk_error.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static cdk_error_t failing_func(int i);

int main(void) {
  char buf[1024] = {0};
  int i = 0;

  while (true) {
    cdk_errno = failing_func(i);
    i++;
    sleep(1);
    cdk_error_dumps(cdk_errno, sizeof(buf), buf);    
    puts(buf);
  }

  return 0;
}

static cdk_error_t nested_failing_func(int i) {
  cdk_errno = cdk_errnof(i, "Error number %d", i);

  return cdk_errno;
}

static cdk_error_t failing_func(int i) {
  cdk_errno = nested_failing_func(i);
  CDK_TRY(cdk_errno);

  return 0;

error_out:
  return cdk_errno;
}
