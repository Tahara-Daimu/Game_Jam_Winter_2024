#pragma once
#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingInputScene :public SceneBase
{
private:
	int backgrouond_image;   //背景画像
	RankingData* ranking;    //ランキング情報
	int score;               //スコア
	char name[15];           //名前
	int name_num;            //名前入力数
	int cursor_x;            //カーソルx座標
	int cursor_y;            //カーソルy座標

	bool error_message;		//エラーメッセージを描画するか

public:
	RankingInputScene();
	virtual ~RankingInputScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//名前入力処理
	bool InputName();
};

