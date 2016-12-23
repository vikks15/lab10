#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;


// bin
int menu()
{
	cout<<"1 - �������� ����� � �������"<<endl;
	cout<<"2 - ������� ����� �� �������"<<endl;
	cout<<"3 - ������� ����� � ����������� �� �������"<<endl;
	cout<<"4 - ������� ����� � �������� �� ���������� "<<endl;
	cout<<"5 - �������� �������"<<endl;
	cout<<"6 - �������� ������� � ����"<<endl;
	cout<<"7 - �����"<<endl;

	int ch;
	cin>>ch;
	cin.clear();
	cin.ignore(256,'\n');
	return ch;
}

const int l_word=31;
const int maxsize=100;

struct DictionaryTxt
{
	char eng[l_word];
	char rus[l_word];
};

void sort(DictionaryTxt dict[100], int &dsize)
{

	int f=0;
	for(int i = 0; i < dsize; i++)
	{
		for (int j=0;j < dsize - i - 1; j++)
		{
			if(strcmp(dict[j].eng,dict[j+1].eng)>0)
			{
				swap(dict[j],dict[j+1]);
				f++;
			}
		}	
		if(f==0) break;
		f=0;
	}
}

void addword (DictionaryTxt dict[100], char word[l_word], char translation[l_word], int &dsize)
{
	DictionaryTxt neword;
	///neword.eng=w;  ������
	strcpy(neword.eng,word);
	strcpy(neword.rus,translation);

	int indplace = 0;
	dsize++;
	dict[dsize-1]=neword;
	sort(dict,dsize);
}

void deleteword(DictionaryTxt dict[100], char word[l_word], int &dsize)
{
	for(int i = 0; i<dsize; i++)
	{
		if(strcmp(dict[i].eng,word)==0)
		{
			for(int j=i; j<dsize-1; j++)
				dict[j]=dict[j+1];
			dsize--;
		}
	}
}

void engtransl(DictionaryTxt dict[100], int &dsize, char word[l_word]) 
{
	int first_ind = 0;
	int last_ind = dsize-1;
	int middle = 0;

	while(first_ind<last_ind)
	{
		middle=first_ind + (last_ind-first_ind)/2;
		if(strcmp(word,dict[middle].eng)<=0) last_ind=middle;
		else first_ind=middle+1;
	}

	if(strcmp(word,dict[last_ind].eng)==0) cout<<dict[last_ind].rus<<endl;
	else cout<<"������ ����� ��� � �������"<<endl;

	//cout<<"li "<<last_ind;
}

void rustransl(DictionaryTxt dict[100], int &dsize, char word[l_word]) 
{

	for(int i = 0; i<dsize; i++)
	{
		if (strcmp(word,dict[i].rus)==0)
		{
			cout<<dict[i].eng;
			break;
		}
		else
			if((i+1)==dsize) cout<<"������ ����� ��� � �������"<<endl;
	}

}

void print(DictionaryTxt dict[100], int &dsize)
{
	ifstream fin("dict.txt");
	for(int i=0; i<dsize; ++i)
	{
		cout<<dict[i].eng<<" ";
		cout<< dict[i].rus<<endl;
	}
	fin.close();

}

void record(DictionaryTxt dict[100], int &dsize)
{
	ofstream fout("newdic.bin");

	for(int i = 0; i<dsize; i++)
	{
		fout<<dict[i].eng<<" "<<dict[i].rus<<endl;
	}
	fout.close();
}

int form(DictionaryTxt dict[100])
{
	int dsize = 0;
	ifstream fin("ndict", ios::binary|ios::in);

	if(fin.is_open()==0)
	{
		cout<<"���� �� ������";
		system("pause");
	}

	fin.read((char*)&dsize, sizeof(int));
	fin.read((char*)dict, sizeof(DictionaryTxt)*dsize);
	return dsize;
}

int main()
{
	system("chcp 1251 > nul");
	DictionaryTxt dict[maxsize];

	int dsize = form(dict);

	sort(dict,dsize);

	char w[l_word];
	char tr[l_word];

	//cout<<"dictsize"<<dsize;

	char dword [l_word];
	while(true)
	{
		switch(menu())
		{
		case 1:
			{
				cout<<"������� ����� � ��� �������:";
				cin>>w>>tr;

				addword(dict,w,tr,dsize);
				break;
			}
		case 2:
			{
				cout<<"������� �����, ������� ����� �������:";
				cin>>dword;
				deleteword(dict,dword,dsize);
				break;
			}
		case 3:
			{
				char engw[l_word];
				cout<<"������� ���������� ����� ��� �������� ";
				cin>>engw;
				engtransl(dict,dsize,engw);
				break;
			}
		case 4: 
			{
				char rusw[l_word];
				cout<<"������� ������� ����� ��� �������� ";
				cin>>rusw;
				rustransl(dict,dsize,rusw);
				break;
			}
		case 5:
			{
				print(dict,dsize);
				break;
			}
		case 6:
			{
				record(dict, dsize);
				break;
			}
		case 7: return 0; 
		default:
			{
				cout<<" ���� ������� ����� �� 1 �� 7"<<endl;
				break;
			}

		}

	}

}