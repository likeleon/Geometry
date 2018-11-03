#pragma once

namespace Geometry {
namespace Index {

namespace Traits {

template <typename Geometry>
struct Tag {
	using Type = void;
};

} // namespace Traits

template <typename Geometry>
struct Tag {
	using Type = typename Traits::Tag<Geometry>::Type;
};

} // namespace Index
} // namespace Geometry