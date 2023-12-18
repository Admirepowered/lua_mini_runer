// DLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include "string"

using namespace std;
#include <sstream>
 

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ws2_32.lib")
#define DEFLISNUM   50
#define MAXBUFSIZE 102400
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

static CRITICAL_SECTION cs;
char ErrorMsg[] = "Http/1.1 403 Forbidden\r\n\r\n<body><h1>403 Forbidden</h1></body>";
int sign = 2;  // Global variable
FILE *fp1;
typedef int(*FUNA)();
FUNA luaL_newstate;
typedef int(*FUNB)(int a);
FUNB luaL_openlibs;
typedef int(*FUNC)(int a,const char *b);
FUNC luaL_loadstring;
typedef int(*FUND)(int a,int b,int c,int d,int e,int f);
FUND lua_pcallk;
typedef const char *(*FUNE)(int a,int b,int c);
FUNE lua_tolstring;
typedef int(*FUNF)(int a,const char *filename,const char *fmod);
FUNF luaL_loadfilex;
typedef const char *(*FUNG)(int a,const char *string);
FUNG lua_pushstring;
typedef void(*FUNH)(int a,const long string);
FUNH lua_pushinteger;
typedef void(*FUNI)(int a,const char *string);
FUNI lua_getglobal;
typedef void(*FUNJ)(int a,int b);
FUNJ lua_settop;
typedef void(*FUNK)(int a,int b,int c);
FUNK lua_pushcclosure;
typedef void(*FUNL)(int a,const char *c);
FUNL lua_setglobal;
typedef void(*FUNM)(int a);
FUNM lua_close;


void lua_pushcfunction(int L,int f){
lua_pushcclosure (L,f,0);
}
void lua_register(int L,const char *n,int f){
lua_pushcfunction (L, f);
lua_setglobal (L, n);
}


void lua_pop(int L,int n){
lua_settop (L,-n-1);
}



int luaL_loadfile(int a,const char *f){
return(luaL_loadfilex (a,f,"bt"));
}

int lua_pcall(int L,int n,int r,int f){
if(r==0)r=-1;
return(lua_pcallk (L,n,r,f,0,0));
}

int luaL_dofile(int a,const char *f){
luaL_loadfile (a,f);
return(lua_pcall (a,0,-1,0));
}


int luaL_dostring(int a,const char *b){
luaL_loadstring (a,b);
return lua_pcall (a,0,-1,0);
}
void print(const char *a){
fputs(a,fp1);
fflush(fp1);
}
void luaprint(int a){
print(lua_tolstring(a,-1,0));
}



void main(){

	int a=0,b=0;
	//fp1 = fopen(".\\log.txt","w+");
	fp1 = fopen(".\\log.txt","wa+");
	print("Run\n");
	//lua_State *L = luaL_newstate();
	
	HMODULE hMod = LoadLibrary("lua53.dll");//dll路径
	if (hMod)
    {
        luaL_newstate = (FUNA)GetProcAddress(hMod, TEXT("luaL_newstate"));//直接使用原工程函数名 
		luaL_openlibs =  (FUNB)GetProcAddress(hMod, TEXT("luaL_openlibs"));
		luaL_loadstring =  (FUNC)GetProcAddress(hMod, TEXT("luaL_loadstring"));
		lua_pcallk =  (FUND)GetProcAddress(hMod, TEXT("lua_pcallk"));
		lua_tolstring =  (FUNE)GetProcAddress(hMod, TEXT("lua_tolstring"));
		luaL_loadfilex = (FUNF)GetProcAddress(hMod, TEXT("luaL_loadfilex"));
		lua_pushstring = (FUNG)GetProcAddress(hMod, TEXT("lua_pushstring"));
		lua_pushinteger  = (FUNH)GetProcAddress(hMod, TEXT("lua_pushinteger"));
		lua_getglobal= (FUNI)GetProcAddress(hMod, TEXT("lua_getglobal"));//ya ru hanshu
		lua_settop = (FUNJ)GetProcAddress(hMod, TEXT("lua_settop"));//ya ru hanshu
		lua_pushcclosure= (FUNK)GetProcAddress(hMod, TEXT("lua_pushcclosure"));
		lua_setglobal=(FUNL)GetProcAddress(hMod, TEXT("lua_setglobal"));
		lua_close=(FUNM)GetProcAddress(hMod, TEXT("lua_close"));
        if (luaL_newstate != NULL)
        {	

			print("Luatest:\n");
			a=luaL_newstate();
			luaL_openlibs(a);
			//luaL_dostring(a,"package.cpath = \"./PanData/script/lib/?.dll;\"");
			//luaL_dostring(a,"\"package.cpath = \"./PanData/script/lib/?.dll;\"");
			//luaL_dostring(a,"print(\"123\")");

			b=luaL_dofile(a,".\\test.lua");
			string cc = SSTR(b);
			print(cc.data());
			print("\n");

			lua_getglobal(a,"test");
			cc=lua_pushstring(a,"CNM");
			//cc = SSTR(b);
			//print(cc.data());
			//print("\n");

			


			int c = lua_pcall(a,1,1,0);
			print(lua_tolstring(a,-1,0));
			print("\nlll");
			//char *intStr = itoa(a);
			string dd = SSTR(a);
			print(dd.data());
			printf("%s",lua_tolstring(a,-1,0));
			lua_close(a);
            //cout<<addfun(5, 4)<<endl;
        }
        else
        {
			print("Lua Init Failed\n");
        }

    }
	
	
	return;
}

