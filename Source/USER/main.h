#ifndef MAIN_H
#define MAIN_H

#ifdef MAIN_EXTERN
#   define MAIN_EXT
#else
#   define MAIN_EXT extern 
#endif


#define     EQUITMENT_ID_SEQ     0X0F0F    //  LOCAL ID  SEQ 

//unsigned char equipMentId[8]={0XA1,0XB2,0XC3,0XD5,0XF2,0X02,EQUITMENT_ID_SEQ>>8,EQUITMENT_ID_SEQ&0XFF};
	
#endif

