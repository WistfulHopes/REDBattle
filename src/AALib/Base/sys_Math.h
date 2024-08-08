#pragma once 
#include <cstdint>
#include <cstring>
#include <xmmintrin.h>
#include <math.h>

#define SMALL_NUMBER		(1.e-8f)
#define Z_PRECISION	0.0f

typedef __m128	VectorRegister;

#define SHUFFLEMASK(A0,A1,B2,B3) ( (A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6) )
#define VectorReplicate( Vec, ElementIndex )	_mm_shuffle_ps( Vec, Vec, SHUFFLEMASK(ElementIndex,ElementIndex,ElementIndex,ElementIndex) )
#define VectorLoadAligned( Ptr )		_mm_load_ps( (const float*)(Ptr) )
#define VectorStoreAligned( Vec, Ptr )	_mm_store_ps( (float*)(Ptr), Vec )

inline float rsqrt_fast(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;                       // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);               // what the fuck?
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));   // 1st iteration
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

inline float InvSqrt(const float F)
{
    // Performs two passes of Newton-Raphson iteration on the hardware estimate
    //    v^-0.5 = x
    // => x^2 = v^-1
    // => 1/(x^2) = v
    // => F(x) = x^-2 - v
    //    F'(x) = -2x^-3

    //    x1 = x0 - F(x0)/F'(x0)
    // => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
    // => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
    // => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
    //
    // This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
    // but retains better accuracy (namely InvSqrt(1) = 1 exactly).

    static const float fOneHalf = 0.5f;
    float X0, X1, X2, FOver2;

    X0 = rsqrt_fast(F);	// 1/sqrt estimate (12 bits)
    FOver2 = F * fOneHalf;

    // 1st Newton-Raphson iteration
    X1 = X0 * X0;
    X1 = fOneHalf - (FOver2 * X1);
    X1 = X0 + (X0 * X1);

    // 2nd Newton-Raphson iteration
    X2 = X1 * X1;
    X2 = fOneHalf - (FOver2 * X2);
    X2 = X1 + (X1 * X2);

    return X2;
}

inline VectorRegister VectorMultiply(const VectorRegister& Vec1, const VectorRegister& Vec2)
{
    return _mm_mul_ps(Vec1, Vec2);
}

inline VectorRegister VectorMultiplyAdd(const VectorRegister& Vec1, const VectorRegister& Vec2, const VectorRegister& Vec3)
{
    return _mm_add_ps(_mm_mul_ps(Vec1, Vec2), Vec3);
}

inline void VectorMatrixMultiply(void* Result, const void* Matrix1, const void* Matrix2)
{
    const VectorRegister* A = (const VectorRegister*)Matrix1;
    const VectorRegister* B = (const VectorRegister*)Matrix2;
    VectorRegister* R = (VectorRegister*)Result;
    VectorRegister Temp, R0, R1, R2;

    // First row of result (Matrix1[0] * Matrix2).
    Temp = VectorMultiply(VectorReplicate(A[0], 0), B[0]);
    Temp = VectorMultiplyAdd(VectorReplicate(A[0], 1), B[1], Temp);
    Temp = VectorMultiplyAdd(VectorReplicate(A[0], 2), B[2], Temp);
    R0 = VectorMultiplyAdd(VectorReplicate(A[0], 3), B[3], Temp);

    // Second row of result (Matrix1[1] * Matrix2).
    Temp = VectorMultiply(VectorReplicate(A[1], 0), B[0]);
    Temp = VectorMultiplyAdd(VectorReplicate(A[1], 1), B[1], Temp);
    Temp = VectorMultiplyAdd(VectorReplicate(A[1], 2), B[2], Temp);
    R1 = VectorMultiplyAdd(VectorReplicate(A[1], 3), B[3], Temp);

    // Third row of result (Matrix1[2] * Matrix2).
    Temp = VectorMultiply(VectorReplicate(A[2], 0), B[0]);
    Temp = VectorMultiplyAdd(VectorReplicate(A[2], 1), B[1], Temp);
    Temp = VectorMultiplyAdd(VectorReplicate(A[2], 2), B[2], Temp);
    R2 = VectorMultiplyAdd(VectorReplicate(A[2], 3), B[3], Temp);

    // Fourth row of result (Matrix1[3] * Matrix2).
    Temp = VectorMultiply(VectorReplicate(A[3], 0), B[0]);
    Temp = VectorMultiplyAdd(VectorReplicate(A[3], 1), B[1], Temp);
    Temp = VectorMultiplyAdd(VectorReplicate(A[3], 2), B[2], Temp);
    Temp = VectorMultiplyAdd(VectorReplicate(A[3], 3), B[3], Temp);

    // Store result
    R[0] = R0;
    R[1] = R1;
    R[2] = R2;
    R[3] = Temp;
}

