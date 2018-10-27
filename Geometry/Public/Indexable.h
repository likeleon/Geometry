#pragma once

#include <utility>

#include "Geometry/Public/IsIndexable.h"

namespace Geometry {
namespace Index {

template <typename Value, bool IsIndexable = Detail::IsIndexable<Value>::Value>
class Indexable {
	static_assert(Detail::IsIndexable<Value>::Value, "Not a valid indexable type");

public:
	using ResultType = const Value&;

	ResultType operator() (const Value& value) const {
		return value;
	}
};

template <typename IndexableType, typename T>
class Indexable<std::pair<IndexableType, T>, false> {
	static_assert(Detail::IsIndexable<IndexableType>::Value, "Not a valid indexable type");

public:
	using ResultType = const IndexableType&;

	ResultType operator() (const std::pair<IndexableType, T>& value) const {
		return value.first;
	}
};

} // namespace Index
} // namespace Geometry