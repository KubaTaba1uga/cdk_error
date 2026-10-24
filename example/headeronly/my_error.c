#include "my_error.h"

_Thread_local my_error_t my_errno = NULL;
_Thread_local struct my_Error my_hidden_errno = {0};