inline void VectorMatrixInverse( void* DstMatrix, const void* SrcMatrix )
{
	typedef float Float4x4[4][4];
	const Float4x4& M = *((const Float4x4*) SrcMatrix);
	Float4x4 Result;
	float Det[4];
	Float4x4 Tmp;

	Tmp[0][0]	= M[2][2] * M[3][3] - M[2][3] * M[3][2];
	Tmp[0][1]	= M[1][2] * M[3][3] - M[1][3] * M[3][2];
	Tmp[0][2]	= M[1][2] * M[2][3] - M[1][3] * M[2][2];

	Tmp[1][0]	= M[2][2] * M[3][3] - M[2][3] * M[3][2];
	Tmp[1][1]	= M[0][2] * M[3][3] - M[0][3] * M[3][2];
	Tmp[1][2]	= M[0][2] * M[2][3] - M[0][3] * M[2][2];

	Tmp[2][0]	= M[1][2] * M[3][3] - M[1][3] * M[3][2];
	Tmp[2][1]	= M[0][2] * M[3][3] - M[0][3] * M[3][2];
	Tmp[2][2]	= M[0][2] * M[1][3] - M[0][3] * M[1][2];

	Tmp[3][0]	= M[1][2] * M[2][3] - M[1][3] * M[2][2];
	Tmp[3][1]	= M[0][2] * M[2][3] - M[0][3] * M[2][2];
	Tmp[3][2]	= M[0][2] * M[1][3] - M[0][3] * M[1][2];

	Det[0]		= M[1][1]*Tmp[0][0] - M[2][1]*Tmp[0][1] + M[3][1]*Tmp[0][2];
	Det[1]		= M[0][1]*Tmp[1][0] - M[2][1]*Tmp[1][1] + M[3][1]*Tmp[1][2];
	Det[2]		= M[0][1]*Tmp[2][0] - M[1][1]*Tmp[2][1] + M[3][1]*Tmp[2][2];
	Det[3]		= M[0][1]*Tmp[3][0] - M[1][1]*Tmp[3][1] + M[2][1]*Tmp[3][2];

	float Determinant = M[0][0]*Det[0] - M[1][0]*Det[1] + M[2][0]*Det[2] - M[3][0]*Det[3];
	const float	RDet = 1.0f / Determinant;

	Result[0][0] =  RDet * Det[0];
	Result[0][1] = -RDet * Det[1];
	Result[0][2] =  RDet * Det[2];
	Result[0][3] = -RDet * Det[3];
	Result[1][0] = -RDet * (M[1][0]*Tmp[0][0] - M[2][0]*Tmp[0][1] + M[3][0]*Tmp[0][2]);
	Result[1][1] =  RDet * (M[0][0]*Tmp[1][0] - M[2][0]*Tmp[1][1] + M[3][0]*Tmp[1][2]);
	Result[1][2] = -RDet * (M[0][0]*Tmp[2][0] - M[1][0]*Tmp[2][1] + M[3][0]*Tmp[2][2]);
	Result[1][3] =  RDet * (M[0][0]*Tmp[3][0] - M[1][0]*Tmp[3][1] + M[2][0]*Tmp[3][2]);
	Result[2][0] =  RDet * (
		M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
		M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
		M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
		);
	Result[2][1] = -RDet * (
		M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
		M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
		M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
		);
	Result[2][2] =  RDet * (
		M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
		M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
		M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
		);
	Result[2][3] = -RDet * (
		M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
		);
	Result[3][0] = -RDet * (
		M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
		M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
		M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
		);
	Result[3][1] =  RDet * (
		M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
		M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
		M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
		);
	Result[3][2] = -RDet * (
		M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
		M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
		M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
		);
	Result[3][3] =  RDet * (
		M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
		);

	std::memcpy( DstMatrix, &Result, 16*sizeof(float) );
}

