#include <iostream>

int main()
{
	while (1)
	{
		std::cout << "コマンドを入力してください > ";

		char command;
		std::cin >> command;

		switch (command)
		{
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