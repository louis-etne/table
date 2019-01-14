//
// MIT License
//
// Copyright (c) 2019 Louis Etienne
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef TABLE_TABLE_HPP
#define TABLE_TABLE_HPP

#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

namespace table
{
    class Table
    {
    public:
        Table(std::vector<std::vector<std::string>> const &content, std::vector<std::string> const &headers)
        {
            content_ = content;
            headers_ = headers;

            // Get the maximum width of each column
            size_t col_nb{count_cols()}; // Column number
            size_t row_nb{count_rows()}; // Row number

            // Get width of each column
            for (size_t col{0}; col < col_nb; ++col) {
                widths_.push_back(0);
            }

            for (size_t row{0}; row < row_nb; ++row) {
                for (size_t col{0}; col < col_nb; ++col) {
                    if (content_[row][col].size() > widths_[col]) {
                        widths_[col] = content_[row][col].size();
                    }
                }
            }

            for (size_t col{0}; col < col_nb; ++col) {
                if (headers_[col].size() > widths_[col]) {
                    widths_[col] = headers_[col].size();
                }
            }
        }

        Table &set_bold_headers(bool const bold_headers)
        {
            bold_headers_ = bold_headers;
            return *this;
        }

        Table &set_is_ascii(bool const is_ascii)
        {
            is_ascii_ = is_ascii;
            return *this;
        }

        Table &set_padding_left(unsigned padding_left)
        {
            padding_left_ = padding_left;
            return *this;
        }

        Table &set_padding_right(unsigned padding_right)
        {
            padding_right_ = padding_right;
            return *this;
        }

        std::string render() const
        {
            std::string output;

            output += draw_top();

            for (size_t i{0}; i < content_.size(); ++i) {
                output += draw_cell(content_[i]);

                if (i < content_.size() - 1) {
                    output += draw_middle_line();
                }
                else {
                    output += draw_line("bottom", "bottom-left", "bottom-mid", "bottom-right");
                }
            }

            return output;
        }

    private:
        std::vector<size_t> widths_;
        std::vector<std::vector<std::string>> content_;
        std::vector<std::string> headers_;

        bool bold_headers_{false};
        bool is_ascii_{false};
        unsigned padding_left_{1};
        unsigned padding_right_{1};

        size_t count_cols() const
        {
            return headers_.size();
        }

        size_t count_rows() const
        {
            return content_.size();
        }

        std::string repeat(std::string const &symbol, size_t num) const
        {
            if (num < 2) {
                return symbol;
            }

            std::string output;
            for (size_t i{0}; i < num; ++i) {
                output.append(symbol);
            }

            return output;
        }

        std::string extend(std::string value, size_t const width, bool const is_bold) const
        {
            while (clean_string(value).size() < width) {
                value += " ";
            }

            // Add padding
            for (unsigned i{0}; i < padding_left_; ++i) {
                value.insert(0, " ");
            }

            for (unsigned i{0}; i < padding_right_; ++i) {
                value.append(" ");
            }

            // Add bold
            if (is_bold) {
                value.insert(0, "\033[1m");
                value.append("\033[0m");
            }

            return value;
        }

        std::string clean_string(std::string const &value) const
        {
            std::regex rgx{"\033\[[0-9]+m"};

            return std::regex_replace(value, rgx, "");
        }

        // Drawing
        std::string draw_line(std::string const &symbol, std::string const &left, std::string const &middle, std::string const &right) const
        {
            std::string output;

            // Top line
            output += get_symbols().at(left);
            for (size_t i{0}; i < widths_.size(); ++i) {
                output += repeat(get_symbols().at(symbol), widths_[i] + (padding_left_ + padding_right_));

                if (i < widths_.size() - 1) {
                    output += get_symbols().at(middle);
                }
                else {
                    output += get_symbols().at(right);
                }
            }
            output += "\n";

            return output;
        }

        std::string draw_middle_line() const
        {
            return draw_line("mid", "left-mid", "mid-mid", "right-mid");
        }

        std::string draw_top() const
        {
            std::string output;

            // Top line
            output += draw_line("top", "top-left", "top-mid", "top-right");

            // Headers line
            output += draw_cell(headers_, true);

            // Bottom line
            output += draw_middle_line();

            return output;
        }

        std::string draw_cell(std::vector<std::string> const &row) const
        {
            return draw_cell(row, false);
        }

        std::string draw_cell(std::vector<std::string> const &row, bool is_headers) const
        {
            std::string output;

            output += get_symbols().at("left");
            for (size_t i{0}; i < widths_.size(); ++i) {
                output += extend(row[i], widths_[i], is_headers && bold_headers_);

                if (i < widths_.size() - 1) {
                    output += get_symbols().at("middle");
                }
                else {
                    output += get_symbols().at("right");
                }
            }
            output += "\n";

            return output;
        }

        std::map<std::string, std::string> get_symbols() const
        {
            if (is_ascii_) {
                return {{"top", "-"},
                        {"top-mid", "+"},
                        {"top-left", "+"},
                        {"top-right", "+"},
                        {"bottom", "-"},
                        {"bottom-mid", "+"},
                        {"bottom-left", "+"},
                        {"bottom-right", "+"},
                        {"left", "|"},
                        {"left-mid", "+"},
                        {"mid", "-"},
                        {"mid-mid", "+"},
                        {"right", "|"},
                        {"right-mid", "+"},
                        {"middle", "|"}};
            }
            else {
                return {{"top", "─"},
                        {"top-mid", "┬"},
                        {"top-left", "┌"},
                        {"top-right", "┐"},
                        {"bottom", "─"},
                        {"bottom-mid", "┴"},
                        {"bottom-left", "└"},
                        {"bottom-right", "┘"},
                        {"left", "│"},
                        {"left-mid", "├"},
                        {"mid", "─"},
                        {"mid-mid", "┼"},
                        {"right", "│"},
                        {"right-mid", "┤"},
                        {"middle", "│"}};
            }
        }
    };

    inline std::ostream &operator<<(std::ostream &os, Table const &table)
    {
        return os << table.render();
    }
}

#endif //TABLE_TABLE_HPP
