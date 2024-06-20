#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};
const Vector3 operator+(const Vector3& v1, const Vector3& v2);