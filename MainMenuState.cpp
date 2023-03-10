#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                             std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    font.loadFromFile("./Fonts/PAPYRUS.ttf");
    view = window->getView();

    initKeys();
    initButtons();

    bgTexture.loadFromFile("./images/bg2fixed.png");

    background.setSize(sf::Vector2f (1920.f,1080.f));
    background.setTexture(&bgTexture);


    title.setFont(font);
    title.setCharacterSize(static_cast<unsigned int>((view.getSize().x / 17.f)));
    title.setString("Steamrush");
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(27.f*view.getSize().x/75.f, 2.f*view.getSize().y/15.f));



    view.setCenter(view.getSize()/2.f);

    errorMessage.setFont(font);
    errorMessage.setCharacterSize(25);
    errorMessage.setString("One or more keys selected are not valid");
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(view.getSize().x/2.f-errorMessage.getGlobalBounds().width/2,3.f*view.getSize().y/4.f-errorMessage.getGlobalBounds().height/2);

}

void MainMenuState::update(const float &dt) {

    checkForClose();
    if(!states->empty()) {
        window->setView(view);
        updateMousePosition();
        updateButtons();
    }

}

void MainMenuState::updateButtons() {

    for(auto &b : buttons)
        b.second->update(mousePos);

    if(buttons["PLAY"]->isPressed()) {
        try {
            states->push(std::make_unique<GameState>(window, states, textEvent, supportedKeys));
        }
        catch (std::runtime_error& error){
           if (strcmp(error.what(),"unsupported_keys")==0){

               renderError=true;
           }
           std::cout << error.what() << std::endl;
        }
    }

    if(buttons["SETTINGS"]->isPressed()) {
        states->push(std::make_unique<SettingsState>(window, states, textEvent, supportedKeys));
        renderError=false;
    }

    if(buttons["EXIT"]->isPressed())
        states->pop();

}

void MainMenuState::render(sf::RenderTarget &target) {

    target.draw(background);
    target.draw(title);
    if (renderError)
        target.draw(errorMessage);

    for(auto &b : buttons)
        b.second->render(target);

}

void MainMenuState::initButtons() {

    buttons["PLAY"] = std::make_unique<Button>(sf::Vector2f(view.getSize().x/4.f, view.getSize().y/12.f), sf::Vector2f(59.f*view.getSize().x/160.f,view.getSize().y/3.f),
                                               sf::Color(130, 130, 130, 200), "Play", font, static_cast<unsigned int>(2.f*view.getSize().y/65.f),
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["SETTINGS"] = std::make_unique<Button>(sf::Vector2f(view.getSize().x/4.f, view.getSize().y/12.f), sf::Vector2f(59.f*view.getSize().x/160.f,13.f*view.getSize().y/30.f),
                                               sf::Color(130, 130, 130, 200), "Settings", font, static_cast<unsigned int>(2.f*view.getSize().y/65.f),
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(view.getSize().x/4.f, view.getSize().y/12.f), sf::Vector2f(59.f*view.getSize().x/160.f,8.f*view.getSize().y/15.f),
                                               sf::Color(130, 130, 130, 200), "Exit", font, static_cast<unsigned int>(2.f*view.getSize().y/65.f),
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}

void MainMenuState::initKeys() {

    std::ifstream file;

    file.open("./Config/mainMenuState_keys.ini");
    std::string keyName;
    std::string key;

    while(file >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file.close();

}
