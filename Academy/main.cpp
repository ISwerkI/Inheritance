#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------------------\n"

//#define INHERITANCE

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
	~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}
	virtual std::ostream& info(std::ostream& os)const
	{
		os.width(LAST_NAME_WIDTH);
		os << std::left;
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}
};
int Human::count = 0;
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	//return os << obj.get_first_name() << "," << obj.get_last_name() << "," << obj.get_age();
	return obj.info(os);
}

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
	~Student()
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
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//				Metods
	std::ostream& info(std::ostream& os)const override
	{
		AcademyMember::info(os);
		return os << experience << endl;
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
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os);
		return os << Diploma_colour << endl;
	}
};

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

	Human* group[] =
	{
		new Student("Кондратенко","Георгий", 18, "РПО", "P-418", 97, 98),
		new Teacher("Stanne", "Michael",55,"Vocals",40),
		new Student("Щербаков", "Илья", 15, "РПО", "P-418", 100, 99.9),
		new Teacher("Henrikson","Martin", 50, "Bass", 40),
		new Student("Татевосян", "Элеонора", 17,"РПО" ,"P-418", 98, 48),
		new Graduate("Plekhov", "Danil", 15, "РПО","P-418",98,100,"Red")
	};
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
	}
	cout << "Количество участников: " << Human::get_count();
}


