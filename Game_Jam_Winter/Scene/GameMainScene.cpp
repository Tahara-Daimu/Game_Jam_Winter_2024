#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

#define WIDTH 640
#define HEIGHT 600

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
mileage(0), main_song_handle(0), player(nullptr),
enemy(nullptr)
{
    //敵画像及び敵のカウント配列の初期化
    for (int i = 0; i < 3; i++)
    {
        enemy_image[i] = NULL;
        enemy_count[i] = NULL;
    }
}

GameMainScene::~GameMainScene()
{
    DeleteSoundMem(main_song_handle);
}

//初期化処理
void GameMainScene::Initialize()
{
    //高得点値を読み込む
    ReadHighScore();

    //画像の読み込み
    back_ground = LoadGraph("Resource/images/back01.bmp"); //背景画像(道路の画像)の読み込み
    barrier_image = LoadGraph("Resource/images/barrier.png"); //バリア画像の読み込み
    int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image); //敵の分割読み込み

    //音楽(BGM,SE,MAINSONG)の読み込み
    main_song_handle = LoadSoundMem("Resource/music/MAINSONG/GameMain_main_song_1.wav");
    //ChangeVolumeSoundMem(100, main_song_handle);

    //エラーチェック 画像が正しく読み込まれているかの確認
    bomber_image = LoadGraph("Resource/images/Bomber.png");

    //エラーチェック
    if (back_ground == -1)
    {
        //背景画像(道路の画像)
        throw("Resource/images/back.bmpがありません\n");
    }

    if (barrier_image == -1)
    {
        //バリア画像の読み込み
        throw("Resource/images/barrier.pngがありません\n");
    }

    if (result == -1)
    {
        //敵用の車の分割読み込み
        throw("Resource/images/car.bmpがありません\n");
    }

    if (main_song_handle == -1)
    {
        //敵用の車の分割読み込み
        throw("Resource/music/MAINSONG/GameMain_main_song_1.wavがありません\n");
    }

    //オブジェクトの生成 プレイヤーと敵 敵の最大数は10？
    player = new Player;
    enemy = new Enemy * [10];

    //オブジェクトの初期化
    player->Initialize();

    //画面内の敵の最大出現数？
    for (int i = 0; i < 10; i++)
    {
        enemy[i] = nullptr;
    }
}

//更新処理
eSceneType GameMainScene::Update()
{
    main_song_fps++;

    //MAINSONG再生
    PlaySoundMem(main_song_handle, DX_PLAYTYPE_BACK, FALSE);

    //プレイヤーの更新
    player->Update();

    //爆発画像の描画時間のカウント
    if (draw_bomber == TRUE) {
        bombtime++;
    }

    else {
        bombtime = 0;
    }
    //爆発状態をオフにする
    if(bombtime > 60) {
        draw_bomber = FALSE;
    }

    //移動距離の更新
    mileage += (int)player->GetSpeed() + 5;

    //テスト
    Test_mileage = mileage / 20 % 100;

    //敵生成処理 間隔で決めている
    if (mileage / 20 % 100 == 0)
    {
        
        // i < 10 の 10は敵の最大数
        for (int i = 0; i < 10; i++)
        {
            //敵の添え字の敵が生成されていないなら生成する
            if (enemy[i] == nullptr)
            {
                //int type = GetRand(3) % 3;

                //乱数 0：黄色　１：青色　２：赤色
                //int type = GetRand(1);

                int type = 0;
                enemy[i] = new Enemy(type, enemy_image[type]);
                enemy[i]->Initialize();
                break;
            }
        }
    }

    //敵の更新と当たり判定チェック
    for (int i = 0; i < 10; i++)
    {
        //敵が生成されていたら中に入る
        if (enemy[i] != nullptr)
        {
            //敵のスピードを更新している これがないとmileageの処理が更新されず動いているように見えなくなる
            enemy[i]->Updata();

            //画面外に行ったら、敵を削除してスコア加算 640.0f
            if (enemy[i]->GetLocation().y >= 750.0f)
            {
                //敵が避けれたから敵の避けたカウントを増分
                //enemy_count[enemy[i]->GetType()]++;

                //Finalizeの中には何も入っていないがもしEnemy側に画像の読み込み等があった場合、この関数からdelete等を使用する
                //今回は画像の読み込み等がGameMainで完結しているのでここから何かすることはない
                enemy[i]->Finalize();

                //画面外に出た分の敵を削除する
                delete enemy[i];

                //空いた分の配列を初期化している
                enemy[i] = nullptr;
            }

            //当たり判定の確認
            if (IsHitCheck(player, enemy[i]))
            {
                player->SetActive(false);
                player->DecreaseHp(-50.0f);
                enemy[i]->Finalize();
                score += 100;
                bomber_x = player->GetLocation().x;
                bomber_y = player->GetLocation().y;
                draw_bomber = TRUE;
                delete enemy[i];
                enemy[i] = nullptr;
            }
        }
    }

    //プレイヤーの燃料化体力が０未満なら、リザルトに遷移する
    /*if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
    {
        return eSceneType::E_RESULT;
    }*/

    if (main_song_fps > 59) {
        main_song_fps = 0;
        main_song_count++;
    }

    return GetNowScene();
}

