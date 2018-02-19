#ifndef _MY_MACRO_H_	//インクルードガード.
#define _MY_MACRO_H_


//============================================================
//	マクロ.
//============================================================

//エラーメッセージ.
#define ERR_MSG(str,title)	{MessageBox(NULL,str,title,MB_OK);}


//解放.

#define SAFE_RELEASE(x)		{ if(x) {(x)->Release();(x)=nullptr; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);   (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=nullptr; } }

//キーボード入力.
//押している間.
#define GETKEY_STAY(x) if (GetAsyncKeyState(x) & 0x8000)	
//押したときだけ.
#define GETKEY_DOWN(x) if (GetAsyncKeyState(x) & 0x0001)

#endif//#ifndef _MY_MACRO_H_