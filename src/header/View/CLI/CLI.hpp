#ifndef VIEW_CLI_HPP
#define VIEW_CLI_HPP

#include "Controller/GameContext.hpp"
#include "Model/Player.hpp"
#include "View/CLI/PlayerView.hpp"
#include <iomanip>

class CLI {
private:
	GameContext context;
	map<PlayerType, shared_ptr<PlayerView>> view;

public:
	CLI();
	void start();
	void config();
	void state();

	void promptConfirmation();
	static int promptOption(int from, int to, string msg);

	template <class T>
	static string promptStorageLocation(string message, Storage<T> storage, function<string(optional<T> &)> validator) {
		while (true) {
			cout << message;
			string location;
			cin >> location;
			if (location == "CANCEL") throw UserCancelledPlayerViewException();

			try {
				auto &item = storage.getItem(location);
				string err = validator(item);
				if (err.size() == 0) {
					return location;
				}
				cout << err << endl;
			} catch (const std::exception &e) {
				std::cerr << e.what() << '\n';
			}
		}
	}

	template <class T>
	static void printStorage(string title, Storage<T> storage, function<string(T &)> toString) {
		auto width = storage.getWidth();
		auto height = storage.getHeight();

		int printWidth = 5 + 6 * width;

		int titleSize = title.size() + 4;
		int leftOffset = (printWidth - titleSize) / 2;
		int rightOffset = printWidth - leftOffset - titleSize;
		for (int i = 0; i < leftOffset; ++i) cout << "=";
		cout << "[ " << title << " ]";
		for (int i = 0; i < rightOffset; ++i) cout << "=";
		cout << endl
				 << endl;

		function<void()> printHorizontalDivider = [width]() {
			cout << "    +";
			for (int i = 0; i < width; ++i)
				cout << "-----+";
			cout << endl;
		};

		char c = 'A';
		cout << "    ";
		for (int x = 0; x < width; ++x)
			cout << "   " << c++ << "  ";
		cout << endl;

		for (int y = 0; y < height; ++y) {
			printHorizontalDivider();

			cout << " " << setfill('0') << setw(2) << y + 1 << " ";
			cout << "| ";
			for (int x = 0; x < width; ++x) {
				auto result = storage.getItem(x, y);
				if (result.has_value()) cout << toString(result.value());
				else cout << "   ";
				cout << " | ";
			}
			cout << endl;
		}
		printHorizontalDivider();
	};

	shared_ptr<PlayerView> getView(PlayerType type);
};

#endif
