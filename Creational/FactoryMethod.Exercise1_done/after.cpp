#include <memory>
#include <vector>
#include <map>
#include <string>

#include "employee.hpp"
#include "hrinfo.hpp"

int main()
{
	using namespace std;

	vector<std::unique_ptr<Employee>> emps;
	emps.push_back(make_unique<Salary>("Jan Kowalski"));
	emps.push_back(make_unique<Hourly>("Adam Nowak"));
	emps.push_back(make_unique<Temp>("Anna Nowakowska"));

	cout << "HR Report:\n---------------\n";
	// generowanie obiektów typu HRInfo
	for (const auto& emp : emps)
	{
		auto hri = emp->generateInfo();
		hri->info();
		cout << endl;
	} // wyciek pamięci
}
