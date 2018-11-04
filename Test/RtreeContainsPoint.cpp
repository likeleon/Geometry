#include "stdafx.h"
#include <cassert>
#include "Geometry/Public/Rtree.h"
#include "Math/Vec3.h"

void TestOne () {
    Geometry::Index::Rtree<4> rtree;
    rtree.Insert({ 0, 0, 0 });
    rtree.Insert({ 1, 1, 0 });
    rtree.Insert({ 2, 2, 0 });
    rtree.Insert({ 3, 3, 0 });
    rtree.Insert({ 4, 4, 0 });
    rtree.Insert({ 4, 3, 0 });
    rtree.Insert({ 0, 3, 0 });

    /*for (typename Rtree::const_iterator it = rtree.begin(); it != rtree.end(); ++it) {
        std::vector<Pt> result;
        rtree.Query(Geometry::Index::Contains(*it), std::back_inserter(result));
        assert(result.size() == 1);
    }*/
}

void TestRtreeContainsPoint () {
    TestOne();
}