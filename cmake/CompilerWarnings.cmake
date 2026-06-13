function(target_enable_all_warnings target)
  if(MSVC)
	target_compile_options(${target} PRIVATE /W4 /permissive-)
	# Treat warnings as errors optionally
	target_compile_options(${target} PRIVATE /WX)
  else()
	# GCC/Clang
	target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow)
	# Treat warnings as errors if supported
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-Werror" COMPILER_SUPPORTS_WERROR)
	if(COMPILER_SUPPORTS_WERROR)
	  target_compile_options(${target} PRIVATE -Werror)
	endif()
  endif()
endfunction()
