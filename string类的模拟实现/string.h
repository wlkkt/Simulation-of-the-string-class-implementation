#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<assert.h>
using namespace std;


namespace bit
{
	class string
	{
	public:
		//δ����棨������+���Σ�
		//string()
		//	:_str(new char[1])//������nullptr�������һ��const char* c_str{return _str}�ķ���������cout<<s2.c_str()ʱ��_str�ǿ�ָ�룬�Կ�ָ��Ĵ�ӡ��δ������Ϊ
		//	,_size(0)//��������������Ҫ�ṩһ���ռ䣬��ʹ�ռ䲻�����Ч�ַ�
		//	,_capacity(0)
		//{
		//	_str[0] = '\0';
		//}

		//string(const char* str)
		//	:_str(new char[strlen(str) + 1])//���ٿռ䣬Ҫ�࿪һ������\0
		//	, _size(strlen(str))
		//	, _capacity(strlen(str))//capacity��size��������\0
		//{
		//}

		typedef char* iterator; //�������ĵײ�ԭ����ָ��
		typedef const char* const_iterator; //�������ĵײ�ԭ����ָ��

		//��ϰ棨ȫȱʡ��
		string(const char* str = "")//str��ȱʡֵ������nullptr��_size��strlen(str)��ʱstrlen���strָ��ĵ�ַ���н����ö�str�ǿ�ָ�룬���ܽ����ÿ�ָ��
			:_size(strlen(str))//�����һ���մ����ɣ���û�в�������ʱ��_size��_capacity��ֵ��Ϊ0��������Ȼ��Ϊ_str����һ��ռ���\0��Ȼ��str������_str
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		const char* c_str()const
		{
			return this->_str;//c_str������һ��ָ�������ָ�룬���������һ���Կս�β���ַ�����(��C-string)����ʾ�ַ�������ĵ�ǰֵ��_str��һ��ָ�������ָ���Ҹ�����ĩβ��\0����ʼ����ʱ��ȱʡֵ���ַ�����һ��\0��
		}

	//�������캯������ͳд��:�Լ����ռ��Լ��������ݣ�
		//string(const string& s)
		//{
		//	_str = new char[s._capacity + 1];
		//	strcpy(_str, s._str);
		//	_size = s._size;
		//	_capacity = s._capacity;
		//}


		//�������캯��������������ִ�д����
		string(const string& s)//��string this,const string& s��
	{
		string tmp(s._str);//s._str��������const char*����string tmp(const char* s)����ʱ�ͻ�ȥ����Ĭ�Ϲ��캯�����Ӷ������һ����s1һ����string�����͵Ķ��󣬴�ʱtmp���൱��s1��
		swap(tmp);//swap��s1������ʵ���ϻ���һ��thisָ�룺��string this��string tmp��,utility�����swap��������thisָ��tmp�������ǿ�ռ䣬��tmp�ᱻ��Ϊ�գ��ڴ���swap����ʱ���thisָ��ָ������ݵ���Ĭ�Ϲ��죬����������ÿ������ʼֵ�����Ծͻ��������ʱ����Ĭ��ֵnullptr����this����Ϊswap�����е���Ĭ�Ϲ����ָ��nullptr��
	}//ͼ�ݡ���
	//�����ʱ����tmp������


	//��ֵ���캯������ͳд����
		//string& operator=(const string& s)
		//{
		//	char* tmp = new char[s._capacity + 1];
		//	strcpy(tmp, s._str);

		//	delete[] _str;
		//	_str = tmp;
		//	_size = s._size; 
		//	_capacity = s._capacity;
		//	return *this;
		//}


		//�ִ�д��
		string& operator=(string tmp)//��string s,string tmp�����ﴫ��Ĳ������ö��ǿ�������ֹ�ں�������ʱs1ָ��nullptr����ǿ����Ļ���û���⣬����һ���µ�ַ��tmp_strָ��һ���µ�ַ����swapʱ��this����
	{
		// �ִ�д��
		swap(tmp);//swap��string this��string tmp��,thisָ��nullptr��tmpָ���Լ��Ŀռ䣬swapʹ��������ָ�뽻��
		return *this;
	}


	//��������
	~string()
	{
		_str = nullptr;
		_size = _capacity = 0;
	}

	//����size
	size_t size()const
	{
		return _size;
	}

	//����capacity
	size_t capacity()const
	{
		return _capacity;
	}


	//+=���������
	string& operator+=(char ch)
	{
		push_back(ch);//Ҫ����һ�����ſ���ֱ�ӵ���push_back����
		return *this;//thisָ���ŵ���string�����ĵ�ַ����*this�Ľ����û�ȡ�ڸõ�ַ�ϴ�ŵ����ݣ���string������޸ĵĽ��
	}

