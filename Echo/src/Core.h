#pragma once
#include <memory>

#ifdef ECHO_BUILD_DLL
	#define ECHO_API __declspec(dllexport)
#else
	#define ECHO_API __declspec(dllimport)
#endif // ECHO_BUILD_DLL

#ifdef ECHO_ENABLE_ASSERTS
	#define ECHO_ASSERT(X, ...) { if(!(x)) { ECHO_ERROR("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
	#define ECHO_CORE_ASSERT(X, ...) { if(!(x)) { ECHO_CORE_ASSERT("Assertion Failed: {0}", _VA_ARGS_); __debugbreak(); } }
#else
	#define ECHO_ASSERT(X, ...)
	#define ECHO_CORE_ASSERT(X, ...) 
#endif // ECHO_ENABLE_ASSERTS

#define BIT(x) (1 << x)

namespace Echo {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
