#include "RankingDispScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingDispScene::RankingDispScene() :background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}


//初期化処理
void RankingDispScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Ranking.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Ranking.bmpがありません\n");
	}

	//ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();
}

//更新処理
eSceneType RankingDispScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void RankingDispScene::Draw()const
{
	//背景の描画
	DrawBox(0, 0, 640, 600, 0x00001e, TRUE);

	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	SetFontSize(30);
	//取得したランキングデータを描画する
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(110, 190 + i * 70, 0xffffff, "%2d %-15s %6d",
			ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
}


//終了時処理
void RankingDispScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);

	//動的メモリの解放
	ranking->Finalize();
	delete ranking;
}


//現在のシーン情報を取得
eSceneType RankingDispScene::GetNowScene()const
{
	return eSceneType::E_RANKING_DISP;
}