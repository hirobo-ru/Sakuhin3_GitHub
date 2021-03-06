//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"
#include <time.h>

//########## マクロ定義 ##########
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0					//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"無我夢走中〜立ち止まっている余裕はない〜"		//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

//マウスのボタン
#define MOUSE_BUTTON_CODE	129	//0x0000〜0x0080まで

//キーボードの種類
#define KEY_CODE_KIND		256	//256種類

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//フォント
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")			//フォントの名前

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//#define IMAGE_BACK_PATH TEXT(".\\IMAGE\\LavaCave.png")  //プレイ画面の背景
#define IMAGE_PLAYER_PATH TEXT(".\\IMAGE\\basya-moR.png")
#define IMAGE_ENEMY_PATH TEXT(".\\IMAGE\\boss_kiri2.png")

#define IMAGE_TITLE_BK_PATH TEXT(".\\IMAGE\\Universe.png")
#define IMAGE_TITLE_ROGO_PATH TEXT(".\\IMAGE\\MyGameLogo.png")
#define IMAGE_TITLE_ROGO_ROTA 0.005
#define IMAGE_TITLE_ROGO_ROTA_MAX 1.1
#define IMAGE_TITLE_ROGO_X_SPEED 1
#define IMAGE_TITLE_START_PATH TEXT(".\\IMAGE\\title_start.png")
#define IMAGE_TITLE_START_CNT 1
#define IMAGE_TITLE_START_CNT_MAX 30

#define IMAGE_END_COMP_PATH    TEXT(".\\IMAGE\\MyGameClear.png")
#define IMAGE_END_COMP_CNT     1
#define IMAGE_END_COMP_CNT_MAX 30

#define IMAGE_END_FAIL_PATH    TEXT(".\\IMAGE\\MyGameOver.png")
#define IMAGE_END_FAIL_CNT     1
#define IMAGE_END_FAIL_CNT_MAX 30

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH  TEXT(".\\MUSIC\\seru_BGM.mp3")

#define MUSIC_BGM_TITLE_PATH  TEXT(".\\MUSIC\\newop.mp3")
#define MUSIC_BGM_COMP_PATH   TEXT(".\\MUSIC\\newed.mp3")
#define MUSIC_BGM_FAIL_PATH   TEXT(".\\MUSIC\\owaowari.mp3")

#define GAME_MAP_TATE_MAX 9
#define GAME_MAP_YOKO_MAX 13
#define GAME_MAP_KIND_MAX 2

#define GAME_MAP_PATH   TEXT(".\\IMAGE\\MAP\\map.png")

#define MAP_DIV_WIDTH 64
#define MAP_DIV_HEIGHT 64
#define MAP_DIV_TATE 10
#define MAP_DIV_YOKO 4
#define MAP_DIV_NUM MAP_DIV_TATE * MAP_DIV_YOKO

//閉じるボタンを押したとき
#define MSG_CLOSE_TITLE			TEXT("終了メッセージ")
#define MSG_CLOSE_CAPTION		TEXT("ゲームを終了しますか？")

#define START_ERR_TITLE  TEXT("スタート位置エラー")
#define START_ERR_CAPTION  TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION TEXT("ゴール位置が決まっていません")

#define MOUSE_R_CLICK_TITLE  TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION  TEXT("ゲームを中断し、タイトル画面に戻りますか？")

#define limit1 30
#define limit2 45
#define limit3 60

enum GAME_MAP_KIND
{
	n = -1,
	k = 4,
	t = 9,
	s = 8,
	g = 7,
	a = -2,
	z = -3
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3,
	CHARA_SPEED_MAX = 4
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る
}MOUSE;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ
	//※タイプは、https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10　を参照

}FONT;

typedef struct STRUCT_BLK
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;
}BLK;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw = FALSE;		//描画できるか
}IMAGE;	//画像構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
}MUSIC;	//音楽構造体

typedef struct STRUCT_TITLE
{
	char path[PATH_MAX];
	int handle;
}TITLE;

typedef struct STRUCT_END
{
	char path[PATH_MAX];
	int handle;
}END;

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;
	int CenterY;

	RECT coll;					//当たり判定
	iPOINT collBeforePt;		//当たる前の座標

}CHARA;	//キャラクター構造体

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;
	BOOL IsDraw;
}IMAGE_BACK;

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;
	double angle;
	double angleMAX;
	double rate;
	double rateMAX;
}IMAGE_ROTA;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;
}IMAGE_BLINK;

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;

}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int width;
	int height;
}MAP;

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { 0 };		//すべてのキーの状態が入る
char OldAllKeyState[256] = { 0 };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;

FONT FontTanu32;
BLK Blk;

//ゲーム関連
int GameScene;		//ゲームシーンを管理

