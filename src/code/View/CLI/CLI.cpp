#include "View/CLI/CLI.hpp"
#include "Exception/CLIException.hpp"
#include "View/CLI/Player/BreederView.hpp"
#include "View/CLI/Player/FarmerView.hpp"
#include "View/CLI/Player/MayorView.hpp"
#include "View/Config/Config.hpp"

int CLI::promptOption(int from, int to, string message) {
	function<int(string)> fn = [=](string input) {
		int result = atoi(input.c_str());
		if (from <= result && result <= to)
			return result;
		else throw PromptException("Pilihan tidak valid");
	};
	return CLI::prompt(message, fn);
};

CLI::CLI() {
	this->view[FarmerType] = shared_ptr<PlayerView>{new FarmerView()};
	this->view[BreederType] = shared_ptr<PlayerView>{new BreederView()};
	this->view[MayorType] = shared_ptr<PlayerView>{new MayorView()};
};

shared_ptr<PlayerView> CLI::getView(PlayerType type) {
	if (this->view.find(type) == this->view.end())
		throw GameException("Unimplemented view");
	return this->view[type];
};

void CLI::config() {
	function<void(string)> fn = [&](string input) {
		try {
			Config::readConfig(input, this->context);
			cout << "Konfigurasi berhasil dimuat" << endl;
		} catch (const std::exception &e) {
			throw PromptException(e.what());
		}
	};
	CLI::prompt("Konfigurasi direktori: ", fn);
}

void CLI::state() {
	cout << "Pilihan state:" << endl;
	cout << "1. Gunakan default" << endl;
	cout << "2. Baca dari file" << endl;

	int option = CLI::promptOption(1, 2, "Masukan piliihan: ");
	if (option == 1) {
		Config::readDefaultState(this->context);
		cout << "Menggunakan state default" << endl;
	} else if (option == 2) {
		function<void(string)> fn = [&](string input) {
			try {
				Config::readState(input, this->context);
				cout << "State berhasil dimuat" << endl;
			} catch (const std::exception &e) {
				throw PromptException(e.what());
			}
		};
		CLI::prompt("Lokasi state file: ", fn);
	}
}

void CLI::start() {
	cout << "Perintah CANCEL untuk menghentikan sebuah perintah" << endl;
	cout << "Perintah EXIT untuk keluar dari permainan" << endl;

	try {
		this->config();
		this->state();
	} catch (const CLIException &err) {
		cout << err.what() << endl;
		return;
	}

	try {
		while (true) {
			this->context.getPlayerController().checkWinner();
			shared_ptr<Player> current = this->context.getPlayerController().getCurrentPlayer();
			shared_ptr<PlayerView> view = this->getView(current->getType());
			view->start(*current);
			this->context.getPlayerController().nextPlayer();
		}
	} catch (const CLIException &) {
	} catch (const EndGameException &err) {
		cout << err.what() << endl;
	}

	cout << "Permainan berakhir!";
}
