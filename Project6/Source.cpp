#include <iostream>
#include <vector>
#include <string>

class String {
private:
    std::vector<char> data;

public:
    String() = default;
    String(const std::string& str) : data(str.begin(), str.end()) {}

    String(const std::vector<char>& vec) : data(vec) {}

    void substitute(const std::string& from, const std::string& to) {
        std::vector<char> result;
        size_t pos = 0;

        while (pos < data.size()) {
            bool found = false;

            for (size_t i = pos; i <= data.size() - from.size(); ++i) {
                if (std::equal(from.begin(), from.end(), data.begin() + i)) {
                    result.insert(result.end(), data.begin() + pos, data.begin() + i);
                    result.insert(result.end(), to.begin(), to.end());
                    pos = i + from.size();
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.insert(result.end(), data.begin() + pos, data.end());
                break;
            }
        }
        data = result;
    }

    bool applySubstitutions(std::vector<std::pair<std::string, std::string>>& substitutions) {
        bool applied = false;
        for (auto sub : substitutions) {
            if (toString().find(sub.first) != std::string::npos)
            {
                if (!sub.second.empty() && sub.second.front() == '.')
                {
                    std::string temp(data.begin(), data.end());
                    sub.second.erase(0, 1);
                    temp.replace(temp.find(sub.first), sub.first.size(), sub.second);
                    data = std::vector<char>(temp.begin(), temp.end());
                    return false;
                }
                substitute(sub.first, sub.second);
                applied = true;
                break;
            }
        }

        return applied;
    }
    std::string toString() const {
        return std::string(data.begin(), data.end());
    }
};

void MarkovAlgorithm(String& str,std::vector<std::pair<std::string, std::string>>& substitutions) 
{
	while (str.applySubstitutions(substitutions));
}
int main() {
    /*String example1("|*||");

    std::vector<std::pair<std::string, std::string>> substitutions1 = {
        {"|b", "ba|"},
        {"ab", "ba"},
        {"b", ""},
        {"*|", "b*"},
        {"*", "c"},
        {"|c", "c"},
        {"ac", "c|"},
        {"c", "."},
    };

    MarkovAlgorithm(example1, substitutions1);

    String example2("101");
    std::vector<std::pair<std::string, std::string>> substitutions2 = {
		{"1", "0|"},
		{"|0", "0||"},
		{"0", ""},
	};

    MarkovAlgorithm(example2, substitutions2);

    std::cout << example1.toString() << std::endl;
    std::cout << example2.toString() << std::endl;*/

    std::string input;
    std::cout << "Enter the initial string: ";
    std::getline(std::cin, input);
    String example3(input);

    std::vector<std::pair<std::string, std::string>> substitutions3;
    std::cout << "Enter substitution rules, end with 'stop': " << std::endl;
    while (true) 
    {
        std::string from, to;

        std::cout << "from: ";
        std::getline(std::cin, from);

        if (from == "stop") {
            break;
        }

        std::cout << "to: ";
        std::getline(std::cin, to);

        substitutions3.push_back({ from, to });
    
	}
    std::cout << "Entered substitution rules:" << std::endl;
    for (auto rule : substitutions3) {
        std::cout << "\"" << rule.first << "\"";
        if (!rule.second.empty() && rule.second.front() == '.')
        {
            
            rule.second.erase(0, 1);
            std::cout << " ->.";
        }
        else
        {
            std::cout << " -> ";
        }
        std::cout << "\"" << rule.second << "\"" << std::endl;
    }
    MarkovAlgorithm(example3, substitutions3);
    
    std::cout << "Result: " << example3.toString() << std::endl;
    return 0;
}
