#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int type, int handle) :type(type), image(handle), Test_y(150.0f), speed(0.0f), location(0.0f), box_size(0.0f), x_up(0.0f), y_up(5.0f)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	

	//出現させるX座標パターンを取得 乱数で敵の出現するレーン＊
	//float random_x = (float)(GetRand(4) * 105 + 40);
	
	
	//(GetRand(3) * 125 + 60)

	int locationRand = GetRand(3);

	switch (locationRand)
	{
	//一番左のレーン　0番目
	case 0:
		Test_random_x = 60.0f;
		break;
	//左から１番目のレーン
	case 1:
		Test_random_x = locationRand * 190;
		break;
	//２番目のレーン
	case 2:
		Test_random_x = locationRand * 160;
		break;
	//３番目のレーン
	case 3:
		Test_random_x = locationRand * 150;
		break;
	//例外が起きた場合に入る
	default:
		break;

	}

	//生成位置の設定 X座標は 0.0f もともと Y座標は -50.0f
	location = Vector2D(Test_random_x, Test_y);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定 typeが0だった場合、スピードも0だがtypeの中身が増えていった場合 Enemyのスピードも2の倍数分増加していく
	// typeは
	//speed = (float)(this->type * 2);
}


void Enemy::Updata()
{
	//位置情報に移動量を加算する X座標は移動のさせず Y座標は敵のスピード＋引数(プレイヤーのスピード)をしている 
	//足している理由はプレイヤーのスピードが速いとき、遅いときでスピードを変更しないとプレイヤーのスピードが遅いのに敵が爆速だったら避けれないため
	//-6 は微調整しているだけ
	//location += Vector2D(0.0f, this->speed + speed - 6);

	//speed;

	//x_up = x_up + 0.0f;
	//y_up = y_up + 5.0f;


	location.x = location.x + x_up;
	location.y = location.y + y_up;

}


void Enemy::Draw()const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0f, 0.0, image, TRUE);

	//DrawCircle(Test_random_x, Test_y, 20, GetColor(255, 0, 0), TRUE);
}


void Enemy::Finalize()
{

}


//敵のタイプを取得
int Enemy::GetType()const
{
	return type;
}


//位置情報を取得
Vector2D Enemy::GetLocation()const
{
	return location;
}


//当たり判定の大きさを取得
Vector2D Enemy::GetBoxSize()const
{
	return box_size;
}