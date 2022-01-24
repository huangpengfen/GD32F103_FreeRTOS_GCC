#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#ifdef GLOBALVAR_EXTERN
#   define GLOBALVAR_EXT
#else
#   define GLOBALVAR_EXT extern
#endif

#pragma  diag_suppress 177
//-----------------------------------------------------------------------------
#define INT8   char
#define UINT8  unsigned char
#define INT16  short
#define UINT16 unsigned short
#define INT32  int
#define UINT32 unsigned int
#define s64_t
#define u64_t
#define f32_t float


#ifndef FALSE
//    #define FALSE 0
#endif

#ifndef TRUE
//    #define TRUE 1
#endif

#ifndef NULL
    #define NULL (void *)0
#endif

//�����궨��
#define FlashVersion            0x00000001
//-----------------------------------------------------------------------------
//���ڳ�ʼ��
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define assert_t(t) if(!(t)){return FALSE;}         //ΪTRUE�򲻴���
#endif

