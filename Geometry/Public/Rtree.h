#pragma once

#include <cassert>
#include <memory>

#include "Geometry/Public/Box.h"
#include "Geometry/Public/InsertVisitor.h"
#include "Geometry/Public/Indexable.h"
#include "Geometry/Public/Node.h"
#include "Geometry/Public/Traits.h"
#include "Geometry/Public/Translator.h"

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

template <typename Value,
		  size_t MaxElements,
		  size_t MinElements = Detail::DefaultMinElements<MaxElements>::value>
class Rtree {
	static_assert(0 < MinElements && 2 * MinElements <= MaxElements + 1, "Invalid min max parameters");

public:
	using Indexable = Indexable<Value>;

	using IndexableType = typename Detail::IndexableType<Detail::Translator<Indexable>>::Type;
	using BoxType = Box<Point<typename Traits::Cooridnate<IndexableType>::Type, Traits::Dimension<IndexableType>::value>>;

private:
	using TranslatorType = Detail::Translator<Indexable>;
	using InternalNode = Detail::InternalNode<BoxType>;
	using Leaf = Detail::Leaf<Value>;

public:		
	void Insert (const Value& value) {
		if (root_ == nullptr) {
			RawCreate();
		}

		RawInsert(value);
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

		InsertVisitor<Value, MinElements, MaxElements, TranslatorType, BoxType> 
			insert_visitor(*root_, value, depth_, 0 /* relative_level */, translator_);
		insert_visitor(*root_);

		++values_count_;
	}

	TranslatorType translator_;
	std::unique_ptr<Leaf> root_;
	size_t values_count_ = 0;
	size_t depth_ = 0;
};

} // namespace Index
} // namespace Geometry
