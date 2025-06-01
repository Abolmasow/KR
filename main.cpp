#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>

// Класс для представления HTML-тега
class HtmlTag {
public:
    std::string name;
    std::unordered_set<std::string> attributes;

    HtmlTag(const std::string& name) : name(name) {}
};
