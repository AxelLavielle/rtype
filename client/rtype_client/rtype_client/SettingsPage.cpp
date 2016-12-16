#include "SettingsPage.hh"

SettingsPage::SettingsPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
  _backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
  _clickSound.setDuration(-1);
  _clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

SettingsPage::~SettingsPage()
{
  clear();
}

bool SettingsPage::init()
{
  initButton(70, 10, 60, Rect(750, 600, 90, 310), "SAVE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::NONE);
  initButton(70, 10, 60, Rect(20, 600, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initCursorBox(Rect(300, 300, 30, 500), "/res/img/scrollBar.png", "/res/img/scrollButton.png");
  initCursorBox(Rect(300, 500, 30, 500), "/res/img/scrollBar.png", "/res/img/scrollButton.png");
  initCheckBox(Rect(300, 200, 40, 40), "/res/img/coche.png", "/res/img/cocheRempli.png");
  return (true);
}

void SettingsPage::clear()
{
  clearGUIElement(_buttons);
  clearGUIElement(_guiElement);
}

bool SettingsPage::launch()
{
  return (true);
}

void SettingsPage::draw()
{
  _graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
  drawGUIElement(_buttons);
  drawGUIElement(_guiElement);
}

IPage::PAGE SettingsPage::event()
{
  IPage::PAGE		page;

  hoverEvent(_buttons);
  page = clickEvent(_buttons);
  if (page != IPage::NONE)
    _soundManager->play(_clickSound);
  else
    clickEvent(_guiElement);
  return (page);
}
