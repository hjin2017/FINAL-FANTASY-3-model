#pragma once
//���� ����
inline int set_st(int st06, int st03, int st01)
{
	int sum;
	sum = (st06*0.6 + st03*0.3 + st01*0.1);
	return sum;
}
//�̹��� �̸�
inline string imageName(string name, int num,bool nu_b)
{
	char str[128];
	char temp[128];
	ZeroMemory(temp, sizeof(temp));
	ZeroMemory(str, sizeof(str));
	strcpy(str, name.c_str());
	if (nu_b)
	{
		strcat(str, itoa(num, temp, 10));
	}
	return str;
}
//����ġ
inline int experience(int lv)
{
	int ex;
	ex = (lv * 10)*2;
	return ex;
}
//�� ��ġ x
inline int  position_x(int tileX,int max,int i)
{
	int x, y;
	y = i / tileX;
	return x = i - y*tileX;
}
//�� ��ġ y
inline int  position_y(int tileX, int max, int i)
{
	int y;
	return	y = i / tileX;
}
//�̸� ���� �ѹ� ã��
inline int set_num(string FileName)
{
	string str;
	str = FileName;
	int num;
	string temp;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == 'e')
		{
			temp = str[i + 1];
			for (int j = 2; j < 10; j++)
			{
				if (str[i + j] != '.')
				{
					temp += str[i + j];
				}
				else if (str[i + j] == '.')
				{
					break;
				}
			}
		}
	}
	return num = atoi(temp.c_str());
}
inline string set_map_load_obj(int i,bool cpymap)
{
	string str;
	char temp[123];
	if (!cpymap)
	{
		str = "����obj/mapSave";
		str += itoa(i, temp, 10);
		str += ".txt ";
		return str;
	}
	else
	{
		str = "����play_1/mapSave";
		str += itoa(i, temp, 10);
		str += ".txt ";
		return str;
	}
	
}
inline string set_map_load_obj(int i,string fileName)
{
	string str;
	char temp[123];
	str = fileName;
	str += itoa(i, temp, 10);
	str += ".txt ";
	return str;
}
inline int move_count(int count, int end, int dr, int i)
{
	int Mcount = count;
	int Mend=end;
	if (end < 0)
	{
		Mend = end* -1;
	}

	Mcount += i;
	if (end < 0)
	{
		if (Mcount > Mend)
		{
			Mcount = dr;
		}
	}
	else if (end >= 0)
	{
		if (Mcount < Mend)
		{
			Mcount = dr;
		}
	}
	
	return Mcount;
}