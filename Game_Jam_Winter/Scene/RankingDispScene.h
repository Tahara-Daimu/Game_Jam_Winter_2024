#pragma once
#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingDispScene :public SceneBase
{
private:

private:
	int background_image; //背景画像
	RankingData* ranking; //ランキング情報
	unsigned int color;		//色指定

public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

