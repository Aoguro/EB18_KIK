//===================================================================
//	�A�v���P�[�V����: �g���Z3��INV-1TGKIT-A�A�z�[��IC�x�N�g������
//	���W���[����	: ���ʒ萔��`�E�w�b�_�t�@�C��
//	�t�@�C����		: define.h
//	�쐬��			: 2018/04/15
//	�쐬��			: HS
//	MPU				: RENESAS RX62T
//	���쌠			: ���C�[�o�C�N
//	�X�V��			:
//===================================================================
//===================================================================
//		���[�h�@Parameter Difinition
//===================================================================
//	Vdc 
//#define	Edc0	(24.0)	// �����d��[V] Vdc
//#define		TEST_M1		// ICS M1
//===================================================================
//		���[�^�I���@�ǂꂩ1��I������B
//===================================================================
//#define	KIK_256_NEW	// RX62T �T�c���[�^256W �I��	@@�@180529�@
#define	KIK_256		// RX62T �T�c���[�^256W �I��	@@�@180529�@
//#define BLY171S	// RX62T BLY171S-15V-8000 �I��	@*****
//===================================================================
//	�O���[�o���}�N����`
//===================================================================
// ******** For Motor ***********************************************
//#define	ELE_DEG(x)	(FIXPOINT_16*x/360)	// Electric Angle

//===================================================================
//		Parameter Difinition
//===================================================================
#define	 Edc0  (24.0)		/* �����d��Edc */
/* Motor Parameter */
#ifdef KIK_256				// �g�c���[�^�I��
#define	cPole		20		// [Pole] Poles of the motor �ɐ��ł�
//#define cMotor_R	(0.233)		// [Ohm] @ Winding resistance
//#define cMotor_Lq	(0.233)		// [mH]  @ q-axis inductance�@
#endif

#ifdef BLY171S				// BLY171S���[�^�I��
#define	cPole		8		// [Pole] Poles of the motor �ɐ��ł�
//#define cMotor_R	(0.233)		// [Ohm] @ Winding resistance
//#define cMotor_Lq	(0.233)		// [mH]  @ q-axis inductance�@
#endif

/* PWM Parameter */
#define	cIMCLK_FRQ	15		//Khz  96[MHz]
#define cPWMPRD		66666		//66666 [ns] PWM fuency	20kHz i_period=4800 50��s
//#define cPWMPRD	100000		// [ns] PWM fuency	10kHz i_period=2400 25��s
#define cDedTime	2375		// [ns] dead time	_inv_deadtime = 228�@2.375��s 4.75%
//#define cDedTime	4750		// [ns] dead time	_inv_deadtime = 456  4.751��s 4.75%

// Tr2�v���X�P���[�l �i1���̒ʉߎ��ԑ��莞�̃^�C�}�\�v���X�P���[�l�j
#define cTr2		64		// 1/64 �v���X�P���[�l

// ���x����@�p�����[�^��`
//#define cTs		(0.00005)	// Ts

#ifdef KIK_256				// �g�c���[�^�I��
// ��]����`
#define cNref1		(500.0)	// ���x�w�ߍő�l 250[rpm]	@@ 180529
#define cN_LOW_MAX	(2)		// �Œᑬ�x 2[rpm] 5.0		@@ 180529
// �d���E�d�������l
#define I1_LIM		(15.0)		// �d���w�ߍő�l[A]15.0
#define V1_LIM		(24.0)		// �d���w�ߍő�l[V]7.0 */
#define	NRPM_MIN	(9)		// �ʑ���Ԃ��n�߂��]��[r/min]IPMSM  3.5[rpm]
#define m1_LIM		(1.27)		// �ϒ����ő�l 1.27
#endif

