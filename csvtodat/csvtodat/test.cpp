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
	cout << "---------------ע��----------------" << endl;
	cout << "1�����뱣֤ ��׼ֵ �� ʵ��ֵ ��λ��ͬ" << endl;
	cout << "2��ʵ��ֵ����׼ֵ������Ϊ�հ׻��� ------" << endl;
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
			else if(line[j] != '"' && line[j] != ' ')
			{
				if( unit_count == 2 && line[j] != '.')				//����Name��ġ�-��
				data[line_count][unit_count].push_back(line[j]);		//ɾ��Name��ġ�.��
				else if(unit_count != 2 && line[j] != '-')
				data[line_count][unit_count].push_back(line[j]);	
			}
		}
		//cout << line_count + 1 << "��" << "  " << unit_count + 1 << "��" << "��Ԫ" << endl;

		line_count++;
	}

	cout << "������" << line_count << "��" << endl;

	system("pause");  //��ͣ����


	for(int i = 0; i < line_count; i++)				//ѭ��ÿ��
	{
		vector<char>::iterator temp;				//������


		//��������Ҫ�ĳ�����
		if(data[i][1].size() == 3)
		{
			if(data[i][1][0] == 'N' && data[i][1][1] == 'O' && data[i][1][2] == 'P' )
				continue;
		}
		else if(data[i][1].size() == 4)
		{
			if(data[i][1][0] == 'M' && data[i][1][1] == 'O' && data[i][1][2] == 'D'&& data[i][1][3] == 'E')
				continue;
		}
		else
		{
		}
		

		//��̬�ж�		R       D		J		C			L		F	
		if(data[i][1][0] == 'F')
			data[i][1][0] = 'D';
		char type = data[i][1][0];
		

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


		//��ʼд��*********************************����

		
		//д��   Step		
		for(temp = data[i][0].begin(); temp != data[i][0].end(); temp++)		
			out << *temp;										
		out << " ";
		
		
		//д��   Name		
		if(data[i][2].empty())
			out << "0";
		else if(data[i][1].size() > 3)
			{
				if(data[i][1][0] == 'D' && data[i][1][1] == 'T')
				{
					for(temp = data[i][2].begin(); temp != data[i][2].end(); temp++)
						out << *temp;
					out << "_";
					for(temp = data[i][1].begin(); temp != data[i][1].end(); temp++)
					{
						if(*temp == '.')
							out << "_";
						else
							out << *temp;	
					}
				}
				else
				{
					for(temp = data[i][2].begin(); temp != data[i][2].end(); temp++)
						out << *temp;
				}

			}			
		out << " ";	

		//д��	ʵ��ֵ	
		if(!data[i][3].empty())
		{
			for(temp = data[i][3].begin(); temp != data[i][3].end(); temp++)
				out << *temp;	
		}
		else if(data[i][1][0] == 'J')
		{
			out << "1";
		}
		else if(data[i][4].empty())
			out << "0";
		else
		{
			for(temp = data[i][4].begin(); temp != data[i][4].end(); temp++)
				out << *temp;	
		}			
		out << " ";	

		//д��	Lcλ��
		out << "A1";
		out << " ";

		//д��	�ߵ���� Hip
		for(temp = data[i][13].begin(); temp != data[i][13].end(); temp++)		
			out << *temp;			
		out << " ";

		//д��	�͵���� Lop
		for(temp = data[i][14].begin(); temp != data[i][14].end(); temp++)		
			out << *temp;						
		out << " ";	

		//д��Gp-1 Gp-2 Gp-3 Gp-4 Gp-5
		out << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " ;
		
		//д��ɾ��skip
		if(data[i][23].empty())
			out << "0";
		else
			out << "1";
		out << " ";
		
		//д��	��̬
		out << type;									
		
		out << " ";	
	
		out << "0" << " " << "0" << endl;
		out << "0" << " ";

		//д���׼ֵ
		if(data[i][1][0] == 'J')
			out << "1";
		else if(data[i][4].empty())
			out << "0";
		else
		{
			for(temp = data[i][4].begin(); temp != data[i][4].end(); temp++)		
				out << *temp;	
		}
		out << " ";

		//д����������
		out << limit << " " << limit <<" ";		
		
		// д����ʱ
		out << "0" << " " ;					
		
		//д��ģʽ
		out << moude << " ";					
		
		out << "0" << " " << "0" << " " << "0" << " "
			<< "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	}


	in.close();//�ر��ļ�
	return 0;
}