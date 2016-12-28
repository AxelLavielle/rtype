#include "PausePage.hh"

PausePage::PausePage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
  _backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
  _clickSound.setDuration(-1);
  _clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

PausePage::~PausePage()
{
  clear();
}

bool PausePage::init()
{
  initButton(25, 5, 60, Rect(_windowSize.first / 2 - 155, 300, 90, 310), "RESUME", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PAUSE);
  initButton(65, 5, 40, Rect(_windowSize.first / 2 - 155, 480, 90, 310), "RETURN\nTO MENU", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initButton(70, 5, 60, Rect(_windowSize.first / 2 - 155, 650, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
  _graph->setMouseCursorVisible(true);
  return (true);
}

void PausePage::clear()
{
  clearGUIElement(_buttons);
  clearGUIElement(_guiElement);
}

bool PausePage::launch()
{
  return (true);
}

void PausePage::draw()
{
  drawGUIElement(_buttons);
  drawGUIElement(_guiElement);
}

IPage::PAGE PausePage::event()
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
