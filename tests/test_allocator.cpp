#include "allocator/memory_resource.h"
#include "allocator/allocator.h"

#include <gtest/gtest.h>
#include <vector>

using namespace allocator;

TEST(AllocatorTests, AllocateDeallocate) {
	CustomMemoryResource mr;
	std::pmr::polymorphic_allocator<int> pa(&mr);

	std::pmr::vector<int> v(pa);
	v.push_back(1);
	v.push_back(2);

	EXPECT_EQ(v.size(), 2u);
}
