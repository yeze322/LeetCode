class Solution {
public:
	bool isNumber(string s) {
		removeBlank(s);
		if (s.empty()) return false;
		int sepaPoint = separateByE(s);
		if (sepaPoint == -1) return false;
		if (sepaPoint == -2){
			if (invalidSigns(s)) return false;
			else return true;
		}
		else{
			string substr1 = s.substr(0, sepaPoint);
			string substr2 = s.substr(sepaPoint+1,s.size()-sepaPoint);
			if (invalidSigns(substr1) || !pureInt(substr2)) return false;
			else return true;
		}
	}
private:
	void removeBlank(string &s){
		int end = s.size() - 1;
		int start = 0;
		while (start < end + 1 && s[start] == ' ') start++;
		while (end > start && s[end] == ' ') end--;
		s = s.substr(start, end - start + 1);
	}
	bool pureInt(const string &s){
		bool hasDigit = isNum(s[0]);
		if (!isNum(s[0]) && s[0] != '+' && s[0] != '-') return false;
		for (int i = 1; i < s.size(); i++){
			if (!isNum(s[i])) return false;
			hasDigit = true;
		}
		return hasDigit;
	}
	/* true = Invalid; false = valid */
	bool invalidSigns(const string & s){
		int signNum = 0;
		int LEN = s.size();
		int dotsNum = 0;
		int eNum = 0;
		bool hasDigit = false;
		for (int i = 0; i < LEN; i++){
			if (isNum(s[i])){
				hasDigit = true;
				continue;
			}
			if (s[i] == '+' || s[i] == '-'){
				if (signNum) return true;
				if (i > 0 && s[i - 1] != 'e') return true;
				signNum++;
			}
			else if (s[i] == '.'){
				//attention: '.1' is valid, "3." is valid, "-1." is valid
				if (dotsNum) return true;
				dotsNum++;
			}
			else if (s[i] == 'e'){
				if (i == 0 || !isNum(s[i - 1]) || eNum) return true;
				if (i == LEN - 1 || !isNum(s[i + 1])) return true;
				eNum++;
			}
			else{//include blank || other chars
				return true;
			}
		}
		return !hasDigit;
	}
	bool isNum(char x){
		return (x >= '0'&&x <= '9');
	}
	int separateByE(const string& s){
		int eNum = 0;
		int LEN = s.size();
		int retIndex = -2;
		for (int i = 0; i < LEN; i++){
			if (s[i] == 'e'){
				if (eNum) return -1;//more than one 'e'
				eNum++;
				retIndex = i;
			}
		}
		return retIndex;
	}
};