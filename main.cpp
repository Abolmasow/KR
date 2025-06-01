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

// Класс для проверки тегов на безопасность
class TagValidator {
private:
    std::unordered_set<std::string> safe_tags = { "a", "b", "i", "u", "p" }; // Разрешенные теги

public:
    bool isSafe(const HtmlTag& tag) {
        return safe_tags.find(tag.name) != safe_tags.end();
    }
};

// Класс для обработки атрибутов
class AttributeHandler {
public:
    void sanitizeAttributes(HtmlTag& tag) {
// В данном примере просто очищаем атрибуты
        tag.attributes.clear();
    }
};

// Класс для генерации итогового HTML
class HtmlGenerator {
public:
    std::string generate(const std::vector<HtmlTag>& tags) {
        std::ostringstream result;
        for (const auto& tag : tags) {
            result << "<" << tag.name << ">";
        }
        return result.str();
    }
};

// Класс для основного санитайзера
class HtmlSanitizer {
private:
    HtmlParser parser;
    TagValidator validator;
    AttributeHandler attributeHandler;
    HtmlGenerator generator;

public:
    std::string sanitize(const std::string& html) {
        auto tags = parser.parse(html);
        std::vector<HtmlTag> safe_tags;
        for (auto& tag : tags) {
            if (validator.isSafe(tag)) {
                attributeHandler.sanitizeAttributes(tag);
                safe_tags.push_back(tag);
            }
        }
        return generator.generate(safe_tags);
    }
};

// Класс для ведения логов
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }
};

// Класс для обработки ошибок
class ErrorHandler {
public:
    void handleError(const std::string& error) {
        std::cerr << "[ERROR]: " << error << std::endl;
    }
};

// Класс для тестирования санитайзера
class SanitizerTester {
private:
    Logger logger;

public:
    void test() {
        HtmlSanitizer sanitizer;
        std::string input = "<script>alert('XSS');</script><b>Bold</b>";
        std::string output = sanitizer.sanitize(input);
        logger.log("Input: " + input);
        logger.log("Output: " + output);
    }
};