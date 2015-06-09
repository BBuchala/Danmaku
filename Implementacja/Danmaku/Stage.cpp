#include "Stage.h"

Stage::Stage(std::string const & file, RECT const * const gameField, LPDIRECT3DDEVICE9 device)
	: _gameField(gameField), boss(nullptr)
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
		hShape = Hitbox::Shape::ELIPSE;
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
	else if (size.compare("ONE_THIRDS") == 0)
	{
		hSize = Hitbox::Size::ONE_THIRDS_LENGTH;
	}
	else if (size.compare("TWO_THIRDS") == 0)
	{
		hSize = Hitbox::Size::TWO_THIRDS_LENGTH;
	}
};


void Stage::CreateBullets(EPattern * const epattern, xml_node <> * bulletNode, std::string const & patternId, Pattern const pattern)
{
	float bulletSpeed, bulletAcc = 0.0f;
	BYTE bulletWidth, bulletHeight;
	std::string bulletImage;
	Hitbox::Shape hShape = Hitbox::Shape::CIRCLE;
	Hitbox::Size hSize = Hitbox::Size::HALF_LENGTH;
	std::string str_tmp = bulletNode->name();
	float bulletScale = 1.0f, bulletRotate = 0.0f;
	for (xml_attribute <>* bulletAtr = bulletNode->first_attribute(); bulletAtr; bulletAtr = bulletAtr->next_attribute())
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
		if (bStr.compare("acc") == 0)
		{
			bulletAcc = std::stof(bulletAtr->value());
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
	if (this->_enemyBulletSprite.Add(bulletImage))
	{
		_enemyBulletSprite[bulletImage]->Initialize(_device, Sprite::GetFilePath(bulletImage), bulletWidth, bulletHeight);
	}
	for (xml_node <> * bulletSubnode = bulletNode->first_node(); bulletSubnode; bulletSubnode = bulletSubnode->next_sibling())
	{
		std::string bStr(bulletSubnode->name());
		if (bStr.compare("Affine") == 0)
		{
			for (xml_attribute <>* bulletAtr = bulletSubnode->first_attribute(); bulletAtr; bulletAtr = bulletAtr->next_attribute())
			{
				std::string snStr(bulletAtr->name());
				if (snStr.compare("scale") == 0)
				{
					bulletScale = std::stof(bulletAtr->value());
				}
				if (snStr.compare("rotate") == 0)
				{
					bulletRotate = std::stof(bulletAtr->value());
				}
			}
		}
	}
	switch(pattern)
	{
	case Pattern::ELLIPSE: case Pattern::SPIRAL:
		bulletSpeed = D3DXToRadian(bulletSpeed);
		break;
	default:
		break;
	}
	epattern->InitializeBullets(_enemyBulletSprite[bulletImage], bulletSpeed, bulletAcc,
		bulletWidth, bulletHeight, hShape, hSize, pow(bulletScale, 1.0f / 60.0f), D3DXToRadian(bulletRotate));
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
	else if (patternType.compare("Spiral") == 0)
	{
		pattern = Pattern::SPIRAL;
	}
	else if (patternType.compare("Fermat") == 0)
	{
		pattern = Pattern::SPIRAL_FERMAT;
	}
	else if (patternType.compare("Hyperbolic") == 0)
	{
		pattern = Pattern::SPIRAL_HYPER;
	}
	else if (patternType.compare("Bezier") == 0)
	{
		pattern = Pattern::BEZIER;
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
	else if (trajType.compare("Fermat") == 0)
	{
		traj = Road::SPIRAL_FERMAT;
	}
	else if (trajType.compare("Hyperbolic") == 0)
	{
		traj = Road::SPIRAL_HYPER;
	}
	else if (trajType.compare("None") == 0)
	{
		traj = Road::NONE;
	}
	else if (trajType.compare("Polygon") == 0)
	{
		traj = Road::POLYGON;
	}
	else if (trajType.compare("Bezier") == 0)
	{
		traj = Road::BEZIER;
	}
};

void Stage::CreatePointsForTMP(TrajectoryManyPoints * const traj, xml_node <> * trajectoryNode)
{
	for (xml_node <> * pointNode = trajectoryNode->first_node(); pointNode; pointNode = pointNode->next_sibling())
	{
		std::string str(pointNode->name());
		if (str.compare("Point") == 0)
		{
			D3DXVECTOR2 newPoint;
			for (xml_attribute <>* pointAtr = pointNode->first_attribute(); pointAtr; pointAtr = pointAtr->next_attribute())
			{
				str = std::string(pointAtr->name());
				if (str.compare("x") == 0)
				{
					this->ChooseVerticalPosition(pointAtr->value(), newPoint.x);
				}
				else if (str.compare("y") == 0)
				{
					this->ChooseHorizontalPosition(pointAtr->value(), newPoint.y);
				}
			}
			traj->AddPoint(newPoint);
		}
	}
};


Road Stage::CreateTrajectory(Enemy * const enemyObj, xml_node <> * trajectory)
{
	Road trajType;
	D3DXVECTOR2 startPoint;
	float a, b = 0.0f;
	TrajectoryManyPoints * trajC;
	for (xml_attribute <>* trajectoryAtr = trajectory->first_attribute(); trajectoryAtr; trajectoryAtr = trajectoryAtr->next_attribute())
	{
		std::string str(trajectoryAtr->name());
		if (str.compare("type") == 0)
		{
			this->ChooseTrajectory(trajectoryAtr->value(), trajType);
		}
		else if (str.compare("center.x") == 0 || str.compare("startPoint.x") == 0)
		{
			this->ChooseVerticalPosition(trajectoryAtr->value(), startPoint.x);
		}
		else if (str.compare("center.y") == 0 || str.compare("startPoint.y") == 0)
		{
			this->ChooseHorizontalPosition(trajectoryAtr->value(), startPoint.y);
		}
		else if (str.compare("a") == 0)
		{
			std::string aValue(trajectoryAtr->value());
			a = std::stof(trajectoryAtr->value());
		}
		else if (str.compare("b") == 0)
		{
			b = std::stof(trajectoryAtr->value());
		}
	}
	if (trajType == Road::POLYGON || trajType == Road::BEZIER)
	{
		switch(trajType)
		{
		case Road::POLYGON: default:
			trajC = new TrajectoryPolygon();
			break;
		case Road::BEZIER:
			trajC = new TrajectoryBezier();
			break;
		}
		this->CreatePointsForTMP(trajC, trajectory);
		trajC->CalculateLength();
		enemyObj->SetTrajectory(trajC);
	}
	else
		enemyObj->SetTrajectory(trajType, startPoint, a, b);
	return trajType;
};


void Stage::CreateAffineParameters(EPattern * const epattern, xml_node <> * patternNode, std::string const & patternId)
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
			rotate = D3DXToRadian(std::stof(affineAtr->value()));
		}
	}
	epattern->SetTranslation(D3DXVECTOR2(std::pow(translate.x, 1.0f / 60.0f), std::pow(translate.y, 1.0f / 60.0f)));
	epattern->SetScaleStep(std::pow(scale, 1.0f / 60.0f));
	epattern->SetRotationStep(rotate);
};


