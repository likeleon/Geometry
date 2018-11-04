#pragma once

#include <cassert>
#include <memory>
#include <utility>

#include "Geometry/Public/Box.h"
#include "Geometry/Public/InsertVisitor.h"
#include "Geometry/Public/Node.h"
#include "Math/Vec3.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <size_t MaxElements>
struct DefaultMinElements {
	static const size_t raw_value = (MaxElements * 3) / 10;
	static const size_t value = 1 <= raw_value ? raw_value : 1;
};

template <size_t MaxElements>
struct DefaultRstarReinsertedElements {
	static const size_t value = (MaxElements * 3) / 10;
};

} // namespace Detail

struct NoProperty {
};

template <
	size_t MaxElements, 
	size_t MinElements = Detail::DefaultMinElements<MaxElements>::value,
	typename Property = NoProperty
>
class Rtree {
	static_assert(0 < MinElements && 2 * MinElements <= MaxElements + 1, "Invalid min max parameters");
	
	using Value = std::pair<Math::Vec3, Property>;
	using Leaf = Detail::Leaf<Property>;

public:
	void Insert (const Math::Vec3& point, const Property& property = NoProperty()) {
		if (root_ == nullptr) {
			RawCreate();
		}

		RawInsert(std::make_pair(point, property));
	}

	size_t size () const {
		return values_count_;
	}

	bool empty () const {
		return values_count_ == 0;
	}

	size_t depth () const {
		return depth_;
	}

private:
	void RawCreate () {
		root_ = std::make_unique<Leaf>();
		values_count_ = 0;
		depth_ = 0;
	}

	void RawInsert (const Value& value) {
		assert(root_ != nullptr && "The root must exist");

		InsertVisitor<Value, Value, MinElements, MaxElements> insert_visitor(*root_, value, depth_, 0 /* relative_level */);
		insert_visitor(*root_);

		++values_count_;
	}

	std::unique_ptr<Leaf> root_;
	size_t values_count_ = 0;
	size_t depth_ = 0;
};

} // namespace Index
} // namespace Geometry
