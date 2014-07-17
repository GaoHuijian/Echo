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
	cout << "***************说明****************" << endl;
	cout << "功能：将CSV格式的ICT测试程序转换为DAT文件" << endl;
	cout << "输入：a.csv" << endl;
    cout << "输出：b.dat" << endl;
	cout << "---------------注意----------------" << endl;
	cout << "1，必须保证 标准值 与 实际值 单位相同" << endl;
	cout << "2，实际值、标准值、不能为空白或者 ------" << endl;
	cout << endl << endl << endl;
	cout << "请确认a.csv文件是否存在？" << endl;
	system("pause");

	ifstream in;
	in.open("a.csv");	//定义输入文件，并打开
	if(!in)
	{
		cerr << "can't open the file" << endl;
		cout << endl;
		return -1;
	}
	else
		cout << "文件打开成功！" << endl;

	
	ofstream out("b.dat");	//定义输出文件，并绑定流

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
				if( unit_count == 2 && line[j] != '.')				//保留Name里的“-”
				data[line_count][unit_count].push_back(line[j]);		//删除Name里的“.”
				else if(unit_count != 2 && line[j] != '-')
				data[line_count][unit_count].push_back(line[j]);	
			}
		}
		//cout << line_count + 1 << "行" << "  " << unit_count + 1 << "个" << "单元" << endl;

		line_count++;
	}

	cout << "程序共有" << line_count << "行" << endl;

	system("pause");  //暂停程序


	for(int i = 0; i < line_count; i++)				//循环每行
	{
		vector<char>::iterator temp;				//迭代器


		//跳过不必要的程序行
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
		

		//型态判定		R       D		J		C			L		F	
		if(data[i][1][0] == 'F')
			data[i][1][0] = 'D';
		char type = data[i][1][0];
		

		//单位判定		R:K M	D:V		Q:V		C:N U M		L:UH MH


		//上下限判定	R:10%	D:20%	J:10%	C:20%		L:40%
		string limit;
		if((data[i][1][0] == 'R')||(data[i][1][0] == 'J'))
			limit = "10.0";
		else if(data[i][1][0] == 'D'||data[i][1][0] == 'C')
			limit = "20.0";
		else
			limit = "40.0";


		//模式判定		R:0		D:0			C:1			L:2		  J:0
		string moude;
		if((data[i][1][0] == 'R') || (data[i][1][1] == 'D') || (data[i][1][1] == 'J'))
			moude = "0";
		else if(data[i][1][0] == 'C')
			moude = "1";
		else
			moude = "2";


		//开始写入*********************************程序

		
		//写入   Step		
		for(temp = data[i][0].begin(); temp != data[i][0].end(); temp++)		
			out << *temp;										
		out << " ";
		
		
		//写入   Name		
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

		//写入	实际值	
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

		//写入	Lc位置
		out << "A1";
		out << " ";

		//写入	高点针号 Hip
		for(temp = data[i][13].begin(); temp != data[i][13].end(); temp++)		
			out << *temp;			
		out << " ";

		//写入	低点针号 Lop
		for(temp = data[i][14].begin(); temp != data[i][14].end(); temp++)		
			out << *temp;						
		out << " ";	

		//写入Gp-1 Gp-2 Gp-3 Gp-4 Gp-5
		out << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " ;
		
		//写入删略skip
		if(data[i][23].empty())
			out << "0";
		else
			out << "1";
		out << " ";
		
		//写入	形态
		out << type;									
		
		out << " ";	
	
		out << "0" << " " << "0" << endl;
		out << "0" << " ";

		//写入标准值
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

		//写入上限下限
		out << limit << " " << limit <<" ";		
		
		// 写入延时
		out << "0" << " " ;					
		
		//写入模式
		out << moude << " ";					
		
		out << "0" << " " << "0" << " " << "0" << " "
			<< "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	}


	in.close();//关闭文件
	return 0;
}