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



	Matrix4x4 m1 = { 3.2f, 0.7f, 9.6f, 4.4f,
					 5.5f, 1.3f, 7.8f, 2.1f,
					 6.9f, 8.0f, 2.6f, 1.0f,
					 0.5f, 7.2f, 5.1f, 3.3f };

	Matrix4x4 m2 = { 4.1f, 6.5f, 3.3f, 2.2f,
					 8.8f, 0.6f, 9.9f, 7.7f,
					 1.1f, 5.5f, 6.6f, 0.0f,
					 3.3f, 9.9f, 8.8f, 2.2f };



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


		// 加法
		Matrix4x4 resultAdd = matrix::Add(m1, m2);

		// 積
		Matrix4x4 resultMultiply = matrix::Multiply(m1, m2);

		// 減法
		Matrix4x4 resultSubtract = matrix::Subtract(m1, m2);

		// 逆行列
		Matrix4x4 inverseM1 = Inverse(m1);

		// 逆行列
		Matrix4x4 inverseM2 = Inverse(m2);

		// 転置行列
		Matrix4x4 TransposeM1 = Transpose(m1);

		// 転置行列
		Matrix4x4 TransposeM2 = Transpose(m2);

		// 単位行列の作成
		Matrix4x4 identity = MakeIdentity4x4();
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		// 表示
		MatrixScreenPrintf(0, 0, resultAdd, "        Add");

		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "        Subtract");

		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "        Multiply");

		MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1, "        inverseM1");

		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2, "        inverseM2");

		MatrixScreenPrintf(kColumnWidth * 5, 0, TransposeM1, "        transposeM1");

		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, TransposeM2, "        transposeM2");

		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "        identity");


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
