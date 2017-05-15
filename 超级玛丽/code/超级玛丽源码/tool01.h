#ifndef __TOOL01
#define __TOOL01

#define ISTEXT(x) ((x)>=32 && (x)<=126)

#define DISTANCE(x,y,x2,y2) (((x)-(x2))*((x)-(x2))+((y)-(y2))*((y)-(y2)))

#define POINT_IN_RECT(x,y,x1,y1,w,h) ((y)>(y1) && (y)<(y1)+(h) \
                                    && (x)>(x1) && (x)<(x1)+(w))

#define IN_AREA(x,x1,w) ( (x)>(x1) && (x)<(x1)+(w) )

#define LINE_ON_LINE(x1,y1,w1,x2,y2,w2) ((y1)==(y2) \
								&& (x1)<(x2)+(w2) && (x1)>(x2)-(w1) )

#define VLINE_IN_RECT(x,y,h,x1,y1,w1,h1) ( (y)+(h)>(y1) && (y)<(y1)+(h1) \
                                    && (x)>(x1) && (x)<(x1)+(w1) )

#define HLINE_IN_RECT(x,y,w,x1,y1,w1,h1) ( (y)>(y1) && (y)<(y1)+(h1) \
                                        && (x)+(w)>(x1) && (x)<(x1)+(w1) )

#define HLINE_ON_RECT(x,y,w,x1,y1,w1,h1) ( (y)>=(y1) && (y)<=(y1)+(h1) \
                                        && (x)+(w)>=(x1) && (x)<=(x1)+(w1) )

#define RECT_HIT_RECT(x,y,w,h,x1,y1,w1,h1) ( (y)+(h)>(y1) && (y)<(y1)+(h1) \
                                        && (x)+(w)>(x1) && (x)<(x1)+(w1) )


int CmpDistance(int x,int y,int x2,int y2,int l)
{
	if(DISTANCE(x,y,x2,y2)<=l*l)
	{
		return 1;
	}
	return 0;
}

int FGetLineJumpCom(char *pchar,FILE *fp)
{
	int ch=-1;
	int i=0;

	//过滤前面的非法字符
	while(!ISTEXT(ch) && !feof(fp))
	{
		ch=fgetc(fp);
	}

	if(!ISTEXT(ch))
	{
		pchar[0]=0;
		return 0;
	}

	//jump comment begin
	if(';' == ch)
	{
		while(ISTEXT(ch) && !feof(fp) )
		{
			ch=fgetc(fp);
		}
		while(!ISTEXT(ch) && !feof(fp))
		{
			ch=fgetc(fp);
		}
	}
	//jump comment end
	
	while(ISTEXT(ch) && !feof(fp))
	{		
		pchar[i]=ch;
		i++;
		ch=fgetc(fp);
	}
	pchar[i]=0;
	return 1;
}

int FGetLine(char *pchar,FILE *fp)
{
	int ch=-1;
	int i=0;

	//过滤前面的非法字符
	while(!ISTEXT(ch) && !feof(fp))
	{
		ch=fgetc(fp);
	}

	if(!ISTEXT(ch))
	{
		pchar[0]=0;
		return 0;
	}
	
	while(ISTEXT(ch) && !feof(fp))
	{		
		pchar[i]=ch;
		i++;
		ch=fgetc(fp);
	}
	pchar[i]=0;
	return 1;
}

#define	KEY_A	65
#define	KEY_B	66
#define	KEY_C	67
#define	KEY_D	68
#define	KEY_E	69
#define	KEY_F	70
#define	KEY_G	71
#define	KEY_H	72
#define	KEY_I	73
#define	KEY_J	74
#define	KEY_K	75
#define	KEY_L	76
#define	KEY_M	77
#define	KEY_N	78
#define	KEY_O	79
#define	KEY_P	80
#define	KEY_Q	81
#define	KEY_R	82
#define	KEY_S	83
#define	KEY_T	84
#define	KEY_U	85
#define	KEY_V	86
#define	KEY_W	87
#define	KEY_X	88
#define	KEY_Y	89
#define	KEY_Z	90

#endif 