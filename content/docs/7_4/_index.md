---
weight: 7
bookFlatSection: true
title: "7.4 private本类可访问"
---

## private本类可访问

自行编译理解以下代码

```
//test_private.cpp
//知识点：private 本类可访问
//编译：g++ my.cpp
#include <iostream>
class Course {
public :
     int getDifficulty( ) { return difficulty;}
private:
	int periodCount( );
	int course;
	int difficulty;
};

class Student{
	public:
		Student(int sc,int st);
		void study(Course & course); 
		void help(Student& other);
		void exercise(){}
	private :
		int otherFunc(){ return 1;}
	private:
		int score;
		int strength;
};

void Student:: study(Course & course){
	score += 1; 
	strength -= course.getDifficulty();
	otherFunc();//OK
	//int n = course.periodCount( ); //wrong  Course类不可访问private函数
}

void Student:: help(Student& other){
	other.score += 2;  //本类可访问private变量
	strength -= 2;
	other.strength -= 4;
	other.exercise( ); 
	otherFunc( );//OK
	other.otherFunc();//OK
}
	
int main()
{

	return 0;
} 

```

## C++类中对同类对象private成员访问

私有成员变量的概念，在脑海中的现象是，以private关键字声明，是类的实现部分，不对外公开，不能在对象外部访问对象的私有成员变量．

　　然而，在实现拷贝构造函数和赋值符函数时，在函数里利用对象直接访问了私有成员变量，因而，产生了困惑．下面以具体实例进行说明：

　　疑惑：为什么第26行和第32行代码可以编译通过，而第39行和第40行代码会产生编译错误？

**答： 私有是指在类外不能访问,并没说在对象间不能访问。**

```
class CTest {
public:
    CTest(int i); 
    CTest(const CTest& rhs);
    CTest& operator=(const CTest& rhs);
    void printCTest(const CTest& rhs);
private:
    int value;
};
 
CTest::CTest(int i):value(i)
{
    cout<<"Contructor of CTest"<<endl;
}
 
CTest::CTest(const CTest& rhs):value(rhs.value)
{
    cout<<"Copy contructor of CTest"<<endl;
}
 
CTest& CTest::operator=(const CTest& rhs)
{
    cout<<"Assign function of CTest"<<endl;
    if(this == &rhs)
        return *this;
    value = rhs.value;                //通过对象访问私有成员变量
    return *this;
}
 
void CTest::printCTest(const CTest& rhs)
{
    cout<<rhs.value<<endl;        //通过对象访问私有成员变量
}
 
int main()
{
    CTest t = 1;
    CTest tt = 2;
    //  cout<<t.value<<endl;        //通过对象访问私有成员变量，编译错误
    //  cout<<tt.value<<endl;        //通过对象访问私有成员变量，编译错误
    t.printCTest(tt);
}
```

产生这种疑惑的原因是自己对私有成员变量的理解有误，封装是编译期的概念，是针对类型而非对象的，在类的成员函数中可以访问同类型实例对象的私有成员变量．

具体的解析如下：从变量value的符号是怎么解析的分析．

**1. 确定符号的查找域**

如第26行代码，当编译器发现value变量时，它会在value变量所属的对象rhs的类域中寻找该符号．

**2. 确定当前域中哪些符号可以访问**

由第1步可知，当前查找的域是类域，而printCTest函数在CTest类体中，所以printCTest可以访问CTest类中的所有变量(包括私有成员变量)，因而value符号在CTest类域中被找到．

如第39行代码，main函数不在CTest类体中，所以main函数不可以访问CTest类域中的私有成员变量．

**3. 符号已查找到，编译通过**

类成员变量的访问权限是编译器强加的，编译器可以找到value，通过编译，自然就可以访问到value变量的值．

**直觉上，我们会以为第26行代码中value符号的查找域应该是对象rhs对应的作用域，然而C++编译器的实现却是在对象rhs的类域查找value符号．**

- 启发：有些直觉是靠不住的，需要深入分析其背后的实现原理，才可以理解透彻．

- **总结：C++的访问修饰符的作用是以类为单位，而不是以对象为单位。**

通俗的讲，同类的对象间可以“互相访问”对方的数据成员，只不过访问途径不是直接访问.

回来查了一下String类的实现才明白，封装性是对类外的操作来说的，在类内操作本类的一个对象时，可以通过该对象访问其私有成员，这种设计也是挺合理的，因为类是自己设计的，当然自己也就知道类的内部结构，所以没有必要对自己也进行类的“封装”。另有一种说法是：“同种类之间是友元关系”。


步骤是：通过一个对象调用其public成员函数，此成员函数可以访问到自己的或者同类其他对象的public/private/protected数据成员和成员函数(类的所有对象共用)，而且还需要指明是哪个对象的数据成员(调用函数的对象自己的成员不用指明，因为有this指针；其他对象的数据成员可以通过引用或指针间接指明)

参考：[C++类中对同类对象private成员访问](https://blog.csdn.net/weixin_40539125/article/details/83120249/)