void Stage::CreatePatternsForSpellcard(Spellcard * const spellcard, xml_node <> * patternNode, D3DXVECTOR2 const & position)
{
	float par1, par2 = 0.0f, interval = 0.0f;
	short bulletNumber = 1;
	Pattern pattern;
	static short patternId = 1;
	float startScale = 1.0f, startRotation = 0.0f;
	for (xml_attribute <>* patternAtr = patternNode->first_attribute(); patternAtr; patternAtr = patternAtr->next_attribute())
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
		else if (pStr.compare("interval") == 0)
		{
			interval = std::stof(patternAtr->value());
		}
		else if (pStr.compare("scale") == 0)
		{
			startScale = D3DXToRadian(std::stof(patternAtr->value()));
		}
		else if (pStr.compare("rotation") == 0)
		{
			startRotation = D3DXToRadian(std::stof(patternAtr->value()));
		}
	}
	std::string patternIdStr = std::to_string(patternId);
	float activationTime = interval;
	spellcard->AddPattern(patternIdStr, EPatternFactory::Instance().Create(pattern, par1, par2, bulletNumber, activationTime));
	spellcard->GetPattern(patternIdStr)->SetScale(startScale);
	spellcard->GetPattern(patternIdStr)->SetRotation(startRotation);
	for (xml_node <> * dNode = patternNode->first_node(); dNode; dNode = dNode->next_sibling())
	{
		std::string str_tmp = dNode->name();
		if (str_tmp.compare("Bullet") == 0)
		{
			this->CreateBullets(spellcard->GetPattern(patternIdStr), dNode, patternIdStr, pattern);
		}
		else if (str_tmp.compare("Affine") == 0)
		{
			this->CreateAffineParameters(spellcard->GetPattern(patternIdStr), dNode, patternIdStr);
		}
	}
	patternId++;
	spellcard->Initialize(position);
};


