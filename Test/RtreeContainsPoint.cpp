#include "stdafx.h"
#include <cassert>
#include "Test/Point.h"
#include "Test/Cs.h"
#include "Geometry/Public/Rtree.h"

void TestOne () {
    using Pt = Point<double, 2, Cartesian>;
    using Rtree = Geometry::Index::Rtree<Pt>;

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
    TestOne();
}