	string& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	//operator[]��������أ������const���ε�string�����͵��ַ�����
	char& operator[](size_t pos)//�����÷��أ���_strָ����ַ������ռ䣩�л�ȡ����Ϊpos���ַ��ı������أ������ڸÿռ�λ�ڶ�����ʵ���ô�����Ҳ����ֻ������Ҫ���������Ǵ�ֵ����ֻ�ܶ�����д���������ÿ����ܶ���д��������ʵ�ʵ�[]�Ĺ���
	{
		assert(pos < _size);//����Ƿ�Խ���д��������д��ʱ����Լ���Խ�磬�ڶ�ȡ��ʱ�����Խ��ȴ��������ɫ�����ߣ�������������д�Ϳ����ڶ�дʱ����Խ����
		return _str[pos];
	}

	//operator[]��������أ�������const���ε�string�����͵��ַ�����
	const char& operator[](size_t pos) const//�����const��������ʾ���ճ����ַ�����ǰ���const��ʾ����ֵ���ܱ��޸�
	{
		assert(pos < _size);
		return _str[pos];
	}

	//������
	iterator begin()
	{
		//cout << "�Զ���begin" << endl;
		return _str;//this->_str
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin()const//����ֵ��ͬ���ܹ��ɺ������أ��������͡�˳�򡢸�����ͬ���ܹ��ɺ������أ����������Ǵ���const char*���͵�thisָ��
	{
		//cout << "�Զ���begin" << endl;
		return _str;
	}

	const_iterator end()const
	{
		return _str + _size;
	}

	//���ݺ���
	void reserve(size_t n)
	{
		//�ۣ����پɿռ�
		if (n > _capacity)//Ϊ������������ʱnһ������_capacity������reserve�Լ�����ʹ��ʱ���ܱ�֤��һ��
		{
			char* tmp = new char[n + 1];//�࿪һ���ռ��Ž�����ʶ��\0 
			strcpy(tmp, _str);//_strָ����ַ����е��ַ����������tmp����
			delete[] _str;//����ԭ���Ŀռ䣨_str��֮ǰ�Ѿ�new���ˣ�
			_str = tmp;//��_strָ���µĿռ�

			_capacity = n;//���¿ռ��_capacity����Ϊn
		}
	}

	//β�嵥���ַ�
	void push_back(char c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);//����capacity��ֵ������0����ʼ��ʱ������ַ�������strlen����Ľ��Ϊ0��������capacity��ֵҲΪ0����������Ҫһ��������ж�
		}

		_str[_size] = c;//��sizeλ���ַ�c����ʱ�Ὣԭ����λ���ϵ�\0���ǵ���sizeͳ����Ч�ַ���������5����Ч�ַ������һ����Ч�ַ���_str[size-1],_str[size]λ�ô�ŵ���\0������Ҫ�ڸ�λ���ϲ������ַ�������Ҫ��\0���ǣ�
		++_size;//�±�����
		_str[_size] = '\0';//��\0���¼ӵ��ַ���ĩβ

	}