void Stage::CreatePatternsForEnemy(Enemy * const enemyObj, xml_node <> * enemyNode)
{
	float par1, par2 = 0.0f, interval = 0.0f;
	short bulletNumber = 1, number = 1;
	Pattern pattern;
	static short patternId = 1;
	float startScale = 1.0f, startRotation = 0.0f;
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
		else if (pStr.compare("scale") == 0)
		{
			startScale = D3DXToRadian(std::stof(patternAtr->value()));
		}
		else if (pStr.compare("rotation") == 0)
		{
			startRotation = D3DXToRadian(std::stof(patternAtr->value()));
		}
	}
	for (int i = 0; i < number; i++)
	{
		std::string patternIdStr = std::to_string(patternId);
		float activationTime = i * interval;
		EPattern * newPattern;
		if (pattern != Pattern::BEZIER)
		{
			newPattern = EPatternFactory::Instance().Create(pattern, par1, par2, bulletNumber, activationTime);
		}
		else
		{
			TrajectoryBezier * tBezier = new TrajectoryBezier();
			this->CreatePointsForTMP(tBezier, enemyNode);
			tBezier->CalculateLength();
			tBezier->SetLoop(true);
			newPattern = new EnemyPatternBezier(tBezier, bulletNumber, activationTime);
		}
		enemyObj->AddPattern(patternIdStr, newPattern);
		enemyObj->GetPattern(patternIdStr).SetScale(startScale);
		enemyObj->GetPattern(patternIdStr).SetRotation(startRotation);
		for (xml_node <> * patternNode = enemyNode->first_node(); patternNode; patternNode = patternNode->next_sibling())
		{
			std::string str_tmp = patternNode->name();
			if (str_tmp.compare("Bullet") == 0)
			{
				this->CreateBullets(&enemyObj->GetPattern(patternIdStr), patternNode, patternIdStr, pattern);
			}
			else if (str_tmp.compare("Affine") == 0)
			{
				this->CreateAffineParameters(&enemyObj->GetPattern(patternIdStr), patternNode, patternIdStr);
			}
		}
		patternId++;
	}
};


void Stage::ChooseBonus(std::string const & bonus, BonusType & bonusType)
{
	if (bonus.compare("Power") == 0)
	{
		bonusType = BonusType::POWER;
	}
	else if (bonus.compare("Score") == 0)
	{
		bonusType = BonusType::SCORE;
	}
	else if (bonus.compare("Bomb") == 0)
	{
		bonusType = BonusType::BOMB;
	}
	else if (bonus.compare("Life") == 0)
	{
		bonusType = BonusType::LIFE;
	}
	else
	{
		bonusType = BonusType::NONE;
	}
};


