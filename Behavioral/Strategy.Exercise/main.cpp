#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
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

//enum StatisticsType
//{
//    avg,
//    min_max,
//    sum
//};

class Statistics
{
public:
    virtual Results calculate(const Data& data_) = 0;
    virtual ~Statistics() = default;
};

using StatisticsCpp11 = std::function<Results(const Data&)>;

struct AvgCpp11
{
    Results operator()(const Data& data_)
    {
        double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
        double avg = sum / data_.size();

        return { {"AVG", avg } };
    }
};


class Avg : public Statistics
{
    // Statistics interface
public:
    Results calculate(const Data& data_) override
    {
        double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
        double avg = sum / data_.size();

        return { {"AVG", avg } };
    }
};

class MinMax : public Statistics
{
    // Statistics interface
public:
    Results calculate(const Data& data_) override
    {
        double min = *(std::min_element(data_.begin(), data_.end()));
        double max = *(std::max_element(data_.begin(), data_.end()));

        return { {"MIN", min }, { "MAX", max} };
    }
};

class Sum : public Statistics
{
public:
    Results calculate(const Data& data_) override
    {
        double sum = std::accumulate(data_.begin(), data_.end(), 0.0);

        return  { {"SUM", sum } };
    }
};

using StatisticsPtr = std::shared_ptr<Statistics>;

class DataAnalyzer
{
    StatisticsPtr stat_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(StatisticsPtr stat) : stat_{stat}
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

    void set_statistics(StatisticsPtr stat)
    {
        stat_ = stat;
    }

    void calculate()
    {
        auto tmp_results = stat_->calculate(data_);

        move(tmp_results.begin(), tmp_results.end(), std::back_inserter(results_));        
    }

    const Results& results() const
    {
        return results_;
    }
};

class StatGroup : public Statistics
{
    std::vector<StatisticsPtr> stats_;
public:
    void add(StatisticsPtr stat)
    {
        stats_.push_back(stat);
    }

    Results calculate(const Data& data) override
    {
        Results results;
        for(const auto& stat : stats_)
        {
            auto tmp_results = stat->calculate(data);

            move(tmp_results.begin(), tmp_results.end(), std::back_inserter(results));   
        }

        return results;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    auto avg = std::make_shared<Avg>();
    auto min_max = std::make_shared<MinMax>();
    auto sum = std::make_shared<Sum>();
    auto std_stats = std::make_shared<StatGroup>();
    std_stats->add(avg);
    std_stats->add(min_max);
    std_stats->add(sum);

    DataAnalyzer da{std_stats};
    da.load_data("data.dat");
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_data.dat");
    da.calculate();

    show_results(da.results());
}
