#ifndef VIEW_CLI_HPP
#define VIEW_CLI_HPP

#include "Color/pcolor.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/PromptException.hpp"
#include "Model/Player.hpp"
#include "View/CLI/PlayerView.hpp"
#include <climits>
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

	// Transformer will throw PromptException when error, and return value_type when succeed
	template <class T>
	static T prompt(string message, function<T(string)> transformer) {
		while (true) {
			cout << message;
			string input;
			cin >> input;
			cin.ignore(INT_MAX, '\n');
			if (input == "CANCEL") throw UserCancelledCLIException();
			try {
				return transformer(input);
			} catch (const PromptException &err) {
				cout << RED << err.what() << NORMAL << endl;
			}
		}
	}

	template <class T>
	static string promptStorageLocation(string message, Storage<T> storage, function<void(string, optional<T> &)> validator) {
		function<string(string)> fn = [=](string location) mutable {
			if (!storage.isCoordinateValid(location))
				throw PromptException("Koordinat tidak valid");
			auto &item = storage.getItem(location);
			validator(location, item);
			return location;
		};
		return CLI::prompt(message, fn);
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
