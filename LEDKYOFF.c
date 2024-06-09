/*
	LEDKYOFF.c	全てのLEDキーをOFFに設定する
	XCコンパイル ： cc /Y LEDKYOFF.c
	GCCコンパイル： gcc -liocs LEDKYOFF.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <iocslib.h>

#define KEY_CODE_NUM	(7) /* キーコードの個数 */
#define LED_KEY_ON	(1) /* LEDキーON */
#define LED_KEY_OFF	(0) /* LEDキーOFF */


void main(void)
{
	int keycode;	/* キー番号 */
	
	printf("LEDKYOFF : 全てのLEDキーをOFFに設定\n");

	for (keycode = 0; keycode < KEY_CODE_NUM; keycode++) {
		LEDMOD(keycode, LED_KEY_OFF);
	}

	exit(0);
}
