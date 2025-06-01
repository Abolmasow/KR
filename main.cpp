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

// Класс для парсинга HTML
class HtmlParser {
public:
    std::vector<HtmlTag> parse(const std::string& html) {
        std::vector<HtmlTag> tags;
// Простейший парсинг HTML (для примера; реальный парсер был бы сложнее)
        size_t pos = 0;
        while ((pos = html.find('<', pos)) != std::string::npos) {
            size_t end = html.find('>', pos);
            if (end == std::string::npos) break;

            std::string tag_content = html.substr(pos + 1, end - pos - 1);
            HtmlTag tag(getTagName(tag_content));
            tags.push_back(tag);
            pos = end + 1;
        }
        return tags;
    }

private:
    std::string getTagName(const std::string& tag_content) {
        size_t space_pos = tag_content.find(' ');
        return space_pos != std::string::npos ? tag_content.substr(0, space_pos) : tag_content;
    }
};