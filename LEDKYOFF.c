/*
	LEDKYOFF.c	�S�Ă�LED�L�[��OFF�ɐݒ肷��
	XC�R���p�C�� �F cc /Y LEDKYOFF.c
	GCC�R���p�C���F gcc -liocs LEDKYOFF.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <iocslib.h>

#define KEY_CODE_NUM	(7) /* �L�[�R�[�h�̌� */
#define LED_KEY_ON	(1) /* LED�L�[ON */
#define LED_KEY_OFF	(0) /* LED�L�[OFF */


void main(void)
{
	int keycode;	/* �L�[�ԍ� */
	
	printf("LEDKYOFF : �S�Ă�LED�L�[��OFF�ɐݒ�\n");

	for (keycode = 0; keycode < KEY_CODE_NUM; keycode++) {
		LEDMOD(keycode, LED_KEY_OFF);
	}

	exit(0);
}
