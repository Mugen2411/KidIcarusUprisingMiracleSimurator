#include "Solver.h"
#include <fstream>

bool Solver::Load(const char* pFilePath)
{
	std::ifstream ifs(pFilePath);
	if (!ifs)
	{
		return false;
	}
	int curID = 0;
	while(1)
	{
		std::string name;
		ifs >> name;

		if (ifs.eof())
		{
			break;
		}

		m_names[curID] = name;

		int maxLv;
		ifs >> maxLv;
		m_maxLevels[curID] = maxLv;

		for (int lv = 0; lv < maxLv; ++lv)
		{
			int H, W;
			ifs >> H >> W;
			Grid2D tmp(H, W);

			for (int y = 0; y < H; ++y)
			{
				for (int x = 0; x < W; ++x)
				{
					char chip;
					ifs >> chip;
					if (chip == '#')
					{
						tmp.Set(x, y, true);
					}
				}
			}

			m_patterns[MiracleID(curID, lv)] = tmp;
		}
		++curID;
	}
	return true;
}

void Solver::AddCandidate(int ID, int level)
{
	--level;
	if (m_patterns.count(MiracleID(ID, level)) == 0)
	{
		std::cout << "パターンリストに含まれない奇跡・レベルです。" << std::endl;
		return;
	}
	for (int lv = 0; lv < MiracleID::MAX_LEVEL; ++lv)
	{
		if (m_candidate.count(MiracleID(ID, lv)))
		{
			m_candidate.erase(MiracleID(ID, lv));
			std::cout << "奇跡「" << m_names[ID] << "」のレベル" << lv + 1 << "は上書きされます。" << std::endl;
		}
	}
	m_candidate.insert(MiracleID(ID, level));
	std::cout << "奇跡「" << m_names[ID] << "」のレベル" << level + 1 << "を候補に追加しました。" << std::endl;
}

void Solver::DeleteCandidate(int ID)
{
	bool isFound = false;
	for (int lv = 0; lv < MiracleID::MAX_LEVEL; ++lv)
	{
		if (m_candidate.count(MiracleID(ID, lv)) == 0)
		{
			m_candidate.erase(MiracleID(ID, lv));
			isFound = true;
		}
	}
	if (isFound)
	{
		std::cout << "奇跡「" << m_names[ID] << "」を候補から削除しました。" << std::endl;
	}
}

void Solver::OutputNames()
{
	for (int id = 0; ; ++id)
	{
		if (m_names.count(id) == 0)
		{
			break;
		}
		std::cout << "ID: " << id << " " << m_names[id] << "(レベル" << m_maxLevels[id] << "まで)" << std::endl;
	}
}
