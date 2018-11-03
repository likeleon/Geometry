#pragma once

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Indexable>
class Translator : public Indexable {
public:
	using ResultType = typename Indexable::ResultType;

	template <typename Value>
	ResultType operator() (const Value& value) const {
		return Indexable::operator()(value);
	}
};

template <typename Translator>
struct ResultType {
	using Type = typename Translator::ResultType;
};

template <typename Translator>
struct IndexableType {
	using Type = std::remove_cv_t<std::remove_reference_t<typename ResultType<Translator>::Type>>;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry
