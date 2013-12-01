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
			else if(line[j] != ' ')
			{
				data[line_count][unit_count].push_back(line[j]);
			}
		}
		cout << line_count + 1 << "行" << "  " << unit_count + 1 << "个" << "单月" << endl;

		line_count++;
	}

	cout << "程序共有" << line_count << "行" << endl;

	system("pause");  //暂停程序


	for(int i = 0; i < line_count; i++)				//循环每行
	{
		vector<char>::iterator temp;				//迭代器

	//型态判定		R       D		J		C			L		F	
	if(data[i][1][0] == 'F')
		data[i][1][0] = 'D';
	
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


		for(temp = data[i][0].begin(); temp != data[i][0].end(); temp++)		
			out << *temp;						//写入   步数				
			
		out << " ";
		
		for(temp = data[i][2].begin(); temp != data[i][2].end(); temp++)		
			out << *temp;						//写入   元件位号				
			
		out << " ";			

		for(temp = data[i][3].begin(); temp != data[i][3].end(); temp++)		
			out << *temp;						//写入	标准值			
			
		out << " ";	

		out << "A1";							//写入	位置

		out << " ";

		for(temp = data[i][10].begin(); temp != data[i][10].end(); temp++)		
			out << *temp;						//写入	高点针号				
			
		out << " ";		

		for(temp = data[i][11].begin(); temp != data[i][11].end(); temp++)		
			out << *temp;						//写入	低点针号				
		
		out << " ";	

		out << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " ";
		
		out << data[i][1][0];					//写入	形态				
		
		out << " ";	

		out << "0" << " " << "0" << endl;
		out << "0" << " ";
		for(temp = data[i][3].begin(); temp != data[i][3].end(); temp++)		
			out << *temp;						//写入	标准值				

		out << " ";

		out << limit << " " << limit <<" ";		//写入上限下线
		out << "0" << " " ;						// 写入延时
		out << moude << " ";
		out << "0" << " " << "0" << " " << "0" << " "
			<< "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	}

	system("pause");  //暂停程序

	in.close();//关闭文件
	return 0;
}