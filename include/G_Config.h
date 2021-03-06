#ifndef G_CONFIG_H
#define G_CONFIG_H

/*
	The config that the Engine need.
*/

// Record all the information about a God.

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <utility>

using std::queue;
using std::map;
using std::set;
using std::vector;
using std::pair;
using std::multimap;
using std::multiset;

class G_Object;
class G_Input;
class G_Output;
class G_World;
class G_Sprit;
class G_Eye;

// Config about World.
typedef int WORLD_NUM;

// Config about Object.
typedef int OBJECT_TYPE;
typedef int OBJECT_NUM;

const int OBJ_KIND=4;

const OBJECT_TYPE OBJ_IN =0;
const OBJECT_TYPE OBJ_OUT=1;
const OBJECT_TYPE OBJ_SPR=2;
const OBJECT_TYPE OBJ_EYE=3;

// Config about keyboard.
typedef int KEY_ID;
typedef int KEY_STA;

// Config about mouse.
const int MOU_BUTTON_NUM=4;

// Config about time.
const int USEC_PER_SEC=1000000;
struct STR_TIME
{
	int  num;
	long sec,usec;
	long sec_per,usec_per;				// The period of time point.
	bool is_use;
	
	STR_TIME(int n=0,long a=0,long b=0,long c=0,long long d=0)
	{
		num=n;
		is_use=1;
		sec=a;
		usec=b;
		sec_per=c;
		usec_per=d;
		
		if(usec>=USEC_PER_SEC)
		{
			sec+=usec/USEC_PER_SEC;
			usec%=USEC_PER_SEC;
		}
		
		if(usec_per>=USEC_PER_SEC)
		{
			sec_per+=usec_per/USEC_PER_SEC;
			usec_per%=USEC_PER_SEC;
		}
	}
	
	bool operator < (const STR_TIME & b) const
	{
		if(sec==b.sec)
			return usec<b.usec;
		return sec<b.sec;
	}
	
	bool add()
	{
		if(sec_per<0 || usec_per<0)
			return 0;
		
		usec+=usec_per;
		sec+=sec_per;
		
		if(usec>=USEC_PER_SEC)
		{
			sec+=usec/USEC_PER_SEC;
			usec%=USEC_PER_SEC;
		}
		
		return 1;
	}
};

// Config about fonts.
const char * const DEFAULT_FONT="r16";

// Config aobout output.
const int TOP_LEF=0;
const int TOP_MID=1;
const int TOP_RIG=2;
const int MID_LEF=3;
const int MID_MID=4;
const int MID_RIG=5;
const int LOW_LEF=6;
const int LOW_MID=7;
const int LOW_RIG=8;

// Config about window.

typedef int COLOR;

struct S_COLOR
{
	unsigned short r,g,b;
	
	S_COLOR(unsigned short _r=0,unsigned short _g=0,unsigned short _b=0):r(_r),g(_g),b(_b) {}
	S_COLOR(COLOR col)
	{
		r=col>>16;
		g=(col>>8) & ((1<<8)-1);
		b=col & ((1<<8)-1);
	}

	operator COLOR() { return (r<<16)|(g<<8)|b; }
};

const COLOR TRANS_COLOR=1;
const COLOR COL_WHITE=16777215;
const COLOR COL_BLACK=0;

struct POS
{
	int x,y;
	
	POS(int _x=0,int _y=0):x(_x),y(_y) {}
};

struct SIZE
{
	unsigned int w,h;
	
	SIZE(unsigned int _w=0,unsigned int _h=0):w(_w),h(_h) {}
};

struct SPEED
{
	double vx,vy;
	
	SPEED(double a=0,double b=0):vx(a),vy(b)
	{}
};

struct POWER
{
	double fx,fy;
	
	POWER(double a=0,double b=0):fx(a),fy(b)
	{}
};

const double eps=1e-8;

inline int sgn(double x)
{
	return x<-eps ? -1 : x>eps;
}

// Config about Message.
typedef int MES_TYPE;

// Need C++ 11 there.
struct MESSAGE
{
	MES_TYPE type;
	int num[8];
	double dnum[4];
	void *p;
};

// Config about Event.
typedef MESSAGE EVENT;

// Define of message type:

// Base message type:
const MES_TYPE M_NULL=0;
const MES_TYPE M_QUIT=1;

// Input message type:
const MES_TYPE M_KEY_PRE=100;
const MES_TYPE M_KEY_REL=101;
const MES_TYPE M_MOU_PRE=102;
const MES_TYPE M_MOU_REL=103;
const MES_TYPE M_MOU_MOV=104;

const MES_TYPE M_TIM_PER=110;

// Output message type:
const MES_TYPE M_EXPOSE =200;
const MES_TYPE M_BUF_SHW=201;
const MES_TYPE M_LIN_SET=202;
const MES_TYPE M_FIL_SET=203;
const MES_TYPE M_FON_SET=213;
const MES_TYPE M_FOR_COL=204;
const MES_TYPE M_BAC_COL=205;
const MES_TYPE M_STR_DRW=206;
const MES_TYPE M_POI_DRW=207;
const MES_TYPE M_LIN_DRW=208;
const MES_TYPE M_REC_DRW=209;
const MES_TYPE M_CIR_DRW=210;
const MES_TYPE M_REC_FIL=212;
const MES_TYPE M_PIC_DRW=214;

// Eye message type:
const MES_TYPE M_PAINT  =300;

// Button message type:
const MES_TYPE M_BUT_ON =400;

#endif
