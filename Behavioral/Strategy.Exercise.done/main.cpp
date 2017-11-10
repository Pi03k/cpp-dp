#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

struct StatResult
{
  std::string description;
  double value;

  StatResult(const std::string& desc, double val) : description(desc), value(val)
  {
  }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

using DataAction = std::function<Results(const Data&)>;

struct Average
{
  Results operator() (const Data& data)
  {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = sum / data.size();
    StatResult result("AVG", avg);
    return { {result} };
  }
}; // class Average

struct MinMax
{
  Results operator() (const Data& data_)
  {
    double min = *(std::min_element(data_.begin(), data_.end()));
    double max = *(std::max_element(data_.begin(), data_.end()));

    Results results_;
    results_.push_back(StatResult("MIN", min));
    results_.push_back(StatResult("MAX", max));
    return results_;
  }
}; // class MinMax

struct Sum
{
  Results operator() (const Data& data_)
  {
    double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
    return { StatResult("SUM", sum) };
  }
}; // class Sum

class DataAnalyzer
{
  Data data_;
  Results results_;

  public:
  DataAnalyzer()
    : data_(), results_()
  {
  }

  void load_data(const std::string& file_name)
  {
    data_.clear();
    results_.clear();

    std::ifstream fin(file_name.c_str());
    if (!fin)
      throw std::runtime_error("File not opened");

    double d;
    while (fin >> d)
    {
      data_.push_back(d);
    }

    std::cout << "File " << file_name << " has been loaded...\n";
  }

  void calculate(DataAction dataAction)
  {
    const auto& actionResults = dataAction(data_);
    //results_.insert(results_.end(), actionResults.begin(), actionResults.end());
    // Still copying - not moving.
    move(actionResults.begin(), actionResults.end(), std::back_inserter(results_));
  }

  const Results& results() const
  {
    return results_;
  }
};

void show_results(const Results& results)
{
  for (const auto& rslt : results)
    std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
  DataAnalyzer da{};
  da.load_data("data.dat");

  da.calculate(Average{});
  da.calculate(MinMax{});
  da.calculate(Sum{});

  show_results(da.results());

  std::cout << "\n\n";

  da.load_data("new_data.dat");
  da.calculate(Sum{});

  show_results(da.results());
}

