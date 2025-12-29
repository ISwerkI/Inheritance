#include <iostream>
#include <fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------------------\n"

//#define INHERITANCE
//#define POLYMORPHISM

class Human
{
protected:
	static const int LAST_NAME_WIDTH = 12;
	static const int FIRST_NAME_WIDTH = 12;
	static const int AGE_WIDTH = 3;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;
public:
	//				get/set
	static int get_count()
	{
		return count;
	}
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}
	//				Constructors:
	Human(const std::string& last_name, const std::string& first_name, int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}
	virtual std::ostream& info(std::ostream& os)const
	{
		os.width(11);
		os << std::left;
		os << std::string(typeid(*this).name()+6) + ":"; 
		os.width(LAST_NAME_WIDTH);
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}
	virtual std::ofstream& write(std::ofstream& ofs)const
	{
		ofs << typeid(*this).name() + 6 << ":";
		ofs << last_name << " " << first_name << " " << age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};
int Human::count = 0;
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	//return os << obj.get_first_name() << "," << obj.get_last_name() << "," << obj.get_age();
	return obj.info(os);
}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	obj.read(ifs);
	return ifs;
}
/*std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	obj.write(ofs);
	return ofs;
}
*/

class AcademyMember :public Human
{
	static const int SPECIALITY_WIDTH = 16;
	std::string speciality;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	//			Constructors
	AcademyMember(const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality): Human(last_name,first_name,age)
	{
		set_speciality(speciality);
		cout << "AMConstructor:\t" << this << endl;
	}
	~AcademyMember()
	{
		cout << "AMDestructor:\t" << this << endl;
	}
	//			Metods
	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		return os;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs << " " << speciality;
		return ofs;
	}
};
std::ostream& operator<<(std::ostream& os, const AcademyMember& obj)
{
	return os << obj.get_speciality();
}


class Student :public AcademyMember
{
protected:
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_group()const
	{
		return group;
	}
	const double get_rating() const
	{
		return rating;
	}
	const double get_attendance() const
	{
		return attendance;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendence(double attendance)
	{
		this->attendance = attendance;
	}

	Student(const std::string& last_name, const std::string& first_name, 
		int age,const std::string& speciality, const std::string& group, 
		double rating, double attendance
	): AcademyMember(last_name, first_name, age, speciality)
	{
		set_group(group);
		set_rating(rating);
		set_attendence(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	virtual ~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		AcademyMember::info(os);
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(ATTENDANCE_WIDTH);
		os << attendance;
		return os;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		AcademyMember::write(ofs);
		ofs << " " << group << " " << rating << " " << attendance;
		return ofs;
	}
};
std::ostream& operator<<(std::ostream& os, const Student& obj)
{
	return os << obj.get_group() << ", " << obj.get_rating() << ", " << obj.get_attendance();

}

class Teacher :public AcademyMember
{
	int experience;
public:
	int get_experience()const
	{
		return experience;
	}
	void set_expirience(int experience)
	{
		this->experience = experience;
	}
	//				Constructor
	Teacher(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality, int experience
	) : AcademyMember(last_name, first_name, age, speciality)
	{
		set_expirience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	virtual ~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//				Metods
	std::ostream& info(std::ostream& os)const override
	{
		AcademyMember::info(os);
		return os << experience << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		AcademyMember::write(ofs);
		ofs << " " << experience;
		return ofs;
	}
};

class Graduate : public Student
{
	std::string Diploma_colour;
public:
	const std::string& get_Diploma_colour()const
	{
		return Diploma_colour;
	}
	void set_Diploma_colour(const std::string& Diploma_colour)
	{
		this->Diploma_colour = Diploma_colour;
	}
	Graduate
	(
		const std::string& last_name, const std::string& first_name,int age,
		const std::string& speciality, 
		const std::string& group,double rating, double attendance,
		const std::string& Diploma_colour
	): Student
	(
		last_name,first_name,age, 
		speciality, 
		group,rating, attendance
	)
	{
		set_Diploma_colour(Diploma_colour);
		cout << "GConstructor:\t" << this << endl;
	}
	virtual ~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os);
		return os << Diploma_colour << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		AcademyMember::write(ofs);
		ofs << " " << Diploma_colour;
		return ofs;
	}
};

void Print(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
	}
}
void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}

Human** Load(std::string filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		n = 0;
		std::string buffer;
		for (;!fin.eof(); n++)
		{
			std::getline(fin, buffer);
		}
		cout << n << endl;
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fin.close();
	return group;
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE
	//Human Danil("Plekhov", "Danil", 15);
	//Danil.info();
	AcademyMember albert("Einstein", "Albert", 146,"Asreonomy");
	albert.info();
	Student Danil("Данил", "Плехов", 15, "Разработка ПО", "P-418", 100, 100);
	Danil.info();
	Teacher Albert("Einstein", "Albert", 146, "Astronomy", 120);
	Albert.info();
#endif

#ifdef POLYMORPHISM


	Human* group[] =
	{
		new Student("Кондратенко","Георгий", 18, "РПО", "P-418", 97, 98),
		new Teacher("Stanne", "Michael",55,"Vocals",40),
		new Student("Щербаков", "Илья", 15, "РПО", "P-418", 100, 99.9),
		new Teacher("Henrikson","Martin", 50, "Bass guitar", 40),
		new Student("Татевосян", "Элеонора", 17,"РПО" ,"P-418", 98, 48),
		new Graduate("Plekhov", "Danil", 15, "РПО","P-418",98,100,"Red")
	};
	Print(group, sizeof(group) / sizeof(group[0]));
	cout << "Количество участников: " << Human::get_count() << endl;
	Save(group, sizeof(group) / sizeof(group[0]), "P_418.txt");
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++) delete group[i];
	std::ifstream fin("Group.txt");
	fin.close();
	system("start notepad Group.txt");
#endif // POLYMORPHISM

}


