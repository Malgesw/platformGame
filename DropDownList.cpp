#include "DropDownList.h"

DropDownList::DropDownList(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Font &textFont,
                           int textSize, std::vector<std::string> fields, const std::string& description,
                           sf::Vector2f descrPosition, sf::Color hoverColor, sf::Color pressedColor, sf::Color textColor) :
                           firstElement(new Button(size, position, color, fields[0], textFont, textSize, hoverColor, pressedColor, 'D', textColor)){

    firstElement->setTextPosition(sf::Vector2f(firstElement->getTextPosition().x, firstElement->getTextPosition().y - 5.f));

    position.y += size.y;

    for(auto &f: fields){

        buttonList.push_back(std::make_unique<Button>(size, position, color, f, textFont, textSize, hoverColor, pressedColor, 'D', textColor));
        position.y += size.y;

    }

    for(auto &b : buttonList){
        b->setTextPosition(sf::Vector2f(b->getTextPosition().x, b->getTextPosition().y - 5.f));
    }

    isOpen = false;
    keyClock.restart();
    maxKeyTime = 0.5f;

    descriptionText.setString(description);
    descriptionText.setPosition(descrPosition);
    descriptionText.setCharacterSize(textSize);
    descriptionText.setFont(textFont);

}

void DropDownList::update(sf::Vector2f mousePos, sf::RenderWindow *window) {

    firstElement->update(mousePos);

    if(firstElement->isPressed() && isReady()){

        if(isOpen)
            isOpen = false;
        else
            isOpen = true;

    }

    if(isOpen){

        for(auto &b : buttonList){

            b->update(mousePos);

            if(b->isPressed() && isReady()){

                isOpen = false;
                firstElement->setField(b->getField());

                std::ofstream ofs;
                std::string first = firstElement->getField();
                std::string w,h;

                for(int i = 0; i < first.find('x'); i++)
                    w += first[i];

                for(int i = first.find('x')+1; i < first.size(); i++)
                    h += first[i];

                window->setSize(sf::Vector2u(std::stoi(w), std::stoi(h)));

                first.replace(first.find('x'), 1, " ");
                ofs.open("./Config/window_settings.ini");
                ofs << first;
                ofs.close();

            }
        }
    }
}

void DropDownList::render(sf::RenderTarget &target) {

    firstElement->render(target);

    if(isOpen){

        for(auto &b : buttonList)
            b->render(target);

    }

    target.draw(descriptionText);

}

bool DropDownList::isReady() {

    if(keyClock.getElapsedTime().asSeconds() >= maxKeyTime){

        keyClock.restart();
        return true;

    }
    else
        return false;

}


