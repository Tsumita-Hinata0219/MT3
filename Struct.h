#pragma once
#include <Vector3.h>


// 行列4x4
struct Matrix4x4 {
	float m[4][4];
};


// 球
struct Sphere {
	Vector3 center;
	float radius;
};


// 直線
struct Line {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 半直線
struct Ray {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 線分
struct Segment {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 平面
struct Plane {
	Vector3 normal;	// !< 法線
	float distance; // !< 距離
};


// 三角形
struct Triangle {
	Vector3 vertices[3]; // !< 頂点
};