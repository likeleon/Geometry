#include "stdafx.h"
#include <cassert>
#include "Point.h"

template <typename Params>
void TestOne () {
    using Pt = Geometry::Model::Point<double, 2, Geometry::Cs::Cartesian>;
    using Rtree = Geometry::Index::Rtree<Pt, Params>;

    Rtree rtree;
    rtree.insert(Pt(0, 0));
    rtree.insert(Pt(1, 1));
    rtree.insert(Pt(2, 2));
    rtree.insert(Pt(3, 3));
    rtree.insert(Pt(4, 4));
    rtree.insert(Pt(4, 3));
    rtree.insert(Pt(0, 3));

    for (typename Rtree::const_iterator it = rtree.begin(); it != rtree.end(); ++it) {
        std::vector<Pt> result;
        rtree.Query(Geometry::Index::Contains(*it), std::back_inserter(result));
        assert(result.size() == 1);
    }
}

void TestRtreeContainsPoint () {
    TestOne<Geometry::Index::Linear<4>>();
    TestOne<Geometry::Index::Quadratic<4>>();
    TestOne<Geometry::Index::Rstar<4>>();
}