#pragma once

#include "Geometry/Public/CoordinateType.h"

namespace Geometry {
namespace Index {

namespace Traits {

template <typename Geometry, std::size_t Dimension>
struct Access {
};

template <typename Geometry, std::size_t Index, std::size_t Dimension>
struct IndexedAccess {
};

} // namespace Traits

template <std::size_t Dimension, typename Geometry>
typename CoordinateType<Geometry>::Type Get (const Geometry& geometry) {
	return Traits::Access<Geometry, Dimension>::Get(geometry);
}

template <std::size_t Dimension, typename Geometry>
void Set (Geometry& geometry, const typename CoordinateType<Geometry>& value) {
	Traits::Access<Geometry, Dimension>::Set(geometry, value);
}

template <std::size_t Index, std::size_t Dimension, typename Geometry>
typename CoordinateType<Geometry>::Type Get (const Geometry& geometry) {
	return Traits::IndexedAccess<Geometry, Index, Dimension>::Get(geometry);
}

template <std::size_t Index, std::size_t Dimension, typename Geometry>
void Set (Geometry& geometry, const CoordinateType<Geometry>& value) {
	Traits::IndexedAccess<Geometry, Index, Dimension>::Set(geometry, value);
}

} // namespace Index
} // namespace Geometry