//描画処理
void GameMainScene::Draw()const
{
    //背景画像(道路)の描画
    //なぜ480か？ 今回の道路の画像の横幅が480になっている２個目のDrawGraphで上の部分を描画しており
    //１回目の部分は徐々にスクロールしていく際にずれが出てくるため、それを１回目の部分でくっつけて(重ねている？)切れ目なしでスクロールしているように見せている 480
    DrawGraph(0, mileage % 650 - 650, back_ground, TRUE);
    DrawGraph(0, mileage % 650, back_ground, TRUE);

    //敵の描画
    for (int i = 0; i < 10; i++)
    {
        //敵が生成されていたら描画する
        if (enemy[i] != nullptr)
        {
            enemy[i]->Draw();
        }
    }

    //プレイヤーの描画
    player->Draw();

    //テスト用
    DrawFormatString(0, 20, GetColor(255, 255, 255), "%0.1ffps %d秒", main_song_fps, main_song_count);
    DrawFormatString(0, 40, GetColor(255, 255, 255), "%d:mileage", Test_mileage);


    //UIの描画 DrawBoxで緑の部分描画
    DrawBox(500, 0, WIDTH, HEIGHT, GetColor(0, 153, 0), TRUE);

    SetFontSize(16);
    DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
    DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
    DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");
    for (int i = 0; i < 3; i++)
    {
        DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
        DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);
    }
    /*DrawFormatString(510, 200, GetColor(0, 0, 0), "走行距離");
    DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);*/
    DrawFormatString(510, 240, GetColor(0, 0, 0), "スピード");
    DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

    //燃料ゲージの描画
    float fx = 510.0f;
    float fy = 390.0f;
    DrawFormatString(fx, fy, GetColor(0, 0, 0), "FUEL METER");
    DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f,
        GetColor(0, 102, 204), TRUE);
    DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

    //体力ゲージの描画
    fx = 510.0f;
    fy = 430.0f;
    DrawFormatString(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
    DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f,
        GetColor(255, 0, 0), TRUE);
    DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0),
        FALSE);
}


//終了時処理
void GameMainScene::Finalize()
{
    /*for (int i = 0; i < 3; i++)
    {
        score += (i + 1) * 50 * enemy_count[i];
    }*/

    //リザルトデータの書き込み
    FILE* fp = nullptr;
    //ファイルオープン
    errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

    //エラーチェック
    if (result != 0)
    {
        throw("Resource/dat/result_data.csvが開けません\n");
    }

    //スコアを保存
    fprintf(fp, "%d,\n", score);

    //避けた数と得点を保存
    for (int i = 0; i < 3; i++)
    {
        fprintf(fp, "%d,\n", enemy_count[i]);
    }

    //ファイルクローズ
    fclose(fp);

    //動的確保したオブジェクトを削除する
    player->Finalize();
    delete player;

    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Finalize();
            delete enemy[i];
            enemy[i] = nullptr;
        }
    }

    delete[] enemy;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene()const
{
    return eSceneType::E_MAIN;
}


//ハイスコア読み込み
void GameMainScene::ReadHighScore()
{
    RankingData data;
    data.Initialize();

    high_score = data.GetScore(0);

    data.Finalize();
}


//当たり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
    //敵情報がなければ、当たり判定を無視する
    if (e == nullptr)
    {
        return false;
    }

    //位置情報の差分を取得
    Vector2D diff_location = p->GetLocation() - e->GetLocation();

    //当たり判定サイズの大きさを取得
    Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

    //コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
    return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}