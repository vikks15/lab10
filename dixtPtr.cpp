#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;
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

struct DictionaryPtr
{
	char *eng;
	char *rus;
};

void sort(DictionaryPtr *dict, int &dsize)
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

void addword (DictionaryPtr *dict, char *word, char *translation, int &dsize)
{
	DictionaryPtr neword;
	///neword.eng=w;  ������

	for(int i = 0; i<dsize; i++)
	{
		if(strcmp(dict[i].eng,word)==0)
		{
			cout<<"����� ����� ��� ����������"<<endl;
			break;
		}
	}

	neword.eng = new char[strlen(word)];
	strcpy(neword.eng,word);

	neword.rus = new char[strlen(translation)];
	strcpy(neword.rus,translation);
	dsize++;
	dict[dsize-1]=neword;
	sort(dict,dsize);

	//delete neword.eng;
	//delete neword.rus;
}

void deleteword(DictionaryPtr *dict, char *word, int &dsize)
{
	int f=0;
	for(int i = 0; i<dsize; i++)
	{
		if(strcmp(dict[i].eng,word)==0)
		{
			for(int j=i; j<dsize-1; j++)
				dict[j]=dict[j+1];
			dsize--;
			f++;
			break;
		}
	}

	if(f==0) cout<<"������ ����� ��� � �������"<<endl;
	else cout<<"����� �������"<<endl;
}

void engtransl(DictionaryPtr *dict, int &dsize, char *word) 
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

void rustransl(DictionaryPtr *dict, int &dsize, char *word) 
{

	for(int i = 0; i<dsize; i++)
	{
		if (strcmp(word,dict[i].rus)==0)
		{
			cout<<dict[i].eng<<endl<<endl;
			break;
		}
		else
			if((i+1)==dsize) cout<<"������ ����� ��� � �������. ����� �������� ����� ������� 1"<<endl;
	}

}

void print(DictionaryPtr *dict, int &dsize)
{
	for(int i=0; i<dsize; ++i)
	{
		cout<<setw(strlen(dict[i].eng)+5)<<dict[i].eng<<" ";
		cout<<setw(1)<<dict[i].rus<<endl;
	}
}

void record(DictionaryPtr *dict, int &dsize)
{
	ofstream fout("newdic.txt");

	for(int i = 0; i<dsize; i++)
	{
		fout<<dict[i].eng<<" "<<dict[i].rus<<endl;
	}

	cout<<"������� ������� � ����"<<endl;

	fout.close();
}

DictionaryPtr *form (int &dsize)
{
	ifstream fin("dictPtr.txt");

	if(fin.is_open()==0)
	{
		cout<<"���� �� ������";
		system("pause");
	}

	char line[65], delims[] = " " ,*word, *nextword;
	int i=0;

	while(fin.getline(line,65))
	{
		dsize++;
	}

	DictionaryPtr *dictPtr = new DictionaryPtr[dsize];
	fin.clear();
	fin.seekg(0);


	while(fin.getline(line,65))
	{
		word=strtok_s(line,delims,&nextword);

		dictPtr[i].eng = new char [strlen(word)+1];
		strcpy(dictPtr[i].eng, word);

		dictPtr[i].rus = new char [strlen(nextword)+1];
		strcpy(dictPtr[i].rus, nextword);

		i++;
	}
	return dictPtr;
	delete dictPtr;
}

int main()
{
	system("chcp 1251 > nul");

	int dsize = 0;
	DictionaryPtr *dictPtr = form(dsize);

	sort(dictPtr,dsize);

	char *w=new char[], *tr = new char[];

	//cout<<"dictsize"<<dsize<<endl;
	while(true)
	{
		switch(menu())
		{
		case 1:
			{
				cout<<"������� ����� � ��� �������:";
				cin>>w>>tr;
				addword(dictPtr,w,tr,dsize);
				break;
			}
		case 2:
			{
				cout<<"������� ��������� �����, ������� ����� �������: ";
				cin>>w;
				deleteword(dictPtr,w,dsize);
				break;
			}
		case 3:
			{
				cout<<"������� ���������� ����� ��� ��������: ";
				cin>>w;
				engtransl(dictPtr,dsize,w);
				break;
			}
		case 4: 
			{
				cout<<"������� ������� ����� ��� ��������: ";
				cin>>w;
				rustransl(dictPtr,dsize,w);
				break;
			}
		case 5:
			{
				print(dictPtr,dsize);
				break;
			}
		case 6:
			{
				record(dictPtr, dsize);
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

	delete w;
	delete tr;
	delete dictPtr;

}