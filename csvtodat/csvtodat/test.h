//日期：2013年11月19日
//用处：将CSV格式的ICT测试程序转换为DAT文件
//说明：输入：CSV格式的文件命名：a.csv	
//      输出：DAT格式的文件：b.dat
//作者：echo
//版权所有 海康科技有限公司
const int MAX_LINE = 1000;		//文件最大行数
const int MAX_UNIT = 20;		//每行最大单月数	
const int MAX_UNIT_CHAR = 20;	//每 单元最大字符数