inline VectorRegister VectorTransformVector(const VectorRegister&  VecP,  const void* MatrixM )
{
	const VectorRegister *M	= (const VectorRegister *) MatrixM;
	VectorRegister VTempX, VTempY, VTempZ, VTempW;

	// Splat x,y,z and w
	VTempX = VectorReplicate(VecP, 0);
	VTempY = VectorReplicate(VecP, 1);
	VTempZ = VectorReplicate(VecP, 2);
	VTempW = VectorReplicate(VecP, 3);
	// Mul by the matrix
	VTempX = VectorMultiply(VTempX, M[0]);
	VTempX = VectorMultiplyAdd(VTempY, M[1], VTempX);
	VTempX = VectorMultiplyAdd(VTempZ, M[2], VTempX);
	VTempX = VectorMultiplyAdd(VTempW, M[3], VTempX);

	return VTempX;
}

namespace EAxis
{
    enum Type
    {
        None,
        X,
        Y,
        Z,
    };
}

class AA_LinearColor
{
public:
    float R, G, B, A;
};

class AA_Vector2
{
public:
    float X, Y;

    AA_Vector2() { X = 0; Y = 0; }
    AA_Vector2(const float& x, const float& y) { X = x; Y = y; }
    void Set(const float& x, const float& y) { X = x; Y = y; }
    void SetX(const float& val) { X = val; }
    void SetY(const float& val) { Y = val; }
    float GetX() { return X; }
    float GetY() { return Y; }
};

class AA_Vector3
{
public:
    float X, Y, Z;

    AA_Vector3() { X = 0; Y = 0; Z = 0; }
    AA_Vector3(const float& x, const float& y, const float& z) { X = x; Y = y; Z = z; }
    void Set(const float& x, const float& y, const float& z) { X = x; Y = y; Z = z; }
    void SetX(const float& val) { X = val; }
    void SetY(const float& val) { Y = val; }
    void SetZ(const float& val) { Z = val; }
    float GetX() { return X; }
    float GetY() { return Y; }
    float GetZ() { return Z; }

    AA_Vector3 operator-(const AA_Vector3& V) const
    {
        return AA_Vector3(X - V.X, Y - V.Y, Z - V.Z);
    }

    AA_Vector3 operator-() const
    {
        return AA_Vector3(-X, -Y, -Z);
    }

    AA_Vector3 operator*(const AA_Vector3& V) const 
    {
        return AA_Vector3(X * V.X, Y * V.Y, Z * V.Z);
    }

    AA_Vector3 operator/=(float V)
    {
        const float RV = 1.f/V;
        X *= RV; Y *= RV; Z *= RV;
        return *this;
    }
    
    AA_Vector3 operator^(const AA_Vector3& V) const
    {
        return AA_Vector3(
            Y * V.Z - Z * V.Y,
            Z * V.X - X * V.Z,
            X * V.Y - Y * V.X
        );
    }

    float operator|(const AA_Vector3& V) const
    {
        return X * V.X + Y * V.Y + Z * V.Z;
    }

    float Size() const
    {
        return sqrtf(X * X + Y * Y + Z * Z);
    }

    float SizeSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    bool Normalize(float Tolerance = SMALL_NUMBER)
    {
        const float SquareSum = X * X + Y * Y + Z * Z;
        if (SquareSum > Tolerance)
        {
            const float Scale = InvSqrt(SquareSum);
            X *= Scale; Y *= Scale; Z *= Scale;
            return true;
        }
        return false;
    }

    AA_Vector3 GetSafeNormal(float Tolerance = SMALL_NUMBER) const
    {
        const float SquareSum = X * X + Y * Y + Z * Z;

        // Not sure if it's safe to add tolerance in there. Might introduce too many errors
        if (SquareSum == 1.f)
        {
            return *this;
        }
        else if (SquareSum < Tolerance)
        {
            return AA_Vector3(0, 0, 0);
        }
        const float Scale = InvSqrt(SquareSum);
        return AA_Vector3(X * Scale, Y * Scale, Z * Scale);
    }

