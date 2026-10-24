#include "cdk_error.h"

_Thread_local cdk_error_t cdk_errno = NULL;
_Thread_local struct cdk_Error cdk_hidden_errno = {0};
