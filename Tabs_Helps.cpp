#include "Game.h"
#include "Tabs_Helps.h"

HelpsAndCredit::HelpsAndCredit()
{
    inlineTab = H_Helps;
    direct = Helps;
    helpsButton.setPosition(411, 473);
    aboutButton.setPosition(411, 557);
    copyrightButton.setPosition(411, 642);
}
HelpsAndCredit::~HelpsAndCredit()
{

}
Tabs HelpsAndCredit::getDirect()
{
    return direct;
}

void HelpsAndCredit::setUp(SDL_Renderer* renderer)
{
    LTexture* helpButtonTex = new LTexture(help_help_buttonP, renderer);
    LTexture* aboutButtonTex = new LTexture(help_about_buttonP, renderer);
    LTexture* copyrightButtonTex = new LTexture(help_copyright_buttonP, renderer);
    LTexture* helpButtonTex_ = new LTexture(help_help_buttonP_, renderer);
    LTexture* aboutButtonTex_ = new LTexture(help_about_buttonP_, renderer);
    LTexture* copyrightButtonTex_ = new LTexture(help_copyright_buttonP_, renderer);
    helpsButton.setTexture(helpButtonTex, helpButtonTex_);
    aboutButton.setTexture(aboutButtonTex, aboutButtonTex_);
    copyrightButton.setTexture(copyrightButtonTex, copyrightButtonTex_);
}

void HelpsAndCredit::handleEvent(SDL_Event* e)
{
    bool flag = 0;
    backButton->handleEvents(e, 1);
    if (backButton->getPressed())
    {
        backButton->setPressed(0);
        direct=Menu;
        flag = 1;
        return;
    }
    direct = Helps;
    helpsButton.handleEvents(e);
    if (helpsButton.getPressed())
    {
        helpsButton.setPressed(0);
        inlineTab = H_Helps;
    }
    aboutButton.handleEvents(e);
    if (aboutButton.getPressed())
    {
        aboutButton.setPressed(0);
        inlineTab = H_About;
    }

    copyrightButton.handleEvents(e);
    if (copyrightButton.getPressed())
    {
        copyrightButton.setPressed(0);
        inlineTab = H_Copyright;
    }
}
void HelpsAndCredit::render(SDL_Renderer* renderer)
{
    static LTexture helpsBg (helpsBgP, renderer);
    helpsBg.render(renderer, 0, 0);
    backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
    helpsButton.render(renderer);
    aboutButton.render(renderer);
    copyrightButton.render(renderer);
    static LTexture helpTextTex(help_help_textP, renderer);
    static LTexture aboutTextTex(help_about_textP, renderer);
    static LTexture cpyrightTextTex(help_copyright_textP, renderer);
    switch (inlineTab)
    {
        case H_Helps:
            helpTextTex.render(renderer, 0, 0);
            break;
        case H_About:
            aboutTextTex.render(renderer, 0, 0);
            break;
        case H_Copyright:
            cpyrightTextTex.render(renderer, 0, 0);
            break;
        default:
            break;
    }
}