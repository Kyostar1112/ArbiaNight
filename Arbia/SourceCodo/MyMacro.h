#ifndef _MY_MACRO_H_	//�ݸٰ�޶ް��.
#define _MY_MACRO_H_


//============================================================
//	ϸ�.
//============================================================

//�װү����.
#define ERR_MSG(str,title)	{MessageBox(NULL,str,title,MB_OK);}


//���.
#define SAFE_RELEASE(x)		if(x){(x)->Release();	(x)=NULL;}
#define SAFE_DELETE(p)		{ if(p) { delete (p);   (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=NULL; } }

//���ް�ޓ���.
//�����Ă����.
#define GETKEY_STAY(x) if (GetAsyncKeyState(x) & 0x8000)	
//�������Ƃ�����.
#define GETKEY_DOWN(x) if (GetAsyncKeyState(x) & 0x0001)

#endif//#ifndef _MY_MACRO_H_