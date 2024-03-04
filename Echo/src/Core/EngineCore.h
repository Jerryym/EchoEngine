#pragma once
#if ECHO_DYNAMIC_LINK
	#ifdef ECHO_BUILD_DLL
		#define ECHO_API __declspec(dllexport)
	#else
		#define ECHO_API __declspec(dllimport)
	#endif // ECHO_BUILD_DLL
#elif ECHO_STATIC_LINK
	#define ECHO_API
#endif // ECHO_DYNAMIC_LINK

#ifdef ECHO_ENABLE_ASSERTS
	#define ECHO_ASSERT(X, ...) { if(!(x)) { ECHO_ERROR("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
	#define ECHO_CORE_ASSERT(X, ...) { if(!(x)) { ECHO_CORE_ASSERT("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
#else
	#define ECHO_ASSERT(X, ...)
	#define ECHO_CORE_ASSERT(X, ...) 
#endif // ECHO_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define BIND_EVENT(x)	 std::bind(&x, this, std::placeholders::_1)