	//β���ַ���
	void append(const char* str)//�����������д��Ŀռ�ȥ���ݣ�Ҫ����Ҫ����Ĵ��Ŀռ�ȥ���ݣ�Ҫ�������20�����ԭ������5��2����10��Ȼ���ܲ���20��
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);//��ص����ݷ�ʽ������_size+_capacity��������²����������ٽ��г�֮���
		}

		strcpy(_str + _size, str);//strcpy����ֱ���ҵ�\0��λ��Ȼ����п�����ֻ��Ҫ��Ϊ�ṩ��λ��_str +_ size����Ԫ�ص�ַ+��ЧԪ�ظ����õ��ľ���\0���ڵ������±꣩ͬʱҲ�ܽ����ַ�����\0������ȥ
		_size += len;
	}


	//��ָ��λ�ò����ַ����ַ���
	void insert(size_t pos, char c)
	{
		assert(pos <= _size);//pos=_sizeʱ���൱��β��
		if (_size == _capacity)//Ҫ��λ�ò��룬_size = _capacity��ʾû��λ��
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);//����
		}
		size_t  end = _size + 1;//end��ʾ\0����һ��Ԫ�ص��±�
		while (end > pos)//��end��pos�غ�ʱ����posλ�ò��루��ʱ�Ѿ��ڳ�����һ����λ��
		{
			_str[end] = _str[end - 1];//�Ѱ���\0�Ĳ����ַ�������ƶ�
			--end;
		}

		_str[pos] = c;
		++_size;
	}

	void insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)//�ַ����� + �����ַ������� > �ַ��ռ��С ->�ռ䲻������
		{
			reserve(_size + len);//��С����
		}

		size_t end = _size + len;//��ʱend��ʾ���ݺ����һ���ַ����±꣨��ʱ���±���ԭ��\0���±�֮���Ѿ�����һЩ���пռ䣩������_size = 10��len = 3��end = 13��pos = 3
		while (end > pos + len - 1)//13 > 5
		{
			_str[end] = _str[end - len];//��ǰ����ַ�����ƶ�,_str[13] = _str[10]��_str[12] = _str[9]��_str[11] = _str[8]��_str[10] = _str[7]��_str[9] = _str[6]��_str[8] = _str[5]��_str[7] = _str[4]��_str[6] = _str[3]
			--end;
		}
		strncpy(_str + pos, str, len);//��len���ȵ��ַ���str����pos��
		_size += len;//����_
	}

	//��ָ��λ�ú�ɾ��n���ַ�
	void erase(size_t pos, size_t len = npos)//pos:��ʼɾ����λ�á�len:Ҫɾ���ĸ���
	{
		assert(pos < _size);//pos==sizeʱ����ʾ\0���±�������ɾ��\0
		//len==npos��posλ�ú���ַ�ȫ��ɾ��
		//if (len == npos || pos + len >= _size)//��Ҫɾ���ĳ��Ⱥܳ� || ��ǰλ�� + Ҫɾ���ĳ��� > �ַ��ĳ��ȣ�
		//{//����pos + len�п��ܻᵼ��������⣬���len����ֵ��npos - 1������һ�����޷������͵����ޣ����pos==6������6֮��ͻᳬ���޷������͵�����
		//	_str[pos] - '\0';//ֱ����posλ�ø�ֵΪ\0��ͬʱ���ַ�����������pos����size��ͳ��\0��
		//	_size = pos;
		//}

		if (len == npos || len > _size - pos)//��Ҫɾ���ĳ��Ⱥܳ� || Ҫɾ���ĳ��� > �ַ��ĳ��� - ��ǰλ�ã�����pos�ƶ���������Ҳ��Ͳ�����������գ��ַ�����-��ǰλ�ñ�ʾ����posλ�ú��ж��ٸ��ַ������Ҫɾ�����ַ�������ԭ��posλ�ú���ַ����������ֱ��ȫ��ɾ��
		{
			_str[pos] - '\0';
			_size = pos;
		}
		else//�������posλ�ú��ȫ���ַ���ɾ��
		{
			strcpy(_str + pos, _str + pos + len);//ע��_str��ָ�룬ɾ��posλ�ú�len���ַ���ֱ�ӽ��±�Ϊpos+lenλ�õ��ַ�������posλ�ü��ɣ���ȱ��
			//strcpy ���Դ�ַ������Ҳ��ַ���������ʼλ�ÿ�ʼ����ַ��ظ��ƣ�ֱ���������ַ� \0 Ϊֹ
			_size -= len;//����_size
		}
	}

	//����Ч�ַ��ĸ����ĳ�n��(����)������Ŀռ���ĳ���ַ����
	void resize(size_t n, char ch = '\0')//Ĭ����\0���
	{
		if (n <= _size)//���ڶ�����Ŀռ�
		{
			_str[n] = '\0';//Ҳ���������\0�ˣ�ֱ�����±�Ϊn��λ�����һ��\0���´ζ�ȡ�ַ���ʱ������ͻ�ֹͣ
			_size = n;//����_size
		}
		else//���n>_size
		{
			reserve(n);//n����capacity�����ݣ�С�ھ�ʲô������
			for (size_t i = _size; i < n; i++)//ѭ�������ַ������
			{
				_str[i] = ch;
			}
			_str[n] = '\0';//������\0
			_size = n;
		}
	}

	//����������������ģ��ʵ��string���ṩ��swap�����������ڲ���Ҫ����utility���ṩ����һ��swap������
	void swap(string& s)//��string* this��string &s��
	{
		std::swap(_str, s._str);//utility���ṩ��swap����������������ʱ�������θ��ƺ�һ��������������û��Ҫ
		std::swap(_size, s._size);//��ȷ���߱�����Ҫʹ��utility���ṩ��swap��������������������Զ���swap�������������ƥ�����
		std::swap(_capacity, s._capacity);//�����������Ա�����е��������Ͱ���ָ����н����������漰�������죨utility���ṩ��swap������Դ���Ĳ�����������Ӧ������һ��ģ�壬����Ǵ��������ô�ͻ���ù��캯����
	}//_str

	//��ָ��λ��Ѱ���ַ�
	size_t find(char ch, size_t pos = 0)
	{
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;//δ������npos
	}

	//��ָ��λ�����Ӵ�
	size_t find(const char* sub, size_t pos = 0)const
	{
		assert(pos < _size);//pos���ܴ���_size
		const char* where = strstr(_str + pos, sub);//����strstr���������Ӵ������ַ����е�һ�γ��ֵ�λ��
		if (where)//���ؽ���ǿվ�ָ�����
		{
			return where - _str;//ָ����������Ӵ���_str�ַ����г��ֵ�λ���±�
		}
		else
		{
			return npos;//δ�ҵ�����npos
		}
	}

	//��ָ��λ�ú���ȡ����Ϊlen���Ӵ�
	string substr(size_t pos = 0, size_t len = npos)
	{
		string sub;//����Ӵ�
		if (len > _size - pos)//_size - pos��ʾָ��λ�ú����ȡ����Ч�ַ�������len>_size-pos�����ж���ȡ����
		{
			for (size_t i = pos; i < _size; i++)
			{
				sub += _str[i];//����+=���أ����β��
			}

		}
		else//�����ȡָ���ĳ��ȣ�len��
		{
			for (size_t i = pos; i < pos + len; i++)
			{
				sub += _str[i];
			}
		}
		return sub;

	}

	//����ռ�
	void clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}


	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;

	public:
		static const int npos;//��̬��Ա����npos
	};


	//��α��ȫ����//
	const int string::npos = -1;//�����npos���ж���

	//string���ṩ�ĺ���ģ�壨����ȫ����Ϊ�˱�֤�ܹ��ڵ���swap����ʱ�ȿ�����ģ��
	void swap(string& x, string& y)//Ϊ�˱������˽�s1.swap(s2)д��swap(s1,s2)���µĶ���Ŀ�������
	{
		x.swap(y);//���ڷ�ģ�庯����ͬ���������������������ͬ�������ȵ��÷�ģ�庯��������ģ�庯�������ģ����Բ���һ�����и���ƥ��ĺ�������ô��ѡ��ģ�壨���ֳɵĳ��ֳɵģ����ֳɵĵ��ǲ���ƥ�䣬��ʱ����ģ�壬�ͻ�ѡ����ģ��ʵ������
	}//����ֱ��ָ��������string&��������utility���ṩ��ȴ������Ӧ�ģ����Ի����ȵ��ø�ģ��


	//==���������
	bool operator==(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());//strcmp�������ַ��Ƚϣ���ȫ��ȷ��ؽ��Ϊ0
		return ret == 0;//�����жϽ��
	}

	//<���������
	bool operator<(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());//��һ���ַ���С�ڵڶ����ַ������򷵻ظ���
		return ret < 0;
	}

	//<=���������
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;//������������صĽ��
	}

	//>���������
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);//����>=�Ľ����
	}

	//>=���������
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}

	//!=���������
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	//���������������
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;//������Ȼ�õ���ϵͳ�ṩ��<<����string�������ַ����е��ַ�������뵽out��
		}
		return out;//��������out
	}

	//����ȡ���������
	istream& operator>>(istream& in, string& s)
	{
		s.clear();//��s�е���Ч�����������Ϊ����ȡ�Ǹ��ǣ���������ԭ��������+=��ʱ�����β����

		char ch;
		ch = in.get();//��ǰ�滺�����еĿո�ͻ��ж�ȡ����
		char buff[128];//��ǰ�涨�ÿ�������ȡ�Ĵ�С���������飩���������reverse�Ļ���Ҫ����128���ַ����ܽ�����һ�ε����룬�������ڶ��Ͽ��ռ䣬����������Ȼռ�ݿռ䣬�������ں�������ʱ�����٣���������ջ�Ͽ��ռ���ٶ�Ҳ����ճ�Ͽ��ռ����
		size_t i = 0;
		while (ch != ' ' && ch != '\n')//����ȡ�����ո�ͻ���ʱ����
		{
			buff[i++] = ch;//��buff��������������ַ�
			// [0,126]
			if (i == 127)//��buff���鵽�����һ��λ��ʱ��������ַ�����127����
			{
				buff[127] = '\0';//�����һ��λ�ø�ֵΪ������ʶ��
				s += buff;//Ȼ��ֱ�ӽ���ʱbuff�е��ַ����뵽s��
				i = 0;//��i������Ϊ0������һ��ѭ��ʱ��buff[0] = ch��ʣ���ַ��������ǵ�ԭ�����ַ�����������
			}

			ch = in.get();//��ȡ�ո�ͻ��з�
		}

		if (i > 0)//���������ַ��Ƚ϶�
		{
			buff[i] = '\0';//���ý�����ʶ��
			s += buff;//β���ַ���������+=ʱ��ֱ�Ӹ����ַ�����С���ٿռ䣩
		}

		return in;
	}


	//���������ж�ȡһ���ı����洢���ַ�����
	istream& getline(istream& in, string& s)
	{
		s.clear();

		char ch;
		//in >> ch;
		ch = in.get();
		char buff[128];
		size_t i = 0;
		while (ch != '\n')
		{
			buff[i++] = ch;
			// [0,126]
			if (i == 127)
			{
				buff[127] = '\0';
				s += buff;
				i = 0;
			}

			ch = in.get();
		}

		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}


	//���麯��///
	//���Ա��������ʵ�֣�size��capacity��operator[]��
	void String_test1()
	{
		string s1("hello world");
		string s2;
		const string s3("how are you");
		for (size_t i = 0; i < s1.size(); i++)
		{
			s1[i]++;
		}

		for (size_t i = 0; i < s1.size(); i++)
		{
			cout << s1[i] << " ";
		}
		cout << endl;

		for (size_t i = 0; i < s1.size(); i++)
		{
			cout << s3[i] << " ";
		}
	}


	//���Ե������ͷ�Χfor
	void String_test2()
	{
		//�٣��������ĵײ㻹��ָ��
		//�ڣ���Χfor�ڵײ��ϵ�ʵ��Ҳ�ǵ���begin��end������������begin�ó�Begin����Χfor�Ͳ�������

		string s4("thank");
		const string s5("galname");//����const���ε��ַ����ܱ��޸ģ����Ե�����ҲҪ��const������
		string::iterator it = s4.begin();
		string::const_iterator it2 = s5.begin();
		while (it != s4.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto ch : s4)//�ڷ�Χfor��������ʵ�֣��ڱ���׶����ͻᱻ�滻���������������ݵĴ���
		{
			cout << ch << " ";
		}
		cout << endl;

		while (it2 != s5.end())
		{
			cout << *it2 << " ";
			++it2;
		}

	}


	//����β����ַ������롢ָ��λ��ɾ����
	void String_test3()
	{
		string s5("helloworld");
		//s5.push_back('1');
		//s5.push_back('2');
		//s5.append("now");

		//cout << s5.c_str() << endl;//��c++���͵��ַ���ת��Ϊc��������ͬʱ��ӡ
		//std::string ���Ͳ���ֱ��֧��ͨ�� << �������������ݴ�ӡ����׼�������std::cout���У���Ҫ֧�ֻ���д << ���غ��������Ҫ��ʾЧ��c_str����Ϊ�˽�C++���ַ�������ת��ΪC����ַ�������ӡ������cout����ֱ�Ӵ�ӡc�����ַ���������Ҫ��ʽ���� c_str() ��������ȡ���Ӧ�� C ����ַ�����
			//s5 += 'x';
			//s5 += "yyyyyy";

			//cout << s5.c_str() << endl;

			//s5.insert(2, 'm');
			//cout << s5.c_str() << endl;
			s5.insert(3, "fuc");

		cout << s5.c_str() << endl;
		//string s6("where are you from\?");
		//cout << s6.c_str() << endl;

		//s6.erase(6, 3);
		//cout << s6.c_str() << endl;

		//s6.resize(5);
		//cout << s6.c_str() << endl;

		//s6.resize(20,'x');
		//cout << s6.c_str() << endl;
	}

	//������ǳ����
	void String_test4()
	{
		string s1("hello world");
		string s2("xxxxxx");
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		//swap(s1, s2);//ϵͳ������utility���е�swap�����������Զ��庯��������ʱλ�����Զ��庯����
		s1.swap(s2);//ָ����ʹ��s1���е��Զ���swap����������s2�ĵ�ַ
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
	}

	//����Ѱ���ַ�
	void String_test5()
	{
		string s1("hello world");
		int num = s1.find("ld", 5);
		cout << num << endl;
		//substr���������Բ���֮ǰ��ȡ��վ�����������ﲻд��
	}

	//�������������
	void String_test6()
	{
		string s1("hello world");
		string s2("hello world");

		cout << (s1 == s2) << endl;

		cout << ("hello world" == s2) << endl;
		cout << (s1 == "hello world") << endl;

		cout << s1 << endl;
		cout << s2 << endl;

		cin >> s1 >> s2;

		cout << s1 << endl;
		cout << s2 << endl;

		getline(cin, s1);
		cout << s1 << endl;
	}
}