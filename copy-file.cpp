#include <exception>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ParseError : public std::exception {
public:
    ParseError() = default;
    virtual const char *what() const noexcept override {
        return "cannot parse the arguments";
    }
};

class ArgumentParser {
public:
    ArgumentParser() = default;
    void add_argument(const std::string &arg) {
        args.insert(arg);
    }
    std::unordered_map<std::string, std::string> parse(int argc, char **argv) const {
        std::unordered_map<std::string, std::string> ret;
        std::string main_chain;
        for(int i = 0; i < argc; ++i) {
            if(args.count(argv[i]) != 0) {
                if(i == argc - 1) {
                    throw ParseError{};
                }
                ret[argv[i]] = argv[i + 1];
            } else {
                if(!main_chain.empty()) main_chain += ' ';
                main_chain += argv[i];
            }
        }
        ret["main_chain"] = main_chain;
        return ret;
    }
private:
    std::unordered_set<std::string> args;
};

namespace fs = std::filesystem;

constexpr int unused = 32, parse_error = 33, fs_error = 34, src_nexist = 35;

void print_usage() {
    std::cout << "------copy-file.exe------\n";
    std::cout << "usage:\n";
    std::cout << "./copy-file.exe -src [source-file] -dst [destination-position]\n";
    std::cout << "example:\n";
    std::cout << "./copy-file.exe -src usage/ds/seg.cpp -dst D:/contest/D.cpp\n";
    std::cout << std::endl;
}

void print_src_nexist() {
    std::cout << "------copy-file.exe------\n";
    std::cout << "the source file you have provided does not exist!\n";
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    try {
        ArgumentParser parser;
        parser.add_argument("-src");
        parser.add_argument("-dst");

        auto parse_result = parser.parse(argc, argv);
        if(parse_result.size() != 3) {
            print_usage();
            return unused;
        }

        // we may assume that parse_result have key "main_chain", "-src" and "-dst"
        std::string src_name = parse_result["-src"], dst_name = parse_result["-dst"];
        fs::path src(src_name), dst(dst_name);

        if(!fs::exists(src)) {
            print_src_nexist();
            return src_nexist;
        }

        if(fs::exists(dst)) {
            fs::remove(dst);
        }
        fs::copy_file(src, dst);

        std::cout << "copy success!" << std::endl;
    } catch(const ParseError &e) {
        std::cout << "parse error catched: " << e.what() << std::endl;
        return parse_error;
    } catch(const fs::filesystem_error &e) {
        std::cout << "filesystem error catched: " << e.what() << std::endl;
        return fs_error;
    }

    return 0;
}