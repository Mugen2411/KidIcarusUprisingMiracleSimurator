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
		case 'c':
		{
			solver.OutputCandidates();
		}break;
		case 'h':
		{
			std::cout << "lコマンド(list)" << std::endl;
			std::cout << "用法：　l" << std::endl;
			std::cout << "奇跡IDと名前の関係と各奇跡の最大レベルを一覧で表示します" << std::endl;
			std::cout << "aコマンド(add)" << std::endl;
			std::cout << "用法：　a【奇跡ID】【レベル】" << std::endl;
			std::cout << "指定した奇跡の指定したレベルのものを探索候補に追加します" << std::endl;
			std::cout << "同じ奇跡が指定された場合はレベルが後から指定したものに上書きされます" << std::endl;
			std::cout << "奇跡IDと名前の関係と各奇跡の最大レベルはlコマンドで確認してください" << std::endl;
			std::cout << "dコマンド(delete)" << std::endl;
			std::cout << "用法：　d【奇跡ID】" << std::endl;
			std::cout << "指定した奇跡を探索候補から削除します" << std::endl;
			std::cout << "奇跡IDと名前の関係はlコマンドで確認してください" << std::endl;
			std::cout << "cコマンド(candidate)" << std::endl;
			std::cout << "用法：　c" << std::endl;
			std::cout << "候補に入っている奇跡のID名前とレベルの一覧を表示します" << std::endl;
			std::cout << "sコマンド(solve)" << std::endl;
			std::cout << "用法：　s" << std::endl;
			std::cout << "候補に入っている奇跡が全てパネルに配置可能か計算し、その一例を表示します" << std::endl;
			std::cout << "余裕がある場合は他に入れられる奇跡のリストも表示します" << std::endl;
			std::cout << "hコマンド(help)" << std::endl;
			std::cout << "用法：　h" << std::endl;
			std::cout << "実装されているコマンドの用法一覧を表示します" << std::endl;
			std::cout << "qコマンド(quit)" << std::endl;
			std::cout << "用法：　q" << std::endl;
			std::cout << "アプリを終了します" << std::endl;
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