#pragma once
#pragma once

#include "../Utility/Vector2D.h"

class Enemy
{
private:

	float Test_random_x;	//テストのX座標
	float Test_y;			//テストのy座標

	int type;             //タイプ
	int image;            //画像
	float speed;          //速さ

	float x_up;			  //X座標に足す分
	float y_up;			  //Y座標に足す分
	Vector2D location;    //位置情報
	Vector2D box_size;    //当たり判定の大きさ

public:
	Enemy(int ytpe, int handle);
	~Enemy();

	void Initialize();            //初期化処理
	void Updata();     //更新処理
	void Draw()const;             //描画処理
	void Finalize();              //終了時処理

	int GetType()const;           //タイプ取得
	Vector2D GetLocation()const;  //位置情報の取得
	Vector2D GetBoxSize()const;   //当たり判定の大きさを取得
};

