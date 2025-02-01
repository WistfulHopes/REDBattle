#pragma once
#include <cstdint>
#include <math.h>

#define SMALL_NUMBER (1.e-8f)
#define Z_PRECISION	0.0f
#define M_PI  3.14159265358979323846264f  // from CRC

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
    float R, G, B, A{};
};

class AA_Vector2
{
public:
    float X, Y{};

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
    float X, Y, Z{};

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

    AA_Vector3& operator*=(float V)
    {
        X *= V;
        Y *= V;
        Z *= V;
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
            float length = sqrtf(SquareSum);
            if (length != 0.0f)
            {
                float ilength = 1.0f / length;

                X *= ilength;
                Y *= ilength;
                Z *= ilength;
            }

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

        AA_Vector3 ret = AA_Vector3(0, 0, 0);

        float length = sqrtf(SquareSum);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;
            ret *= ilength;
        }

        return ret;
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
    float X, Y, Z, W{};

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
public:
    float Pitch{};
    float Yaw{};
    float Roll{};

    AA_Rotator(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
    {
    }
};

class AA_Matrix
{
public:
    union
    {
        float M[4][4]{};
    };

    AA_Matrix()
    {
        M[0][0] = 1;
        M[0][1] = 0;
        M[0][2] = 0;
        M[0][3] = 0;
        M[1][0] = 0;
        M[1][1] = 1;
        M[1][2] = 0;
        M[1][3] = 0;
        M[2][0] = 0;
        M[2][1] = 0;
        M[2][2] = 1;
        M[2][3] = 0;
        M[3][0] = 0;
        M[3][1] = 0;
        M[3][2] = 0;
        M[3][3] = 1;
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


    AA_Matrix(float x, float y, float z)
    {
        M[0][0] = 1;
        M[0][1] = 0;
        M[0][2] = 0;
        M[0][3] = 0;
        M[1][0] = 0;
        M[1][1] = 1;
        M[1][2] = 0;
        M[1][3] = 0;
        M[2][0] = 0;
        M[2][1] = 0;
        M[2][2] = 1;
        M[2][3] = 0;
        M[3][0] = x;
        M[3][1] = y;
        M[3][2] = z;
        M[3][3] = 1;
    }


    AA_Matrix(const AA_Vector3 EyePosition, const AA_Vector3 LookDirection, const AA_Vector3 UpVector)
    {
        // Vector3Subtract(eye, target)
        AA_Vector3 vz = {
            EyePosition.X - LookDirection.X, EyePosition.Y - LookDirection.Y, EyePosition.Z - LookDirection.Z
        };

        // Vector3Normalize(vz)
        AA_Vector3 v = vz;
        float length = sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
        if (length == 0.0f) length = 1.0f;
        float ilength = 1.0f / length;
        vz *= ilength;

        // Vector3CrossProduct(up, vz)
        AA_Vector3 vx = {
            UpVector.Y * vz.Z - UpVector.Z * vz.Y, UpVector.Z * vz.X - UpVector.X * vz.Z,
            UpVector.X * vz.Y - UpVector.Y * vz.X
        };

        // Vector3Normalize(x)
        v = vx;
        length = sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
        if (length == 0.0f) length = 1.0f;
        ilength = 1.0f / length;
        vx *= ilength;

        // Vector3CrossProduct(vz, vx)
        AA_Vector3 vy = {vz.Y * vx.Z - vz.Z * vx.Y, vz.Z * vx.X - vz.X * vx.Z, vz.X * vx.Y - vz.Y * vx.X};

        M[0][0] = vx.X;
        M[0][1] = vy.X;
        M[0][2] = vz.X;
        M[0][3] = 0.0f;
        M[1][0] = vx.Y;
        M[1][1] = vy.Y;
        M[1][2] = vz.Y;
        M[1][3] = 0.0f;
        M[2][0] = vx.Z;
        M[2][1] = vy.Z;
        M[2][2] = vz.Z;
        M[2][3] = 0.0f;
        M[3][0] = -(vx.X * EyePosition.X + vx.Y * EyePosition.Y + vx.Z * EyePosition.Z); // Vector3DotProduct(vx, eye)
        M[3][1] = -(vy.X * EyePosition.X + vy.Y * EyePosition.Y + vy.Z * EyePosition.Z); // Vector3DotProduct(vy, eye)
        M[3][2] = -(vz.X * EyePosition.X + vz.Y * EyePosition.Y + vz.Z * EyePosition.Z); // Vector3DotProduct(vz, eye)
        M[3][3] = 1.0f;
    }

    AA_Matrix(float FOVY, float AspectRatio, float MinZ, float MaxZ)
    {
        double top = MinZ * tan(FOVY * 0.5);
        double bottom = -top;
        double right = top * AspectRatio;
        double left = -right;

        // MatrixFrustum(-right, right, -top, top, near, far);
        float rl = (float)(right - left);
        float tb = (float)(top - bottom);
        float fn = MaxZ - MinZ;

        M[0][0] = MinZ * 2.0f / rl;
        M[1][1] = MinZ * 2.0f / tb;
        M[2][0] = ((float)right + (float)left) / rl;
        M[2][1] = ((float)top + (float)bottom) / tb;
        M[2][2] = -(MaxZ + MinZ) / fn;
        M[2][3] = -1.0f;
        M[3][2] = -(MaxZ * MinZ * 2.0f) / fn;
    }

    AA_Matrix(AA_Rotator Rotator)
    {
        Rotator = AA_Rotator(Rotator.Pitch * (M_PI / 180.0f), Rotator.Yaw * (M_PI / 180.0f),
                             Rotator.Roll * (M_PI / 180.0f));

        auto matrix = AA_Matrix();

        float cosz = cosf(-Rotator.Roll);
        float sinz = sinf(-Rotator.Roll);
        float cosy = cosf(-Rotator.Yaw);
        float siny = sinf(-Rotator.Yaw);
        float cosx = cosf(-Rotator.Pitch);
        float sinx = sinf(-Rotator.Pitch);

        M[0][0] = cosz * cosy;
        M[0][1] = cosz * siny * sinx - sinz * cosx;
        M[0][2] = cosz * siny * cosx + sinz * sinx;

        M[1][0] = sinz * cosy;
        M[1][1] = sinz * siny * sinx + cosz * cosx;
        M[1][2] = sinz * siny * cosx - cosz * sinx;

        M[2][0] = -siny;
        M[2][1] = cosy * sinx;
        M[2][2] = cosy * cosx;

        *this = matrix;
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
        AA_Matrix result = AA_Matrix();

        result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M
            [3][0];
        result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M
            [3][1];
        result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M
            [3][2];
        result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[0][1] + M[0][3] * Other.M
            [3][3];
        result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M
            [3][0];
        result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M
            [3][1];
        result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M
            [3][2];
        result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M
            [3][3];
        result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M
            [3][0];
        result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M
            [3][1];
        result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M
            [3][2];
        result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M
            [3][3];
        result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M
            [3][0];
        result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M
            [3][1];
        result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M
            [3][2];
        result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M
            [3][3];

        return result;
    }

    AA_Matrix Inverse() const
    {
        AA_Matrix result = AA_Matrix();

        // Cache the matrix values (speed optimization)
        float a00 = M[0][0], a01 = M[0][1], a02 = M[0][2], a03 = M[0][3];
        float a10 = M[1][0], a11 = M[1][1], a12 = M[1][2], a13 = M[1][3];
        float a20 = M[2][0], a21 = M[2][1], a22 = M[2][2], a23 = M[2][3];
        float a30 = M[3][0], a31 = M[3][1], a32 = M[3][2], a33 = M[3][3];

        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

        result.M[0][0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
        result.M[0][1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
        result.M[0][2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
        result.M[0][3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
        result.M[1][0] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
        result.M[1][1] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
        result.M[1][2] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
        result.M[1][3] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
        result.M[2][0] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
        result.M[2][1] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
        result.M[2][2] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
        result.M[2][3] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
        result.M[3][0] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
        result.M[3][1] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
        result.M[3][2] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
        result.M[3][3] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

        return result;
    }

    AA_Vector4 TransformFVector4(const AA_Vector4& P) const
    {
        AA_Vector4 result;

        float x = P.X;
        float y = P.Y;
        float z = P.Z;
        float w = P.W;

        result.X = M[0][0] * x + M[1][0] * y + M[2][0] * z + M[3][0] * w;
        result.Y = M[0][1] * x + M[1][1] * y + M[2][1] * z + M[3][1] * w;
        result.Z = M[0][2] * x + M[1][2] * y + M[2][2] * z + M[3][2] * w;
        result.W = M[0][3] * x + M[1][3] * y + M[2][3] * z + M[3][3] * w;

        return result;
    }

    static AA_Matrix CreateIdentity()
    {
        return AA_Matrix(AA_Vector4(1, 0, 0, 0), AA_Vector4(0, 1, 0, 0), AA_Vector4(0, 0, 1, 0),
                         AA_Vector4(0, 0, 0, 1));
    }
};
