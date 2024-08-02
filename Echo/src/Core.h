#pragma once
#include <memory>

#ifdef ECHO_PLATFORM_WINDOWS

#else
	#error EchoEngine only supports Windows!
#endif // ECHO_PLATFORM_WINDOWS

#ifdef ECHO_ENABLE_ASSERTS
	#define ECHO_ASSERT(X, ...) { if(!(x)) { ECHO_ERROR("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
	#define ECHO_CORE_ASSERT(X, ...) { if(!(x)) { ECHO__CORE_ASSERT("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
#else
	#define ECHO_ASSERT(X, ...)
	#define ECHO_CORE_ASSERT(X, ...) 
#endif // ECHO_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define BIND_EVENT(x)	 std::bind(&x, this, std::placeholders::_1)

namespace Echo {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