#ifdef BLY171S				// BLY171S���[�^�I��
// ��]����`
#define cNref1		(400.0)		// ���x�w�ߍő�l 250[rpm]
#define cN_LOW_MAX	(2.0)		// �Œᑬ�x 2[rpm]		@@ 180529
// �d���E�d�������l
#define I1_LIM		(5.1)		// �d���w�ߍő�l[A] 3.1
#define V1_LIM		(5.0)		// �d���w�ߍő�l[V]12.0 4.5 */
#define NRPM_MIN	(400.)		// �ʑ���Ԃ��n�߂��]��[r/min]IPMSM 400[rpm]
#define m1_LIM		(1.27)		// �ϒ����ő�l 1.27
#endif

//===================================================================
//	�O���[�o���萔��`
//===================================================================
// ******** �萔 ****************************************************
#define	ONEPI	(3.1415926535)
#define	TWOPI	(2.0*3.1415926535)
#define	Ts0	(0.00005)		// �T���v�����O����50��s 0.00005*/
#define	R2Edc0  (2.0/Edc0)		// 2.0/Edc */


#define	DEG030N  (0.523598775583333)	/* ��hole[rad] 30 */
#define	DEG090N  (1.57079632675)	/* ��hole[rad] 90 */
#define	DEG150N  (2.61799387791667)	/* ��hole[rad] 150 */
#define	DEG210N  (3.66519142908333)	/* ��hole[rad] 210 */
#define	DEG270N  (4.71238898025)	/* ��hole[rad] 270 */
#define	DEG330N  (5.75958653141667)	/* ��hole[rad] 330 */

#define	DEG060N  (1.04719755116667)	/* ��hole[rad] 60 */
#define	DEG120N  (2.09439510233333)	/* ��hole[rad] 120 */
#define	DEG180N  (3.1415926535)		/* ��hole[rad] 180 */
#define	DEG240N  (4.18879020466667)	/* ��hole[rad] 240 */
#define	DEG300N  (5.23598775583333)	/* ��hole[rad] 300 */

#define	EMR_DRPM (10000)	/* ��]���ω����ُ�[r/min] */

//#define	FIXPOINT_12	0x1000		// fix point Q12 4096
//#define	FIXPOINT_15F	0x7FFF		// fix point Q15 32767
//#define	FIXPOINT_15	0x8000		// fix point Q15 32768
//#define	FIXPOINT_16	0x10000		// fix point Q16 65536
//#define	FIXPOINT_31	0x80000000	// fix point Q31
//#define	FIXPOINT_30	0x40000000	// fix point Q30
//#define	cROUND_BIT15	0x00008000	// Rounding off
//#define	cRADIAN_90	1.570796327	// 90�x�� radian �ւ̕ϊ��W�� (��/2.)
//#define	PAI2		6.283185306	// ��*2.

//===================================================================
//	�h�^�n�萔��` (not control parameter)
//===================================================================

#define  SW_in()     (PORTE.PORT.BIT.B4)	// MOTOR-1 MOTOR-2 ���� @******************
//#define  LED1_set(d) (PORTA.DR.BIT.B2=(d))
//#define  LED2_set(d) (PORTA.DR.BIT.B3=(d))
//#define  LED3_set(d) (PORTB.DR.BIT.B0=(d))
//#define  LED4_set(d) (PORTB.DR.BIT.B3=(d))
//#define  SW_in()     (PORTE.PORT.BIT.B4)	// MOTOR-1 @******************
//#define  SW_in_m2()  (PORT9.PORT.BIT.B1)	// MOTOR-2 @******************

/* �C�� U <--> W */
#define  W_in()      (PORTB.PORT.BIT.B4)	// MOTOR-1 PB4 @***** S
#define  V_in()      (PORT1.PORT.BIT.B1)	// MOTOR-1 P11 @***** S
#define  U_in()      (PORT1.PORT.BIT.B0)	// MOTOR-1 P10 @***** S
/* �C�� U <--> W */
#define  W_in_m2()   (PORTE.PORT.BIT.B3)	// MOTOR-2 PE3 @***** S
#define  V_in_m2()   (PORTE.PORT.BIT.B1)	// MOTOR-2 PE1 @***** S
#define  U_in_m2()   (PORTE.PORT.BIT.B0)	// MOTOR-2 PE0 @***** S

// file end