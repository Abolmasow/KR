#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <regex>

using namespace std;

class HtmlTag {
public:
    string name;

    HtmlTag(const string& tagName) : name(tagName) {}
    virtual ~HtmlTag() = default;
};

class SafeTag : public HtmlTag {
public:
    SafeTag(const string& tagName) : HtmlTag(tagName) {}
};

class UnsafeTag : public HtmlTag {
public:
    UnsafeTag(const string& tagName) : HtmlTag(tagName) {}
};

class HtmlParser {
public:
    vector<string> parse(const string& html) {
        regex tagRegex(R"(<\s([^ >]+)[^>]>)");
        vector<string> tags;
        smatch match;

        auto searchStart = html.cbegin();
        while (regex_search(searchStart, html.cend(), match, tagRegex)) {
            tags.push_back(match[1].str());
            searchStart = match.suffix().first;
        }
        return tags;
    }
};

class TagFactory {
public:
    static HtmlTag* createTag(const string& name, bool isSafe) {
        if (isSafe) {
            return new SafeTag(name);
        } else {
            return new UnsafeTag(name);
        }
    }
};

class TagValidator {
private:
    unordered_set<string> safeTags = { "b", "i", "u", "p", "a" }; // Разрешенные теги

public:
    bool isSafe(const string& tag) {
        return safeTags.find(tag) != safeTags.end();
    }
};

class AttributeHandler {
public:
    void sanitizeAttributes(HtmlTag& tag) {
// В данном случае мы просто игнорируем их
    }
};

class HtmlGenerator {
public:
    string generate(const vector<HtmlTag*>& tags) {
        ostringstream result;
        for (const auto& tag : tags) {
            result << "<" << tag->name << "></" << tag->name << ">";
        }
        return result.str();
    }
};

class HtmlSanitizer {
private:
    HtmlParser parser;
    TagValidator validator;
    AttributeHandler attributeHandler;
    HtmlGenerator generator;

public:
    string sanitize(const string& html) {
        vector<HtmlTag*> safeTags;
        auto tags = parser.parse(html);

        for (const auto& tagName : tags) {
            bool isSafe = validator.isSafe(tagName);
            HtmlTag* tag = TagFactory::createTag(tagName, isSafe);
            attributeHandler.sanitizeAttributes(*tag);

            if (isSafe) {
                safeTags.push_back(tag);
            } else {
                delete tag; // Удаляем небезопасный тег
            }
        }

        string sanitizedHtml = generator.generate(safeTags);

        for (auto tag : safeTags) {
            delete tag; // Очистка памяти
        }

        return sanitizedHtml;
    }
};

// Пример использования
int main() {
    HtmlSanitizer sanitizer;
    string input = "<script>alert('XSS');</script><b>Bold</b><i>Italic</i><u>Underline</u>";
    string output = sanitizer.sanitize(input);

    cout << "Input HTML: " << input << endl;
    cout << "Sanitized HTML: " << output << endl;

    return 0;
}