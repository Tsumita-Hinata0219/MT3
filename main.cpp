#include <Novice.h>
#include "Function.h"

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



	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };


	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };
	Vector3 cameraPosition{ 0.0f, 0.0f, -1.0f };

	Vector3 kLocalVertics[3] = {};
	kLocalVertics[0] = { -0.2f,0.0f,0.0f };
	kLocalVertics[1] = { 0.0f,0.2f,0.0f };
	kLocalVertics[2] = { 0.2f,0.0f,0.0f };


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


		Vector3 cross = Cross(v1, v2);



		//左
		if (keys[DIK_A] != 0) {
			translate.x -= 0.01f;
		}
		//右
		if (keys[DIK_D] != 0) {
			translate.x += 0.01f;
		}
		//前
		if (keys[DIK_W] != 0) {
			translate.z += 0.01f;
		}
		//後
		if (keys[DIK_S] != 0) {
			translate.z -= 0.01f;
		}

		//右
		if (keys[DIK_UP] != 0) {
			rotate.y += 0.05f;
		}
		//左
		if (keys[DIK_DOWN] != 0) {
			rotate.y -= 0.05f;
		}

		//計算
		//ワールドへ
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);

		//ビュー
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(ScreenWidth) / float(ScreenHeight), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = matrix::Multiply(worldMatrix, matrix::Multiply(viewMatrix, projectionMatrix));
		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(ScreenWidth), float(ScreenHeight), 0.0f, 1.0f);

		Vector3 screenVertices[3] = {};
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertices = Transform(kLocalVertics[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertices, viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		// 表示
		VectorScreenPrintf(10, 10, cross, "Cross");


		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		);


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
