/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2009 Hex-Rays <info@hex-rays.com>

   Detected compiler: Visual C++
*/

#include <windows.h>
#include <defs.h>


//-------------------------------------------------------------------------
// Data declarations

extern char cp[]; // idb
extern char Format[]; // idb
extern int dword_402128; // weak
extern int dword_40212C; // weak
extern char byte_402130; // weak
extern char aC[4]; // idb
extern char asc_402138[2]; // idb
extern int dword_40213C; // weak
extern int dword_402140; // weak
extern int dword_402144; // weak
extern int dword_402148; // weak
extern int dword_40214C; // weak
extern _UNKNOWN unk_402208; // weak
extern _UNKNOWN unk_402210; // weak
extern int __security_cookie; // weak

//-------------------------------------------------------------------------
// Function declarations

int __cdecl main(int argc, const char **argv, const char **envp);
int (*__cdecl sub_40176E())(void);
int (*__cdecl sub_401794())(void);
// void *__cdecl memset(void *Dst, int Val, size_t Size);
// int printf(const char *Format, ...);
// int __stdcall connect(SOCKET s, const struct sockaddr *name, int namelen);
// int __stdcall WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
// unsigned __int32 __stdcall inet_addr(const char *cp);
// u_short __stdcall htons(u_short hostshort);
// int __stdcall recv(SOCKET s, char *buf, int len, int flags);
// SOCKET __stdcall socket(int af, int type, int protocol);
// int __stdcall send(SOCKET s, const char *buf, int len, int flags);


