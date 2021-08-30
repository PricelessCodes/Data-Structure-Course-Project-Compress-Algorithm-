#include <iostream>
#include <stdio.h>
#include <fstream>      // std::ifstream
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
using namespace std;
class CTNode
{
	public:
	int Info;
	char Letter;
	char Binary;
	CTNode * PLeft;
	CTNode * PRight;
	CTNode()
	{
		Info = NULL;
		Binary = NULL;
		PLeft = NULL;
		PRight = NULL;
	}
};
class CNode
{
	public:
	int Info;
	char Letter;
	char * B;
	int n;
	char Binary;
	CNode * PNext;
	CTNode * PDown;
	CNode()
	{
		PNext = NULL;
		PDown = NULL;
		Info = NULL;
		Letter = NULL;
		Binary = NULL;
		n = NULL;
		B = NULL;
	}
};
class CList
{
	public:
	CNode * PHead;
	CNode * PTail;
	public:
	CList()
	{
		PHead=NULL;
		PTail=NULL;
	}
	~CList()
	{
		CNode * PTrav = PHead;
		while ( PTrav != NULL )
		{
			PHead = PHead->PNext;
			delete PTrav;
			PTrav = PHead;
		}
	}
	void disp()
	{
		CNode * PTrav = PHead;
		while (PTrav != NULL)
		{
			cout<<PTrav->Info<<"   "<<PTrav->Letter<<endl;
			PTrav = PTrav->PNext;
		}
	}
	void Attach ( CNode * PN )
	{
		if ( PHead == NULL )
		{
			PHead = PTail = PN;
		}
		else
		{
			PTail->PNext = PN;
			PTail = PN;
		}
	}
	void Delele ()
	{
		CNode * PTrav = PHead;
		while ( PTrav != NULL )
		{
			PHead = PHead->PNext;
			delete PTrav;
			PTrav = PHead;
		}
	}
	CNode * POP()
	{
		CNode * PTrav = PHead;
		PHead = PHead->PNext;
		PTrav->PNext = NULL;
		return PTrav;
	}
};
class CSList
{
	public:
	CNode * PHead;
	public:
	CSList()
	{
		PHead = NULL;
	}
	~CSList()
	{
		CNode * PTrav = PHead;
		while ( PTrav != NULL )
		{
			PHead = PHead->PNext;
			delete PTrav;
			PTrav = PHead;
		}
	}
	void disp()
	{
		CNode * PTrav = PHead;
		while (PTrav != NULL)
		{
			cout<<PTrav->Info<<"   "<<PTrav->Letter<<endl;
			PTrav = PTrav->PNext;
		}
	}
	void Delele ()
	{
		CNode * PTrav = PHead;
		while ( PTrav != NULL )
		{
			PHead = PHead->PNext;
			delete PTrav;
			PTrav = PHead;
		}
	}
	void Insert (CNode * PNN)
	{
		CNode * PTrav = PHead;
		CNode * PB = NULL;
		while (PTrav != NULL)
		{
			if (PTrav->Info > PNN->Info)
			{
				break;
			}
			PB = PTrav;
			PTrav = PTrav->PNext;
		}
		if (PB != NULL)
		{
			PB->PNext = PNN;
		}
		else
		{
			PHead = PNN;
		}
		PNN->PNext = PTrav;
	}
};
class CTree
{
	public:
	CTNode * PRoot;
	public:
	CTree()
	{
		PRoot = NULL;
	}
	void DispAll( CTNode * PTrav, char Binary[], int i, CList & BL )
	{
		if (PTrav == NULL)
		{
			return;
		}
		if (PTrav->PLeft == NULL && PTrav->PRight == NULL  )
		{
			Binary[i] = PTrav->Binary;
			CNode * PNN;
			PNN = new CNode;
			PNN->Binary = NULL;
			PNN->Info = NULL;
			PNN->Letter = PTrav->Letter;
			PNN->PDown = NULL;
			PNN->PNext = NULL;
			PNN->n = i+1;
			PNN->B = new char[100000];
			for ( int z=0 ; z<i+1 ; z++ )
			{
				PNN->B[z] = Binary[z];
			}
			BL.Attach(PNN);
			Binary = NULL;
			return;
		}
		if ( i >= 0 )
		{
			Binary[i]=PTrav->Binary;
		}
		DispAll (PTrav->PLeft,Binary,i+1,BL);
		DispAll (PTrav->PRight,Binary,i+1,BL);
	}
	void Disp(CList & BL, int lc)
	{
		char * Binary;
		Binary = new char[lc];
		int i=-1;
		DispAll(PRoot,Binary,i,BL);
	}
};
void main()
{
	clock_t Start, End;
	Start = clock();
	printf ("Calculating Time...\n");
	CTree CT;
	CSList SL;
	CList L;
	char Letters;
	int N,i,f;
	CNode * PNN = NULL;
	CNode * PTrav = NULL;
	ofstream   fl2 ("Debug\\Compressed.bmp", ofstream::binary);
	ifstream   fl ("Debug\\Image.bmp", ifstream::binary);
	fl.seekg (0, fl.end);
    int lc = fl.tellg();
	/*cout<<"File Length: "<<lc<<endl;
	system ("pause");*/
	fl.seekg (0, fl.beg);
	for ( i=0 ; i<lc ; i++ )
	{
		fl.read ( &Letters , 1);
		if ( L.PHead == NULL )
		{
			PNN= new CNode;
			PNN->PNext = NULL;
			PNN->PDown = NULL;
			PNN->Binary = NULL;
			PNN->Letter = Letters;
			PNN->Info = 1;
			L.Attach ( PNN );
		}
		else
		{
			PTrav = L.PHead;
			f=0;
			while ( PTrav != NULL )
			{
				if ( PTrav->Letter == Letters )
				{
					PTrav->Info +=1;
					f=1;
					break;
				}
				PTrav = PTrav->PNext;
			}
			if ( f==0 )
			{
				PNN= new CNode;
				PNN->PNext = NULL;
				PNN->PDown = NULL;
				PNN->Binary = NULL;
				PNN->Letter = Letters;
				PNN->Info = 1;
				L.Attach ( PNN );
			}
		}
	}
	PTrav = L.PHead;
	CNode * PCut = NULL;
	int count=0;
	while ( L.PHead != NULL )
	{
		PCut=PTrav;
		PTrav = PTrav->PNext;
		L.PHead = PTrav;
		PCut->PNext= NULL;
		SL.Insert(PCut);
		count++;
	}
	/*
	cout<<" ___Sorted Linked List____"<<endl;
	SL.disp();
	*/
		PTrav = SL.PHead;
		CTNode * PNT;
		CTNode * PNTC;
		while ( PTrav->PNext != NULL )
		{
			PNT = new CTNode;
			PNT->Info = PTrav->Info + PTrav->PNext->Info;

			if ( PTrav->PDown == NULL )
			{
				PNTC = new CTNode;
				PNTC->Info = PTrav->Info;
				PNTC->Binary = '0';
				PNTC->Letter = PTrav->Letter;
				PNTC->PLeft = NULL;
				PNTC->PRight = NULL;
				PNT->PLeft = PNTC;
			}
			else
			{
				PNT->PLeft = PTrav->PDown;
				PTrav->PDown->Binary = '0';
			}
			SL.PHead = PTrav->PNext;
			PTrav->PNext = NULL;
			delete PTrav;
			PTrav = SL.PHead;
			if ( PTrav->PDown == NULL )
			{
				PNTC = new CTNode;
				PNTC->Info = PTrav->Info;
				PNTC->Binary = '1';
				PNTC->Letter = PTrav->Letter;
				PNTC->PLeft = NULL;
				PNTC->PRight = NULL;
				PNT->PRight = PNTC;
			}
			else
			{

				PNT->PRight = PTrav->PDown;
				PTrav->PDown->Binary = '1';
			}

			SL.PHead = PTrav->PNext;
			PTrav->PNext = NULL;
			delete PTrav;
			PTrav = SL.PHead;

			PNN = new CNode;
			PNN->Info = PNT->Info;
			PNN->PDown = PNT;
			PNN->PNext = NULL;
			SL.Insert(PNN);
			PTrav = SL.PHead;
		}
		if ( count == 1 )
		{
			PNT = new CTNode;
			PNT->Info = PTrav->Info;
			PNT->PRight = NULL;

			PNTC = new CTNode;
			PNTC->Info = PTrav->Info;
			PNTC->Binary = '0';
			PNTC->Letter = PTrav->Letter;
			PNTC->PLeft = NULL;
			PNTC->PRight = NULL;
			PNT->PLeft = PNTC;

			SL.PHead = PTrav->PNext;
			PTrav->PNext = NULL;
			delete PTrav;
			PTrav = SL.PHead;

			PNN = new CNode;
			PNN->Info = PNT->Info;
			PNN->PDown = PNT;
			PNN->PNext = NULL;
			SL.Insert(PNN);
			PTrav = SL.PHead;
		}

	CT.PRoot = SL.PHead->PDown;
	CList BL;
	CT.Disp(BL,lc);
	PTrav = BL.PHead;
	int sasa=0;
	/*cout<<" ____Binary Tree____"<<endl;
	while (PTrav!=NULL)
	{
		cout<<PTrav->Letter<<"    ";
		for ( int j = 0 ; j< PTrav->n ; j++ )
		{
			cout<<PTrav->B[j];
		}
		cout<<endl;
		PTrav = PTrav->PNext;
	}
	system("pause");*/
	int size=0;
	char Curr;
	fl.seekg (0, fl.beg);
	for ( i=0 ; i<lc ; i++ )
	{
		fl.read ( &Letters , 1);
		Curr=Letters;
		PTrav = BL.PHead;
		while ( PTrav != NULL )
		{
			if ( Curr == PTrav->Letter )
			{
				size+=PTrav->n;
				break;
			}
			PTrav = PTrav->PNext;
		}
	}
	fl.seekg (0, fl.beg);
	char mask = 1;
	char temp = 0;
	int iBits = 7;
	char * Compressed;
	Compressed = new char[size];
	int h=0,o=0,v=0;
	for ( o=0 ; o<lc ; o++ )
	{
		fl.read ( &Letters , 1);
		Curr=Letters;
		PTrav = BL.PHead;
		while ( PTrav != NULL )
		{
			if ( Curr == PTrav->Letter )
			{
				break;
			}
			PTrav = PTrav->PNext;
		}
		for ( h=0 ; h < PTrav->n ; h++ )
		{
			if ( PTrav->B[h] == '1' )
			{
				temp = temp|(mask << iBits);
			}
			iBits--;
			if ( iBits == -1 )
			{

				iBits = 7;
				Compressed[v]=temp;
				temp = 0;
				v++;
			}
		}
	}
	Compressed[v]=temp;
	v++;
	int Bit = iBits;
	int swak=0;
	char swak2='0';
	for ( swak=0 ; swak < 8 ; swak++,swak2++ )
	{
		if ( swak == Bit )
		{
			fl2.write ( &swak2 , 1);
			break;
		}
	}
	/*
	cout<<"The Position Of The Last Bit In The Last Char: "<<swak2<<endl;
	system("pause");*/
	char ca=0;
	for ( swak=0 ; ; swak++,ca++ )
	{
		if ( swak == count-1 )
		{
			fl2.write ( &ca , 1);
			break;
		}
	}
	/*
	cout<<"Number Of Huffman Chars: "<<count<<endl;
	system("pause");*/
	fl.seekg (0, fl.beg);
	PTrav = BL.PHead;
	while(PTrav!=NULL)
	{
		fl2.write ( &PTrav->Letter , 1);
		for ( i=0 ; i < PTrav->n ; i++ )
		{
			fl2.write ( &PTrav->B[i], 1);
		}
		fl2.write ( " ", 1);
		PTrav=PTrav->PNext;
	}
	int j;
	fl.seekg (0, fl.beg);
	for ( j=0 ; j < v ; j++ )
	{
		//cout<<Compressed[j];
		fl2.write ( &Compressed[j] , 1);
	}
	cout<<"File Is Compressed...."<<endl;
	End = clock();
	double Time = End - Start;
	printf ("It took (%f seconds).\n",((float)Time)/CLOCKS_PER_SEC);
	//cout<<"Press Any Key And Wait A While..."<<endl;
	system ("pause");
}