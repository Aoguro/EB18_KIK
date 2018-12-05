/***********************************************************************/
/*                                                                     */
/*  FILE        :iolib_inv.c                                           */
/*  DATE        :Thu, Aug 23, 2012                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :RX62T                                                 */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.53).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
                  
#include "iodefine.h"
//#include "iodefine_RPDL.h"
#include <machine.h>
#include "iolib.h"
//#include "R_PG_default.h"
#include "define.h"
#include "testt.h"


static int  _inv_peak     = 2300;
static int  _inv_hpeak    = 2200; //1100;
static int  _inv_deadtime = 50;

int	itemp_u = 0;
int	itemp_v = 0;
int	itemp_w = 0;

int TMP_T = 0;
int TMP_P = 0;
int TMP_HP = 0;
int TMP_DEAD = 0;
unsigned char TMP_I = 0;

void  inverter_init(int fs, int dt)		// fs : �����qns�r�Adt�F�f�b�h�^�C���ins�j
{
    int		i_period;
    int		_inv_hcc;			
    
   // i_period = cIMCLK_FRQ * fs / 1000;		// 4800
     i_period = (int)((48000000.0f)/fs-1);
   // _inv_deadtime = (int)(cIMCLK_FRQ*((float)dt/1000.0));	//cIMCLK_FRQ=96(MHz)
    _inv_deadtime =50;
    _inv_hcc = i_period >> 1;			// 2400
   //_inv_peak   = i_period - _inv_deadtime - _inv_deadtime; // �����炪������
    _inv_peak   = i_period - _inv_deadtime;	// �o�O
    _inv_hpeak  = _inv_peak>>1;
    
    TMP_T = i_period;
    TMP_P = _inv_peak;
    TMP_HP = _inv_hpeak;
    TMP_DEAD = _inv_deadtime;
//*************************************************
// MTU3 MTU4 ����PWM���[�h������
// Timer_Set_MTU;	// MTU3,MTU4 ������
//*************************************************  
    //Wakeup MTU3
    MSTP(MTU3)=0;				// ���W���[���X�g�b�v���� MTU3,MTU4
    MTU.TSTRA.BIT.CST3 = 0;			// MTU3�^�C�}�\�J�E���^(TCNT)�̓����~
    MTU.TSTRA.BIT.CST4 = 0;			// MTU4�^�C�}�\�J�E���^(TCNT)�̓����~
    // Counts on PCLK/1
     MTU3.TCR.BYTE=0x00;			// @@? 180523 AKI
     MTU4.TCR.BYTE=0x00;			// @@? 180523 AKI
    // Counts on PCLK/1�@�^�C�}�[�R���g���[�����W�X�^(TCR)�ݒ�
    //MTU3.TCR.BIT.TPSC=0x0;			// TCNT�̃N���A�֎~
    //MTU3.TCR.BIT.CCLR=0x0;			// TCNT�͗����オ��G�b�W�ŃJ�E���g
    //MTU3.TCR.BIT.CKEG=0x1;			// TCNT�͓����N���b�NICLK�ŃJ�E���g(0x01�FICLK/4)
    //MTU4.TCR.BIT.TPSC=0x0;			// TCNT�̃N���A�֎~
    //MTU4.TCR.BIT.CCLR=0x0;			// TCNT�͗����オ��G�b�W�ŃJ�E���g
    //MTU4.TCR.BIT.CKEG=0x1;			// TCNT�͓����N���b�NICLK�ŃJ�E���g(0x01�FICLK/4)
    // Initialization of the 16bit counter
    MTU3.TCNT = _inv_deadtime; 			// MTU3 �J�E���^�����l dt
    MTU4.TCNT = 0;				// MTU4 �J�E���^�����l 0
    
    //PWM Duty set
    MTU3.TGRB =i_period/2 ;		// 
    MTU4.TGRA =i_period/2 ; 
    MTU4.TGRB =i_period/2 ; 
    MTU3.TGRD =i_period/2 ;		// �o�b�t�@���W�X�^
    MTU4.TGRC =i_period/2 ;
    MTU4.TGRD =i_period/2 ; 
    //MTU3.TGRB = duty;				// i_period*0.46;//
    //MTU4.TGRA = duty-500;			// i_period*0.46-500;//
    //MTU4.TGRB = duty-1000;			// i_period*0.46-1000;//
    //MTU3.TGRD = duty;				// i_period*0.46;//
    //MTU4.TGRC = duty-500;			// i_period*0.46-500;//
   // MTU4.TGRD = duty-1000;			// i_period*0.46-1000;//
   
    // Dead time set 
    MTU.TDDRA = _inv_deadtime; 			// �f�b�h�^�C���f�[�^���W�X�^
   
   // half the PWM carrier cycle 
    MTU.TCBRA = i_period;			// �R���y�A�}�b�`���W�X�^
    MTU.TCDRA = i_period;			// �o�b�t�@���W�X�^
   // half the PWM carrier cycle + Dead time
    MTU3.TGRA = i_period + _inv_deadtime;	// �R���y�A�}�b�`���W�X�^
    MTU3.TGRC = i_period + _inv_deadtime;	// �o�b�t�@���W�X�^
    // Timer Output control
    MTU.TOCR1A.BIT.PSYE = 1;			// �g�O���o�͋���
    MTU.TOCR1A.BIT.TOCL=0;			// OLSN�r�b�g�AOLSP�r�b�g�ւ̏������݂�����
    MTU.TOCR1A.BIT.OLSP=1;			// �����̏o�� ����LOW �A�N�e�B�uHIGH
    MTU.TOCR1A.BIT.OLSN=1;			// �t���̏o�� ����LOW �A�N�e�B�uHIGH
    // Set PWM mode 3
    MTU3.TMDR.BIT.MD = 0xf;			// ����PWM���[�h�R�@�R�E�J�œ]�� 0604
    MTU4.TMDR.BYTE = 0x00;			// @@? 180523
    // Buffer is enabled
    MTU3.TMDR.BIT.BFA = 1;			// TGRA , TGRC �o�b�t�@����
    MTU3.TMDR.BIT.BFB = 1;			// TGRB , TGRD �o�b�t�@����
    MTU4.TMDR.BIT.BFA = 0;			// @@? 180523
    MTU4.TMDR.BIT.BFB = 0;			// @@? 180523
    // �^�C�}�A�E�g�v�b�g�}�X�^�C�l�[�u�����W�X�^�̐ݒ�
    MTU.TOERA.BIT.OE3B=1;
    MTU.TOERA.BIT.OE4A=1;
    MTU.TOERA.BIT.OE4B=1;
    MTU.TOERA.BIT.OE3D=1;
    MTU.TOERA.BIT.OE4C=1;
    MTU.TOERA.BIT.OE4D=1;
    MTU.TSTRA.BIT.CST3 = 1;			// MTU3�^�C�}�\�J�E���^(TCNT)�̓���C�l�[�u��
    MTU.TSTRA.BIT.CST4 = 1;			// MTU4�^�C�}�\�J�E���^(TCNT)�̓���C�l�[�u��
//*************************************************
// MTU6 MTU7 ����PWM���[�h������
// Timer_Set_MTU;	// MTU3,MTU4 ������
//*************************************************  
    //Wakeup MTU6
    MSTP(MTU6)=0;
    MTU.TSTRB.BIT.CST6 = 0;			// MTU6�^�C�}�\�J�E���^(TCNT)�̓����~
    MTU.TSTRB.BIT.CST7 = 0;			// MTU7�^�C�}�\�J�E���^(TCNT)�̓����~
    // Counts on PCLK/1�@�^�C�}�[�R���g���[�����W�X�^(TCR)�ݒ�
    MTU6.TCR.BYTE=0x00;				// @@? 180523
    MTU7.TCR.BYTE=0x00;				// @@? 180523
    // Initialization of the 16bit counter
    MTU6.TCNT = _inv_deadtime; 			// MTU6 �J�E���^�����l dt
    MTU7.TCNT = 0;				// MTU7 �J�E���^�����l 0
   
    // set PWM Duty    
    MTU6.TGRB = i_period/2;			// �R���y�A�}�b�`���W�X�^ 
    MTU7.TGRA = i_period/2; 
    MTU7.TGRB = i_period/2;
    MTU6.TGRD = i_period/2;  //B 0629
    MTU7.TGRC = i_period/2; 
    MTU7.TGRD = i_period/2; 
    //MTU6.TGRB = duty-2000;			// i_period*0.46-2000=200
    //MTU7.TGRA = duty-1000;			// i_period*0.46-1000=1200
    //MTU7.TGRB = duty-500;			// i_period*0.46-500=1700
    //MTU6.TGRD = duty-2000;			// i_period*0.46-2000=200
    //MTU7.TGRC = duty-1000;			// i_period*0.46-1000=1200
    //MTU7.TGRD = duty-500;			// i_period*0.46-500=1700
    
     // Dead time 
    MTU.TDDRB = _inv_deadtime; 			// �f�b�h�^�C���f�[�^���W�X�^
    // half the PWM carrier cycle
    MTU.TCBRB = i_period;			// �R���y�A�}�b�`���W�X�^
    MTU.TCDRB = i_period;			// �o�b�t�@���W�X�^
    // half the PWM carrier cycle + Dead time
    MTU6.TGRA = i_period + _inv_deadtime;	// �R���y�A�}�b�`���W�X�^
    MTU6.TGRC = i_period + _inv_deadtime;	// �o�b�t�@���W�X�^
    // Timer Output control
    MTU.TOCR1B.BIT.PSYE = 1;			// �g�O���o�͋���
    MTU.TOCR1B.BIT.TOCL=0;			// OLSN�r�b�g�AOLSP�r�b�g�ւ̏������݂�����
    MTU.TOCR1B.BIT.OLSP=1;			// �����̏o�� ����LOW �A�N�e�B�uHIGH
    MTU.TOCR1B.BIT.OLSN=1;			// �t���̏o�� ����LOW �A�N�e�B�uHIGH
    // Set PWM mode 3
    MTU6.TMDR.BIT.MD= 0xf;//0604
    MTU7.TMDR.BYTE = 0x00;
    // Buffer is enabled
    MTU6.TMDR.BIT.BFA = 1;			// TGRA , TGRC �o�b�t�@����
    MTU6.TMDR.BIT.BFB = 1;			// TGRB , TGRD �o�b�t�@����
    MTU7.TMDR.BIT.BFA = 0;			// @@? 180523 AKI
    MTU7.TMDR.BIT.BFB = 0;			// @@? 180523 AKI
    // �^�C�}�A�E�g�v�b�g�}�X�^�C�l�[�u�����W�X�^�̐ݒ�
    MTU.TOERB.BIT.OE6B = 1;
    MTU.TOERB.BIT.OE7A = 1;
    MTU.TOERB.BIT.OE7B = 1;
    MTU.TOERB.BIT.OE6D = 1;
    MTU.TOERB.BIT.OE7C = 1;
    MTU.TOERB.BIT.OE7D = 1;
    
    MTU.TSTRB.BIT.CST6 = 1;			// MTU6�^�C�}�\�J�E���^(TCNT)�̓���C�l�[�u��
    MTU.TSTRB.BIT.CST7 = 1;			// MTU7�^�C�}�\�J�E���^(TCNT)�̓���C�l�[�u��
    

/*************************************************/
    // �����ݒ�
     //MTU.TSYRA.BYTE = 0xC6;	// MTU1��MTU2,MTU3��MTU4�𓯊��ݒ�
     MTU.TSYRA.BYTE = 0x06;	// MTU1��MTU2�𓯊��ݒ� 0604
    //MTU.TSYRB.BYTE = 0xC0;	// MTU6��MTU7�𓯊��ݒ� 0604   
    // �O���M���ŏo�͑���؂�ւ��ݒ�
    MTU.TGCRA.BIT.FB = 0;
    //*****************************
    //*      MTU �L���v�`���ݒ�   *
    //*******����������************
    // MOTOR-1
    MTU0.TCR.BYTE = 0x03;	// ��MTU0, TCNT�̃N���A�֎~�C1/64 �v���X�P�[��
    //MTU0.TCR.BYTE = 0x06;	// ��MTU0, TCNT�̃N���A�֎~�C�O���N���b�N�FMTCLKC �[�q���͂ŃJ�E���g
    MTU0.TIORH.BYTE = 0x0A;	// ��MTIOC0A,��MTIOC0B ���G�b�W�ŃC���v�b�g�L���v�`��0xA0
    MTU0.TIORL.BYTE = 0xAA;	// ��MTIOC0C, ���G�b�W�ŃC���v�b�g�L���v�`��
    //R_PG_Timer_StartCount_MTU_U0_C0();	// �^�C�}�[START
     // MOTOR-2
    MTU1.TCR.BYTE = 0x03;	// ��MTU0, TCNT�̃N���A�֎~�C1/64 �v���X�P�[�� 
    MTU2.TCR.BYTE = 0x03;	// ��MTU1, TCNT�̃N���A�֎~�C1/64 �v���X�P�[��
    //MTU1.TCR.BYTE = 0x06;	// ��MTU0, TCNT�̃N���A�֎~�C1/256 �v���X�P�[�� 
    //MTU2.TCR.BYTE = 0x06;	// ��MTU1, TCNT�̃N���A�֎~�C�O���N���b�N�FMTCLKC �[�q���͂ŃJ�E���g
    MTU1.TIOR.BYTE = 0xAA;	// ��MTIOC1A,��MTIOC1B ���G�b�W�ŃC���v�b�g�L���v�`��
    MTU2.TIOR.BYTE = 0x0A;	// ��MTIOC2A ���G�b�W�ŃC���v�b�g�L���v�`��
    // Count Start
    MTU.TSTRA.BYTE = 0x01;	// �^�C�}�[START MTU0  0526 0x01
    MTU.TCSYSTR.BYTE = 0x7B;	// MTU1,2��MTU3,4��MTU6,7�𓯎��X�^�[�g�ݒ�
   // MTU.TCSYSTR.BYTE = 0x60;	// MTU1,2��MTU3,4��MTU6,7�𓯎��X�^�[�g�ݒ�
}

