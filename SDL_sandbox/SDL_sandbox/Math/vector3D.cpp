#include "vector3D.h"

tVector3D::tVector3D():
m_x(0),
m_y(0),
m_z(0)
{
}

tVector3D::tVector3D(float vx, float vy, float vz)
{
	m_x = vx;
	m_y = vy;
	m_z = vz;
}

tVector3D::tVector3D(const tVector3D& v)
{
    m_x = v.m_x;
    m_y = v.m_y;
    m_z = v.m_z;
}

tVector3D tVector3D::operator * (float mult) const
{
	return tVector3D(m_x * mult, m_y * mult, m_z * mult);
}

tVector3D tVector3D::operator + (const tVector3D& v) const
{
	return tVector3D(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}

tVector3D tVector3D::operator - (const tVector3D& v) const
{
	return tVector3D(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
}