add_library(custom_allocator STATIC
	allocator_resource.cpp
)

target_include_directories(custom_allocator
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_compile_features(custom_allocator PUBLIC cxx_std_23)

target_enable_all_warnings(custom_allocator)

if(MSVC)
  target_compile_definitions(custom_allocator PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()


set_target_properties(custom_allocator PROPERTIES
	EXPORT_NAME custom_allocator
)