void Stage::CreateBonus(Enemy * const enemyObj, xml_node <> * bonus, D3DXVECTOR2 const & position)
{
	BonusType bonusType;
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
			positionX = (_gameField->right - _gameField->left) / 3.0f;
		}
		else if (pos.compare("HALF") == 0)
		{
			positionX = (_gameField->right - _gameField->left) / 2.0f;
		}
		else if (pos.compare("TWO_THIRDS") == 0)
		{
			positionX = (_gameField->right - _gameField->left) * 2.0f / 3.0f;
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


void Stage::CreateEnemies(xml_node <> * time, std::string const & timeValue)
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
		if (this->_enemySprite.Add(imageFile))
		{
			_enemySprite[imageFile]->Initialize(_device, Sprite::GetFilePath(imageFile));
		}
		for (int i = 0; i < number; ++i)
		{
			Enemy * enemyObj = new Enemy(position, life, speed);
			enemyObj->InitializeSprite(_enemySprite[imageFile]);
			Road trajType;
			float tmp_length = length, tmp_distance = distance, tmp_start = start;
			for (xml_node <> * enemyNode = enemy->first_node(); enemyNode; enemyNode = enemyNode->next_sibling())
			{
				std::string eStr(enemyNode->name());
				if (eStr.compare("Pattern") == 0)
				{
					this->CreatePatternsForEnemy(enemyObj, enemyNode);
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
			enemyObj->InitializePatterns(position);
			switch(trajType)
			{
			case Road::ELIPSE: case Road::SPIRAL:
				tmp_start = D3DXToRadian(start);
				tmp_distance = D3DXToRadian(distance);
				tmp_length = D3DXToRadian(length);
				enemyObj->SetSpeed(D3DXToRadian(enemyObj->GetSpeed()));
				break;
			}
			enemyObj->InitializeHitbox(Hitbox::Shape::ELIPSE, Hitbox::Size::TWO_THIRDS_LENGTH);
			enemyObj->SetDistance(tmp_start - i * tmp_distance);
			enemyObj->GetTrajectory()->SetLength(tmp_start + tmp_length + i * tmp_distance);
			newEnemyQue.push_back(enemyObj);
		}
	}
	_enemyMap[std::stof(timeValue)].first = false;
	_enemyMap[std::stof(timeValue)].second = newEnemyQue;
};


void Stage::CreateBoss(xml_node <> * time, std::string const & timeValue)
{
	for( xml_node <> * bossNode = time->first_node(); bossNode; bossNode = bossNode->next_sibling())
	{
		std::string str(bossNode->name());
		if (str.compare("Boss") == 0)
		{
			std::string image, name;
			D3DXVECTOR2 position;
			USHORT life;
			Hitbox::Size hSize;
			for ( xml_attribute <>* bossAtr = bossNode->first_attribute(); bossAtr; bossAtr = bossAtr->next_attribute() )
			{
				str = std::string(bossAtr->name());
				if (str.compare("image") == 0)
				{
					image = std::string(bossAtr->value());
					if (this->_enemySprite.Add(image))
						_enemySprite[image]->Initialize(_device, Sprite::GetFilePath(image));
				}
				else if (str.compare("name") == 0)
				{
					name = std::string(bossAtr->value());
				}
				else if (str.compare("life") == 0)
				{
					life = static_cast<USHORT>(std::stof(bossAtr->value()));
				}
				else if (str.compare("position.x") == 0)
				{
					this->ChooseVerticalPosition(bossAtr->value(), position.x);
				}
				else if (str.compare("position.y") == 0)
				{
					this->ChooseHorizontalPosition(bossAtr->value(), position.y);
				}
				else if (str.compare("hitboxSize") == 0)
				{
					this->ChooseHitboxSize(bossAtr->value(), hSize);
				}
			}

			this->boss = new Boss(position, life, name);
			this->boss->InitializeSprite(_enemySprite[image]);
			this->boss->InitializeHitbox(Hitbox::Shape::ELIPSE, hSize);

			for (xml_node <> * spellcardNode = bossNode->first_node(); spellcardNode; spellcardNode = spellcardNode->next_sibling())
			{
				str = spellcardNode->name();
				if (str.compare("Spellcard") == 0)
				{
					Spellcard * spellcard;
					std::string name;
					float time;
					UINT bonus;
					for ( xml_attribute <>* spellcardAtr = spellcardNode->first_attribute(); spellcardAtr; spellcardAtr = spellcardAtr->next_attribute() )
					{
						str = spellcardAtr->name();
						if (str.compare("name") == 0)
						{
							name = std::string(spellcardAtr->value());
						}
						else if (str.compare("time") == 0)
						{
							time = std::stof(spellcardAtr->value());
						}
						else if (str.compare("bonus") == 0)
						{
							bonus = std::stoi(spellcardAtr->value());
						}
					}
					spellcard = new Spellcard(name, time, bonus);
					for (xml_node <> * patternNode = spellcardNode->first_node(); patternNode; patternNode = patternNode->next_sibling())
					{
						str = patternNode->name();
						if (str.compare("Pattern") == 0)
						{
							this->CreatePatternsForSpellcard(spellcard, patternNode, position);
						}
						spellcard->SetPosition(boss->GetCenter());
						this->boss->AddSpellcard(spellcard);
					}
				}
			}
		}
	}
	this->bossPair.first = std::stoi(timeValue);
	this->bossPair.second = this->boss;
};


void Stage::CreateStageElements()
{
	// Pocz¹tek Stejd¿a
	xml_node <> * stage = _stageDoc.first_node();
	// iteracja po wszystkich punktach w czasie
	for(xml_node <> * time = stage->first_node(); time; time = time->next_sibling())
	{
		// Pobranie wartoœci punktu w czasie
		std::string secTime, nodeType;
		for (xml_attribute <>* timeAtr = time->first_attribute(); timeAtr; timeAtr = timeAtr->next_attribute())
		{
			std::string str(timeAtr->name());
			if (str.compare("sec") == 0)
			{
				secTime = std::string(timeAtr->value());
			}
			else if (str.compare("type") == 0)
			{
				nodeType = std::string(timeAtr->value());
			}
		}
		if (nodeType.compare("normal") == 0)
		{
			this->CreateEnemies(time, secTime);
		}
		else if (nodeType.compare("boss") == 0)
		{
			this->CreateBoss(time, secTime);
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
