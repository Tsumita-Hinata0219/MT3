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


	Sphere sphere1 = { 0.0f,0.0f, 0.0f, 0.5f };
	int sphereColor = WHITE;
	Sphere sphere2 = { 2.0f,0.0f, 0.0f, 0.5f };



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
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(ScreenWidth) / float(ScreenHeight), 0.1f, 100.0f);
		Matrix4x4 WorldViewProjectionMatrix = matrix::Multiply(worldMatrix, matrix::Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(ScreenWidth), float(ScreenHeight), 0.0f, 1.0f);


		// 衝突判定
		if (onCollision(sphere1, sphere2)) {
			sphereColor = RED;
		}
		else {
			sphereColor = WHITE;
		}

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		//スフィアのImGui
		ImGui::DragFloat3("Sphere1Center", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere1Radius", &sphere1.radius, 0.01f);
		ImGui::DragFloat3("Sphere2Center", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("Sphere2Radius", &sphere2.radius, 0.01f);
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);
		DrawSphere(sphere1, WorldViewProjectionMatrix, viewportMatrix, sphereColor);
		DrawSphere(sphere2, WorldViewProjectionMatrix, viewportMatrix, WHITE);

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