void  inverter_set_uvw(float u, float v, float w, unsigned short YT_cnt, unsigned short MN)
{
    int   itemp;
    
    //countc1++;
    
    /* U���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-u+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
    		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU3.TGRB = itemp;	// M-1 PWM�o�͂P�@�R���y�A���W�X�^	@*****
	MTU3.TGRD = itemp;
    }
    else
    {
	MTU6.TGRB = itemp;
	MTU6.TGRD = itemp;// M-2 PWM�o�͂P�@�R���y�A���W�X�^	@*****
    }
    itemp_u = itemp;
    
   /* V���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-v+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
    		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU4.TGRA = itemp;	// M-1 PWM�o�͂Q�@�R���y�A���W�X�^	@*****
	MTU4.TGRC = itemp;

    }
    else
    {
	MTU7.TGRA = itemp;	// M-2 PWM�o�͂Q�@�R���y�A���W�X�^	@*****
	MTU7.TGRC = itemp;
	
    }
    itemp_v = itemp;    
    
    
   /* W���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-w+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
  		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU4.TGRB = itemp;	// M-1 PWM�o�͂R�@�R���y�A���W�X�^	@*****
	MTU4.TGRD = itemp;
    }
    else
    {
	MTU7.TGRB = itemp;	// M-2 PWM�o�͂R�@�R���y�A���W�X�^	@*****
	MTU7.TGRD = itemp;
    }
    itemp_w = itemp;        
    
}
void  inverter_set_uvw_2(float u, float v, float w, unsigned short YT_cnt_2, unsigned short MN)
{
    int   itemp;
    
   // countc2++;
    
    /* U���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-u+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt_2==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
    		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU3.TGRB = itemp;	// M-1 PWM�o�͂P�@�R���y�A���W�X�^	@*****
	MTU3.TGRD = itemp;
    }
    else
    {
	MTU6.TGRB = itemp;
	MTU6.TGRD = itemp;// M-2 PWM�o�͂P�@�R���y�A���W�X�^	@*****
    }
    itemp_u = itemp;
    
   /* V���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-v+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt_2==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
    		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU4.TGRA = itemp;	// M-1 PWM�o�͂Q�@�R���y�A���W�X�^	@*****
	MTU4.TGRC = itemp;

    }
    else
    {
	MTU7.TGRA = itemp;	// M-2 PWM�o�͂Q�@�R���y�A���W�X�^	@*****
	MTU7.TGRC = itemp;
	
    }
    itemp_v = itemp;    
    
    
   /* W���̃^�C�}�[�Z�b�g */
    itemp = (int) ((-w+1.0)*((float)_inv_hpeak)+((float)_inv_deadtime));
    
    if(YT_cnt_2==1)  /* �J�F������Ⴂ */
    {
    	if (itemp>(_inv_peak))
	{  itemp = _inv_peak;  }
    	else
	{
		if (itemp<0){  itemp = 0;  }
    		else{ }
	}
    }
    else  /* �R�F��������� */
    {
    	if (itemp>(_inv_peak + _inv_deadtime))
	{  itemp = _inv_peak + _inv_deadtime;  }
    	else
	{
		if (itemp<_inv_deadtime){  itemp = _inv_deadtime;  }
  		else{ }
	}   
    }
    if(MN == 0)
    {
	MTU4.TGRB = itemp;	// M-1 PWM�o�͂R�@�R���y�A���W�X�^	@*****
	MTU4.TGRD = itemp;
    }
    else
    {
	MTU7.TGRB = itemp;	// M-2 PWM�o�͂R�@�R���y�A���W�X�^	@*****
	MTU7.TGRD = itemp;
    }
    itemp_w = itemp;        
    
}

