#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                             std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    font.loadFromFile("./Fonts/PAPYRUS.ttf");

    initKeys();
    initButtons();
    initTextFields();
    initDropDownList();

    bgTexture.loadFromFile("./images/OPTIONS.png");

    //background.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    background.setSize(sf::Vector2f(1920, 1080));
    //background.setFillColor(sf::Color::Green);
    background.setTexture(&bgTexture);

}

void SettingsState::update(const float &dt) {

    checkForClose();
    if(states->size() != 1) { //now there is only the MainMenuState in the stack
        updateMousePosition();
        updateTextFields();
        updateButtons();
    }
    else
        sf::sleep(sf::seconds(0.05)); //0.05s is waited to prevent a second pop() after pressing ESC
}

void SettingsState::updateButtons() {

    for(auto &b : buttons)
        b.second->update(mousePos);

    if(buttons["EXIT"]->isPressed())
        states->pop();

}

void SettingsState::render(sf::RenderTarget &target) {

    target.draw(background);

    for(auto &b : buttons)
        b.second->render(target);

    for(auto &t : textFields)
        t.second->render(target);

    dropDownList->render(target);

}

void SettingsState::updateTextFields() {

    if(textEvent.type == sf::Event::TextEntered){

        for(auto &t : textFields){

            if(t.second->contains(mousePos)){

                if(textEvent.text.unicode < 128){

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        t.second->setString("Space");
                    else{

                        sf::String string = static_cast<sf::String>(textEvent.text.unicode);
                        std::transform(string.begin(), string.end(), string.begin(), ::toupper);
                        t.second->setString(string);

                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    t.second->clear();

            }
        }
    }

    dropDownList->update(mousePos, window);

    updateKeys();

}

void SettingsState::updateKeys() {

    std::ofstream file;

    file.open("./Config/settingsState_keys.ini");

    for(auto &t : textFields)
        file << t.second->getDescription() << " " << static_cast<std::string>(t.second->getString()) << std::endl;

    file.close();

}

void SettingsState::initButtons() {

    sf::Vector2f winSize(window->getView().getSize());

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(winSize.x/4.f,
                                                            winSize.y/12.f),
                                               sf::Vector2f(3.f*winSize.x/8.f,
                                                            3.f*winSize.y/4.f),
                                               sf::Color(70, 70, 70, 200), "Exit", font, static_cast<unsigned int>(2.f*winSize.y/65.f),
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}

void SettingsState::initTextFields() {

    sf::Vector2f winSize(window->getView().getSize());

    textFields["LEFT"] = std::make_unique<TextField>(sf::Vector2f(winSize.x/8.f, winSize.y/12.f), sf::Vector2f(winSize.x/8.f, winSize.y/6.f), static_cast<unsigned int>(11.f*winSize.y/300.f),
                                                     sf::Vector2f(5.f*winSize.x/32.f, 11.f*winSize.y/60.f), "Left", sf::Vector2f(winSize.x/20.f, 11.f*winSize.y/60.f),
                                                     &font, sf::Color(31, 157, 115, 255));

    textFields["RIGHT"] = std::make_unique<TextField>(sf::Vector2f(winSize.x/8.f, winSize.y/12.f), sf::Vector2f(winSize.x/8.f, 4.f*winSize.y/15.f), static_cast<unsigned int>(11.f*winSize.y/300.f),
                                                     sf::Vector2f(5.f*winSize.x/32.f, 17.f*winSize.y/60.f), "Right", sf::Vector2f(winSize.x/20.f, 17.f*winSize.y/60.f),
                                                     &font, sf::Color(31, 157, 115, 255));

    textFields["JUMP"] = std::make_unique<TextField>(sf::Vector2f(winSize.x/8.f, winSize.y/12.f), sf::Vector2f(winSize.x/8.f, 11.f*winSize.y/30.f), static_cast<unsigned int>(11.f*winSize.y/300.f),
                                                     sf::Vector2f(5.f*winSize.x/32.f, 23.f*winSize.y/60.f), "Jump", sf::Vector2f(winSize.x/20.f, 23.f*winSize.y/60.f),
                                                     &font, sf::Color(31, 157, 115, 255));

    textFields["SHOOT"] = std::make_unique<TextField>(sf::Vector2f(winSize.x/8.f, winSize.y/12.f), sf::Vector2f(winSize.x/8.f, 7.f*winSize.y/15.f), static_cast<unsigned int>(11.f*winSize.y/300.f),
                                                     sf::Vector2f(5.f*winSize.x/32.f, 29.f*winSize.y/60.f), "Shoot", sf::Vector2f(winSize.x/20.f, 29.f*winSize.y/60.f),
                                                     &font, sf::Color(31, 157, 115, 255));

    std::ifstream file;

    file.open("./Config/settingsState_keys.ini");

    std::string keyName;
    std::string key;
    auto i = textFields.begin();

    while(file >> keyName >> key && i != textFields.end()){
        i->second->setString(key);
        i++;
    }

    for(auto &t : textFields){
        if(t.second->getString() == "\b")
            t.second->clear();
    }

    file.close();

}

void SettingsState::initDropDownList() {

    sf::Vector2f winSize(window->getView().getSize());
    std::vector<std::string> fields;
    fields = {"720x480", "1280x720", "1920x1080", "800x600"};

    dropDownList = std::make_unique<DropDownList>(sf::Vector2f(winSize.x/8.f, winSize.y/13.f), sf::Vector2f(winSize.x/2.25f, winSize.y/6.f),
                                                  sf::Color(130, 130, 130, 200),
                                                  font, static_cast<unsigned int>(11.f*winSize.y/300.f), fields, "Resolution", sf::Vector2f(winSize.x/2.25f, 1.7f*winSize.y/15.f),
                                                  sf::Color(150, 150, 150, 255),
                                                  sf::Color(20, 20, 20, 200));

    std::ifstream file;
    file.open("./Config/window_settings.ini");
    std::string first;
    std::string second;
    while(file >> first >> second) {
        first += "x";
        first += second;
        dropDownList->setFirstElement(first);
    }
    file.close();

}

void SettingsState::initKeys() {

    std::ifstream file;

    file.open("./Config/mainMenuState_keys.ini");

    std::string keyName;
    std::string key;

    while(file >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file.close();

}
