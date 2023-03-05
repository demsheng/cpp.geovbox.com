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