void  inverter_start_int(void)
{
//  MTU3
    // TGIEA of MTU3 interrupt is enabled
   // MTU3.TIER.BIT.TGIEA = 1;	// MPU3 TGIA ���� vect=129
  //  IEN(MTU3,TGIA3) = 1;	// MPU3 �R������ TGIA3 ����
   // IPR(MTU3,TGIA3) = 15;	// �v���C�I���e�B
   // set_psw(0x00010000);
    //IEN(MTU3,TCIV3) = 1;	// MPU3 �R������ TGIA3 ����
    //IPR(MTU3,TCIV3) = 3;	// �v���C�I���e�B
    
    
    MTU4.TIER.BIT.TCIEV = 1;	// MPU4 TCIEV ���� vect=134
   
    IEN(MTU4,TCIV4) = 1;	// MPU4 �R�J������ TCIV4 ����
    IPR(MTU4,TCIV4) = 15;	// �v���C�I���e�B*/
    /*IEN(MTU4,TGIA4) = 1;	// MPU4 �J������ TGIA4 ����
    IPR(MTU4,TGIA4) = 3;	// �v���C�I���e�B
   // MTU4.TIER.BIT.TTGE2=1; */ 
    
   // MTU6.TIER.BIT.TGIEA = 1;	// MPU6 TGIA ���� vect=142
   // IEN(MTU6,TGIA6) = 1;	// MPU6 �R������ TGIA6 ����
   // IPR(MTU6,TGIA6) = 15;	// �v���C�I���e�B
    //set_psw(0x00010000);
    
    MTU7.TIER.BIT.TCIEV = 1;	// MPU7 �R�J�����݁@TCIEV ���� vect=149
   
    IEN(MTU7,TCIV7) = 1;	// MPU7 �J������ TCIV7 ����
    IPR(MTU7,TCIV7) = 15;	// �v���C�I���e�B
    /*IEN(MTU7,TGIA7) = 1;	// MPU7 �J������ TGIA7 ����
    IPR(MTU7,TGIA7) = 3;	// �v���C�I���e�B
    MTU7.TIER.BIT.TTGE2=1; */
}

