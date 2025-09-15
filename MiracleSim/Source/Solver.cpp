#include "Solver.h"
#include <fstream>
#include <vector>
#include <iomanip>

bool Solver::Load(const char* pFilePath)
{
	std::ifstream ifs(pFilePath);
	if (!ifs)
	{
		return false;
	}
	int curID = 0;
	while (1)
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
		if (m_candidate.count(MiracleID(ID, lv)) != 0)
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
	std::cout << "--- 奇跡IDと最大レベル一覧 ---" << std::endl;
	for (int id = 0; ; ++id)
	{
		if (m_names.count(id) == 0)
		{
			break;
		}
		std::cout << "[ID: " << id << "] " << m_names[id] << "(レベル" << m_maxLevels[id] << "まで)" << std::endl;
	}
}

void Solver::OutputCandidates()
{
	std::cout << "--- 現在候補に入っている奇跡 ---" << std::endl;
	for (auto& cand : m_candidate)
	{
		std::cout << "[ID: " << cand.GetID() << "] " << m_names[cand.GetID()] << "(レベル" << cand.GetLevel() + 1 << ")" << std::endl;
	}
}

void Solver::Solve()
{
	struct HISTORY
	{
		MiracleID id;
		int X, Y;
		int R;
	};
	std::vector<Grid2D> curBoard;
	std::vector<std::vector<HISTORY>> curHistory(1);
	std::vector<Grid2D> nextBoard;
	std::vector<std::vector<HISTORY>> nextHistory;

	const int BOARD_SIZE = 6;
	curBoard.push_back(Grid2D(BOARD_SIZE, BOARD_SIZE));

	for (auto& cand : m_candidate)
	{
		for (int bIdx = 0; bIdx < curBoard.size(); ++bIdx)
		{
			for (int r = 0; r < 4; ++r)
			{
				Grid2D panel = m_patterns[cand].GetRotated(r);

				for (int y = 0; y < BOARD_SIZE - panel.GetHeight() + 1; ++y)
				{
					for (int x = 0; x < BOARD_SIZE - panel.GetWidth() + 1; ++x)
					{
						bool canPlace = true;
						Grid2D nx = curBoard[bIdx];
						for (int y2 = 0; y2 < panel.GetHeight(); ++y2)
						{
							for (int x2 = 0; x2 < panel.GetWidth(); ++x2)
							{
								if (!panel.Get(x2, y2))
								{
									continue;
								}
								if (curBoard[bIdx].Get(x2 + x, y2 + y))
								{
									canPlace = false;
								}
								else
								{
									nx.Set(x2 + x, y2 + y, true);
								}
							}
						}
						if (canPlace)
						{
							nextBoard.push_back(nx);
							nextHistory.push_back(curHistory[bIdx]);
							nextHistory.back().push_back(HISTORY{ cand, x, y, r });
						}
					}
				}
			}
		}

		if (nextBoard.empty())
		{
			std::cout << "入らない奇跡があります" << std::endl;
			return;
		}

		curBoard = nextBoard;
		curHistory = nextHistory;
		nextBoard.clear();
		nextHistory.clear();
	}

	auto& example = curHistory.back();
	std::vector<std::vector<int>> ans(BOARD_SIZE);
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		ans[y].resize(BOARD_SIZE, -1);
	}
	for (auto& h : example)
	{
		auto pat = m_patterns[h.id].GetRotated(h.R);
		for (int y = 0; y < pat.GetHeight(); ++y)
		{
			for (int x = 0; x < pat.GetWidth(); ++x)
			{
				if (pat.Get(x, y))
				{
					ans[h.Y + y][h.X + x] = h.id.GetID();
				}
			}
		}
	}
	OutputCandidates();
	std::cout << "入れるパターンの例：" << std::endl;
	auto _DrawChip = [](bool RLDU[4])
		{
			char code[16] = {
				' ', ' ', ' ', 'q',
				' ', 'l', 'k', 'w',
				' ', 'm', 'j', 'v',
				'x', 't', 'u', 'n'
			};
			int idx = 0;
			for (int i = 0; i < 4; ++i)
			{
				idx |= RLDU[i] << i;
			}
			std::cout << code[idx];
		};
	auto _DrawLine = [&](int from, int to)
		{
			std::cout << "\x1b(0";

			for (int x = 0; x < 13; ++x)
			{
				bool RLDU[4] = { true, true, true, true };
				if (x % 2 == 1)
				{
					RLDU[2] = false;
					RLDU[3] = false;

					if (from >= 0 && to < BOARD_SIZE)
					{
						if (ans[from][(x - 1) / 2] == ans[to][(x - 1) / 2])
						{
							RLDU[0] = false;
							RLDU[1] = false;
						}
					}
					_DrawChip(RLDU);
					_DrawChip(RLDU);
					_DrawChip(RLDU);
				}
				else
				{
					if (from < 0 || to >= BOARD_SIZE || x == 0 || x == 12)
					{
						if (from < 0)
						{
							RLDU[3] = false;

							if (x == 0)
							{
								RLDU[1] = false;
							}
							else if (x == 12)
							{
								RLDU[0] = false;
							}
							else if (ans[to][(x - 2) / 2] == ans[to][(x - 2) / 2 + 1])
							{
								RLDU[2] = false;
							}
						}
						if (to >= BOARD_SIZE)
						{
							RLDU[2] = false;

							if (x == 0)
							{
								RLDU[1] = false;
							}
							else if (x == 12)
							{
								RLDU[0] = false;
							}
							else if (ans[from][(x - 2) / 2] == ans[from][(x - 2) / 2 + 1])
							{
								RLDU[3] = false;
							}
						}
						if (x == 0)
						{
							RLDU[1] = false;

							if (from < 0)
							{
								RLDU[3] = false;
							}
							else if (to >= BOARD_SIZE)
							{
								RLDU[2] = false;
							}else if (ans[from][0] == ans[to][0])
							{
								RLDU[0] = false;
							}
						}
						if (x == 12)
						{
							RLDU[0] = false;

							if (from < 0)
							{
								RLDU[3] = false;
							}
							else if (to >= BOARD_SIZE)
							{
								RLDU[2] = false;
							}
							else if (ans[from][BOARD_SIZE - 1] == ans[to][BOARD_SIZE - 1])
							{
								RLDU[1] = false;
							}
						}
					}
					else
					{
						if (ans[from][(x - 2) / 2] == ans[to][(x - 2) / 2])
						{
							RLDU[1] = false;
						}
						if (ans[from][(x - 2) / 2 + 1] == ans[to][(x - 2) / 2 + 1])
						{
							RLDU[0] = false;
						}
						if (ans[from][(x - 2) / 2] == ans[from][(x - 2) / 2 + 1])
						{
							RLDU[3] = false;
						}
						if (ans[to][(x - 2) / 2] == ans[to][(x - 2) / 2 + 1])
						{
							RLDU[2] = false;
						}
					}
					_DrawChip(RLDU);
				}
			}

			std::cout << "\x1b(B";
			std::cout << std::endl;
		};

	_DrawLine(-1, 0);
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		std::cout << "\x1b(0" << 'x' << "\x1b(B";
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			if (x != 0 && ans[y][x] != ans[y][x - 1])
			{
				std::cout << "\x1b(0" << 'x' << "\x1b(B";
			}
			else
			{
				if (x != 0)
				{
					std::cout << " ";
				}
			}
			if (ans[y][x] != -1)
			{
				std::cout << std::setw(3) << ans[y][x];
			}
			else
			{
				std::cout << "\x1b(0" << 'a' << 'a' << 'a' << "\x1b(B";
			}
		}
		std::cout << "\x1b(0" << 'x' << "\x1b(B";
		std::cout << std::endl;
		_DrawLine(y, y + 1);
	}
	std::cout << "--- 追加可能な奇跡一覧---" << std::endl;
	bool isFound = false;
	for (auto& cand : m_patterns)
	{
		auto miracleId = cand.first;

		bool isExist = false;
		for (int lv = miracleId.GetLevel(); lv < m_maxLevels[miracleId.GetID()]; lv++)
		{
			if (m_candidate.count(MiracleID(miracleId.GetID(), lv)))
			{
				isExist = true;
			}
		}
		if (isExist)
		{
			continue;
		}
		bool isPossible = false;
		for (int bIdx = 0; bIdx < curBoard.size(); ++bIdx)
		{
			for (int r = 0; r < 4; ++r)
			{
				Grid2D panel = m_patterns[miracleId].GetRotated(r);

				for (int y = 0; y < BOARD_SIZE - panel.GetHeight() + 1; ++y)
				{
					for (int x = 0; x < BOARD_SIZE - panel.GetWidth() + 1; ++x)
					{
						bool canPlace = true;
						Grid2D nx = curBoard[bIdx];
						for (int y2 = 0; y2 < panel.GetHeight(); ++y2)
						{
							for (int x2 = 0; x2 < panel.GetWidth(); ++x2)
							{
								if (!panel.Get(x2, y2))
								{
									continue;
								}
								if (curBoard[bIdx].Get(x2 + x, y2 + y))
								{
									canPlace = false;
								}
							}
						}
						if (canPlace)
						{
							isPossible = true;
							break;
						}
					}
				}
			}
		}
		if (isPossible)
		{
			std::cout << "[ID:" << miracleId.GetID() << "] " << m_names[miracleId.GetID()] << "(レベル" << miracleId.GetLevel() + 1 << ")" << std::endl;
			isFound = true;
		}
	}

	if (!isFound)
	{
		std::cout << "追加できる奇跡はありません" << std::endl;
	}
}