    bool IsNearlyZero(float Tolerance) const
    {
        return
            fabs(X) <= Tolerance
            && fabs(Y) <= Tolerance
            && fabs(Z) <= Tolerance;
    }
};

class AA_Vector4
{
public:
    float X, Y, Z, W;

    AA_Vector4() { X = 0; Y = 0; Z = 0; W = 0; }
    AA_Vector4(AA_Vector3 vec, const float& w) { X = vec.GetX(); Y = vec.GetY(); Z = vec.GetZ(); W = w; }
    AA_Vector4(const float& x, const float& y, const float& z, const float& w) { X = x; Y = y; Z = z; W = w; }
    void Set(const float& x, const float& y, const float& z, const float& w) { X = x; Y = y; Z = z; W = w; }
    void SetX(const float& val) { X = val; }
    void SetY(const float& val) { Y = val; }
    void SetZ(const float& val) { Z = val; }
    void SetW(const float& val) { W = val; }
    float GetX() { return X; }
    float GetY() { return Y; }
    float GetZ() { return Z; }
    float GetW() { return W; }

    AA_Vector4 operator/=(float V)
    {
        const float RV = 1.f/V;
        X *= RV; Y *= RV; Z *= RV; W *= RV;
        return *this;
    }
};

class AA_Rotator
{
    float X, Y, Z;
};

class AA_Matrix
{
public:
    union
    {
        float M[4][4];
    };

    AA_Matrix()
    {
        M[0][0] = 0;
        M[0][1] = 0;
        M[0][2] = 0;
        M[0][3] = 0;
        M[1][0] = 0;
        M[1][1] = 0;
        M[1][2] = 0;
        M[1][3] = 0;
        M[2][0] = 0;
        M[2][1] = 0;
        M[2][2] = 0;
        M[2][3] = 0;
        M[3][0] = 0;
        M[3][1] = 0;
        M[3][2] = 0;
        M[3][3] = 0;
    }

    AA_Matrix(AA_Vector4 a, AA_Vector4 b, AA_Vector4 c, AA_Vector4 d) {
        M[0][0] = a.GetX();
        M[0][1] = a.GetY();
        M[0][2] = a.GetZ();
        M[0][3] = a.GetW();
        M[1][0] = b.GetX();
        M[1][1] = b.GetY();
        M[1][2] = b.GetZ();
        M[1][3] = b.GetW();
        M[2][0] = c.GetX();
        M[2][1] = c.GetY();
        M[2][2] = c.GetZ();
        M[2][3] = c.GetW();
        M[3][0] = d.GetX();
        M[3][1] = d.GetY();
        M[3][2] = d.GetZ();
        M[3][3] = d.GetW();
    }

    AA_Matrix(const AA_Vector3 EyePosition, const AA_Vector3 LookDirection, const AA_Vector3 UpVector) {
        const AA_Vector3 ZAxis = LookDirection.GetSafeNormal();
        const AA_Vector3 XAxis = (UpVector ^ ZAxis).GetSafeNormal();
        const AA_Vector3 YAxis = ZAxis ^ XAxis;

        for (uint32_t RowIndex = 0; RowIndex < 3; RowIndex++)
        {
            M[RowIndex][0] = (&XAxis.X)[RowIndex];
            M[RowIndex][1] = (&YAxis.X)[RowIndex];
            M[RowIndex][2] = (&ZAxis.X)[RowIndex];
            M[RowIndex][3] = 0.0f;
        }
        M[3][0] = -EyePosition | XAxis;
        M[3][1] = -EyePosition | YAxis;
        M[3][2] = -EyePosition | ZAxis;
        M[3][3] = 1.0f;
    }

