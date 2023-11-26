/*** 
 * @description: ���ɸ������ȵ��������,��ѡ�Ƿ������д��ĸ��Сд��ĸ�������ַ����Լ����ֵ�
 * @param: 
 * @return: 
 * @Author: Gnara
 * @Date: 2022-02-07 19:16:15
 * @LastEditTime: 2022-02-08 13:29:06
 * @LastEditors: Gnara
 * @Description: 
 * @FilePath: \vscode\C\project\Make_random_password.cpp
 * @One more thing
 */


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

string Random_choose(int,int,string);
//���ѡ�ֶκ���
string make_password(int,int *);
//�����������
string make_capital_letter(int);
//���ɴ�д��ĸ
string make_small_letter(int);
//����Сд��ĸ
string make_number(int);
//��������
string make_punctuation(int);
//���ɷ���

string password;

int op_array[4],type;
enum operand
{
    capital_letter = 0,
    small_letter,
    number,
    punctuation
};
//�����������,���涨�����ַ�Ϊö������

int main(void)
{
    srand(time(0));
    for (int i = 0; i < 4;i++)
    {
        op_array[i] = -1;
    }
//��ʼ����������

    cout << "Choose the types of password:" << endl;
    cout << "Captial\tSmall\tNumber\tPunctuation\n";
    cout << "0\t1\t2\t3\n";
    cout << "Enter '-1' if do not need\n";
    for (int i = 0; i < 4;i++)
    {
        cin >> op_array[i];
        if(op_array[i] != -1)
        {
            type++;
        }
    }
    int length;
    cout << "Enter the lengeh of password" << endl;
    cin >> length;
    cout << make_password(length,op_array) << endl;
    system("pause");
}


string make_password(int len,int *op)
{

    for (int i = 0; i < 4;i++)
    {
        if(op[i] != -1)
        {
            switch (i)
            {
                case capital_letter:
                    make_capital_letter(len / type);
                    break;
                case small_letter:
                    make_small_letter(len / type);
                    break;
                case number:
                    make_number(len / type);
                    break;
                case punctuation:
                    make_punctuation(len / type);
                    break;
            }
        }
    }
    return password;
}

string Random_choose(int len,int n,string lib)
{
    int r;
    for (int i = 0; i < len;i++)
    {
        r = rand() % n;
        password += lib.substr(r, 1);
    }
    return password;
}
//���ѡ��������һ������Ϊ�������볤�ȣ��ڶ�������Ϊ�����ַ������ȣ�����������Ϊ�����ַ���
string make_capital_letter(int len)
{
    string capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Random_choose(len, (capital.length()), capital);
    return password;
}
string make_small_letter(int len)
{
    string small_letter = "abcdefghijklmnopqrstuvwxyz";
    Random_choose(len, (small_letter.length()), small_letter);
    return password;
}
string make_number(int len)
{
    string num = "0123456789";
    Random_choose(len, (num.length()), num);
    return password;
}
string make_punctuation(int len)
{
    string punc = "`~!@#$%^&*()-=+*/:;'<>.\"\\";
    Random_choose(len, (punc.length()), punc);
    return password;
}
