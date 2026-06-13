#include "allocator/memory_resource.h"

#include <new>
#include <cstdlib>
#include <mutex>

namespace allocator {

namespace {
std::mutex alloc_mutex;
}

CustomMemoryResource::CustomMemoryResource() noexcept = default;
CustomMemoryResource::~CustomMemoryResource() = default;

void* CustomMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
	std::lock_guard<std::mutex> lk(alloc_mutex);
	void* p = nullptr;
#if defined(_MSC_VER)
	p = _aligned_malloc(bytes, alignment);
	if(!p) throw std::bad_alloc();
#else
	if(posix_memalign(&p, alignment, bytes) != 0) p = nullptr;
	if(!p) throw std::bad_alloc();
#endif
	return p;
}

void CustomMemoryResource::do_deallocate(void* p, std::size_t, std::size_t) {
	std::lock_guard<std::mutex> lk(alloc_mutex);
#if defined(_MSC_VER)
	_aligned_free(p);
#else
	free(p);
#endif
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
	return this == &other;
}

} // namespace allocator
