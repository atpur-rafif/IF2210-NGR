#ifndef VIEW_CLI_PLAYERVIEW_HPP
#define VIEW_CLI_PLAYERVIEW_HPP

#include "Exception/PlayerViewException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Player.hpp"
#include <exception>

class PlayerView {
public:
	virtual ~PlayerView();
	virtual PlayerView *clone() = 0;
	void start(Player &player);
	void runPlayerCommand(Player &player, string command);
	virtual void runSpecializedPlayerCommand(Player &player, string command) = 0;
	void printInventory(Player &player);
	void eat(Player &player);

	template <class T>
	string promptItemFromInventory(Player &player, T *&item) {
		while (true) {
			cout << "Location: ";
			string location;
			cin >> location;

			if (location == "CANCEL")
				throw UserCancelledPlayerViewException();

			try {
				auto rawItem = player.inventory.getItem(location);
				if (!rawItem.has_value()) {
					cout << "Item doesn't exist at this location" << endl;
					continue;
				}

				T *casted = dynamic_cast<T *>(rawItem->getRaw());
				if (casted == NULL) {
					cout << "Invalid item type" << endl;
					continue;
				};

				item = casted;
				return location;

			} catch (const exception &err) {
				cout << err.what() << endl;
			}
		}
	};
};

#endif
