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
  initButton(70, 10, 60, Rect(380, 200, 90, 310), "PLAY", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PAUSE);
  initButton(20, 10, 60, Rect(380, 380, 90, 310), "OPTION", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGS);
  initButton(70, 10, 60, Rect(380, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
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