int GameEndKind;
RECT GoalRect = { -1, -1, -1, -1 };

//IMAGE_BACK ImageBack[IMAGE_BACK_NUM];

IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;

IMAGE_BLINK ImageEndCOMP;
IMAGE_BLINK ImageEndFAIL;

//プレイヤー関連
CHARA player;		//ゲームのキャラ
CHARA enemy;		//敵キャラ
CHARA breakplayer;	//プレイヤー抜け出すよう
CHARA breakenemy;	//敵キャラ抜け出すよう
CHARA trap; //仕掛け

MUSIC BGM;
TITLE Title;
END Owa;

MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;

//制限時間に使う
time_t n_time, s_time;
time_t e_timeF; //ステージ1用
time_t e_timeS; //ステージ2用
time_t e_timeT; //ステージ3用

int FontHandle;  //フォントの設定用。

int bossFlag;  //ボスにつかまったかどうかのフラグ。

int Stage = 1;  //ステージ設定。

int StageComp = 0; //ステージをクリアしたかどうかの判定。

//ステージ1のマップ
GAME_MAP_KIND mapDataF[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ 
		// 0 1 2 3 4 5 6 7 8 9 0 1 2
		   k,k,k,k,k,k,k,k,k,k,k,k,k,  //0
		   k,t,t,t,t,t,t,t,t,t,t,t,k,  //1
		   k,t,k,k,k,k,k,k,k,k,k,t,k,  //2
		   k,t,k,k,k,k,k,k,k,k,k,t,k,  //3
		   k,t,k,k,k,k,k,k,k,k,k,t,k,  //4
		   k,t,k,k,k,k,k,k,k,k,k,t,k,  //5
		   k,t,k,k,k,k,k,k,k,k,k,t,k,  //6
		   k,t,t,t,t,t,t,t,t,t,t,t,k,  //7
		   k,k,k,k,k,k,k,k,k,k,k,k,k,
};

//ステージ2のマップ
GAME_MAP_KIND mapDataS[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ 
		// 0 1 2 3 4 5 6 7 8 9 0 1 2
		   k,k,k,k,k,k,k,k,k,k,k,k,k,  //0
		   k,t,t,t,t,t,t,t,t,t,t,t,k,  //1
		   k,t,k,k,k,k,t,k,k,k,k,t,k,  //2
		   k,t,k,k,k,k,t,k,k,k,k,t,k,  //3
		   k,t,t,t,t,t,t,t,t,t,t,t,k,  //4
		   k,t,k,k,k,k,t,k,k,k,k,t,k,  //5
		   k,t,k,k,k,k,t,k,k,k,k,t,k,  //6
		   k,t,t,t,t,t,t,t,t,t,t,t,k,  //7
		   k,k,k,k,k,k,k,k,k,k,k,k,k,
};

//ステージ3のマップ
GAME_MAP_KIND mapDataT[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	// 0 1 2 3 4 5 6 7 8 9 0 1 2
	  k,k,k,k,k,k,k,k,k,k,k,k,k,  //0
	  k,t,t,t,t,t,t,t,t,t,t,t,k,  //1
	  k,t,k,k,k,k,t,k,k,k,k,t,k,  //2
	  k,t,k,k,k,k,t,k,k,k,k,t,k,  //3
	  k,t,k,k,k,k,t,k,k,k,k,t,k,  //4
	  k,t,k,k,k,k,t,k,k,k,k,t,k,  //5
	  k,t,k,k,k,k,t,k,k,k,k,t,k,  //6
	  k,t,t,t,t,t,t,t,t,t,t,t,k,  //7
	  k,k,k,k,k,k,k,k,k,k,k,k,k,
};

