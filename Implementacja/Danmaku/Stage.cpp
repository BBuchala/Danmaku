#include "Stage.h"

Stage::Stage(std::string const & file, RECT const * const gameField, LPDIRECT3DDEVICE9 device)
	: _gameField(gameField)
{
	_stageContents = std::auto_ptr<char>(XML2Char(file));
	_device = device;
	this->ReadXMLFile();
	this->CreateStageElements();
	this->ClearDocument();
};


char * Stage::XML2Char ( std::string const & stageFile )
{
	std::ifstream file( stageFile );
	if( file.bad() )
	{
		exit( - 1 );
	}
	std::filebuf * pbuf = file.rdbuf();
	long fileLength = pbuf->pubseekoff( 0, std::ios::end, std::ios::in );
	file.seekg( 0 );
	char * out = new char[ fileLength + 1 ];
	file.read( out, fileLength );
	return out;
};


void Stage::ReadXMLFile()
{
	try
	{
		_stageDoc.parse<0>(_stageContents.get());
	}
	catch( rapidxml::parse_error e )
	{
		e.what();
	}
};


void Stage::CreateStageElements()
{
	using namespace rapidxml;
	// Pocz¹tek Stejd¿a
	xml_node <> * stage = _stageDoc.first_node();
	// iteracja po wszystkich punktach w czasie
	for(xml_node <> * time = stage->first_node(); time; time = time->next_sibling())
	{
		// Pobranie wartoœci punktu w czasie
		xml_attribute <>* atr = time->first_attribute();
		std::string str(atr->name());
		if (str.compare("sec") == 0)
		{
			std::deque<Enemy*> newEnemyQue;
			for( xml_node <> * enemy = time->first_node(); enemy; enemy = enemy->next_sibling())
			{
				Enemy * enemyObj;
				short number = 1;
				float distance = 0.0f;
				D3DXVECTOR2	position;
				std::string imageFile;
				short life;
				float speed;
				for ( xml_attribute <>* enemyAtr = enemy->first_attribute(); enemyAtr; enemyAtr = enemyAtr->next_attribute() )
				{
					std::string eStr(enemyAtr->name());
					if (eStr.compare("number") == 0)
					{
						number = std::stoi(enemyAtr->value());
					}
					else if (eStr.compare("distance") == 0)
					{
						distance = std::stof(enemyAtr->value());
					}
					else if (eStr.compare("image") == 0)
					{
						imageFile = std::string(enemyAtr->value());
					}
					else if (eStr.compare("center.x") == 0)
					{
						std::string a = enemyAtr->value();
						if (String::isNumber(a))
							position.x = std::stof(enemyAtr->value());
						else
						{
							if (a.compare("HALF") == 0)
							{
								position.x = (_gameField->right - _gameField->left) / 2.0f;
							}
						}
					}
					else if (eStr.compare("center.y") == 0)
					{
						std::string a = enemyAtr->value();
						if (String::isNumber(a))
							position.y = std::stoi(enemyAtr->value());
						else
						{
							if (a.compare("TOP") == 0)
							{
								position.y = _gameField->top;
							}
						}
					}
					else if (eStr.compare("life") == 0)
					{
						life = std::stoi(enemyAtr->value());
					}
					else if (eStr.compare("speed") == 0)
					{
						speed = std::stof(enemyAtr->value());
					}
				}
				float angle, interval, bulletSpeed;
				short bulletNumber, bulletWidth, bulletHeight;
				Pattern pattern;
				std::string bulletImage, patternId;
				Hitbox::Size hSize;

				enemyObj = new Enemy(position, life, speed);
				enemyObj->InitializeSprite(_device, Sprite::GetFilePath(imageFile));

				for (xml_node <> * enemyNode = enemy->first_node(); enemyNode; enemyNode = enemyNode->next_sibling())
				{
					std::string eStr(enemyNode->name());
					if (eStr.compare("Pattern") == 0)
					{
						for (xml_attribute <>* patternAtr = enemyNode->first_attribute(); patternAtr; patternAtr = patternAtr->next_attribute())
						{
							std::string pStr(patternAtr->name());
							if (pStr.compare("type") == 0)
							{
								std::string typeName = patternAtr->value();
								if (typeName.compare("Line") == 0)
								{
									pattern = Pattern::LINEP;
								}
							}
							else if (pStr.compare("id") == 0)
							{
								patternId = patternAtr->value();
							}
							else if (pStr.compare("angle") == 0)
							{
								angle = std::stof(patternAtr->value());
							}
							else if (pStr.compare("bulletNumber") == 0)
							{
								bulletNumber = std::stoi(patternAtr->value());
							}
							else if (pStr.compare("interval") == 0)
							{
								interval = std::stof(patternAtr->value());
							}
						}
						for (xml_node <> * patternNode = enemyNode->first_node(); patternNode; patternNode = patternNode->next_sibling())
						{
							std::string str_tmp = patternNode->name();
							if (str_tmp.compare("Bullet") == 0)
							{
								for (xml_attribute <>* bulletAtr = patternNode->first_attribute(); bulletAtr; bulletAtr = bulletAtr->next_attribute())
								{
									std::string bStr(bulletAtr->name());
									if (bStr.compare("image") == 0)
									{
										bulletImage = bulletAtr->value();
									}
									if (bStr.compare("speed") == 0)
									{
										bulletSpeed = std::stof(bulletAtr->value());
									}
									if (bStr.compare("width") == 0)
									{
										bulletWidth = std::stoi(bulletAtr->value());
									}
									if (bStr.compare("height") == 0)
									{
										bulletHeight = std::stoi(bulletAtr->value());
									}
									if (bStr.compare("hitboxSize") == 0)
									{
										std::string hitboxSize = bulletAtr->value();
										if (hitboxSize.compare("HALF") == 0)
										{
											hSize = Hitbox::Size::HALF_LENGTH;
										}
									}
								}
								enemyObj->AddPattern(Pattern::LINEP, patternId, angle, bulletNumber, interval);
								enemyObj->InitializePattern(_device, position);
								enemyObj->GetPattern(patternId).InitializeBullets(Sprite::GetFilePath(bulletImage), bulletSpeed, bulletWidth, bulletHeight, Hitbox::Shape::CIRCLE, hSize);
							}
						}
					}
				}
				enemyObj->InitializeHitbox(Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH);
				enemyObj->SetTrajectory(Road::LINE, position, D3DXToRadian(-90));
				newEnemyQue.push_back(enemyObj);
			}
			_enemyMap[std::stoi(std::string(atr->value()))] = newEnemyQue;
		}
	}
};


void Stage::ClearDocument()
{
	_stageDoc.clear();
};


std::deque<Enemy*> * const Stage::GetEnemies(short const time)
{
	EnemyMap::const_iterator it = _enemyMap.find( time );
	if ( it != _enemyMap.end())
	{
		return &_enemyMap[time];
	}
	else
		return nullptr;
};

void Stage::RemoveEnemies(short const key)
{
	EnemyMap::const_iterator it = _enemyMap.find(key);
	if ( it != _enemyMap.end())
	{
		_enemyMap.erase(key);
	}
};
