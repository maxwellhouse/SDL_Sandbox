#ifndef VECTOR3D_H
#define VECTOR3D_H
/// Minimal 3-dimensional vector abstraction
class tVector3D
{
public:

    // Constructors
    tVector3D();

	tVector3D(float vx, float vy, float vz);

	tVector3D(const tVector3D& v);

	// Destructor
	~tVector3D() {}

	// A minimal set of vector operations
	tVector3D operator * (float mult) const; // result = this * arg

	tVector3D operator + (const tVector3D& v) const; // result = this + arg

	tVector3D operator - (const tVector3D& v) const; // result = this - arg

	float m_x;
    float m_y;
    float m_z;
};


#endif // VECTOR3D_H