GAME_MAP_KIND mapDataInitF[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

GAME_MAP_KIND mapDataInitS[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

GAME_MAP_KIND mapDataInitT[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAPCHIP mapChipF;

MAPCHIP mapChipS;

MAPCHIP mapChipT;

MAP mapF[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAP mapS[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAP mapT[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

iPOINT startPt{ -1,-1 };

RECT mapCollF[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

RECT mapCollS[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

RECT mapCollT[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

VOID MY_MOUSE_UPDATE(VOID);			//マウスの入力情報を更新する
BOOL MY_MOUSE_DOWN(int);			//ボタンを押しているか、マウスコードで判断する
BOOL MY_MOUSE_UP(int);				//ボタンを押し上げたか、マウスコードで判断する
BOOL MY_MOUSEDOWN_KEEP(int, int);	//ボタンを押し続けているか、マウスコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY_INIT(VOID);	//プレイ画面初期化
VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

BOOL MY_CHECK_MAPF_PLAYER_COLL(RECT);
BOOL MY_CHECK_MAPS_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(IDI_ICON1);							//アイコンファイルを読込
	SetWindowUserCloseEnableFlag(FALSE);				//閉じるボタンで、勝手にウィンドウが閉じないようにする

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }


	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から
	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapDataF[tate][yoko] == s)
			{
				startPt.x = mapChipF.width * yoko + mapChipF.width / 2;
				startPt.y = mapChipF.height * tate + mapChipF.height / 2;
			}

			if (mapDataF[tate][yoko] == g)
			{
				GoalRect.left = mapChipF.width * yoko;
				GoalRect.top = mapChipF.height * tate;
				GoalRect.right = mapChipF.width * (yoko + 1);
				GoalRect.bottom = mapChipF.height * (tate + 1);
			}
		}
	}

	/*if (startPt.x == -1 && startPt.y == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);
		return -1;
	}

	if (GoalRect.left == -1)
	{
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);
		return -1;
	}*/

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		//画面の閉じるボタンを押されたとき
		if (GetWindowUserCloseFlag(TRUE))
		{
			if (CheckSoundMem(BGM_TITLE.handle) != 0)
			{
				StopSoundMem(BGM_TITLE.handle);
			}

			//終了ダイアログを表示
			int Ret = MessageBox(GetMainWindowHandle(), MSG_CLOSE_CAPTION, MSG_CLOSE_TITLE, MB_YESNO | MB_ICONASTERISK);
			if (Ret == IDYES) { break; }	//YESなら、ゲームを中断する
		}

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_MOUSE_UPDATE();						//マウスの状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{

	//一時的に、現在のキーの入力状態を格納する
	char TempKey[KEY_CODE_KIND];

	//直前のキー入力をとっておく
	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//マウスの入力情報を更新する
VOID MY_MOUSE_UPDATE(VOID)
{
	//マウスの以前の座標を取得
	mouse.OldPoint = mouse.Point;

	//マウスの以前のボタン入力を取得
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//マウスの座標を取得
	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	//マウスの押しているボタンを取得
	mouse.InputValue = GetMouseInput();

	//左ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//押していない

	//中ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//押している
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//押していない

	//右ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//押していない

	//ホイールの回転量を取得
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//ボタンを押しているか、マウスーコードで判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//マウスコードのボタンを押している時
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//ボタンを押している
	}
	else
	{
		return FALSE;	//ボタンを押していない
	}
}

//ボタンを押し上げたか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//直前は押していて
		&& mouse.Button[MOUSE_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//ボタンを押し上げている
	}
	else
	{
		return FALSE;	//ボタンを押し上げていない
	}
}

//ボタンを押し続けているか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
//引　数：int：ボタンを押し続ける時間
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//フォントをこのソフト用に、一時的にインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントをこのソフト用に、一時的にアンインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントを読み込む関数
//引　数：const char *：読み込むフォントの名前
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：BOOL ：エラー時はFALSE / 正常時はTRUE
BOOL MY_FONT_CREATE(VOID)
{
	FontHandle = CreateFontToHandle(NULL, 40, 3);
	ChangeFont("たぬき油性マジック");
	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	//デバッグ用
	//DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
		}

		MY_PLAY_INIT();	//ゲーム初期化

		SetMouseDispFlag(FALSE);

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//プレイヤーのスタート地点
		player.image.x = 690;
		player.image.y = 430;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		//敵のスタート地点
		enemy.image.x = 42;
		enemy.image.y = 78;

		//プレイヤーの画像初期化
		player.image.handle = LoadGraph(TEXT(".//IMAGE//basya-moR.png"));

		//ゲーム開始の時間を入れる
		time(&s_time);

		//制限時間の設定
		e_timeF = s_time + limit1; //ステージ1
		e_timeS = s_time + limit2; //ステージ2
		e_timeT = s_time + limit3; //ステージ3

		//ボスにつかまったフラグをOFFにする。
		bossFlag = 0;

		SetMousePoint(player.image.x, player.image.y);

		GameEndKind = GAME_END_FAIL;

		//ゲームのシーンをプレイ画面にする
		GameScene = GAME_SCENE_PLAY;
	}
	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);
	
	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,
		ImageTitleROGO.rate,
		ImageTitleROGO.angle,
		ImageTitleROGO.image.handle, TRUE);

	if (ImageTitleSTART.IsDraw == TRUE)
	{
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	return;
}

