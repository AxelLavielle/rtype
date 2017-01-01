#include "SettingsPage.hh"

SettingsPage::SettingsPage()
{

}

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

void	SettingsPage::setServerInfo(const std::string &ip, const int port)
{
	std::stringstream	ss;

	ss << port;
	_ip = ip;
	_port = ss.str();
}

bool SettingsPage::init()
{
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155, 900, 90, 310), "NEXT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGSNEXT);
  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "SAVE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SAVE);
  initCursorBox(Rect(_windowSize.first / 2 - 250, 350, 30, 500), "/res/img/scrollBar.png", "/res/img/scrollButton.png");
  initCursorBox(Rect(_windowSize.first / 2 - 250, 500, 30, 500), "/res/img/scrollBar.png", "/res/img/scrollButton.png");	
  initInputBox(Rect(_windowSize.first / 2 - 250, 650, 30, 500), "/res/img/buttonRoom.png", Color(135, 206, 250, 255), _ip + ":" + _port);

  std::vector<AGUIElement* >::iterator it = _guiElement.begin();
  int i = 0;
  SaveConfig	sv;
  sv.readFromFile();
  while (it != _guiElement.end())
  {
	  if ((*it)->getTypeName() == "CursorBox" && i == 0)
	  {
		  static_cast<CursorBox*>(*it)->setValue(sv.getMusic());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "CursorBox" && i == 1)
	  {
		  static_cast<CursorBox*>(*it)->setValue(sv.getSfx());
		  i++;
	  }
	  else if ((*it)->getTypeName() == "InputBox")
		  static_cast<InputBox*>(*it)->setText(sv.getIport());
	  it++;
  }

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

void SettingsPage::manageConfigs()
{
	std::vector<AGUIElement* >::iterator it = _guiElement.begin();
	int i = 0;
	SaveConfig	sv;

	sv.readFromFile();
	while (it != _guiElement.end())
	{
		if ((*it)->getTypeName() == "CursorBox" && i == 0)
		{
			sv.setMusic(static_cast<CursorBox*>(*it)->getValue());
			i++;
		}
		else if ((*it)->getTypeName() == "CursorBox" && i == 1)
		{
			sv.setSfx(static_cast<CursorBox*>(*it)->getValue());
			i++;
		}
		else if ((*it)->getTypeName() == "InputBox")
			sv.setIport(static_cast<InputBox*>(*it)->getText());
		it++;
	}
	sv.writeToFile();
}

void SettingsPage::draw()
{
  _graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
  _graph->drawText("Hen Type", _windowSize.first / 2 - 250, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("Music volume", _windowSize.first / 2 - 130, 300, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("SFX volume", _windowSize.first / 2 - 100, 450, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  _graph->drawText("IP PORT", _windowSize.first / 2 - 70, 600, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
  drawGUIElement(_buttons);
  drawGUIElement(_guiElement);
}

std::pair<std::string, int>		SettingsPage::getServerInfo() const
{
	std::vector<AGUIElement* >::const_iterator	it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		if ((*it)->getTypeName() == "InputBox")
		{
			InputBox	*box;
			std::string		text;
			std::size_t		pos;
			std::pair<std::string, int>		res;

			res.first = "";
			res.second = -1;
			box = static_cast<InputBox* >((*it));
			text = box->getText();
			try
			{
				pos = text.find(":");
				if (pos <= 0 || pos + 1 >= text.size())
					return (res);
				res.first = text.substr(0, pos);
				res.second = std::stoi(text.substr(pos + 1));
			}
			catch (const std::exception &e)
			{
				std::cerr << "Bad server info" << std::endl;
				return (res);
			}
			return (res);
		}
		++it;
	}
	return (std::make_pair<std::string, int>("", -1));
}

std::pair<std::string, std::pair<int, int> > SettingsPage::save() const
{
  return (std::pair<std::string, std::pair<int, int> >(static_cast<InputBox*>(_guiElement[2])->getText(),std::pair<int, int>(static_cast<CursorBox*>(_guiElement[0])->getValue(), static_cast<CursorBox*>(_guiElement[1])->getValue())));
}

IPage::PAGE SettingsPage::event()
{
  IPage::PAGE		page;

  hoverEvent(_buttons);
  page = clickEvent(_buttons);
  if (page != IPage::NONE)
	  _soundManager->play(_clickSound);
  if (page == IPage::SAVE)
	  manageConfigs();
  else if (page == IPage::SETTINGSNEXT)
  {
	  manageConfigs();
	  clickEvent(_guiElement);
  }
  else
    clickEvent(_guiElement);
  return (page);
}
