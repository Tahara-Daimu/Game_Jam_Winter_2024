#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() :background_image(NULL), /*menu_image(NULL),*/kuruma_image(NULL), state_image(NULL), help_image(NULL), ranking_image(NULL), end_image(NULL),
cursor_image(NULL), menu_cursor(0), Title_Bgm(0), cursor_down_se(0), cursor_up_se(0)
{

}

TitleScene::~TitleScene()
{
	//DeleteSoundMem(Title_Bgm);
	DeleteSoundMem(cursor_down_se);
	DeleteSoundMem(cursor_up_se);
}


//初期化処理
void TitleScene::Initialize()
{
	SetBackgroundColor(50, 50, 50, 0);
	//画像の読み込み
	kuruma_image = LoadGraph("Resource/images/kuruma1.bmp");
	state_image = LoadGraph("Resource/images/start_m.bmp");
	ranking_image = LoadGraph("Resource/images/ranking_m.bmp");
	help_image = LoadGraph("Resource/images/help_m.bmp");
	end_image = LoadGraph("Resource/images/end_m.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");
	cursor_down_se = LoadSoundMem("Resource/music/SE/Title_cursor_se.wav");
	cursor_up_se = LoadSoundMem("Resource/music/SE/Title_cursor_se.wav");
	//タイトルBGM
	Title_Bgm = LoadSoundMem("Resource/music/BGM/Title_and_help_bgm.wav");
	//音声ファイルのボリュームを変更できる 0:無音 255:最大音量
	ChangeVolumeSoundMem(50, Title_Bgm);

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}

	if (state_image == -1)
	{
		throw("Resource/images/start_m.bmpがありません\n");
	}
	/*if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}*/
	if (cursor_image == -1)
	{
		throw("Resource/images/cursor.bmpがありません\n");
	}
	if (Title_Bgm == -1)
	{
		throw("Resource/music/BGM/Title_and_help_bgm.wavがありません\n");
	}
	if (cursor_down_se == -1)
	{
		throw("Resource/music/SE/Title_cursor_se.wavがありません\n");
	}
	if (cursor_up_se == -1)
	{
		throw("Resource/music/SE/Title_cursor_se.wavがありません\n");
	}
}


//更新処理
eSceneType TitleScene::Update()
{
	PlaySoundMem(Title_Bgm, DX_PLAYTYPE_LOOP, FALSE);

	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(cursor_down_se, DX_PLAYTYPE_BACK, TRUE);
		menu_cursor++;
		//１番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}	
	}


	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(cursor_up_se, DX_PLAYTYPE_BACK, TRUE);
		menu_cursor--;
		//１番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}
	
	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		//StopSoundMem();
		switch (menu_cursor)
		{
		case 0:
			StopSoundMem(Title_Bgm);
			DeleteSoundMem(Title_Bgm);
			return eSceneType::E_MAIN;

		case 1:
			return eSceneType::E_RANKING_DISP;

		case 2:
			return eSceneType::E_HELP;

		case 3:
			return eSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();

	//
}


//描画処理
void TitleScene::Draw()const
{
	//タイトル画像の描画
	//DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	/*DrawGraph(120, 200, menu_image, TRUE);*/

	DrawGraph(140, 400, kuruma_image, TRUE);

	DrawGraph(210, 200, state_image,TRUE);

	DrawGraph(210, 240, ranking_image, TRUE);

	DrawGraph(210, 280, help_image, TRUE);

	DrawGraph(210, 320, end_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(180, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}


//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	/*DeleteGraph(menu_image);*/
	DeleteGraph(cursor_image);
	DeleteGraph(kuruma_image);
	DeleteGraph(state_image);
	DeleteGraph(ranking_image);
	DeleteGraph(help_image);
	DeleteGraph(end_image);

}


//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene()const
{
	return eSceneType::E_TITLE;
}