//プレイ画面初期化
VOID MY_PLAY_INIT(VOID)
{

	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	//DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 80 / 100, BGM.handle);

		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//今の時間を記憶する
	time(&n_time);

	if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) {
		if (player.image.y > 60)
		{
			if (Stage == 1) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 60))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}
				else if ((player.image.x > 73 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}
				else {
					player.image.y--;
					breakplayer.image.y = player.image.y;
				}
			}

			if (Stage == 2) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 60))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}
				
				//プレイヤーから左上
				else if ((player.image.x > 73 && player.image.x < 349) &&
						(player.image.y > 83 && player.image.y < 210))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//右上
				else if ((player.image.x > 381 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 210))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//左下
				else if ((player.image.x > 73 && player.image.x < 349) &&
					(player.image.y > 264 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}

				//右下
				else if ((player.image.x > 381 && player.image.x < 643) &&
						(player.image.y > 264 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}

				else {
					player.image.y--;
					breakplayer.image.y = player.image.y;
				}
			}

			if (Stage == 3) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 60))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}

				//左
				else if ((player.image.x > 73 && player.image.x < 349) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//右
				else if ((player.image.x > 381 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				else {
					player.image.y--;
					breakplayer.image.y = player.image.y;
				}
			}
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE) {
		if (player.image.y < 520)
		{
			if (Stage == 1) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 446 && player.image.y < 520))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}
				else if ((player.image.x > 73 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}
				else {
					player.image.y++;
					breakplayer.image.y = player.image.y;
				}
			}

			if (Stage == 2) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 446 && player.image.y < 520))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}
				//プレイヤーから左上
				else if ((player.image.x > 73 && player.image.x < 349) &&
					(player.image.y > 83 && player.image.y < 210))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//右上
				else if ((player.image.x > 381 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 210))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//左下
				else if ((player.image.x > 73 && player.image.x < 349) &&
					(player.image.y > 264 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}

				//右下
				else if ((player.image.x > 381 && player.image.x < 643) &&
					(player.image.y > 264 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}

				else{
					player.image.y++;
					breakplayer.image.y = player.image.y;
				}
			}

			if (Stage == 3) {
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 60))
				{
					/*if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;*/
				}

				//左
				else if ((player.image.x > 73 && player.image.x < 349) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				//右
				else if ((player.image.x > 381 && player.image.x < 643) &&
					(player.image.y > 83 && player.image.y < 426))
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					//player.image.y++;
				}

				else {
					player.image.y++;
					breakplayer.image.y = player.image.y;
				}
			}
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE) {

		//プレイヤー画像を左向きにする。
		player.image.handle = LoadGraph(TEXT(".//IMAGE//basya-moL.png"));

		if (Stage == 1) {
			if ((player.image.x > 73 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}
			else if (player.image.x > 41)
			{
				player.image.x--;
				breakplayer.image.x = player.image.x;
				/*if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.x--;
				}*/
			}
		}

		if (Stage == 2) {
			//プレイヤーから左上
			if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 83 && player.image.y < 210))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//右上
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 210))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//左下
			else if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 264 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}

			//右下
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 264 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}

			else if (player.image.x > 41)
			{
				player.image.x--;
				breakplayer.image.x = player.image.x;
				/*if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
						(player.image.y > 0 && player.image.y < 70))
					{

					}
					else {
						player.image.x--;
					}*/
			}
		}

		if (Stage == 3) {
			if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
				(player.image.y > 0 && player.image.y < 60))
			{
				/*if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;*/
			}

			//左
			else if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//右
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			else {
				player.image.x--;
				breakplayer.image.x = player.image.x;
			}
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) {

		//プレイヤーの画像の向きを右向きにする。
		player.image.handle = LoadGraph(TEXT(".//IMAGE//basya-moR.png"));


		if (Stage == 1) {
			if ((player.image.x > 73 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}
			else if (player.image.x < 698)
			{
				player.image.x++;
				breakplayer.image.x = player.image.x;
				/*if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.y--;
				}*/
			}
		}

		if (Stage == 2) {
			//左上
			if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 83 && player.image.y < 210))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//右上
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 210))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//左下
			else if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 264 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}

			//右下
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 264 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;
			}

			else if (player.image.x < 698)
			{
				player.image.x++;
				breakplayer.image.x = player.image.x;
				/*if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.y--;
				}*/
			}
		}

		if (Stage == 3) {
			if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
				(player.image.y > 0 && player.image.y < 60))
			{
				/*if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;*/
			}

			//左
			else if ((player.image.x > 73 && player.image.x < 349) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			//右
			else if ((player.image.x > 381 && player.image.x < 643) &&
				(player.image.y > 83 && player.image.y < 426))
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				//player.image.y++;
			}

			else if(player.image.x < 698)
			{
				player.image.x++;
				breakplayer.image.x = player.image.x;
			}
		}
	}

	//ゲームのクリア判定

	//ステージ1
	if (Stage == 1) {
		if ((e_timeF - n_time) <= 0)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			//ステージクリアのカウント
			StageComp++;

			GameEndKind = GAME_END_COMP;

			GameScene = GAME_SCENE_END;
		}
	}

	//ステージ2
	if (Stage == 2) {
		if ((e_timeS - n_time) <= 0)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			//ステージクリアのカウント
			StageComp++;

			GameEndKind = GAME_END_COMP;

			GameScene = GAME_SCENE_END;
		}
	}

	//ステージ3
	if (Stage >= 3) {
		if ((e_timeT - n_time) <= 0)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			//ステージクリアのカウント
			StageComp++;

			GameEndKind = GAME_END_COMP;

			GameScene = GAME_SCENE_END;
		}
	}


	//捕まり判定
	if ((enemy.image.x - 50 <= player.image.x && enemy.image.x + 50 >= player.image.x) &&
		(enemy.image.y - 50 <= player.image.y && enemy.image.y + 50 >= player.image.y))
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		//ボスにつかまったとき、プレイヤーの画像を変える。
		bossFlag = 1;

		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_END;
	}

	//敵の移動

	//右
	if (enemy.image.x <= player.image.x)
	{
		if (Stage == 1) {
			if ((enemy.image.x > 71 && enemy.image.x < 643) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 70;
				}
				else if (enemy.image.x > 630)
				{
					enemy.image.x = 645;
				}
			}
			/*else if (enemy.image.x == player.image.x)
			{
				if (enemy.image.y >= player.image.y)
				{

				}
			}*/
			else if (enemy.image.x < 698)
			{
				enemy.image.x++;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 68))
				{

				}
				else {
					player.image.y--;
				}*/
			}
		}

		if (Stage == 2) {
			//左上
			if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 83 && enemy.image.y < 210))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右上
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 83 && enemy.image.y < 210))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 630)
				{
					enemy.image.x = 645;
				}
			}

			//左下
			else if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 264 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右下
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 264 && enemy.image.y < 426))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 630)
				{
					enemy.image.x = 645;
				}
			}

			/*else if (enemy.image.x == player.image.x)
			{
				if (enemy.image.y >= player.image.y)
				{

				}
			}*/

			else if (enemy.image.x < 698)
			{
				enemy.image.x++;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 68))
				{

				}
				else {
					player.image.y--;
				}*/
			}
		}

		if (Stage >= 3) {
			//左
			if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 420)
				{
					enemy.image.x = 430;
				}
			}

			else if (enemy.image.x < 698)
			{
				enemy.image.x++;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 68))
				{

				}
				else {
					player.image.y--;
				}*/
			}
		}
	}

	//左
	if (enemy.image.x >= player.image.x)
	{
		if (Stage == 1) {
			if ((enemy.image.x > 71 && enemy.image.x < 690) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 70;
				}
				else if (enemy.image.x > 680)
				{
					enemy.image.x = 691;
				}
			}
			else if (enemy.image.x > 41)
			{
				enemy.image.x--;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.x--;
				}*/
			}
		}

		if (Stage == 2) {
			//左上
			if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 83 && enemy.image.y < 210))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右上
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 83 && enemy.image.y < 210))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 630)
				{
					enemy.image.x = 645;
				}
			}

			//左下
			else if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 264 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右下
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 264 && enemy.image.y < 426))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 630)
				{
					enemy.image.x = 645;
				}
			}
			else if (enemy.image.x > 41)
			{
				enemy.image.x--;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.x--;
				}*/
			}
		}

		if (Stage >= 3) {
			//左
			if ((enemy.image.x > 73 && enemy.image.x < 349) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 80)
				{
					enemy.image.x = 72;
				}
				else if (enemy.image.x > 340)
				{
					enemy.image.x = 351;
				}
			}

			//右
			else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
				(enemy.image.y > 83 && enemy.image.y < 426))
			{
				if (enemy.image.x < 390)
				{
					enemy.image.x = 380;
				}
				else if (enemy.image.x > 420)
				{
					enemy.image.x = 430;
				}
			}

			else if (enemy.image.x > 41)
			{
				enemy.image.x--;
				/*breakplayer.image.x = player.image.x;
				if ((player.image.x > 0 && player.image.x < GAME_WIDTH) &&
					(player.image.y > 0 && player.image.y < 70))
				{

				}
				else {
					player.image.x--;
				}*/
			}
		}
	}

	//上
	if (enemy.image.y > 60)
	{
		if (enemy.image.y >= player.image.y)
		{
			if (Stage == 1) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 0 && enemy.image.y < 60))
				{
					if (enemy.image.y < 60)
					{
						enemy.image.y = 61;
					}
				}
				else if ((enemy.image.x > 71 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 82;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 427;
					}
				}
				else {
					enemy.image.y--;
				}
			}

			if (Stage == 2) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 0 && enemy.image.y < 60))
				{
					if (enemy.image.y < 60)
					{
						enemy.image.y = 61;
					}
				}
				//左上
				if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 83 && enemy.image.y < 210))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 200)
					{
						enemy.image.y = 213;
					}
				}

				//右上
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 210))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 200)
					{
						enemy.image.y = 213;
					}
				}

				//左下
				else if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 264 && enemy.image.y < 426))
				{
					if (enemy.image.y < 270)
					{
						enemy.image.y = 260;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				//右下
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 264 && enemy.image.y < 426))
				{
					if (enemy.image.y < 270)
					{
						enemy.image.y = 260;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}
				else {
					enemy.image.y--;
				}
			}

			if (Stage >= 3) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 0 && enemy.image.y < 60))
				{
					if (enemy.image.y < 60)
					{
						enemy.image.y = 61;
					}
				}
				//左
				if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				//右
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				else {
					enemy.image.y--;
				}
			}
		}
	}

	//下
	if (enemy.image.y < 520)
	{
		if (enemy.image.y <= player.image.y)
		{
			if (Stage == 1) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 446 && enemy.image.y < 520))
				{
					if (enemy.image.y > 520)
					{
						enemy.image.y = 519;
					}
				}
				else if ((enemy.image.x > 71 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 82;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 427;
					}
				}
				else {
					enemy.image.y++;
					//breakenemy.image.y = enemy.image.y;
				}
			}

			if (Stage == 2) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 446 && enemy.image.y < 520))
				{
					if (enemy.image.y > 520)
					{
						enemy.image.y = 519;
					}
				}
				//左上
				if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 83 && enemy.image.y < 210))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 200)
					{
						enemy.image.y = 213;
					}
				}

				//右上
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 210))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 200)
					{
						enemy.image.y = 213;
					}
				}

				//左下
				else if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 264 && enemy.image.y < 426))
				{
					if (enemy.image.y < 270)
					{
						enemy.image.y = 260;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				//右下
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 264 && enemy.image.y < 426))
				{
					if (enemy.image.y < 270)
					{
						enemy.image.y = 260;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}
				else {
					enemy.image.y++;
					//breakenemy.image.y = enemy.image.y;
				}
			}

			if (Stage >= 3) {
				if ((enemy.image.x > 0 && enemy.image.x < GAME_WIDTH) &&
					(enemy.image.y > 0 && enemy.image.y < 60))
				{
					if (enemy.image.y < 60)
					{
						enemy.image.y = 61;
					}
				}
				//左
				if ((enemy.image.x > 73 && enemy.image.x < 349) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				//右
				else if ((enemy.image.x > 381 && enemy.image.x < 643) &&
					(enemy.image.y > 83 && enemy.image.y < 426))
				{
					if (enemy.image.y < 90)
					{
						enemy.image.y = 80;
					}
					else if (enemy.image.y > 420)
					{
						enemy.image.y = 430;
					}
				}

				else {
					enemy.image.y++;
					//breakenemy.image.y = enemy.image.y;
				}
			}
		}
	}



	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		iPOINT R_ClickPt = mouse.Point;

		SetMouseDispFlag(TRUE);

		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			SetMouseDispFlag(TRUE);

			GameScene = GAME_SCENE_START;
			return;
		}
		else if (Ret == IDNO)
		{
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			SetMouseDispFlag(FALSE);
		}
	}

	/*//スペースキーを押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		//ゲームのシーンをエンド画面にする
		GameScene = GAME_SCENE_END;

		return;
	}*/

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//ステージ1
			if (Stage == 1) {
				DrawGraph(
					mapF[tate][yoko].x,
					mapF[tate][yoko].y,
					mapChipF.handle[mapF[tate][yoko].kind],
					TRUE);
			}

			//ステージ2
			if (Stage == 2) {
				DrawGraph(
					mapS[tate][yoko].x,
					mapS[tate][yoko].y,
					mapChipS.handle[mapS[tate][yoko].kind],
					TRUE);
			}

			//ステージ3
			if (Stage >= 3) {
				DrawGraph(
					mapT[tate][yoko].x,
					mapT[tate][yoko].y,
					mapChipT.handle[mapT[tate][yoko].kind],
					TRUE);
			}
		}
	}

	//時間の表示
	//ステージ1
	if (Stage == 1) {
		DrawFormatStringToHandle(0, 20, GetColor(255, 255, 255), FontHandle, "残り時間:%d", e_timeF - n_time);
	}

	//ステージ2
	if (Stage == 2) {
		DrawFormatStringToHandle(0, 20, GetColor(255, 255, 255), FontHandle, "残り時間:%d", e_timeS - n_time);
	}

	//ステージ3
	if (Stage == 3) {
		DrawFormatStringToHandle(0, 20, GetColor(255, 255, 255), FontHandle, "残り時間:%d", e_timeT - n_time);

		//仕掛けの描画
		trap.image.handle = LoadGraph(".//IMAGE/yazirushi2.png");
		DrawGraph(375, 65, trap.image.handle, TRUE);
		DrawGraph(375, 450, trap.image.handle, TRUE);
	}

	//プレイヤーの描画
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//敵の描画
	DrawGraph(enemy.image.x, enemy.image.y, enemy.image.handle, TRUE);

	//画面遷移
	//DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));

	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画


	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);
		}

		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);
		}

		//次のステージへいけるかどうかの判定
		if (StageComp >= 1) {
			Stage++;
		}

		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;

		return;
	}

	/*if (CheckSoundMem(Owa.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 30 / 100, Owa.handle);

		PlaySoundMem(Owa.handle, DX_PLAYTYPE_LOOP);
	}*/

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		{
			ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		}
		else
		{
			if (ImageEndCOMP.IsDraw == FALSE)
			{
				ImageEndCOMP.IsDraw = TRUE;
			}
			else if (ImageEndCOMP.IsDraw == TRUE)
			{
				ImageEndCOMP.IsDraw = FALSE;
			}
			ImageEndCOMP.Cnt = 0;
		}

		//次のステージへ
		//Stage++;

		break;

	case GAME_END_FAIL:
		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);

			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		{
			ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		}
		else
		{
			if (ImageEndFAIL.IsDraw == FALSE)
			{
				ImageEndFAIL.IsDraw = TRUE;
			}
			else if (ImageEndFAIL.IsDraw == TRUE)
			{
				ImageEndFAIL.IsDraw = FALSE;
			}
			ImageEndFAIL.Cnt = 0;
		}
		break;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:

		//捕まった場合の画像に変更。
		if (bossFlag == 1) {
			player.image.handle = LoadGraph(TEXT(".//IMAGE//basya_card2.jpg"));
		}

		if (ImageEndFAIL.IsDraw == TRUE)
		{
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		}
		break;
	}

	DrawString(0, 0, "エスケープキーを押してタイトル画面へ！", GetColor(255, 255, 255));

	//デバッグ用
	/*if (Stage == 2) {
		//Stage = 2;
		DrawString(0, 0, "エスケープキーを押してタイトル画面へ！", GetColor(255, 255, 255));
	}*/
	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;

	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
	if (ImageTitleROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
	ImageTitleROGO.image.x = 230;
	ImageTitleROGO.image.y = GAME_HEIGHT / 2;
	ImageTitleROGO.angle = DX_PI * 2;
	ImageTitleROGO.angleMAX = DX_PI * 2;
	ImageTitleROGO.rate = 0.0;
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;

	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);
	if (ImageTitleSTART.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;
	ImageTitleSTART.Cnt = 0.0;
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;
	ImageTitleSTART.IsDraw = FALSE;

	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);
	if (ImageEndCOMP.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;
	ImageEndCOMP.Cnt = 0.0;
	ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;
	ImageEndCOMP.IsDraw = FALSE;
	
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
	if (ImageEndFAIL.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;
	ImageEndFAIL.Cnt = 0.0;
	ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;
	ImageEndFAIL.IsDraw = FALSE;
	


	/*strcpy_s(ImageBack[0].image.path, IMAGE_BACK_PATH);
	strcpy_s(ImageBack[1].image.path, IMAGE_BACK_REV_PATH);
	strcpy_s(ImageBack[2].image.path, IMAGE_BACK_PATH);
	strcpy_s(ImageBack[3].image.path, IMAGE_BACK_REV_PATH);

	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);
		if (ImageBack[num].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}

		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}

	ImageBack[0].image.x = GAME_WIDTH / 2 - ImageBack[0].image.width / 2;
	ImageBack[0].image.y = 0 - ImageBack[0].image.height * 0;
	ImageBack[0].IsDraw = FALSE;

	ImageBack[1].image.x = GAME_WIDTH / 2 - ImageBack[1].image.width / 2;
	ImageBack[1].image.y = 0 - ImageBack[1].image.height * 1;
	ImageBack[1].IsDraw = FALSE;

	ImageBack[2].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;
	ImageBack[2].image.y = 0 - ImageBack[2].image.height * 2;
	ImageBack[2].IsDraw = FALSE;

	ImageBack[3].image.x = GAME_WIDTH / 2 - ImageBack[3].image.width / 2;
	ImageBack[3].image.y = 0 - ImageBack[3].image.height * 3;
	ImageBack[3].IsDraw = FALSE;
	*/

	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
	player.CenterX = player.image.x + player.image.width / 2;
	player.CenterY = player.image.y + player.image.height / 2;
	player.speed = CHARA_SPEED_LOW;

	
	strcpy_s(enemy.image.path, IMAGE_ENEMY_PATH);
	enemy.image.handle = LoadGraph(enemy.image.path);
	if (enemy.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(enemy.image.handle, &enemy.image.width, &enemy.image.height);
	enemy.image.x = GAME_WIDTH / 2 - enemy.image.width / 2;
	enemy.image.y = GAME_HEIGHT / 2 - enemy.image.height / 2;
	enemy.CenterX = enemy.image.x + enemy.image.width / 2;
	enemy.CenterY = enemy.image.y + enemy.image.height / 2;
	enemy.speed = CHARA_SPEED_MIDI;//
	

	/*
	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.tama[0].handle[0]);

	if (tamaRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		player.tama[cnt].width = player.tama[0].width;

		player.tama[cnt].height = player.tama[0].height;

		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		player.tama[cnt].y = player.image.y;

		player.tama[cnt].IsDraw = FALSE;

		player.tama[cnt].changeImageCnt = 0;

		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		player.tama[cnt].nowImageKind = 0;

		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}*/

	//ステージ1の画像設定。
	int mapResF = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChipF.handle[0]);

	if (mapResF == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChipF.handle[0], &mapChipF.width, &mapChipF.height);
	
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{

		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInitF[tate][yoko] = mapDataF[tate][yoko];

			mapF[tate][yoko].kind = mapDataF[tate][yoko];

			mapF[tate][yoko].width = mapChipF.width;
			mapF[tate][yoko].height = mapChipF.height;

			mapF[tate][yoko].x = yoko * mapF[tate][yoko].width;
			mapF[tate][yoko].y = tate * mapF[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapCollF[tate][yoko].left = (yoko + 0) * mapChipF.width + 1;
			mapCollF[tate][yoko].top = (tate + 0) * mapChipF.height + 1;
			mapCollF[tate][yoko].right = (yoko + 1) * mapChipF.width - 1;
			mapCollF[tate][yoko].bottom = (tate + 1) * mapChipF.height - 1;
		}
	}

	//ステージ2の画像設定。
	int mapResS = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChipS.handle[0]);

	if (mapResS == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChipS.handle[0], &mapChipS.width, &mapChipS.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{

		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInitS[tate][yoko] = mapDataS[tate][yoko];

			mapS[tate][yoko].kind = mapDataS[tate][yoko];

			mapS[tate][yoko].width = mapChipS.width;
			mapS[tate][yoko].height = mapChipS.height;

			mapS[tate][yoko].x = yoko * mapS[tate][yoko].width;
			mapS[tate][yoko].y = tate * mapS[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapCollS[tate][yoko].left = (yoko + 0) * mapChipS.width + 1;
			mapCollS[tate][yoko].top = (tate + 0) * mapChipS.height + 1;
			mapCollS[tate][yoko].right = (yoko + 1) * mapChipS.width - 1;
			mapCollS[tate][yoko].bottom = (tate + 1) * mapChipS.height - 1;
		}
	}

	//ステージ3の画像設定。
	int mapResT = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChipT.handle[0]);

	if (mapResT == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChipT.handle[0], &mapChipT.width, &mapChipT.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{

		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInitT[tate][yoko] = mapDataT[tate][yoko];

			mapT[tate][yoko].kind = mapDataT[tate][yoko];

			mapT[tate][yoko].width = mapChipT.width;
			mapT[tate][yoko].height = mapChipT.height;

			mapT[tate][yoko].x = yoko * mapT[tate][yoko].width;
			mapT[tate][yoko].y = tate * mapT[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapCollS[tate][yoko].left = (yoko + 0) * mapChipS.width + 1;
			mapCollS[tate][yoko].top = (tate + 0) * mapChipS.height + 1;
			mapCollS[tate][yoko].right = (yoko + 1) * mapChipS.width - 1;
			mapCollS[tate][yoko].bottom = (tate + 1) * mapChipS.height - 1;
		}
	}

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	/*for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}
	*/
	DeleteGraph(player.image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);

	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);

	//for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

	//for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{
	//プレイ画面の音楽
	strcpy_s(BGM.path, MUSIC_BGM_PATH);
	BGM.handle = LoadSoundMem(BGM.path);
	if (BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//タイトル画面の音楽
	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);		//パスの設定
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);	//読み込み
	if (BGM_TITLE.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//エンド画面の音楽

	//コンプリートの音楽
	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);		//パスの設定
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);	//読み込み
	if (BGM_COMP.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//フォールトの音楽
	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);		//パスの設定
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);	//読み込み
	if (BGM_FAIL.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	//DeleteSoundMem(player.musicShot.handle);

	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}


BOOL MY_CHECK_MAPF_PLAYER_COLL(RECT player)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player, mapCollF[tate][yoko]) == TRUE)
			{
				if (mapF[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
}

BOOL MY_CHECK_MAPS_PLAYER_COLL(RECT player)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player, mapCollS[tate][yoko]) == TRUE)
			{
				if (mapS[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
}

BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;
	}

	return FALSE;
}
