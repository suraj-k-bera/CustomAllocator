#pragma once

#include "memory_resource.h"
#include <memory_resource>

namespace allocator {

template <typename T>
class polymorphic_allocator {
public:
	using value_type = T;

	polymorphic_allocator(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) noexcept
		: resource_(mr) {}

	template <class U>
	polymorphic_allocator(const polymorphic_allocator<U>& other) noexcept
		: resource_(other.resource_) {}

	T* allocate(std::size_t n) {
		return static_cast<T*>(resource_->allocate(n * sizeof(T), alignof(T)));
	}

	void deallocate(T* p, std::size_t n) noexcept {
		resource_->deallocate(p, n * sizeof(T), alignof(T));
	}

	std::pmr::memory_resource* resource_;
};

} // namespace allocator
