#include "CreateRoomPage.hh"

CreateRoomPage::CreateRoomPage(IGraphManager * graph, IEventManager * event, const PathFileManager & fileManager, ISoundManager * soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

CreateRoomPage::~CreateRoomPage()
{
	clear();
}

bool CreateRoomPage::init()
{
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "PLAY", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::CREATEROOMACTION);
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	initInputBox(Rect(_windowSize.first / 2 - 350, 500, 30, 700), "/res/img/buttonRoom.png", Color(255, 255, 255));
	return (true);
}

void CreateRoomPage::clear()
{
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool CreateRoomPage::launch()
{
	return (true);
}

void CreateRoomPage::draw()
{
	_graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
	_graph->drawText("Hen Type", _windowSize.first / 2 - 250, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
}

IPage::PAGE CreateRoomPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	clickEvent(_guiElement);
	page = clickEvent(_buttons);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

std::string CreateRoomPage::getRoomName() const
{
	std::vector<AGUIElement* >::const_iterator	it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		if ((*it)->getTypeName() == "InputBox")
		{
			InputBox	*box;
	
			box = static_cast<InputBox* >((*it));
			return (box->getText());
		}
		++it;
	}
	return ("");
}
