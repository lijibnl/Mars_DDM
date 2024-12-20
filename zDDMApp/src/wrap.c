unsigned int reverseBits(int nobits, unsigned int num) 
{  
	unsigned int reverse_num = 0; 
	int i; 
	for (i = 0; i < nobits; i++) 
	{ 
		if((num & (1 << i))) 
		reverse_num |= 1 << ((nobits - 1) - i); 
	} 
	return reverse_num; 
} 


/******************************************************************
* Routines to assemble SPI strings from arrays, and to talk to 
* ASIC via SPI port.
*******************************************************************/

int wrap(void *pscal){
    int index, chip, tmp, chan, j, chn;
    int NCHIPS;
    NCHIPS=zDDM_NCHIPS;
    unsigned int tword,tword2;

    for(chip=0;chip<NCHIPS;chip++){

	/* do globals first */
	j=0;
	tword=0;
	tword=globalstr[chip].tm &1;  /*
/*1 */	j++;	
	tword=tword<<1|globalstr[chip].sbm &1;
/*2 */ 	j++;
	tword=tword<<1|globalstr[chip].saux &1;
/*3 */	j++;
	tword=tword<<1|globalstr[chip].sp &1;
/*4 */	j++;
	tword=tword<<1|globalstr[chip].slh &1;
/*5 */	j++;
	tword=tword<<2|reverseBits(2,globalstr[chip].g) &3;
/*7 */	j+=2;
	tword=tword<<5|reverseBits(5,globalstr[chip].c) &31;
/*12 */	j+=5;
	tword=tword<<2|reverseBits(2,globalstr[chip].ss) &3;
/*14 */	j+=2;
	tword=tword<<2|reverseBits(2,globalstr[chip].tr) &3;
/*16 */	j+=2;
	tword=tword<<1|globalstr[chip].sse &1;
/*17 */	j++;
	tword=tword<<1|globalstr[chip].spur &1;
/*18 */	j++;
	tword=tword<<1|globalstr[chip].rt &1;
/*19 */	j++;
	tword=tword<<2|reverseBits(2,globalstr[chip].ts) &3;
/*21 */	j+=2;
	tword=tword<<1|globalstr[chip].sl &1;
/*22 */	j++;
	tword=tword<<1|globalstr[chip].sb &1;
/*23 */	j++;
	tword=tword<<1|globalstr[chip].sbn &1;
/*24 */	j++;
	tword=tword<<1|globalstr[chip].m1 &1;
/*25 */	j++;
	tword=tword<<1|globalstr[chip].m0 &1;
/*26 */	j++;
	tword=tword<<1|globalstr[chip].senfl2 &1;
/*27 */	j++;
	tword=tword<<1|globalstr[chip].senfl1 &1;
/*28 */	j++;
	tword=tword<<1|globalstr[chip].rm &1;
/*29 */	j++;
	tmp=reverseBits(10,globalstr[chip].pb);
	tword=tword<<3|((tmp>>7) &7);
/*32 */	j+=3;
	
	printf("# bits=%i   tword=%x\n",j, tword);
	loads[chip][0]=tword;
	tword2=0;
	j=0;
	tword2=tword2|(tmp & 0x7f);
/*7 */	j+=7;
	tword2=tword2<<10|reverseBits(10,globalstr[chip].pa) & 0x3ff;
/*17 */	j+=10;

	chn=31;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;
	
	chn=30;	
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][1]=tword2;
	tword2=0;

	j=0;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=29;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=28;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|(tmp >>1);
/*32 */	j+=3;
	loads[chip][2]=tword2;
	printf("# bits=%i   tword2=%x\n",j, tword2);

	tword2=0;
	j=0;
	tword2=tword2|(tmp &0x1);
/*1 */	j++;
	chn=27;

	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=26;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=25;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][3]=tword2;

	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=24;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=23;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;

	chn=22;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][4]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=21;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=20;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|tmp>>1;
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][5]=tword2;
	tword2=0;
	j=0;
	tword2=tword2|tmp&1;
/*1 */	j++;
	chn=19;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=18;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=17;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][6]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=16;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=15;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;
	
	chn=14;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][7]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=13;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=12;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|tmp>>1;
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][8]=tword2;
	tword2=0;
	j=0;

	tword2=tword2|tmp&1;
/*1 */	j+=1;

	chn=11;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=10;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=9;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][9]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;
	
	chn=8;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=7;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;

	chn=6;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;


	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][10]=tword2;
	tword2=0;
	j=0;
	
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;


	chn=5;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

 	chn=4;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|tmp>>1;
/*32 */	j+=3;

 	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][11]=tword2;
	tword2=0;
	j=0;

	tword2=tword2|tmp&1;
/*1 */	j++;
	chn=3;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=2;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=1;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][12]=tword2;
	tword2=0;
	j=0;

	tword2=tword2|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=0;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;
	tword2=tword2<<15;
/*32 */	j+=15;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][13]=tword2;

	/* do globals first */
	j=0;
	tword=0;
	tword=globalstr[chip].tm;  /*
/*1 */	j++;	
	tword=tword<<1|globalstr[chip].sbm;
