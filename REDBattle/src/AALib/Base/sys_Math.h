#pragma once
#include <cstdint>
#include "raymath.h"

#define SMALL_NUMBER		(1.e-8f)
#define Z_PRECISION	0.0f


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
    float R, G, B, A {};
};

class AA_Vector2
{
public:
    float X, Y {};

    AA_Vector2()
    {
        X = 0;
        Y = 0;
    }

    AA_Vector2(const float& x, const float& y)
    {
        X = x;
        Y = y;
    }

    void Set(const float& x, const float& y)
    {
        X = x;
        Y = y;
    }

    void SetX(const float& val) { X = val; }
    void SetY(const float& val) { Y = val; }
    float GetX() { return X; }
    float GetY() { return Y; }
};

class AA_Vector3
{
public:
    float X, Y, Z {};

    AA_Vector3()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    AA_Vector3(const float& x, const float& y, const float& z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    void Set(const float& x, const float& y, const float& z)
    {
        X = x;
        Y = y;
        Z = z;
    }

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
        const float RV = 1.f / V;
        X *= RV;
        Y *= RV;
        Z *= RV;
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
            auto temp = Vector3Normalize(*(Vector3*)this);
            *this = *(AA_Vector3*)&temp;
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
        auto temp = Vector3Normalize(*(Vector3*)this);
        return *(AA_Vector3*)&temp;
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
    float X, Y, Z, W {};

    AA_Vector4()
    {
        X = 0;
        Y = 0;
        Z = 0;
        W = 0;
    }

    AA_Vector4(AA_Vector3 vec, const float& w)
    {
        X = vec.GetX();
        Y = vec.GetY();
        Z = vec.GetZ();
        W = w;
    }

    AA_Vector4(const float& x, const float& y, const float& z, const float& w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    void Set(const float& x, const float& y, const float& z, const float& w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

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
        const float RV = 1.f / V;
        X *= RV;
        Y *= RV;
        Z *= RV;
        W *= RV;
        return *this;
    }
};

class AA_Rotator
{
    float Pitch, Yaw, Roll {};
};

class AA_Matrix
{
public:
    union
    {
        float M[4][4] {};
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

    AA_Matrix(AA_Vector4 a, AA_Vector4 b, AA_Vector4 c, AA_Vector4 d)
    {
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

    AA_Matrix(const AA_Vector3 EyePosition, const AA_Vector3 LookDirection, const AA_Vector3 UpVector)
    {
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

    void Set(AA_Vector4 a, AA_Vector4 b, AA_Vector4 c, AA_Vector4 d)
    {
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
        return M[0][0] * (
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

    AA_Matrix Mult(const AA_Matrix& Other) const
    {
        auto Result = MatrixMultiply(*(Matrix*)this, *(Matrix*)&Other);
        return *(AA_Matrix*)&Result;
    }

    AA_Matrix Inverse() const
    {
        auto Result = MatrixInvert(*(Matrix*)this);
        return *(AA_Matrix*)&Result;
    }

    AA_Vector4 TransformFVector4(const AA_Vector4& P) const
    {
        AA_Vector4 result;
        Matrix mat = *(Matrix*)this;
        
        float x = P.X;
        float y = P.Y;
        float z = P.Z;
        float w = P.W;

        result.X = mat.m0*x + mat.m4*y + mat.m8*z + mat.m12*w;
        result.Y = mat.m1*x + mat.m5*y + mat.m9*z + mat.m13*w;
        result.Z = mat.m2*x + mat.m6*y + mat.m10*z + mat.m14*w;
        result.W = mat.m3*x + mat.m7*y + mat.m11*z + mat.m15*w;
        
        return result;
    }

    static AA_Matrix CreateIdentity()
    {
        return AA_Matrix(AA_Vector4(1, 0, 0, 0), AA_Vector4(0, 1, 0, 0), AA_Vector4(0, 0, 1, 0),
                         AA_Vector4(0, 0, 0, 1));
    }
};
