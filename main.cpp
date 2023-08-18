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



	Vector3 translate{ 4.1f, 2.6f, 0.8f };

	Vector3 scale{ 1.5f,5.2f,7.3f };

	Vector3 point{ 2.3f,3.8f,1.4f };

	Matrix4x4 trnsformMatrix = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f};



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


		Vector3 trnsformed = Transform(point, trnsformMatrix);

		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

		Matrix4x4 scalematrix = MakeeScaleMatrix(scale);
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		// 表示
		VectorScreenPrintf(0, 0, trnsformed, "transform");

		MatrixScreenPrintf(0, 30, translateMatrix, "translateMatrix");

		MatrixScreenPrintf(0, 120, scalematrix, "scaleMatrix");


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
