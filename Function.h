#pragma once
#include <Struct.h>
#include <Vector3.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>


// 加算
Vector3 Add(const Vector3 v1, const Vector3 v2);

// 減算
Vector3 Subtract(const Vector3 v1, const Vector3 v2);

// スカラー倍
Vector3 Multiply(float scalar, const Vector3 v);

// 内積
float Dot(const Vector3 v1, const Vector3 v2);

// 長さ
float Length(const Vector3 v);

// 正規化
Vector3 Normalize(const Vector3 v);


// 表示
static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label)
{

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);

	Novice::ScreenPrintf(x + kColumnWidth * 1, y, "%.02f", vector.y);

	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);

	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}