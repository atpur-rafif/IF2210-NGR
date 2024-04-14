#ifndef VIEW_CLI_PLAYERVIEW_HPP
#define VIEW_CLI_PLAYERVIEW_HPP

#include "Controller/GameContext.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Farmer.hpp"
#include <exception>

class PlayerView {
public:
	virtual ~PlayerView();
	virtual PlayerView *clone() = 0;
	void start(Player &player);
	void runPlayerCommand(Player &player, string command);
	virtual void runSpecializedPlayerCommand(Player &player, string command) = 0;
	static void printInventory(Player &player);
	void eat(Player &player);

	template <class T>
	string promptItemFromInventory(Player &player, shared_ptr<T> &item) {
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

				shared_ptr<T> casted = dynamic_pointer_cast<T>(rawItem.value());
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
