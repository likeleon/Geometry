#include "stdafx.h"
#include <cassert>
#include "Test/Cs.h"
#include "Geometry/Public/Point.h"
#include "Geometry/Public/Rtree.h"

void TestOne () {
    using Pt = Geometry::Index::Point<double, 2>;
    using Rtree = Geometry::Index::Rtree<Pt, 16>;

    Rtree rtree;
    rtree.Insert(Pt(0, 0));
    rtree.Insert(Pt(1, 1));
    rtree.Insert(Pt(2, 2));
    rtree.Insert(Pt(3, 3));
    rtree.Insert(Pt(4, 4));
    rtree.Insert(Pt(4, 3));
    rtree.Insert(Pt(0, 3));

    /*for (typename Rtree::const_iterator it = rtree.begin(); it != rtree.end(); ++it) {
        std::vector<Pt> result;
        rtree.Query(Geometry::Index::Contains(*it), std::back_inserter(result));
        assert(result.size() == 1);
    }*/
}

void TestRtreeContainsPoint () {
    TestOne();
}