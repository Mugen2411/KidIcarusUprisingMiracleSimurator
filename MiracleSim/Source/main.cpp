#include <iostream>
#include "Solver.h"

int main()
{
	Solver solver;
	if (!solver.Load("patterns.txt"))
	{
		std::cout << "パターンファイルの読み込みに失敗しました";
		return 0;
	}

	while (1)
	{
		std::cout << "コマンドを入力してください > ";

		char command;
		std::cin >> command;

		switch (command)
		{
		case 'l':
		{
			solver.OutputNames();
		}break;
		case 'a':
		{
			int ID, level;
			std::cin >> ID >> level;
			solver.AddCandidate(ID, level);
		}break;
		case 'd':
		{
			int ID;
			std::cin >> ID;
			solver.DeleteCandidate(ID);
		}break;
		case 's':
		{
			solver.Solve();
		}break;
		case 'q':
		{
			std::cout << "アプリケーションを終了します。" << std::endl;
			exit(0);
		}break;
		default:
		{
			std::cout << "不明なコマンドです。hコマンドでヘルプを確認してください。" << std::endl;
		}break;
		}
	}
	return 0;
}