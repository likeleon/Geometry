#pragma once

#include <cstddef>

namespace Detail {

template <std::size_t DimensionCount, std::size_t Index>
struct ArrayAssign {
    template <typename T>
    static void Apply(T values[], const T& value) {
        values[Index] = value;
    }
};

template <>
struct ArrayAssign<2, 2> {
    template <typename T>
    static void Apply(T[], const T&) {
    }
};

template <>
struct ArrayAssign<1, 1> {
    template <typename T>
    static void Apply(T[], const T&) {
    }
};

template <>
struct ArrayAssign<1, 2> {
    template <typename T>
    static void Apply(T[], const T&) {
    }
};

}

template <typename CoordinateType, std::size_t DimensionCount, typename CoordinateSystem>
class Point {
    static_assert(DimensionCount >= 1, "Dimension greater than zero expected");

public:
    Point () = default;

    explicit Point (const CoordinateType& v0) {
        Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
        Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, CoordinateType());
        Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, CoordinateType());
    }

    explicit Point (const CoordinateType& v0, const CoordinateType& v1) {
        Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
        Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, v1);
        Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, CoordinateType());
    }

    explicit Point (const CoordinateType& v0, const CoordinateType& v1, const CoordinateType& v2) {
        Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
        Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, v1);
        Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, v2);
    }

    template <std::size_t K>
    const CoordinateType& Get () const {
        static_assert(K < DimensionCount);
        return values[K];
    }

    template <std::size_t K>
    void Set (const CoordinateType& value) {
        static_assert(K < DimensionCount);
        values[K] = value;
    }

private:
    CoordinateType values_[DimensionCount];
};
