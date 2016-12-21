#include "MapGeneratorFromFile.hh"

Map					MapGenerator::generate()
{

}

Map					MapGenerator::generate(const std::string &mapFile)
{
	std::ifstream			file(mapFile.c_str());
	char				c;
	std::string			nb;
	enum rtype::EntityType		type;
	Map				map;
	int				horLine = -1;
	IEntity				*entity;
	std::vector<IEntity *>		entityList;

	while (file.get(c))
	{
		if (c >= '0' && c <= '9')
			nb += c;
		if (horLine == -1 && c == '\n')
			horLine = entityList.size();
		if (nb.size() == 2)
		{
			type = static_cast<enum rtype::EntityType>(std::stoi(nb));
			if (type == rtype::VOID)
			{
				entity = new AEntity();
				entity->setType(type);
			}
			else if (type == rtype::BARRIER)
				entity = new Barrier();
			else if (type == rtype::MONSTER)
				entity = new Monster();
			else if (type == rtype::POWER_UP)
				entity = new PowerUp();
			else if (type == rtype::PLAYER)
				entity = new Player();
			entityList.push_back(entity);
			nb = "";
		}
	}
	map.setEntityList(entityList);
	return (map);
}
