#include "spline.h"

tCRSpline::tCRSpline():
m_VectorPoints(), 
m_Delta_t(0)
{
}

tCRSpline::tCRSpline(const tCRSpline& s)
{
    for (int i = 0; i < (int)s.m_VectorPoints.size(); i++)
    {
        m_VectorPoints.push_back(s.m_VectorPoints[i]);
    }
    m_Delta_t = s.m_Delta_t;
}

tCRSpline::~tCRSpline()
{}

// Solve the Catmull-Rom parametric equation for a given time(t) and vector quadruple (p1,p2,p3,p4)
tVector3D tCRSpline::Eq(float t, const tVector3D& p1, const tVector3D& p2, const tVector3D& p3, const tVector3D& p4)
{
    float t2 = t * t;
    float t3 = t2 * t;

    float b1 = .5f * (  -t3 + 2*t2 - t);
    float b2 = .5f * ( 3*t3 - 5*t2 + 2);
    float b3 = .5f * (-3*t3 + 4*t2 + t);
    float b4 = .5f * (   t3 -   t2    );

    return (p1*b1 + p2*b2 + p3*b3 + p4*b4); 
}

void tCRSpline::AddSplinePoint(const tVector3D& v)
{
    m_VectorPoints.push_back(v);
    m_Delta_t = (float)1 / (float)m_VectorPoints.size();
}

tVector3D tCRSpline::GetInterpolatedSplinePoint(float t)
{
    // Find out in which interval we are on the spline
    int p = (int)(t / m_Delta_t);
    // Compute local control point indices
#define BOUNDS(pp) { if (pp < 0) pp = 0; else if (pp >= (int)m_VectorPoints.size()-1) pp = m_VectorPoints.size() - 1; }
    int p0 = p - 1;     BOUNDS(p0);
    int p1 = p;         BOUNDS(p1);
    int p2 = p + 1;     BOUNDS(p2);
    int p3 = p + 2;     BOUNDS(p3);
    // Relative (local) time 
	float lt = (t - m_Delta_t*(float)p) / m_Delta_t;
	// Interpolate
    return tCRSpline::Eq(lt, m_VectorPoints[p0], m_VectorPoints[p1], m_VectorPoints[p2], m_VectorPoints[p3]);
}

int tCRSpline::GetNumPoints()
{
	return m_VectorPoints.size();
}

tVector3D& tCRSpline::GetNthPoint(int n)
{
	return m_VectorPoints[n];
}


