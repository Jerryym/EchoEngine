#pragma once
#if NEST_DYNAMIC_LINK
	#ifdef ECHO_BUILD_DLL
		#define NEST_API __declspec(dllexport)
	#else
		#define NEST_API __declspec(dllimport)
	#endif //NEST_DYNAMIC_LINK
#elif NEST_STATIC_LINK
	#define NEST_API
#endif // NEST_STATIC_LINK

#ifdef NEST_ENABLE_ASSERTS
	#define NEST_ASSERT(X, ...) { if(!(x)) { ECHO_ERROR("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
	#define NEST_CORE_ASSERT(X, ...) { if(!(x)) { ECHO_CORE_ASSERT("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
#else
	#define NEST_ASSERT(X, ...)
	#define NEST_CORE_ASSERT(X, ...) 
#endif // NEST_ENABLE_ASSERTS
