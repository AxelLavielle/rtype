#include "SettingsNextPage.hh"

SettingsNextPage::SettingsNextPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
  _backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
  _clickSound.setDuration(-1);
  _clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

SettingsNextPage::~SettingsNextPage()
{
  clear();
}

bool SettingsNextPage::init()
{
  initButton(70, 10, 60, Rect(750, 600, 90, 310), "SAVE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SAVE);
  initButton(70, 10, 60, Rect(385, 600, 90, 310), "PREC", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGS);
  initButton(70, 10, 60, Rect(20, 600, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initInputBox(Rect(500, 100, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(500, 175, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(500, 250, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(500, 325, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(500, 400, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(500, 475, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  return (true);
}

void SettingsNextPage::clear()
{
  clearGUIElement(_buttons);
  clearGUIElement(_guiElement);
}

bool SettingsNextPage::launch()
{
  return (true);
}

void SettingsNextPage::draw()
{
  _graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
  _graph->drawText("Nom du Joueur", 100, 100, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Haut", 100, 175, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Gauche", 100, 250, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Droite", 100, 325, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Bas", 100, 400, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Tirer", 100, 475, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  drawGUIElement(_buttons);
  drawGUIElement(_guiElement);
}

std::pair<std::string, std::pair<int, int> > SettingsNextPage::save() const
{
  return (std::pair<std::string, std::pair<int, int> >(static_cast<InputBox*>(_guiElement[2])->getText(),std::pair<int, int>(static_cast<CursorBox*>(_guiElement[0])->getValue(), static_cast<CursorBox*>(_guiElement[1])->getValue())));
}

IPage::PAGE SettingsNextPage::event()
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
