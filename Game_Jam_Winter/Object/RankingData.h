﻿#pragma once
class RankingData
{
private:
	int score[6];       //スコアデータ
	int rank[6];        //ランクデータ
	char name[6][15];   //名前データ


public:
	RankingData();
	~RankingData();

	void Initialize();   //初期化処理
	void Finalize();    //終了処理

public:
	//ランキングデータの設定
	void SetRankingData(int score, const char* name);
	//スコア取得処理
	int GetScore(int value)const;
	//ランク取得処理
	int GetRank(int value)const;
	//名前取得処理
	const char* GetName(int value)const;

private:
	//データ入れ替え処理
	void SortData();
};

