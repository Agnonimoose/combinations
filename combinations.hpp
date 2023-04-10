#include <iostream>
#include <math.h> 
#include <string>
#include <vector>

class combination {
public:
	bool operator==(combination& other) {
		if (typeid(combos_) != typeid(other.combos_)) {
			return false;
		}
		else if (combos_.size() != other.combos_.size()) {
			return false;
		}
		else if (typeid(combos_[0]) != typeid(other.combos_[0])) {
			return false;
		}
		else {
			std::cout << "checking eles combos_.size() = "<< combos_.size() << std::endl;
			for (int c = 0; c < combos_.size(); c++) {
				std::cout << " c = " << c << std::endl;
				if (combos_[c].size() != other.combos_[c].size()) {
					return false;
				}
				for (int e = 0; e < combos_[c].size(); e++) {
					std::cout << "combos_[c][e] = " << combos_[c][e] << "  other.combos_[c][e] = " << other.combos_[c][e] << std::endl;
					if (combos_[c][e] != other.combos_[c][e]) {
						return false;
					}
				}
			}
		}
		return true;
	};
	bool operator!=(combination& other) {
		bool result;
		result = !(*this == other);
		return result;
	}
private:
	std::vector <std::vector<int>> combos_;

};

class str_combination : public combination {
public:
	str_combination() {
	}
	str_combination(std::vector <std::vector<std::string>> preset) {
		combos_ = preset;
	}
	void printCombos(void);
	std::vector<std::vector<std::string>> combos(void);
	void append_combo(std::vector<std::string> combo);
	void append_combo(std::vector <std::vector<std::string>> combo);

private:
	void setCombos(std::vector<std::vector<std::string>> combo_set);
	std::vector<std::vector<std::string>> combos_;

};

std::vector<std::vector<std::string>> str_combination::combos(void) {
	return combos_;
}

void str_combination::append_combo(std::vector <std::vector<std::string>> combo) {
	for (auto& element : combo) {
		combos_.push_back(element);
	}
}

class int_combination : public combination {
public:
	int_combination() {
	}
	int_combination(std::vector <std::vector<int>> preset) {
		combos_ = preset;
	}

	void printCombos(void);
	std::vector<std::vector<int>> combos(void);
	void append_combo(std::vector<int> combo);
	void append_combo(std::vector <std::vector<int>> combo);


private:
	void setCombos(std::vector<std::vector<int>> combo_set);
	std::vector<std::vector<int>> combos_;

};

void int_combination::setCombos(std::vector<std::vector<int>> combo_set) {
	combos_ = combo_set;
}

void str_combination::setCombos(std::vector<std::vector<std::string>> combo_set) {
	combos_ = combo_set;
}

void int_combination::append_combo(std::vector<int> combo) {
	combos_.push_back(combo);
}

void int_combination::append_combo(std::vector <std::vector<int>> combo) {
	for (auto& element : combo) {
		combos_.push_back(element);
	}
}

std::vector<std::vector<int>> int_combination::combos(void) {
	return combos_;
}

void int_combination::printCombos(void) {
	std::cout << "Printing combos " << std::endl;
	for (int i = 0; i < combos_.size(); i++) {
		std::cout << "Combo " << i << ": {";
		for (int j = 0; j < combos_[i].size(); j++) {
			std::cout << combos_[i][j] << " ,";
		}
		std::cout << "}" << std::endl;
	}
}

class int_combinations {
public:
	std::vector<std::vector<int>> makeCombos(int k, std::vector<int> opts);
	std::vector<std::vector<int>> combos(void);
	int_combination cartCombos(int k, std::vector<int> opts);
	void printCombos(void);
	bool compare(int_combinations other);

private:
	void _makeCombos(std::vector<int> a, int reqLen, int s, int currLen, std::vector<bool> check, int l);
	int_combination combos_;
};

std::vector<std::vector<int>> int_combinations::makeCombos(int k, std::vector<int> opts) {
	int optSize = opts.size();
	std::vector<bool> check(optSize);
	_makeCombos(opts, k, 0, 0, check, optSize);
	return combos();
}

void int_combinations::_makeCombos(std::vector<int> a, int reqLen, int s, int currLen, std::vector<bool> check, int l)
{
	if (currLen > reqLen) {
		return;
	}
	else if (currLen == reqLen) {
		std::vector<int>  tmp;
		for (int i = 0; i < l; i++) {
			if (check[i] == true) {
				tmp.push_back(a[i]);
			}
		}
		combos_.append_combo(tmp);

		return;
	}
	if (s == l) {
		return;
	}
	check[s] = true;
	_makeCombos(a, reqLen, s + 1, currLen + 1, check, l);
	check[s] = false;
	_makeCombos(a, reqLen, s + 1, currLen, check, l);
}


std::vector<std::vector<int>> int_combinations::combos(void) {
	return combos_.combos();
}

void int_combinations::printCombos(void) {
	combos_.printCombos();
}

bool int_combinations::compare(int_combinations other) {
	bool result;
	result = (combos_ == other.combos_);
	std::cout << "combinations are = " << result << std::endl;
	return result;
}
