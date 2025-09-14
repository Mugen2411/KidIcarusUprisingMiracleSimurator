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