/*2 */ 	j++;
	tword=tword<<1|globalstr[chip].saux;
/*3 */	j++;
	tword=tword<<1|globalstr[chip].sp;
/*4 */	j++;
	tword=tword<<1|globalstr[chip].slh;
/*5 */	j++;
	tword=tword<<2|globalstr[chip].g;
/*7 */	j+=2;
	tword=tword<<5|globalstr[chip].c;
/*12 */	j+=5;
	tword=tword<<2|globalstr[chip].ss;
/*14 */	j+=2;
	tword=tword<<2|globalstr[chip].tr;
/*16 */	j+=2;
	tword=tword<<1|globalstr[chip].sse;
/*17 */	j++;
	tword=tword<<1|globalstr[chip].spur;
/*18 */	j++;
	tword=tword<<1|globalstr[chip].rt;
/*19 */	j++;
	tword=tword<<2|globalstr[chip].ts;
/*21 */	j+=2;
	tword=tword<<1|globalstr[chip].sl;
/*22 */	j++;
	tword=tword<<1|globalstr[chip].sb;
/*23 */	j++;
	tword=tword<<1|globalstr[chip].sbn;
/*24 */	j++;
	tword=tword<<1|globalstr[chip].m1;
/*25 */	j++;
	tword=tword<<1|globalstr[chip].m0;
/*26 */	j++;
	tword=tword<<1|globalstr[chip].senfl2;
/*27 */	j++;
	tword=tword<<1|globalstr[chip].senfl1;
/*28 */	j++;
	tword=tword<<1|globalstr[chip].rm;
/*29 */	j++;
	tword=tword<<3|(globalstr[chip].pb>>7);
/*32 */	j+=3;
	
	printf("# bits=%i   tword=%x\n",j, tword);
	loads[chip][0]=tword;
	tword2=0;
	j=0;
	tword2=tword2|(globalstr[chip].pb & 0x3ff);
/*7 */	j+=7;
	tword2=tword2<<10|globalstr[chip].pa;
/*17 */	j+=10;

	chn=31;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;
	
	chn=30;	
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][1]=tword2;
	tword2=0;

	j=0;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=29;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=28;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|(tmp>>1);
/*32 */	j+=3;
	loads[chip][2]=tword2;
	printf("# bits=%i   tword2=%x\n",j, tword2);

	tword2=0;
	j=0;
	tword2=tword2|(tmp&0x1);
/*1 */	j++;
	chn=27;

	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=26;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=25;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][3]=tword2;

	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=24;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=23;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;

	chn=22;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][4]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=21;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=20;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<4|(tmp>>1);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][5]=tword2;
	tword2=0;
	j=0;
	tword2=tword2|(tmp&1);
/*1 */	j++;
	chn=19;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=18;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=17;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][6]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=16;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=15;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;
	
	chn=14;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][7]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;

	chn=13;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

	chn=12;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|(tmp>>1);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][8]=tword2;
	tword2=0;
	j=0;

	tword2=tword2|(tmp&1);
/*1 */	j+=1;

	chn=11;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=10;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=9;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][9]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;
	
	chn=8;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;

	chn=7;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*18 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*19 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*20 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*21 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*24 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*25 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*29 */	j+=4;

	chn=6;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*30 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*31 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*32 */	j++;


	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][10]=tword2;
	tword2=0;
	j=0;
	
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*1 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*4 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*5 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*9 */	j+=4;


	chn=5;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*10 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*11 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*12 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*13 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*16 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*17 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*21 */	j+=4;

 	chn=4;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*22 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*23 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*24 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*25 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*28 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*29 */	j++;
	tmp=reverseBits(4,channelstr[chip*32+chn].dp);
	tword2=tword2<<3|(tmp>>1);
/*32 */	j+=3;

 	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][11]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<4|(tmp&1);
/*1 */	j++;
	chn=3;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*2 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*3 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*4 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*5 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*8 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*9 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*13 */	j+=4;

	chn=2;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*14 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*15 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*16 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*17 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*20 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*21 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*25 */	j+=4;

	chn=1;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*26 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*27 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*28 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*29 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*32 */	j+=3;

	printf("# bits=%i  tword2=%x\n",j, tword2);
	loads[chip][12]=tword2;
	tword2=0;
	j=0;

	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*1 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*5 */	j+=4;

	chn=0;
	tword2=tword2<<1|channelstr[chip*32+chn].st;
/*6 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sm;
/*7 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].nc2;
/*8 */	j++;
	tword2=tword2<<1|channelstr[chip*32+chn].sel;
/*9 */	j++;
	tword2=tword2<<3|reverseBits(3,channelstr[chip*32+chn].da);
/*12 */	j+=3;
	tword2=tword2<<1|channelstr[chip*32+chn].nc1;
/*13 */	j++;
	tword2=tword2<<4|reverseBits(4,channelstr[chip*32+chn].dp);
/*17 */	j+=4;
	tword2=tword2<<15;
/*32 */	j+=15;

	printf("# bits=%i   tword2=%x\n",j, tword2);
	loads[chip][13]=tword2;

    }
return(0);
}
