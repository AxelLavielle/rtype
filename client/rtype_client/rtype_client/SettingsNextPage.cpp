#include "SettingsNextPage.hh"

SettingsNextPage::SettingsNextPage()
{

}

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
  initInputKey(Rect(_windowSize.first / 2 - 100, 750, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255));

  std::vector<AGUIElement* >::iterator it = _guiElement.begin();
  int i = 0;
  SaveConfig	sv;
  sv.readFromFile();
  while (it != _guiElement.end())
  {
	  if ((*it)->getTypeName() == "InputBox")
		  static_cast<InputBox*>(*it)->setText(sv.getPlayerName());
	  else if ((*it)->getTypeName() == "InputKey" && i == 0)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getUp());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputKey" && i == 1)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getLeft());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputKey" && i == 2)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getRight());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputKey" && i == 3)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getDown());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputKey" && i == 4)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getPew());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputKey" && i == 5)
	  {
		  static_cast<InputKey*>(*it)->setText(sv.getSuperPew());
		  i++;
	  }
	  it++;
  }

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

void SettingsNextPage::manageConfigs()
{
	std::vector<AGUIElement* >::iterator it = _guiElement.begin();
	int i = 0;
	SaveConfig	sv;

	sv.readFromFile();
	while (it != _guiElement.end())
	{
		if ((*it)->getTypeName() == "InputBox")
			sv.setPlayerName(static_cast<InputBox*>(*it)->getText());
		else if ((*it)->getTypeName() == "InputKey" && i == 0)
		{
			sv.setUp(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		else if ((*it)->getTypeName() == "InputKey" && i == 1)
		{
			sv.setLeft(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		else if ((*it)->getTypeName() == "InputKey" && i == 2)
		{
			sv.setRight(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		else if ((*it)->getTypeName() == "InputKey" && i == 3)
		{
			sv.setDown(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		else if ((*it)->getTypeName() == "InputKey" && i == 4)
		{
			sv.setPew(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		else if ((*it)->getTypeName() == "InputKey" && i == 5)
		{
			sv.setSuperPew(static_cast<InputKey*>(*it)->getText());
			i++;
		}
		it++;
	}
	sv.writeToFile();
}

void SettingsNextPage::draw()
{
  _graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
  _graph->drawText("Hen Type", _windowSize.first / 2 - 250, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Player name", _windowSize.first / 2 - 450, 300, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Up", _windowSize.first / 2 - 450, 375, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Left", _windowSize.first / 2 - 450, 450, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Right", _windowSize.first / 2 - 450, 525, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Down", _windowSize.first / 2 - 450, 600, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Shoot", _windowSize.first / 2 - 450, 675, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Super shoot", _windowSize.first / 2 - 450, 750, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
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
  if (page == IPage::SAVE)
	  manageConfigs();
  else if (page == IPage::SETTINGS)
  {
	  manageConfigs();
	  clickEvent(_guiElement);
  }
  else
    clickEvent(_guiElement);
  return (page);
}