//----- (00401000) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  SOCKET v3; // edi@1
  signed int v4; // esi@1
  signed int v5; // esi@3
  int v6; // eax@5
  signed int v7; // esi@5
  int v8; // eax@8
  int v9; // eax@10
  int v10; // eax@12
  int v11; // eax@14
  int *v12; // eax@17
  char v13; // cl@18
  int v14; // [sp+Ch] [bp-3DCh]@1
  struct sockaddr name; // [sp+10h] [bp-3D8h]@1
  struct WSAData WSAData; // [sp+20h] [bp-3C8h]@1
  char v17; // [sp+1B4h] [bp-234h]@1
  int v18; // [sp+1B5h] [bp-233h]@1
  __int16 v19; // [sp+1B9h] [bp-22Fh]@1
  char v20; // [sp+1BBh] [bp-22Dh]@1
  int v21; // [sp+1BCh] [bp-22Ch]@5
  int v22; // [sp+1C0h] [bp-228h]@5
  int v23; // [sp+1C4h] [bp-224h]@5
  int v24; // [sp+1C8h] [bp-220h]@5
  int v25; // [sp+1CCh] [bp-21Ch]@5
  int v26; // [sp+1D4h] [bp-214h]@1
  int v27; // [sp+1D8h] [bp-210h]@1
  char v28; // [sp+1DCh] [bp-20Ch]@1
  char buf; // [sp+1E0h] [bp-208h]@1
  char Dst; // [sp+1E1h] [bp-207h]@1
  unsigned int v31; // [sp+3E4h] [bp-4h]@1

  v31 = (unsigned int)&v14 ^ __security_cookie;
  buf = 0;
  memset(&Dst, 0, 0x1FFu);
  WSAStartup(0x202u, &WSAData);
  v3 = socket(2, 1, 6);
  name.sa_family = 2;
  *(_DWORD *)&name.sa_data[2] = inet_addr("159.253.22.174");
  *(_WORD *)&name.sa_data[0] = htons(0xC41u);
  connect(v3, &name, 16);
  recv(v3, &buf, 17, 8);
  printf("%s ", &buf);
  v26 = 0x6361685F; //dword_402128;
  v18 = 0;
  v19 = 0;
  v20 = 0;
  LOBYTE(v14) = 0;
  *(_WORD *)((char *)&v14 + 1) = 0;
  BYTE3(v14) = 0;
  v27 = 0x5F656D6B; //dword_40212C;
  v28 = 0;
  v17 = 0;
  recv(v3, &v17, 8, 8);
  recv(v3, &buf, 2, 8);
  recv(v3, (char *)&v14, 4, 8);
  v4 = 0;
  do
  {
    *(&v17 + v4) ^= *((_BYTE *)&v26 + v4);
    printf("%c ", *(&v17 + v4++));
  }
  while ( v4 < 8 );
  printf("\n");
  v5 = 0;
  do
    printf("%c ", *((_BYTE *)&v14 + v5++));
  while ( v5 < 4 );
  printf("\n");
  v21 = dword_40213C;
  v22 = dword_402140;
  v23 = dword_402144;
  v24 = dword_402148;
  v25 = dword_40214C;
  v6 = 0;
  *(int *)((char *)&v25 + 3) = v14;
  v7 = 0;
  while ( 1 )
  {
    if ( v6 == 8 )
      v6 = 0;
    *((_BYTE *)&v21 + v7) ^= *(&v17 + v6);
    v8 = v6 + 1;
    if ( v8 == 8 )
      v8 = 0;
    *((_BYTE *)&v21 + v7 + 1) ^= *(&v17 + v8);
    v9 = v8 + 1;
    if ( v9 == 8 )
      v9 = 0;
    *((_BYTE *)&v21 + v7 + 2) ^= *(&v17 + v9);
    v10 = v9 + 1;
    if ( v10 == 8 )
      v10 = 0;
    *((_BYTE *)&v21 + v7 + 3) ^= *(&v17 + v10);
    v11 = v10 + 1;
    if ( v11 == 8 )
      v11 = 0;
    *((_BYTE *)&v22 + v7) ^= *(&v17 + v11);
    v7 += 5;
    v6 = v11 + 1;
    if ( v7 >= 25 )
    {
      v12 = &v21;
      do
      {
        v13 = *(_BYTE *)v12;
        v12 = (int *)((char *)v12 + 1);
      }
      while ( v13 );
      send(v3, (const char *)&v21, (char *)v12 - ((char *)&v21 + 1), 0);
      recv(v3, &buf, 50, 0);
      printf("%s ", &buf);
      while ( 1 )
        ;
    }
  }
}
// 402128: using guessed type int dword_402128;
// 40212C: using guessed type int dword_40212C;
// 402130: using guessed type char byte_402130;
// 40213C: using guessed type int dword_40213C;
// 402140: using guessed type int dword_402140;
// 402144: using guessed type int dword_402144;
// 402148: using guessed type int dword_402148;
// 40214C: using guessed type int dword_40214C;
// 403000: using guessed type int __security_cookie;

//----- (0040176E) --------------------------------------------------------
int (*__cdecl sub_40176E())(void)
{
  int (*result)(void); // eax@1
  unsigned int v1; // edi@1

  result = (int (*)(void))&unk_402208;
  v1 = (unsigned int)&unk_402208;
  if ( &unk_402208 < &unk_402208 )
  {
    do
    {
      result = *(int (**)(void))v1;
      if ( *(_DWORD *)v1 )
        result = (int (*)(void))result();
      v1 += 4;
    }
    while ( v1 < (unsigned int)&unk_402208 );
  }
  return result;
}

//----- (00401794) --------------------------------------------------------
int (*__cdecl sub_401794())(void)
{
  int (*result)(void); // eax@1
  unsigned int v1; // edi@1

  result = (int (*)(void))&unk_402210;
  v1 = (unsigned int)&unk_402210;
  if ( &unk_402210 < &unk_402210 )
  {
    do
    {
      result = *(int (**)(void))v1;
      if ( *(_DWORD *)v1 )
        result = (int (*)(void))result();
      v1 += 4;
    }
    while ( v1 < (unsigned int)&unk_402210 );
  }
  return result;
}

// ALL OK, 3 function(s) have been successfully decompiled
