/*
	LEDKYMOD.c	LEDキーのモードを設定する
	XCコンパイル ： cc /Y LEDKYMOD.c
	GCCコンパイル： gcc -liocs LEDKYMOD.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iocslib.h>

#define CODE_NUM	(7) 		/* キーコードの種類 */
#define PARAM_NUM	(CODE_NUM+1)	/* キーコード名の個数 */
#define PARAM_ALL	(PARAM_NUM-1)	/* ALLパラメータ位置 */
#define LED_KEY_NUL	(2) 		/* LEDキーON/OFF指定なし */
#define LED_KEY_ON	(1)		/* LEDキーON */
#define LED_KEY_OFF	(0) 		/* LEDキーOFF */
#define LED_KEY_ALL	(7)		/* LEDキー全て */

/* LEDキーの一覧 */
char *keyCodeName[2][PARAM_NUM] = {
	{"かな", "ローマ字", "コード入力", "CAPS", "INS", "ひらがな", "全角", "全て"},
	{"KANA", "ROME",     "CODE",       "CAPS", "INS", "HIRA",     "ZEN",  "ALL" }
};

/* ON/OFFモードの一覧 */
char *ledModeName[] = {"OFF", "ON"};

/* オプション解析結果を格納する構造体 */
typedef struct {
	int keyCode;	/* キー番号 */
	int onoff;	/* ON/OFFモード */
} KEY_CODE_OPT;

/* エラーコード定義 */
enum ret {RET_SUCESS = 0, ERR_OPT_NUM, ERR_ON_OFF, ERR_LED_KEY};

/* プロトタイプ宣言 */
void usage(void);
int  option_analysis(KEY_CODE_OPT *, int, char **);


/* 使用方法の表示 */
void usage(void)
{
	int i;

	puts("\nLEDキーのモードを設定します\n  使用法：LEDKYMOD <LEDキー名> <LEDモード>\n");

	puts("LEDキー名");
	for (i = 0; i < PARAM_NUM; i++) {
		printf("  %s\t( = %s)\n",  keyCodeName[1][i], keyCodeName[0][i]);
	}
	puts("\nLEDモード\n  ON / OFF\n");
}

/* オプション解析 */
int option_analysis(KEY_CODE_OPT *keyCodeOpt, int argc, char **argv)
{
	int keyCode;	/* キーコード */

	if (argc != 3) { /* 引数が２つ以外なら使用法を表示して終了 */
		puts("オプションの個数が正しくありません");
		usage();
		return ERR_OPT_NUM; /* 引数の数が違う */
	}

	/* ON/OFFモードのオプション解析*/
	keyCodeOpt->onoff = LED_KEY_NUL; /* 0/1以外の値にしておく */

	if (stricmp(argv[2], "ON") == 0) {
		keyCodeOpt->onoff = LED_KEY_ON;
	}
	if (stricmp(argv[2], "OFF") == 0) {
		keyCodeOpt->onoff = LED_KEY_OFF;
	}

	if (keyCodeOpt->onoff == LED_KEY_NUL) { /* ONかOFFに設定されたか？ */
		puts("ON/OFFモードには「ON」か「OFF」を指定してください");
		usage();
		return ERR_ON_OFF; /* ON/OFF以外が指定された */
	}

	/* LEDキー指定のオプション解析 */
	for (keyCode = 0; keyCode < PARAM_NUM; keyCode++) {
		if (stricmp(argv[1], keyCodeName[1][keyCode]) == 0) {
			/* LEDキー名を検出した */
			keyCodeOpt->keyCode = keyCode;
			return RET_SUCESS; /* 正常終了 */
		}
	}

	puts("LEDキー名が正しくありません");
	usage();
	return ERR_LED_KEY; /* エラー終了：キーが見つからなかった */
}

/* メイン関数 */
void main(int argc, char *argv[])
{
	int keyCode;	/* キーコード */
	int retOptFunc;	/* オプション解析の戻り値 */

	KEY_CODE_OPT keyCodeOpt; /* オプション構造体 */

	/* オプション解析 */
	retOptFunc = option_analysis(&keyCodeOpt, argc, argv);

	/* オプション解析エラー判断 */
	if (retOptFunc != RET_SUCESS) {
		exit(retOptFunc); /* オプションエラーで終了 */
	}

	/* IOCSコールを実行 */
	if (keyCodeOpt.keyCode == LED_KEY_ALL) {
		/* LEDキー全てを設定 */
		for (keyCode = 0; keyCode <= CODE_NUM; keyCode++) {
			LEDMOD(keyCode, keyCodeOpt.onoff);
		}
	}
	else {
		/* 個別のLEDキーを設定 */
		LEDMOD(keyCodeOpt.keyCode, keyCodeOpt.onoff);
	}

	/* 結果表示 */
	printf("LEDKYMOD : LEDキー[%s]のモードを[%s]に設定しました\n", 
		keyCodeName[0][keyCodeOpt.keyCode], ledModeName[keyCodeOpt.onoff]);

	exit(RET_SUCESS); /* 正常終了 */
}
