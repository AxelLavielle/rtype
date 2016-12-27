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
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "SAVE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SAVE);
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155, 900, 90, 310), "PREC", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGS);
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initInputBox(Rect(_windowSize.first / 2 - 100, 300, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(_windowSize.first / 2 - 100, 375, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(_windowSize.first / 2 - 100, 450, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(_windowSize.first / 2 - 100, 525, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(_windowSize.first / 2 - 100, 600, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
  initInputKey(Rect(_windowSize.first / 2 - 100, 675, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));
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
  _graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
  _graph->drawText("Hen Type", _windowSize.first / 2 - 250, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Nom du Joueur", _windowSize.first / 2 - 400, 300, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Haut", _windowSize.first / 2 - 400, 375, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Gauche", _windowSize.first / 2 - 400, 450, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Droite", _windowSize.first / 2 - 400, 525, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Bas", _windowSize.first / 2 - 400, 600, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Tirer", _windowSize.first / 2 - 400, 675, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
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
