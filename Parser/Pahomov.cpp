#include<iostream>
#include<fstream>
#include<string>
#include"nlohmann/json.hpp"
#include <any>
#include <iomanip>

struct Student {
	std::string name;
	std::any group;
	std::any avg;
	std::any debt;
};

auto get_name(const nlohmann::json& j)
{
	if (j.is_string())
		return j.get<std::string>();
	else
	{
		std::cout << "ERROR: Wrong type of Student" << std::endl;
		exit(0);
	}

};

auto get_avg(const nlohmann::json& j) -> std::any {
	if (j.is_null())
		return nullptr;
	else if (j.is_string())
		return j.get<std::string>();
	else if (j.is_number_float())
		return j.get<float>();
	else if (j.is_number())
		return j.get<int>();
	else
	{
		std::cout << "ERROR: Wrong type of Avg" << std::endl;
		exit(0);
	}
}

auto get_group(const nlohmann::json& j) -> std::any
{
	if (j.is_null())
		return nullptr;
	else if (j.is_string())
		return j.get<std::string>();
	else if (j.is_number_float())
		return j.get<double>();
	else if (j.is_number())
		return j.get<int>();
	else
	{
		std::cout << "ERROR: Wrong type of Group" << std::endl;
		exit(0);
	}
};

auto get_debt(const nlohmann::json& j) -> std::any
{
	if (j.is_null())
		return nullptr;
	else if (j.is_string())
		return j.get<std::string>();
	else
		return j.get<std::vector<std::string> >();
};

auto print_student(struct Student s)
{
	std::cout << " | "<<std::setw(15);
	std::cout << s.name;

	std::cout << " | "<< std::setw(15);
	if (s.group.type() == typeid(std::nullptr_t)) {
		std::cout << "null";
	}
	else if (s.group.type() == typeid(std::string))
	{
		std::cout << std::any_cast<std::string>(s.group);
	}
	else if (s.group.type() == typeid(int))
	{
		std::cout << std::any_cast<int>(s.group);
	}
	else if (s.group.type() == typeid(double))
	{
		std::cout << std::any_cast<double>(s.group);
	}

	std::cout<< " | " << std::setw(15);
	if (s.avg.type() == typeid(std::nullptr_t)) {
		std::cout << "null";
	}
	else if (s.avg.type() == typeid(std::string))
	{
		std::cout << std::any_cast<std::string>(s.avg);
	}
	else if (s.group.type() == typeid(float))
	{
		std::cout << std::any_cast<float>(s.avg);
	}
	else if (s.group.type() == typeid(int))
	{
		std::cout << std::any_cast<int>(s.avg);
	}

	std::cout << " | " << std::setw(15);
	if (s.debt.type() == typeid(std::nullptr_t)) {
		std::cout<< "null";
	}
	else if (s.debt.type() == typeid(std::string)) {
		std::cout << std::any_cast<std::string>(s.debt);
	}
	else {
		std::cout << std::any_cast<std::vector<std::string>>(s.debt).size();
	}
	std::cout << " | " << std::endl;
	
};

auto PrintHedder()
{
	std::cout << " | " << std::setw(15);
	std::cout << " name ";
	std::cout << " | " << std::setw(15);
	std::cout << " group ";
	std::cout << " | " << std::setw(15);
	std::cout << " avg ";
	std::cout << " | " << std::setw(15);
	std::cout << " debt ";
	std::cout << " | " << std::endl;
}

auto InputAdress()
{
	std::string adress;
	std::cout << "adress of json file: ";
	std::cin >> adress;
	return adress;
}

int main()
{
	nlohmann::json objJson;

	std::fstream fileInput;
	std::string adress = InputAdress();
	
	fileInput.open(adress);

	if (fileInput.is_open())
	{
		fileInput >> objJson;

		int size = objJson["_meta"][0]["count"];

		PrintHedder();

		for (int i = 0; i < size; i++)
		{
			Student s;
			s.name = get_name(objJson["items"][i]["name"]);
			s.group = get_group(objJson["items"][i]["group"]);
			s.avg = get_avg(objJson["items"][i]["avg"]);
			s.debt = get_debt(objJson["items"][i]["debt"]);
			print_student(s);
		}
	}
	else
	{
		std::cout << "ERROR: No file: " <<adress <<std::endl;
	}

	
	
};
