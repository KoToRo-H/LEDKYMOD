/*
	LEDKYMOD.c	LED�L�[�̃��[�h��ݒ肷��
	XC�R���p�C�� �F cc /Y LEDKYMOD.c
	GCC�R���p�C���F gcc -liocs LEDKYMOD.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iocslib.h>

#define CODE_NUM	(7) 		/* �L�[�R�[�h�̎�� */
#define PARAM_NUM	(CODE_NUM+1)	/* �L�[�R�[�h���̌� */
#define PARAM_ALL	(PARAM_NUM-1)	/* ALL�p�����[�^�ʒu */
#define LED_KEY_NUL	(2) 		/* LED�L�[ON/OFF�w��Ȃ� */
#define LED_KEY_ON	(1)		/* LED�L�[ON */
#define LED_KEY_OFF	(0) 		/* LED�L�[OFF */
#define LED_KEY_ALL	(7)		/* LED�L�[�S�� */

/* LED�L�[�̈ꗗ */
char *keyCodeName[2][PARAM_NUM] = {
	{"����", "���[�}��", "�R�[�h����", "CAPS", "INS", "�Ђ炪��", "�S�p", "�S��"},
	{"KANA", "ROME",     "CODE",       "CAPS", "INS", "HIRA",     "ZEN",  "ALL" }
};

/* ON/OFF���[�h�̈ꗗ */
char *ledModeName[] = {"OFF", "ON"};

/* �I�v�V������͌��ʂ��i�[����\���� */
typedef struct {
	int keyCode;	/* �L�[�ԍ� */
	int onoff;	/* ON/OFF���[�h */
} KEY_CODE_OPT;

/* �G���[�R�[�h��` */
enum ret {RET_SUCESS = 0, ERR_OPT_NUM, ERR_ON_OFF, ERR_LED_KEY};

/* �v���g�^�C�v�錾 */
void usage(void);
int  option_analysis(KEY_CODE_OPT *, int, char **);


/* �g�p���@�̕\�� */
void usage(void)
{
	int i;

	puts("\nLED�L�[�̃��[�h��ݒ肵�܂�\n  �g�p�@�FLEDKYMOD <LED�L�[��> <LED���[�h>\n");

	puts("LED�L�[��");
	for (i = 0; i < PARAM_NUM; i++) {
		printf("  %s\t( = %s)\n",  keyCodeName[1][i], keyCodeName[0][i]);
	}
	puts("\nLED���[�h\n  ON / OFF\n");
}

/* �I�v�V������� */
int option_analysis(KEY_CODE_OPT *keyCodeOpt, int argc, char **argv)
{
	int keyCode;	/* �L�[�R�[�h */

	if (argc != 3) { /* �������Q�ȊO�Ȃ�g�p�@��\�����ďI�� */
		puts("�I�v�V�����̌�������������܂���");
		usage();
		return ERR_OPT_NUM; /* �����̐����Ⴄ */
	}

	/* ON/OFF���[�h�̃I�v�V�������*/
	keyCodeOpt->onoff = LED_KEY_NUL; /* 0/1�ȊO�̒l�ɂ��Ă��� */

	if (stricmp(argv[2], "ON") == 0) {
		keyCodeOpt->onoff = LED_KEY_ON;
	}
	if (stricmp(argv[2], "OFF") == 0) {
		keyCodeOpt->onoff = LED_KEY_OFF;
	}

	if (keyCodeOpt->onoff == LED_KEY_NUL) { /* ON��OFF�ɐݒ肳�ꂽ���H */
		puts("ON/OFF���[�h�ɂ́uON�v���uOFF�v���w�肵�Ă�������");
		usage();
		return ERR_ON_OFF; /* ON/OFF�ȊO���w�肳�ꂽ */
	}

	/* LED�L�[�w��̃I�v�V������� */
	for (keyCode = 0; keyCode < PARAM_NUM; keyCode++) {
		if (stricmp(argv[1], keyCodeName[1][keyCode]) == 0) {
			/* LED�L�[�������o���� */
			keyCodeOpt->keyCode = keyCode;
			return RET_SUCESS; /* ����I�� */
		}
	}

	puts("LED�L�[��������������܂���");
	usage();
	return ERR_LED_KEY; /* �G���[�I���F�L�[��������Ȃ����� */
}

/* ���C���֐� */
void main(int argc, char *argv[])
{
	int keyCode;	/* �L�[�R�[�h */
	int retOptFunc;	/* �I�v�V������̖͂߂�l */

	KEY_CODE_OPT keyCodeOpt; /* �I�v�V�����\���� */

	/* �I�v�V������� */
	retOptFunc = option_analysis(&keyCodeOpt, argc, argv);

	/* �I�v�V������̓G���[���f */
	if (retOptFunc != RET_SUCESS) {
		exit(retOptFunc); /* �I�v�V�����G���[�ŏI�� */
	}

	/* IOCS�R�[�������s */
	if (keyCodeOpt.keyCode == LED_KEY_ALL) {
		/* LED�L�[�S�Ă�ݒ� */
		for (keyCode = 0; keyCode <= CODE_NUM; keyCode++) {
			LEDMOD(keyCode, keyCodeOpt.onoff);
		}
	}
	else {
		/* �ʂ�LED�L�[��ݒ� */
		LEDMOD(keyCodeOpt.keyCode, keyCodeOpt.onoff);
	}

	/* ���ʕ\�� */
	printf("LEDKYMOD : LED�L�[[%s]�̃��[�h��[%s]�ɐݒ肵�܂���\n", 
		keyCodeName[0][keyCodeOpt.keyCode], ledModeName[keyCodeOpt.onoff]);

	exit(RET_SUCESS); /* ����I�� */
}
