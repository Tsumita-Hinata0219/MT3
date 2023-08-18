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



	Vector3 rotate{ 0.4f, 1.43f, -0.8f };



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


		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);

		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);

		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

		Matrix4x4 rotateXYZMatrix = matrix::Multiply(rotateXMatrix, matrix::Multiply(rotateYMatrix, rotateZMatrix));
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		// 表示
		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");

		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateXMatrix");

		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateXMatrix");

		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXMatrix");


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
