#ifndef VIEW_CLI_PLAYERVIEW_HPP
#define VIEW_CLI_PLAYERVIEW_HPP

#include "Exception/PlayerViewException.hpp"
#include "Model/Player.hpp"

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
			string location;
			cin >> location;

			if (location == "CANCEL")
				throw UserCancelledPlayerViewException();

			auto rawItem = player.inventory.getItem(location);
			if (!rawItem.has_value()) {
				cout << "Item has no value" << endl;
				continue;
			}

			T *casted = dynamic_cast<T *>(rawItem->getRaw());
			if (casted == NULL) {
				cout << "Invalid item type" << endl;
				continue;
			};

			item = casted;
			return location;
		}
	};
};

#endif