    AA_Matrix(float HalfFOVX, float HalfFOVY, float MultFOVX, float MultFOVY, float MinZ, float MaxZ)
        : AA_Matrix(
            AA_Vector4(MultFOVX / tanf(HalfFOVX), 0.0f, 0.0f, 0.0f),
            AA_Vector4(0.0f, MultFOVY / tanf(HalfFOVY), 0.0f, 0.0f),
            AA_Vector4(0.0f, 0.0f, ((MinZ == MaxZ) ? (1.0f - Z_PRECISION) : MaxZ / (MaxZ - MinZ)), 1.0f),
            AA_Vector4(0.0f, 0.0f, -MinZ * ((MinZ == MaxZ) ? (1.0f - Z_PRECISION) : MaxZ / (MaxZ - MinZ)), 0.0f)
        )
    {
    }

    void Set(AA_Vector4 a, AA_Vector4 b, AA_Vector4 c, AA_Vector4 d) {
        M[0][0] = a.GetX();
        M[0][1] = a.GetY();
        M[0][2] = a.GetZ();
        M[0][3] = a.GetW();
        M[1][0] = b.GetX();
        M[1][1] = b.GetY();
        M[1][2] = b.GetZ();
        M[1][3] = b.GetW();
        M[2][0] = c.GetX();
        M[2][1] = c.GetY();
        M[2][2] = c.GetZ();
        M[2][3] = c.GetW();
        M[3][0] = d.GetX();
        M[3][1] = d.GetY();
        M[3][2] = d.GetZ();
        M[3][3] = d.GetW();
    }

    void Set(uint32_t idx1, uint32_t idx2, const float& val)
    {
        M[idx1][idx2] = val;
    }

    float Get(uint32_t idx1, uint32_t idx2) const
    {
        return M[idx1][idx2];
    }

    AA_Vector3 GetScaledAxis(EAxis::Type InAxis) const
    {
        switch (InAxis)
        {
        case EAxis::X:
            return AA_Vector3(M[0][0], M[0][1], M[0][2]);

        case EAxis::Y:
            return AA_Vector3(M[1][0], M[1][1], M[1][2]);

        case EAxis::Z:
            return AA_Vector3(M[2][0], M[2][1], M[2][2]);

        default:
            return AA_Vector3(0, 0, 0);
        }
    }
    
    float Determinant() const
    {
        return	M[0][0] * (
                    M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                    M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
                    M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
                    ) -
                M[1][0] * (
                    M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                    M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                    M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
                    ) +
                M[2][0] * (
                    M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
                    M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                    M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                    ) -
                M[3][0] * (
                    M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
                    M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
                    M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                    );
    }

    AA_Matrix& Mult(const AA_Matrix& Other) const
    {
        AA_Matrix Result;
        VectorMatrixMultiply(&Result, this, &Other);
        return Result;
    }

    AA_Matrix Inverse() const
    {
        AA_Matrix Result;

        // Check for zero scale matrix to invert
        if (GetScaledAxis(EAxis::X).IsNearlyZero(SMALL_NUMBER) &&
            GetScaledAxis(EAxis::Y).IsNearlyZero(SMALL_NUMBER) &&
            GetScaledAxis(EAxis::Z).IsNearlyZero(SMALL_NUMBER))
        {
            // just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
            Result = AA_Matrix(AA_Vector4(1, 0, 0, 0), AA_Vector4(0, 1, 0, 0), AA_Vector4(0, 0, 1, 0), AA_Vector4(0, 0, 0, 1));
        }
        else
        {
            const float	Det = Determinant();

            if (Det == 0.0f)
            {
                Result = AA_Matrix(AA_Vector4(1, 0, 0, 0), AA_Vector4(0, 1, 0, 0), AA_Vector4(0, 0, 1, 0), AA_Vector4(0, 0, 0, 1));;
            }
            else
            {
                VectorMatrixInverse(&Result, this);
            }
        }

        return Result;
    }

    AA_Vector4 TransformFVector4(const AA_Vector4 &P) const
    {
        AA_Vector4 Result;
        VectorRegister VecP = VectorLoadAligned(&P);
        VectorRegister VecR = VectorTransformVector(VecP, this);
        VectorStoreAligned(VecR, &Result);
        return Result;
    }

    static AA_Matrix CreateIdentity()
    {
        return AA_Matrix(AA_Vector4(1, 0, 0, 0), AA_Vector4(0, 1, 0, 0), AA_Vector4(0, 0, 1, 0), AA_Vector4(0, 0, 0, 1));
    }
};