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
		//未合体版（不带参+带参）
		//string()
		//	:_str(new char[1])//不能是nullptr，如果有一个const char* c_str{return _str}的方法当我们cout<<s2.c_str()时，_str是空指针，对空指针的打印是未定义行为
		//	,_size(0)//所以这里最起码要提供一个空间，即使空间不存放有效字符
		//	,_capacity(0)
		//{
		//	_str[0] = '\0';
		//}

		//string(const char* str)
		//	:_str(new char[strlen(str) + 1])//开辟空间，要多开一个包含\0
		//	, _size(strlen(str))
		//	, _capacity(strlen(str))//capacity和size都不包含\0
		//{
		//}

		typedef char* iterator; //迭代器的底层原理是指针
		typedef const char* const_iterator; //迭代器的底层原理是指针

		//结合版（全缺省）
		string(const char* str = "")//str的缺省值不能是nullptr，_size（strlen(str)）时strlen会对str指向的地址进行解引用而str是空指针，不能解引用空指针
			:_size(strlen(str))//这里给一个空串即可，当没有参数传入时，_size和_capacity的值均为0，但是仍然会为_str开辟一块空间存放\0，然后将str拷贝给_str
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		const char* c_str()const
		{
			return this->_str;//c_str：返回一个指向数组的指针，该数组包含一个以空结尾的字符序列(即C-string)，表示字符串对象的当前值，_str是一个指向数组的指针且该数组末尾有\0（初始化的时候缺省值空字符里有一个\0）
		}

	//拷贝构造函数（传统写法:自己开空间自己拷贝数据）
		//string(const string& s)
		//{
		//	_str = new char[s._capacity + 1];
		//	strcpy(_str, s._str);
		//	_size = s._size;
		//	_capacity = s._capacity;
		//}


		//拷贝构造函数（拷贝构造的现代写法）
		string(const string& s)//（string this,const string& s）
	{
		string tmp(s._str);//s._str的类型是const char*，即string tmp(const char* s)，此时就会去调用默认构造函数，从而构造出一个与s1一样的string类类型的对象，此时tmp就相当于s1了
		swap(tmp);//swap（s1），但实际上还有一个this指针：（string this，string tmp）,utility库里的swap函数会让this指向tmp所开的那块空间，而tmp会被置为空（在传入swap函数时会对this指针指向的内容调用默认构造，且由于我们每个定初始值，所以就会采用声明时给的默认值nullptr，即this会因为swap函数中调用默认构造而指向nullptr）
	}//图⑤、⑥
	//最后临时对象tmp被销毁


	//赋值构造函数（传统写法）
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


		//现代写法
		string& operator=(string tmp)//（string s,string tmp）这里传入的不是引用而是拷贝（防止在后续交换时s1指向nullptr如果是拷贝的话就没问题，开辟一块新地址，tmp_str指向一块新地址，在swap时与this交换
	{
		// 现代写法
		swap(tmp);//swap（string this，string tmp）,this指向nullptr，tmp指向自己的空间，swap使得这两个指针交换
		return *this;
	}


	//析构函数
	~string()
	{
		_str = nullptr;
		_size = _capacity = 0;
	}

	//计算size
	size_t size()const
	{
		return _size;
	}

	//计算capacity
	size_t capacity()const
	{
		return _capacity;
	}


	//+=运算符重载
	string& operator+=(char ch)
	{
		push_back(ch);//要加上一个符号可以直接调用push_back函数
		return *this;//this指针存放的是string类对象的地址，对*this的解引用获取在该地址上存放的内容，即string类对象修改的结果
	}

	string& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	//operator[]运算符重载（处理非const修饰的string类类型的字符串）
	char& operator[](size_t pos)//传引用返回，将_str指向的字符串（空间）中获取索引为pos的字符的别名返回，且由于该空间位于堆上其实不用传引用也可以只不过需要拷贝，但是传值拷贝只能读不能写，而传引用拷贝能读能写，更符号实际的[]的功能
	{
		assert(pos < _size);//检测是否越界读写，数组在写的时候可以检查出越界，在读取的时候检查出越界却不报错（绿色波浪线），而这里这样写就可以在读写时进行越界检查
		return _str[pos];
	}

	//operator[]运算符重载（处理有const修饰的string类类型的字符串）
	const char& operator[](size_t pos) const//后面的const是用来表示接收常量字符串，前面的const表示返回值不能被修改
	{
		assert(pos < _size);
		return _str[pos];
	}

	//迭代器
	iterator begin()
	{
		//cout << "自定义begin" << endl;
		return _str;//this->_str
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin()const//返回值不同不能构成函数重载，参数类型、顺序、个数不同才能构成函数重载，在这里我们传入const char*类型的this指针
	{
		//cout << "自定义begin" << endl;
		return _str;
	}

	const_iterator end()const
	{
		return _str + _size;
	}

	//扩容函数
	void reserve(size_t n)
	{
		//③：销毁旧空间
		if (n > _capacity)//为其它函数传参时n一定大于_capacity，但是reserve自己单独使用时不能保证这一点
		{
			char* tmp = new char[n + 1];//多开一个空间存放结束标识符\0 
			strcpy(tmp, _str);//_str指向的字符串中的字符逐个拷贝给tmp数组
			delete[] _str;//销毁原来的空间（_str在之前已经new过了）
			_str = tmp;//令_str指向新的空间

			_capacity = n;//将新空间的_capacity调整为n
		}
	}

	//尾插单个字符
	void push_back(char c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);//由于capacity的值可能是0（初始化时传入空字符串导致strlen计算的结果为0进而导致capacity的值也为0），所以需要一个额外的判断
		}

		_str[_size] = c;//在size位置字符c，此时会将原来该位置上的\0覆盖掉（size统计有效字符个数，有5个有效字符，最后一个有效字符是_str[size-1],_str[size]位置存放的是\0，现在要在该位置上插入新字符，就需要将\0覆盖）
		++_size;//下标右移
		_str[_size] = '\0';//将\0重新加到字符串末尾

	}

	//尾插字符串
	void append(const char* str)//不能依据现有串的空间去扩容，要根据要插入的串的空间去扩容（要插入的是20，如果原来的是5扩2倍到10依然不能插入20）
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);//最保守的扩容方式就是用_size+_capacity，如果害怕不够还可以再进行乘之类的
		}

		strcpy(_str + _size, str);//strcpy可以直接找到\0的位置然后进行拷贝（只需要人为提供好位置_str +_ size，首元素地址+有效元素个数得到的就是\0所在的数组下标）同时也能将新字符串的\0拷贝过去
		_size += len;
	}


	//在指定位置插入字符与字符串
	void insert(size_t pos, char c)
	{
		assert(pos <= _size);//pos=_size时候相当于尾插
		if (_size == _capacity)//要有位置插入，_size = _capacity表示没有位置
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);//扩容
		}
		size_t  end = _size + 1;//end表示\0后面一个元素的下标
		while (end > pos)//当end与pos重合时才在pos位置插入（此时已经腾出来了一个空位）
		{
			_str[end] = _str[end - 1];//把包括\0的部分字符都向后移动
			--end;
		}

		_str[pos] = c;
		++_size;
	}

	void insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)//字符数量 + 插入字符串长度 > 字符空间大小 ->空间不够扩容
		{
			reserve(_size + len);//最小扩容
		}

		size_t end = _size + len;//此时end表示扩容后最后一个字符的下标（此时的下标与原来\0的下标之间已经有了一些空闲空间），假设_size = 10、len = 3、end = 13、pos = 3
		while (end > pos + len - 1)//13 > 5
		{
			_str[end] = _str[end - len];//将前面的字符向后移动,_str[13] = _str[10]、_str[12] = _str[9]、_str[11] = _str[8]、_str[10] = _str[7]、_str[9] = _str[6]、_str[8] = _str[5]、_str[7] = _str[4]、_str[6] = _str[3]
			--end;
		}
		strncpy(_str + pos, str, len);//将len长度的字符串str插入pos处
		_size += len;//更新_
	}

	//在指定位置后删除n个字符
	void erase(size_t pos, size_t len = npos)//pos:开始删除的位置、len:要删除的个数
	{
		assert(pos < _size);//pos==size时，表示\0的下表，不可能删除\0
		//len==npos则pos位置后的字符全部删除
		//if (len == npos || pos + len >= _size)//（要删除的长度很长 || 当前位置 + 要删除的长度 > 字符的长度）
		//{//但是pos + len有可能会导致溢出问题，如果len给的值是npos - 1，即差一个到无符号整型的上限，如果pos==6，加上6之后就会超出无符号整型的上限
		//	_str[pos] - '\0';//直接在pos位置赋值为\0，同时将字符个数缩减至pos个（size会统计\0）
		//	_size = pos;
		//}

		if (len == npos || len > _size - pos)//（要删除的长度很长 || 要删除的长度 > 字符的长度 - 当前位置），将pos移动至运算符右侧后就不会有溢出风险，字符长度-当前位置表示的是pos位置后还有多少个字符，如果要删除的字符数量比原来pos位置后的字符数量还多就直接全部删除
		{
			_str[pos] - '\0';
			_size = pos;
		}
		else//如果不是pos位置后的全部字符都删除
		{
			strcpy(_str + pos, _str + pos + len);//注意_str是指针，删除pos位置后len个字符，直接将下标为pos+len位置的字符拷贝至pos位置即可（补缺）
			//strcpy 会从源字符串（右侧字符串）的起始位置开始逐个字符地复制，直到遇到空字符 \0 为止
			_size -= len;//更新_size
		}
	}

	//将有效字符的个数改成n个(扩容)，多出的空间用某个字符填充
	void resize(size_t n, char ch = '\0')//默认用\0填充
	{
		if (n <= _size)//存在多出来的空间
		{
			_str[n] = '\0';//也不用填充多个\0了，直接在下标为n的位置添加一个\0，下次读取字符串时到这里就会停止
			_size = n;//更新_size
		}
		else//如果n>_size
		{
			reserve(n);//n大于capacity就扩容，小于就什么都不做
			for (size_t i = _size; i < n; i++)//循环插入字符传入的
			{
				_str[i] = ch;
			}
			_str[n] = '\0';//最后加上\0
			_size = n;
		}
	}

	//交换函数（这里是模拟实现string类提供的swap函数，函数内部还要调用utility库提供的另一个swap函数）
	void swap(string& s)//（string* this，string &s）
	{
		std::swap(_str, s._str);//utility库提供的swap函数传入两个对象时会有三次复制和一次析构，在这里没必要
		std::swap(_size, s._size);//明确告诉编译器要使用utility库提供的swap函数，否则编译器会用自定义swap函数，会参数不匹配错误
		std::swap(_capacity, s._capacity);//将两个对象成员变量中的内置类型包括指针进行交换，不会涉及拷贝构造（utility库提供的swap函数会对传入的参数进行自适应，它是一个模板，如果是传入对象，那么就会调用构造函数）
	}//_str

	//从指定位置寻找字符
	size_t find(char ch, size_t pos = 0)
	{
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;//未到返回npos
	}

	//在指定位置找子串
	size_t find(const char* sub, size_t pos = 0)const
	{
		assert(pos < _size);//pos不能大于_size
		const char* where = strstr(_str + pos, sub);//利用strstr函数返回子串在主字符串中第一次出现的位置
		if (where)//返回结果非空就指针相减
		{
			return where - _str;//指针相减就是子串在_str字符串中出现的位置下标
		}
		else
		{
			return npos;//未找到返回npos
		}
	}

	//从指定位置后提取长度为len的子串
	string substr(size_t pos = 0, size_t len = npos)
	{
		string sub;//存放子串
		if (len > _size - pos)//_size - pos表示指定位置后可提取的有效字符个数，len>_size-pos，则有多少取多少
		{
			for (size_t i = pos; i < _size; i++)
			{
				sub += _str[i];//利用+=重载，逐个尾插
			}

		}
		else//否则就取指定的长度（len）
		{
			for (size_t i = pos; i < pos + len; i++)
			{
				sub += _str[i];
			}
		}
		return sub;

	}

	//清理空间
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
		static const int npos;//静态成员变量npos
	};


	//（伪）全局域//
	const int string::npos = -1;//类外对npos进行定义

	//string类提供的函数模板（放在全局是为了保证能够在调用swap函数时先看到该模板
	void swap(string& x, string& y)//为了避免有人将s1.swap(s2)写成swap(s1,s2)导致的多余的拷贝构造
	{
		x.swap(y);//对于非模板函数和同名函数，如果其它条件相同，会优先调用非模板函数而不是模板函数，如果模板可以产生一个具有更好匹配的函数，那么就选择模板（有现成的吃现成的，有现成的但是不够匹配，此时还有模板，就会选择用模板实例化）
	}//这里直接指定了两个string&参数，而utility库提供的却是自适应的，所以会优先调用该模板


	//==运算符重载
	bool operator==(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());//strcmp函数逐字符比较，完全相等返回结果为0
		return ret == 0;//返回判断结果
	}

	//<运算符重载
	bool operator<(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());//第一个字符串小于第二个字符串，则返回负数
		return ret < 0;
	}

	//<=运算符重载
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;//两个运算符重载的结合
	}

	//>运算符重载
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);//逆着>=的结果来
	}

	//>=运算符重载
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}

	//!=运算符重载
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	//流插入运算符重载
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;//这里依然用的是系统提供的<<，将string类对象的字符串中的字符逐个插入到out中
		}
		return out;//返回最后的out
	}

	//流提取运算符重载
	istream& operator>>(istream& in, string& s)
	{
		s.clear();//将s中的有效数据清除，因为流提取是覆盖，如果不清楚原有数据在+=的时候就是尾插了

		char ch;
		ch = in.get();//将前面缓冲区中的空格和换行读取出来
		char buff[128];//提前规定好可以流提取的大小（缓冲数组），如果采用reverse的话需要输入128个字符才能进行下一次的输入，且它是在堆上开空间，函数结束依然占据空间，而数组在函数结束时就销毁，且数组在栈上开空间的速度也比在粘上开空间更快
		size_t i = 0;
		while (ch != ' ' && ch != '\n')//流提取遇到空格和换行时结束
		{
			buff[i++] = ch;//向buff数组中逐个插入字符
			// [0,126]
			if (i == 127)//当buff数组到达最后一个位置时（输入的字符超过127个）
			{
				buff[127] = '\0';//将最后一个位置赋值为结束标识符
				s += buff;//然后直接将此时buff中的字符插入到s中
				i = 0;//将i重新置为0，当再一次循环时，buff[0] = ch，剩余字符进来覆盖掉原来的字符，依次类推
			}

			ch = in.get();//读取空格和换行符
		}

		if (i > 0)//如果插入的字符比较短
		{
			buff[i] = '\0';//设置结束标识符
			s += buff;//尾插字符串（调用+=时会直接根据字符串大小开辟空间）
		}

		return in;
	}


	//从输入流中读取一行文本并存储到字符串中
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


	//检验函数///
	//尝试遍历的相关实现（size、capacity、operator[]）
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


	//尝试迭代器和范围for
	void String_test2()
	{
		//①：迭代器的底层还是指针
		//②：范围for在底层上的实现也是调用begin和end，如果将上面的begin该成Begin，范围for就不起作用

		string s4("thank");
		const string s5("galname");//对于const修饰的字符不能被修改，所以迭代器也要用const来修饰
		string::iterator it = s4.begin();
		string::const_iterator it2 = s5.begin();
		while (it != s4.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto ch : s4)//在范围for不用自行实现，在编译阶段它就会被替换成类似于上述内容的代码
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


	//尝试尾插和字符串插入、指定位置删除等
	void String_test3()
	{
		string s5("helloworld");
		//s5.push_back('1');
		//s5.push_back('2');
		//s5.append("now");

		//cout << s5.c_str() << endl;//将c++类型的字符串转换为c语言类型同时打印
		//std::string 类型并不直接支持通过 << 操作符将其内容打印到标准输出流（std::cout）中（想要支持还得写 << 重载函数否则就要显示效用c_str），为了将C++的字符串类型转换为C风格字符串并打印出来（cout可以直接打印c风格的字符串），需要显式调用 c_str() 函数来获取其对应的 C 风格字符串：
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

	//尝试深浅拷贝
	void String_test4()
	{
		string s1("hello world");
		string s2("xxxxxx");
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		//swap(s1, s2);//系统会优先utility库中的swap函数而不是自定义函数（调试时位进入自定义函数）
		s1.swap(s2);//指定了使用s1类中的自定义swap函数并传入s2的地址
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
	}

	//尝试寻找字符
	void String_test5()
	{
		string s1("hello world");
		int num = s1.find("ld", 5);
		cout << num << endl;
		//substr的用例可以采用之前截取网站的用例，这里不写了
	}

	//尝试运算符重载
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