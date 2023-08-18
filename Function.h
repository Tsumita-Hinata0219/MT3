#pragma once
#include <Struct.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <Novice.h>
#include <iostream>
#include <cassert>
#include "imgui.h"
#include <algorithm>



// 表示
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);



// 3次元ベクトル
namespace vector {

	// 加算
	Vector3 Add(const Vector3 v1, const Vector3 v2);

	// 減算
	Vector3 Subtract(const Vector3 v1, const Vector3 v2);

	// スカラー倍
	Vector3 Multiply(float scalar, const Vector3 v);
}

// 内積
float Dot(const Vector3 v1, const Vector3 v2);

// 長さ
float Length(const Vector3 v);

// 正規化
Vector3 Normalize(const Vector3 v);


// 行列
namespace matrix {

	// 加算
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	// 減算
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	// 乗算
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

// 単位行列の作成
Matrix4x4 MakeIdentity4x4();

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);

// 座標変換
Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3 scele);

// 回転行列(X,Y,Z)
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

// 回転行列(all)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);

// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspecrRatio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// グリッドの描画
void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

// 球の描画
void DrawSphere(
	const Sphere& sphere, 
	const Matrix4x4& viewProjectionMatrix, 
	const Matrix4x4& viewportMatrix, 
	unsigned int color);

// 正射影ベクトル
Vector3 Project(const Vector3 v1, const Vector3 v2);

// 最近接点
Vector3 ClosestPoint(const Vector3 point, const Segment segment);



