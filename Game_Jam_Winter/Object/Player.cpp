#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define WIDTH 640.0f
#define HEIGHT 600.0f
#define TIME 8

Player::Player() :image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),speed(0.0f)
{

}


Player::~Player()
{

}


//初期化処理
void Player::Initialize()
{
	nowAura = 0;
	combo1 = 0;
	combo10 = 0;
	combo100 = 0;
	nowComboDigit = 1;
	Digit2 = FALSE;
	Digit3 = FALSE;

	location = Vector2D(190.0f, HEIGHT - 100.0f);
	box_size = Vector2D(31.0f, 60.0f);
	speed = 3.0f;
	keyCount = 0;

	FontHandle = CreateFontToHandle(NULL, 40, 8);

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");
	LoadDivGraph("Resource/images/aura.png", 4, 4, 1, 90, 140, aura);

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;
	keyCount++;

	//十字移動処理
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT)
		&& TIME <= keyCount)
	{
		move += Vector2D(-130.0f, 0.0f);
		keyCount = 0;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT)
		&& TIME <= keyCount)
	{
		move += Vector2D(130.0f, 0.0f);
		keyCount = 0;
	}
	location += move;

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= WIDTH - 180.0f) ||
		(location.y < box_size.y) || (location.y >= HEIGHT - box_size.y))
	{
		location -= move;
	}

	//オーラ切り替え
	if (InputControl::GetButton(XINPUT_BUTTON_B)) nowAura = 0;
	if (InputControl::GetButton(XINPUT_BUTTON_A)) nowAura = 1;
	if (InputControl::GetButton(XINPUT_BUTTON_X)) nowAura = 2;
	if (InputControl::GetButton(XINPUT_BUTTON_Y)) nowAura = 3;
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	
	switch (nowComboDigit)
	{
	case 1:
		DrawFormatStringToHandle(location.x - 10, location.y - 25, 0x00ffff, FontHandle, "%d", combo1);
		break;

	case 2:
		DrawFormatStringToHandle(location.x - 20, location.y - 25, 0x00ffff, FontHandle, "%d%d", combo10, combo1);
		break;

	case 3:
		DrawFormatStringToHandle(location.x - 30, location.y - 25, 0x00ffff, FontHandle, "%d%d%d", combo100, combo10, combo1);
		break;

	default:
		break;
	}

	//当たり判定用
	DrawBox(location.x - box_size.x, location.y - box_size.y, 
		location.x + box_size.x, location.y + box_size.y, 0xffffff, FALSE);

	int x = 45;
	int y = 70;
	switch (nowAura)
	{
	case 0:
		DrawGraph(location.x - x, location.y - y, aura[0], TRUE);
		break;

	case 1:
		DrawGraph(location.x - x, location.y - y, aura[1], TRUE);
		break;

	case 2:
		DrawGraph(location.x - x, location.y - y, aura[2], TRUE);
		break;

	case 3:
		DrawGraph(location.x - x, location.y - y, aura[3], TRUE);
		break;

	default:
		break;
	}
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);
}

//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}