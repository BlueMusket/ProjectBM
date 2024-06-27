#pragma once

#define DELEGATE_ARGS_COUNT 0
#define DELEGATE_ARGS
#define DELEGATE_TEMPLATE_ARGS

#include "Delegate.inl"

#undef DELEGATE_ARGS_COUNT
#undef DELEGATE_ARGS
#undef DELEGATE_TEMPLATE_ARGS

// --------------------------------------------------

#define DELEGATE_ARGS_COUNT 1
#define DELEGATE_ARGS Func func, A a
#define DELEGATE_TEMPLATE_ARGS template< typename Func, typename A>

#include "Delegate.inl"

#undef DELEGATE_ARGS_COUNT
#undef DELEGATE_ARGS
#undef DELEGATE_TEMPLATE_ARGS