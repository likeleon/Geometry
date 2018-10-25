﻿#pragma once

#include <cassert>
#include <memory>
#include "Node.h"

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
          size_t MinElements = Detail::DefaultMinElements<MaxElements>::value,
          size_t ReinsertedElements = Detail::DefaultRstarReinsertedElements<MaxElements>::value,
          size_t OverlapCostThreshold = 32>
class Rtree {
    static_assert(0 < MinElements && 2 * MinElements <= MaxElements + 1, "Invalid min max parameters");

public:
    void Insert (const Value& value) {
        if (root == nullptr) {
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

private:
    void RawCreate () {
        root = std::make_unique<Leaf>();
    }

    void RawInsert (const Value& value) {
        assert(root != nullptr && "The root must exist");

        // TODO

        ++values_count_;
    }

    std::unique_ptr<Leaf> root;
    std::size_t values_count_ = 0;
};

} // namespace Index
} // namespace Geometry
