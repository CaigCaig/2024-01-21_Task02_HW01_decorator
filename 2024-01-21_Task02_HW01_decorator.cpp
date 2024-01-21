#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) const {
        std::string data_r = data;
        std::reverse(data_r.begin(), data_r.end());
        text_->render(data_r);
    }
};

class Link : public DecoratedText{
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& url, const std::string& data) const {
        std::cout << "<a href=";
        text_->render(url);
        std::cout << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() {
    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");
    std::cout << std::endl;

    auto text_block_p = new Paragraph(new Text());
    text_block_p->render("Hello world");
    std::cout << std::endl;

    auto text_block_r = new Reversed(new Text());
    text_block_r->render("Hello world");
    std::cout << std::endl;

    auto text_block_l = new Link(new Text());
    text_block_l->render("netology.ru", "Hello world");
    std::cout << std::endl;

    system("pause");
}

/*

В программу рендеринга HTML из лекции (раздел про паттерн «Декоратор») добавьте новые классы для декорирования текста.

class Paragraph: ...

auto text_block = new Paragraph(new Text());
text_block->render("Hello world");

>>> <p>Hello world</p>
class Reversed: ...
 
auto text_block = new Reversed(new Text());
text_block->render("Hello world");

>>> dlrow olleH
class Link: ...

auto text_block = new Link(new Text());
text_block->render("netology.ru", "Hello world");

>>> <a href=netology.ru>Hello world</a>
Обратите внимание

Сигнатура метода Link::render() не совпадает с сигнатурой оригинального метода.
Для разворота строки используйте функцию std::reverse cppreference.

*/