#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

int main()
{
	typedef struct Studentdata                   //记录学生数据的结构体
	{
		string name;
		string sex;
		double score;
	}class_1;
	class_1 students[101];
	ifstream fin("score.csv", ios::in);
	char chrs[50];                               //记录文件中每行的数据
	string line;                                 //将chrs[i]转为string类型记录在这里，便于后边字符串处理
	fin.getline(chrs, sizeof(chrs));             //第一行是表头，读取后不做处理
	int student_count = 0;                       //标记是第几个学生，从0开始标记
	while (fin.getline(chrs, sizeof(chrs))) {    //按行读取，直至读完
		line = chrs;                             //char[]转为string，便于字符串处理
		int sign[3];                             //记录第n个逗号的下标
		int sign_count = 1;                      //标记是第几个逗号
		for (int i = 0; i < line.length(); ++i) {//识别并记录每行数据逗号的位置
			if (line[i] == ',') {
				sign[sign_count] = i;
				sign_count++;
			}
		}
		//对字符串数据分割为name,sex,score，包括去除无用空格，score 的 string to double
		students[student_count].name = line.substr(0, sign[1]);
		students[student_count].sex = line.substr(sign[1] + 1, sign[2] - sign[1] - 1);
		if (students[student_count].sex.find_first_not_of(" ") != 0)students[student_count].sex.erase(0, students[student_count].sex.find_first_not_of(" "));
		string str_score = line.substr(sign[2] + 1, line.length());
		if (str_score.find_first_not_of(" ") != 0)str_score.erase(0, str_score.find_first_not_of(" "));
		students[student_count].score = stod(str_score);

		student_count++;
	}
	fin.close();
	int student_num = student_count;             //记录学生总数
	//各种平均数的计算
	double average_all;
	double average_male;
	double average_female;
	//average_all
	double score_sum = 0.0;
	for (int i = 0; i < student_num; i++) {
		score_sum += students[i].score;
	}
	average_all = score_sum / student_num;
	//average_male
	double score_male = 0.0;
	int male_num = 0;
	for (int i = 0; i < student_num; i++) {
		if (students[i].sex == "Male") {
			male_num++;
			score_male += students[i].score;
		}
	}
	average_male = score_male / male_num;
	//average_female
	double score_female = 0.0;
	int female_num = 0;
	for (int i = 0; i < student_num; i++) {
		if (students[i].sex == "Female") {
			female_num++;
			score_female += students[i].score;
		}
	}
	average_female = score_female / female_num;
	//分数排序
	for (int i = 0; i < student_count - 1; i++) {
		for (int j = 0; j < student_count - 1; j++) {
			if (students[j].score < students[j + 1].score)swap(students[j], students[j + 1]);
			else if (students[j].score == students[j + 1].score) {
				if (students[j].name > students[j + 1].name)swap(students[j], students[j + 1]);
			}
		}
	}
	//打印结果，输出格式：数字均为保留小数后一位
	cout << fixed << setprecision(1)
		<< "Average score of all students is: " << average_all << endl
		<< "Average score of male students is: " << average_male << endl
		<< "Average score of female students is: " << average_female << endl;
	cout << endl;
	for (int i = 0; i < student_count; i++) {
		cout << fixed << setprecision(1) << students[i].name << " " << students[i].sex << " " << students[i].score << endl;
	}
		return 0;
}
