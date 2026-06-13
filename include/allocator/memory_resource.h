#pragma once

#include <memory_resource>
#include <cstddef>

namespace allocator {

class CustomMemoryResource : public std::pmr::memory_resource {
public:
	CustomMemoryResource() noexcept;
	~CustomMemoryResource() override;

protected:
	void* do_allocate(std::size_t bytes, std::size_t alignment) override;
	void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

} // namespace allocator