void  inverter_stop_int(void)
{
//  TGIEA of MTU3 interrupt is desabled
   /* MTU3.TIER.BIT.TGIEA = 0;	// MPU3 TGIA �֎~
    MTU4.TIER.BIT.TGIEA = 0;	// MPU4 TGIA �֎~
    MTU6.TIER.BIT.TGIEA = 0;	// MPU6 TGIA �֎~
    MTU7.TIER.BIT.TGIEA = 0;	// MPU7 TGIA �֎~*/
//  ICU.IER[0x10].BIT.IEN1  =0;	// MPU3�R������ TGIA3 �֎~
//  ICU.IER[0x11].BIT.IEN2  =0;	// MPU3�J������ TCIV4 �֎~
//  ICU.IER[0x11].BIT.IEN6  =0;	// MPU6�R������ TGIA6 �֎~
//  ICU.IER[0x13].BIT.IEN1  =0;	// MPU6�J������ TCIV7 �֎~
    MTU3.TGRB =0.1;		// 
    MTU4.TGRA =0.1 ; 
    MTU4.TGRB =0.1 ; 
    MTU3.TGRD =0.1 ;		
    MTU4.TGRC =0.1 ;
    MTU4.TGRD =0.1 ; 
    MTU3.TGRA=0.1;
    MTU3.TGRC=0.1;
}


