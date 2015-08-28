#ifndef SPLINE_H
#define SPLINE_H

// Simple catmull rom spline stolen mostly from code project.

#include "vector3d.h"
#include <vector>

class tCRSpline
{
public:

    // Constructors and destructor
    tCRSpline();
    tCRSpline(const tCRSpline&);
    ~tCRSpline();

    // Operations
    void AddSplinePoint(const tVector3D& v);
	tVector3D GetInterpolatedSplinePoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
	int GetNumPoints();
	tVector3D& GetNthPoint(int n);

    // Static method for computing the Catmull-Rom parametric equation
    // given a time (t) and a vector quadruple (p1,p2,p3,p4).
    static tVector3D Eq(float t, const tVector3D& p1, const tVector3D& p2, const tVector3D& p3, const tVector3D& p4);

private:
    std::vector<tVector3D> m_VectorPoints;
    float m_Delta_t;
};

#endif // SPLINE_H