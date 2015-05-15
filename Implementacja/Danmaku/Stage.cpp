#include "Stage.h"

Stage::Stage(std::string const & file, RECT const * const gameField, LPDIRECT3DDEVICE9 device)
	: _gameField(gameField)
{
	_stageContents = std::unique_ptr<char>(XML2Char(file));
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


void Stage::CreateBullets(Enemy * const enemyObj, xml_node <> * patternNode, std::string const & patternId, Pattern const pattern)
{
	float bulletSpeed;
	BYTE bulletWidth, bulletHeight;
	std::string bulletImage;
	Hitbox::Shape hShape = Hitbox::Shape::CIRCLE;
	Hitbox::Size hSize = Hitbox::Size::HALF_LENGTH;
	std::string str_tmp = patternNode->name();
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
	switch(pattern)
	{
	case Pattern::ELLIPSE:
		bulletSpeed = D3DXToRadian(bulletSpeed);
		break;
	default:
		break;
	}
	enemyObj->GetPattern(patternId).InitializeBullets(Sprite::GetFilePath(bulletImage), bulletSpeed, bulletWidth, bulletHeight, hShape, hSize);
};


void Stage::ChoosePattern(std::string const & patternType, Pattern & pattern )
{
	if (patternType.compare("Line") == 0)
	{
		pattern = Pattern::LINE;
	}
	else if (patternType.compare("Ellipse") == 0)
	{
		pattern = Pattern::ELLIPSE;
	}
};


void Stage::ChooseTrajectory(std::string const & trajType, Road & traj)
{
	if (trajType.compare("Line") == 0)
	{
		traj = Road::LINE;
	}
	else if (trajType.compare("Ellipse") == 0)
	{
		traj = Road::ELIPSE;
	}
	else if (trajType.compare("Spiral") == 0)
	{
		traj = Road::SPIRAL;
	}
	else if (trajType.compare("None") == 0)
	{
		traj = Road::NONE;
	}
};


Road Stage::CreateTrajectory(Enemy * const enemyObj, xml_node <> * trajectory)
{
	Road trajType;
	D3DXVECTOR2 startPoint;
	float a, b = 0.0f;
	for (xml_attribute <>* trajectoryAtr = trajectory->first_attribute(); trajectoryAtr; trajectoryAtr = trajectoryAtr->next_attribute())
	{
		std::string str(trajectoryAtr->name());
		if (str.compare("type") == 0)
		{
			this->ChooseTrajectory(trajectoryAtr->value(), trajType);
		}
		else if (str.compare("center.x") == 0)
		{
			this->ChooseVerticalPosition(trajectoryAtr->value(), startPoint.x);
		}
		else if (str.compare("center.y") == 0)
		{
			this->ChooseHorizontalPosition(trajectoryAtr->value(), startPoint.y);
		}
		else if (str.compare("a") == 0)
		{
			a = std::stof(trajectoryAtr->value());
		}
		else if (str.compare("b") == 0)
		{
			b = std::stof(trajectoryAtr->value());
		}
	}
	enemyObj->SetTrajectory(trajType, startPoint, a, b);
	return trajType;
};


void Stage::CreateAffineParameters(Enemy * const enemyObj, xml_node <> * patternNode, std::string const & patternId)
{
	D3DXVECTOR2 translate = D3DXVECTOR2(0.0f, 0.0f);
	float rotate = 0.0f, scale = 1.0f; 
	std::string str_tmp = patternNode->name();
	for (xml_attribute <>* affineAtr = patternNode->first_attribute(); affineAtr; affineAtr = affineAtr->next_attribute())
	{
		std::string pStr(affineAtr->name());
		if (pStr.compare("translate.x") == 0)
		{
			translate.x = std::stof(affineAtr->value());
		}
		else if (pStr.compare("translate.y") == 0)
		{
			translate.y = std::stof(affineAtr->value());
		}
		else if (pStr.compare("scale") == 0)
		{
			scale = std::stof(affineAtr->value());
		}
		else if (pStr.compare("rotate") == 0)
		{
			rotate = std::stof(affineAtr->value());
		}
	}
	enemyObj->GetPattern(patternId).SetTranslation(D3DXVECTOR2(std::pow(translate.x, 1.0f / 60.0f), std::pow(translate.y, 1.0f / 60.0f)));
	enemyObj->GetPattern(patternId).SetScale(std::pow(scale, 1.0f / 60.0f));
	enemyObj->GetPattern(patternId).SetRotation(std::pow(rotate, 1.0f / 60.0f));
};


void Stage::CreatePatterns(Enemy * const enemyObj, xml_node <> * enemyNode, D3DXVECTOR2 const & position)
{
	float par1, par2 = 0.0f, interval = 0.0f;
	short bulletNumber = 1, number = 1;
	Pattern pattern;
	static short patternId = 1;
	for (xml_attribute <>* patternAtr = enemyNode->first_attribute(); patternAtr; patternAtr = patternAtr->next_attribute())
	{
		std::string pStr(patternAtr->name());
		if (pStr.compare("type") == 0)
		{
			this->ChoosePattern(patternAtr->value(), pattern);
		}
		else if (pStr.compare("par1") == 0)
		{
			par1 = std::stof(patternAtr->value());
		}
		else if (pStr.compare("par2") == 0)
		{
			par2 = std::stof(patternAtr->value());
		}
		else if (pStr.compare("bulletNumber") == 0)
		{
			bulletNumber = std::stoi(patternAtr->value());
		}
		else if (pStr.compare("number") == 0)
		{
			number = std::stoi(patternAtr->value());
		}
		else if (pStr.compare("interval") == 0)
		{
			interval = std::stof(patternAtr->value());
		}
	}
	for (int i = 0; i < number; i++)
	{
		std::string patternIdStr = std::to_string(patternId);
		for (xml_node <> * patternNode = enemyNode->first_node(); patternNode; patternNode = patternNode->next_sibling())
		{
			float activationTime = i * interval;
			enemyObj->AddPattern(pattern, patternIdStr, par1, par2, bulletNumber, interval, activationTime);
			enemyObj->InitializePattern(_device, position);
			std::string str_tmp = patternNode->name();
			if (str_tmp.compare("Bullet") == 0)
			{
				this->CreateBullets(enemyObj, patternNode, patternIdStr, pattern);
			}
			else if (str_tmp.compare("Affine") == 0)
			{
				this->CreateAffineParameters(enemyObj, patternNode, patternIdStr);
			}
		}
		patternId++;
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
	short number = 1;
	for (xml_attribute <>* bonusAtr = bonus->first_attribute(); bonusAtr; bonusAtr = bonusAtr->next_attribute())
	{
		std::string str(bonusAtr->name());
		if (str.compare("type") == 0)
		{
			this->ChooseBonus(bonusAtr->value(), bonusType);
		}
		else if (str.compare("number") == 0)
		{
			number = std::stoi(bonusAtr->value());
		}
		else if (str.compare("value") == 0)
		{
			value = std::stof(bonusAtr->value());
		}
	}
	for (int i = 0; i < number; i++)
	{
		enemyObj->SetBonus(bonusType, value);
	}
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
		else if (pos.compare("ONE_THIRDS") == 0)
		{
			positionX = (_gameField->bottom - _gameField->top) / 3.0f;
		}
		else if (pos.compare("HALF") == 0)
		{
			positionX = (_gameField->right - _gameField->left) / 2.0f;
		}
		else if (pos.compare("TWO_THIRDS") == 0)
		{
			positionX = (_gameField->bottom - _gameField->top) * 2.0f / 3.0f;
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
		else if (pos.compare("ONE_THIRDS") == 0)
		{
			positionY = (_gameField->bottom - _gameField->top) / 3.0f;
		}
		else if (pos.compare("HALF") == 0)
		{
			positionY = (_gameField->bottom - _gameField->top) / 2.0f;
		}
		else if (pos.compare("TWO_THIRDS") == 0)
		{
			positionY = (_gameField->bottom - _gameField->top) * 2.0f / 3.0f;
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
		short number = 1;
		float distance = 0.0f, start = 0.0f;
		D3DXVECTOR2	position;
		std::string imageFile;
		short life;
		float speed, length = 0.0f;
		for ( xml_attribute <>* enemyAtr = enemy->first_attribute(); enemyAtr; enemyAtr = enemyAtr->next_attribute() )
		{
			std::string eStr(enemyAtr->name());
			if (eStr.compare("number") == 0)
			{
				number = std::stoi(enemyAtr->value());
			}
			else if (eStr.compare("start") == 0)
			{
				start = std::stof(enemyAtr->value());
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
			else if (eStr.compare("length") == 0)
			{
				length = std::stof(enemyAtr->value());
			}
		}
		for (int i = 0; i < number; ++i)
		{
			Enemy * enemyObj = new Enemy(position, life, speed);
			enemyObj->InitializeSprite(_device, Sprite::GetFilePath(imageFile));
			Road trajType;
			float tmp_length = length, tmp_distance = distance, tmp_start = start;
			for (xml_node <> * enemyNode = enemy->first_node(); enemyNode; enemyNode = enemyNode->next_sibling())
			{
				std::string eStr(enemyNode->name());
				if (eStr.compare("Pattern") == 0)
				{
					this->CreatePatterns(enemyObj, enemyNode, position);
				}
				else if (eStr.compare("Bonus") == 0)
				{
					this->CreateBonus(enemyObj, enemyNode, position);
				}
				else if (eStr.compare("Trajectory") == 0)
				{
					trajType = this->CreateTrajectory(enemyObj, enemyNode);
				}
			}
			switch(trajType)
			{
			case Road::ELIPSE: case Road::SPIRAL:
				tmp_start = D3DXToRadian(start);
				tmp_distance = D3DXToRadian(distance);
				tmp_length = D3DXToRadian(length);
				enemyObj->SetSpeed(D3DXToRadian(enemyObj->GetSpeed()));
				break;
			}
			enemyObj->InitializeHitbox(Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH);
			enemyObj->SetDistance(tmp_start - i * tmp_distance);
			enemyObj->GetTrajectory()->SetLength(tmp_start + tmp_length + i * tmp_distance);
			newEnemyQue.push_back(enemyObj);
		}
	}
	_enemyMap[std::stof(std::string(timeValue))].first = false;
	_enemyMap[std::stof(std::string(timeValue))].second = newEnemyQue;
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
		if (!_enemyMap[time].first)
		{
			_enemyMap[time].first = true;
			return &_enemyMap[time].second;
		}
	}
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
