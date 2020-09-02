#include <iostream>
#include <fstream>
#include <cstdlib>

const char* filename = "records.bin";
const char* tempname = "temp.bin";

class Employee
{
	int32_t id;
	char name[25];
	int8_t age;
	char address[35];
	char role[20];
	double salary;
public:
	void display();
	void insert_employee();
	void display_employees();
	void search_employee();
	void edit_employee();
	void delete_employee();
	void show_employees();
};

void Employee::insert_employee()
{
	std::fstream iofile(filename, std::ios::binary || std::ios::in);
	iofile.seekg(0, std::ios::end);
	id = int32_t(iofile.tellg()) / sizeof(*this) + 1;
	iofile.close();

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Insert employee's name: ";
	std::cin.getline(name, sizeof(name));

	std::cout << "Insert employee's age: ";
	std::cin >> age;

	std::cout << "Insert employee's address: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.getline(address, sizeof(address));

	std::cout << "Insert employee's role: ";
	std::cin.getline(role, sizeof(role));

	std::cout << "Insert employee' salary: ";
	std::cin >> salary;

	iofile.open(filename, std::ios::binary | std::ios::app);
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
	iofile.close();
	std::cin.ignore();
}

void Employee::display()
{
	std::cout << "Id: " << id << '\n';
	std::cout << "Name: " << name << '\n';
	std::cout << "Age: " << age << '\n';
	std::cout << "Address: " << address << '\n';
	std::cout << "Role: " << role << '\n';
	std::cout << "Salary: " << salary << '\n';
}

void Employee::display_employees()
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.good())
	{
		std::perror("Error in file opening");
		return;
	}
	while (!in.eof())
	{
		if (in.read(reinterpret_cast<char*>(this), sizeof(*this)).good())
		display();
	}
	in.close();
}

void Employee::search_employee()
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.good())
	{
		std::perror("Error in file opening");
		return;
	}
	std::cout << "Enter employee's id: ";
	int64_t to_find;
std::cin >> to_find;
std::cout << '\n';
in.seekg((to_find - 1) * sizeof(*this));
in.read(reinterpret_cast<char*>(this), sizeof(*this));
in.close();
display();
}

void Employee::edit_employee()
{
	std::fstream iofile(filename, std::ios::binary | std::ios::in);
	if (!iofile.good())
	{
		std::perror("Error in file opening");
		return;
	}
	std::cout << "Enter employee's id: ";
	int64_t to_find;
	std::cin >> to_find;
	std::cout << '\n';
	std::cin.ignore();
	iofile.seekg((to_find - 1) * sizeof(*this));
	iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
	iofile.close();
	display();
	std::cout << "Enter new data: \n";
	std::cout << "Insert employee's name: ";
	std::cin.getline(name, sizeof(name));

	std::cout << "Insert employee's age: ";
	std::cin >> age;

	std::cout << "Insert employee's address: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.getline(address, sizeof(address));

	std::cout << "Insert employee's role: ";
	std::cin.getline(role, sizeof(role));

	std::cout << "Insert employee' salary: ";
	std::cin >> salary;

	iofile.open(filename, std::ios::binary | std::ios::out || std::ios::in);
	iofile.seekp((to_find - 1) * sizeof(*this));
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
	iofile.close();
	std::cin.ignore();
}

void Employee::delete_employee()
{
	std::cout << "Enter employee's id: ";
	int64_t to_find;
	std::cin >> to_find;
	std::cin.ignore();

	std::fstream iofile(filename, std::ios::binary || std::ios::in);
	if (!iofile.good())
	{
		std::perror("Error in file opening");
		return;
	}
	iofile.seekg(0, std::ios::end);
	int32_t last_id = int32_t(iofile.tellg()) / sizeof(*this);
	iofile.seekg(0);

	std::ofstream tempfile(tempname, std::ios::binary);

	int32_t current_id = 1;

	for (int i = 1; i <= last_id; i++)
	{
		iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
		id = current_id;
		if (i == to_find) continue;
		current_id++;
		tempfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	iofile.close();
	tempfile.close();
	if (std::remove(filename))
	{
		std::perror("Error removing");
		return;
	}
	if (std::rename(tempname, filename)) {
		std::perror("Error renaming");
		return;
	}
}

void Employee::show_employees()
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.good())
	{
		std::perror("Error in file opening");
		in.close();
		return;
	}
	if(!in.eof())
	{
		std::cout << "There are no entries avalable.\n";
		in.close();
		return;
	}
	while (!in.eof())
	{
		if (in.read(reinterpret_cast<char*>(this), sizeof(*this)).good())
		{
			if (salary > 20000)
			{
				display();
			}
		}
	}
	in.close();
}

int main()
{
	Employee em;
	bool running = true;
	std::cout << "Staff Managment System" << '\n';
	while (running)
	{
		std::cout << "Options:\n";
		std::cout << "1. Insert a new employee.\n";
		std::cout << "2. Display all employee.\n";
		std::cout << "3. Search for a specific employee.\n";
		std::cout << "4. Edit a specific employee.\n";
		std::cout << "5. Delete a specific employee.\n";
		std::cout << "6. Display all employees with a wage higher than 20k.\n";
		std::cout << "7. Quit.\n";
		int choice = -1;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			em.insert_employee();
			break;
		case 2:
			em.display_employees();
			break;
		case 3:
			em.search_employee();
			break;
		case 4:
			em.edit_employee();
			break;
		case 5:
			em.delete_employee();
			break;
		case 6: 
			em.show_employees();
			break;
		case 7: 
			running = false;
			break;
		default:
			std::cout << "Invalid choice: \n";
			break;
		}
		std::cin.ignore();
	}
}