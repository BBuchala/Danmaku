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
	long fileLength = static_cast<long>(pbuf->pubseekoff( 0, std::ios::end, std::ios::in ));
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


void Stage::ChooseHitboxShape(std::string const & shape, Hitbox::Shape & hShape)
{
	if (shape.compare("CIRCLE") == 0)
	{
		hShape = Hitbox::Shape::CIRCLE;
	}
	else if (shape.compare("ELLIPSE") == 0)
	{
		hShape = Hitbox::Shape::ELLIPSE;
	}
};


void Stage::ChooseHitboxSize(std::string const & size, Hitbox::Size & hSize)
{
	if (size.compare("HALF") == 0)
	{
		hSize = Hitbox::Size::HALF_LENGTH;
	}
	else if (size.compare("TWO_THIRDS") == 0)
	{
		hSize = Hitbox::Size::TWO_THIRDS_LENGTH;
	}
	else if (size.compare("FULL") == 0)
	{
		hSize = Hitbox::Size::FULL_LENGTH;
	}
};


void Stage::CreateBullets(Enemy * const enemyObj, xml_node <> * patternNode, std::string const & patternId)
{
	float bulletSpeed;
	BYTE bulletWidth, bulletHeight;
	std::string bulletImage;
	Hitbox::Shape hShape = Hitbox::Shape::CIRCLE;
	Hitbox::Size hSize = Hitbox::Size::HALF_LENGTH;
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
			if (bStr.compare("hitboxShape") == 0)
			{
				this->ChooseHitboxShape(bulletAtr->value(), hShape);
			}
			if (bStr.compare("hitboxSize") == 0)
			{
				this->ChooseHitboxSize(bulletAtr->value(), hSize);
			}
		}
		enemyObj->GetPattern(patternId).InitializeBullets(Sprite::GetFilePath(bulletImage), bulletSpeed, bulletWidth, bulletHeight, hShape, hSize);
	}
};


void Stage::ChoosePattern(std::string const & patternType, Pattern & pattern )
{
	if (patternType.compare("Line") == 0)
	{
		pattern = Pattern::LINE;
	}
};


void Stage::CreatePatterns(Enemy * const enemyObj, xml_node <> * enemy, D3DXVECTOR2 const & position)
{
	float angle, interval;
	short bulletNumber;
	Pattern pattern;
	std::string patternId;
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
					this->ChoosePattern(patternAtr->value(), pattern);
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
				enemyObj->AddPattern(pattern, patternId, angle, bulletNumber, interval);
				enemyObj->InitializePattern(_device, position);
				this->CreateBullets(enemyObj, patternNode, patternId);
			}
		}
		if (eStr.compare("Bonus") == 0)
		{
			this->CreateBonus(enemyObj, enemyNode, position);
		}
	}
};


void Stage::ChooseBonus(std::string const & bonus, Bonuses & bonusType)
{
	if (bonus.compare("Power") == 0)
	{
		bonusType = Bonuses::POWER;
	}
	else if (bonus.compare("Score") == 0)
	{
		bonusType = Bonuses::SCORE;
	}
	else if (bonus.compare("Bomb") == 0)
	{
		bonusType = Bonuses::BOMB;
	}
	else if (bonus.compare("Life") == 0)
	{
		bonusType = Bonuses::LIFE;
	}
	else
	{
		bonusType = Bonuses::NONE;
	}
};


void Stage::CreateBonus(Enemy * const enemyObj, xml_node <> * bonus, D3DXVECTOR2 const & position)
{
	Bonuses bonusType;
	float value = 1.0f;
	for (xml_attribute <>* bonusAtr = bonus->first_attribute(); bonusAtr; bonusAtr = bonusAtr->next_attribute())
	{
		std::string str(bonusAtr->name());
		if (str.compare("type") == 0)
		{
			this->ChooseBonus(bonusAtr->value(), bonusType);
		}
		else if (str.compare("value") == 0)
		{
			value = std::stof(bonusAtr->value());
		}
	}
	enemyObj->SetBonus(bonusType, value);
};


void Stage::ChooseVerticalPosition(std::string const & pos, float & positionX )
{
	if (String::isNumber(pos))
	{
		positionX = std::stof(pos);
	}
	else
	{
		if (pos.compare("LEFT") == 0)
		{
			positionX = static_cast<float>(_gameField->left);
		}
		else if (pos.compare("HALF") == 0)
		{
			positionX = (_gameField->right - _gameField->left) / 2.0f;
		}
		else if (pos.compare("RIGHT") == 0)
		{
			positionX = static_cast<float>(_gameField->right);
		}
	}
};


void Stage::ChooseHorizontalPosition(std::string const & pos, float & positionY )
{
	if (String::isNumber(pos))
		positionY = std::stof(pos);
	else
	{
		if (pos.compare("TOP") == 0)
		{
			positionY = static_cast<float>(_gameField->top);
		}
		else if (pos.compare("HALF") == 0)
		{
			positionY = (_gameField->bottom - _gameField->top) / 2.0f;
		}
		else if (pos.compare("BOTTOM") == 0)
		{
			positionY = static_cast<float>(_gameField->bottom);
		}
	}
};


void Stage::CreateEnemies(xml_node <> * time, char * timeValue)
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
				this->ChooseVerticalPosition(enemyAtr->value(), position.x);
			}
			else if (eStr.compare("center.y") == 0)
			{
				this->ChooseHorizontalPosition(enemyAtr->value(), position.y);
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

		enemyObj = new Enemy(position, life, speed);
		enemyObj->InitializeSprite(_device, Sprite::GetFilePath(imageFile));

		this->CreatePatterns(enemyObj, enemy, position);

		enemyObj->InitializeHitbox(Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH);
		enemyObj->SetTrajectory(Road::LINE, position, D3DXToRadian(-90));
		newEnemyQue.push_back(enemyObj);
	}
	_enemyMap[std::stoi(std::string(timeValue))] = newEnemyQue;
};


void Stage::CreateStageElements()
{
	// Pocz¹tek Stejd¿a
	xml_node <> * stage = _stageDoc.first_node();
	// iteracja po wszystkich punktach w czasie
	for(xml_node <> * time = stage->first_node(); time; time = time->next_sibling())
	{
		// Pobranie wartoœci punktu w czasie - tylko jedna powinna byæ
		xml_attribute <>* atr = time->first_attribute();
		std::string str(atr->name());
		if (str.compare("sec") == 0)
		{
			this->CreateEnemies(time, atr->value());
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
