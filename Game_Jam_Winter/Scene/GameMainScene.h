#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"

class GameMainScene :public SceneBase
{
private:

	//テスト用
	float main_song_fps = 0.0f;
	int main_song_count = 0;
	int Test_mileage = 0;

	int score;			 //スコア
	int high_score;      //ハイスコア
	int back_ground;     //背景画像
	int bomber_image;	 //爆発画像
	int bomber_x;		 //爆発画像のX座標
	int bomber_y;		 //爆発画像のY座標
	int draw_bomber;	 //爆発画像を描画するかどうか
	int bombtime;		 //爆発状態のカウント
	int barrier_image;   //バリア映像
	int mileage;         //走行距離
	int enemy_image[3];  //敵画像
	int enemy_count[3];  //通り過ぎた敵カウント

	int main_song_handle;//ゲームメインで流れるメインの曲用変数


	Player* player;      //プレイヤー
	Enemy** enemy;       //敵 ダブルポインタなので配列のだったら配列の先頭のアドレス(場所)を指す

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);
};

