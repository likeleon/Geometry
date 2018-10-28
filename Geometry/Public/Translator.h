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
using ResultTypeT = typename ResultType<Translator>::Type;

template <typename Translator>
struct IndexableType {
	using Type = std::remove_cv_t<std::remove_reference_t<ResultTypeT<Translator>>>;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry
