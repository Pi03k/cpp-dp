#include "report_builder.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>

using namespace std;

class DataParser
{
public:
    explicit DataParser(ReportBuilder& report_builder) : report_builder_(report_builder)
    {
    }

    virtual void Parse(const std::string& file_name)
    {
        report_builder_.add_header(string("Raport from file: ") + file_name);

        report_builder_.begin_data();

        ifstream fin(file_name.c_str());

        while (!fin.eof())
        {
            string row;
            getline(fin, row);

            DataRow data;
            string delimiters = "\t ";
            boost::split(data, row, boost::is_any_of(delimiters), boost::algorithm::token_compress_on);

            report_builder_.add_row(data);
        }

        report_builder_.end_data();

        report_builder_.add_footer("Copyright RaportBuilder 2013");
    }

    virtual ~DataParser() = default;

public:
    ReportBuilder& report_builder_;
};

int main()
{
    HtmlReportBuilder html_builder;

    DataParser parser(html_builder);
    parser.Parse("data.txt");

    HtmlDocument doc = html_builder.get_report();

    cout << doc << endl;

    //	CsvReportBuilder csv_builder;

    //	DataParser parser(csv_builder);
    //    parser.Parse("../data.txt");

    //	CsvDocument doc = csv_builder.get_report();

    //	for(CsvDocument::const_iterator it = doc.begin(); it != doc.end(); ++it)
    //		cout << *it << endl;
}
