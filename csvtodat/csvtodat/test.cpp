#include "test.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

int main()
{	
	system("color 2e");
	cout << "***************˵��****************" << endl;
	cout << "���ܣ���CSV��ʽ��ICT���Գ���ת��ΪDAT�ļ�" << endl;
	cout << "���룺a.csv" << endl;
    cout << "�����b.dat" << endl;
	cout << endl << endl << endl;
	cout << "��ȷ��a.csv�ļ��Ƿ���ڣ�" << endl;
	system("pause");

	ifstream in;
	in.open("a.csv");	//���������ļ�������
	if(!in)
	{
		cerr << "can't open the file" << endl;
		cout << endl;
		return -1;
	}
	else
		cout << "�ļ��򿪳ɹ���" << endl;

	
	ofstream out("b.dat");	//��������ļ���������

	string line;
	vector<char> data[MAX_LINE][MAX_UNIT];
	int line_count = 0;
	while(getline(in, line))
	{
		string::size_type line_size = line.size();
		int unit_count = 0;
		for(string::size_type j = 0; j < line_size; j++)
		{
			if(line[j] == ',')
			{
				unit_count++;
			}
			else if(line[j] != ' ')
			{
				data[line_count][unit_count].push_back(line[j]);
			}
		}
		cout << line_count + 1 << "��" << "  " << unit_count + 1 << "��" << "����" << endl;

		line_count++;
	}

	cout << "������" << line_count << "��" << endl;

	system("pause");  //��ͣ����


	for(int i = 0; i < line_count; i++)				//ѭ��ÿ��
	{
		vector<char>::iterator temp;				//������

	//��̬�ж�		R       D		J		C			L		F	
	if(data[i][1][0] == 'F')
		data[i][1][0] = 'D';
	
	//��λ�ж�		R:K M	D:V		Q:V		C:N U M		L:UH MH


	//�������ж�	R:10%	D:20%	J:10%	C:20%		L:40%
	string limit;
	if((data[i][1][0] == 'R')||(data[i][1][0] == 'J'))
		limit = "10.0";
	else if(data[i][1][0] == 'D'||data[i][1][0] == 'C')
		limit = "20.0";
	else
		limit = "40.0";

	//ģʽ�ж�		R:0		D:0			C:1			L:2		  J:0
	string moude;
	if((data[i][1][0] == 'R') || (data[i][1][1] == 'D') || (data[i][1][1] == 'J'))
		moude = "0";
	else if(data[i][1][0] == 'C')
		moude = "1";
	else
		moude = "2";


		for(temp = data[i][0].begin(); temp != data[i][0].end(); temp++)		
			out << *temp;						//д��   ����				
			
		out << " ";
		
		for(temp = data[i][2].begin(); temp != data[i][2].end(); temp++)		
			out << *temp;						//д��   Ԫ��λ��				
			
		out << " ";			

		for(temp = data[i][3].begin(); temp != data[i][3].end(); temp++)		
			out << *temp;						//д��	��׼ֵ			
			
		out << " ";	

		out << "A1";							//д��	λ��

		out << " ";

		for(temp = data[i][10].begin(); temp != data[i][10].end(); temp++)		
			out << *temp;						//д��	�ߵ����				
			
		out << " ";		

		for(temp = data[i][11].begin(); temp != data[i][11].end(); temp++)		
			out << *temp;						//д��	�͵����				
		
		out << " ";	

		out << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " ";
		
		out << data[i][1][0];					//д��	��̬				
		
		out << " ";	

		out << "0" << " " << "0" << endl;
		out << "0" << " ";
		for(temp = data[i][3].begin(); temp != data[i][3].end(); temp++)		
			out << *temp;						//д��	��׼ֵ				

		out << " ";

		out << limit << " " << limit <<" ";		//д����������
		out << "0" << " " ;						// д����ʱ
		out << moude << " ";
		out << "0" << " " << "0" << " " << "0" << " "
			<< "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	}

	system("pause");  //��ͣ����

	in.close();//�ر��ļ�
	return 0;
}