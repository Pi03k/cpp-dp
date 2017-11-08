#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include <iostream>
#include <string>
#include <memory>
#include "hrinfo.hpp"

class Employee
{
	private:
		std::string name_;
	protected:
		std::string name() const
		{
			return name_;
		}
	public:
		Employee(const std::string& name);
		virtual ~Employee() = default;

		virtual void description() const = 0;
		virtual std::unique_ptr<HRInfo> generateInfo() const = 0;
};

class Salary : public Employee
{
	public:
		Salary(const std::string& name);

		void description() const override;
		std::unique_ptr<HRInfo> generateInfo() const override;
};

class Hourly : public Employee
{
	public:
		Hourly(const std::string& name);

		void description() const override;
		std::unique_ptr<HRInfo> generateInfo() const override;
};

class Temp : public Employee
{
	public:
		Temp(const std::string& name);

		void description() const override;
		std::unique_ptr<HRInfo> generateInfo() const override;
};

#endif /* EMPLOYEE_HPP_ */
