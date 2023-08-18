#include <Novice.h>
#include "Function.h"
#include "imgui.h"

const char kWindowTitle[] = "LE2B_20_ツミタ_ヒナタ_";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;
	Novice::Initialize(kWindowTitle, ScreenWidth, ScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	//Affine
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	//カメラ
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };


	//ローカル
	Vector3 LocalVertics[2] = {};
	LocalVertics[0] = { -0.2f,0.0f,0.0f };
	LocalVertics[1] = { 0.2f,0.0f,0.0f };

	Vector3 localCoodinate = { 0.0f,0.0f,0.0f };


	Segment segment = { {-2.0f,-1.0f,0.1f},{3.0f,2.0f,2.0f} };
	Vector3 point = { 0.0f,0.6f,0.6f };


	Vector3 project = Project(vector::Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);
	Sphere pointSphere = { point,0.1f };
	Sphere closestPointSphere = { closestPoint,0.01f };



	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		//計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(ScreenWidth) / float(ScreenHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(ScreenWidth), float(ScreenHeight), 0.0f, 1.0f);
		Matrix4x4 WorldViewProjectionMatrix = matrix::Multiply(worldMatrix, matrix::Multiply(viewMatrix, projectionMatrix));


		//正射影ベクトルと最近接点
		project = Project(vector::Subtract(point, segment.origin), segment.diff);
		closestPoint = ClosestPoint(point, segment);


		Vector3 start = Transform(Transform(segment.origin, WorldViewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(vector::Add(segment.origin, segment.diff), WorldViewProjectionMatrix), viewportMatrix);
		//ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);
		DrawSphere(pointSphere, WorldViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, WorldViewProjectionMatrix, viewportMatrix, BLACK);


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
